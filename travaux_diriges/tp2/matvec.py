# Produit matrice-vecteur v = A.u
import numpy as np
from mpi4py import MPI

globCom = MPI.COMM_WORLD
nbp     = globCom.size
rank    = globCom.rank

# Dimension du problème (peut-être changé)
dim = 120
# Initialisation de la matrice
A = np.array([[(i+j) % dim+1. for i in range(dim)] for j in range(dim)])
# print(f"A = {A}")

# Initialisation du vecteur u
u = np.array([i+1. for i in range(dim)])
# print(f"u = {u}")

# # Produit matrice-vecteur
# v = A.dot(u)
# print(f"v = {v}")

_dim = dim // nbp + (rank < dim % nbp)
_dims = None
if rank == 0:
    _dims = np.array([dim // nbp + (rank < dim % nbp) for rank in range(nbp)]).astype(np.int32) * int(dim)
    print(_dims)
    # _dims = _dims * dim

_A = np.empty((_dim, dim), dtype=np.double)

globCom.Scatterv((A.T, _dims), _A, root=0)

_v = _A.dot(u)

v = None
a = None
if rank == 0:
    v = np.empty(dim, dtype=np.double)
    a = _dims // dim

globCom.Gatherv(_v, [v, a], root=0)

if rank == 0:
    assert np.allclose(v, A.dot(u))