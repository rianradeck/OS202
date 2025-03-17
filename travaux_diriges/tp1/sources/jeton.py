import time
import numpy as np
from mpi4py import MPI

globCom = MPI.COMM_WORLD.Dup()
nbp     = globCom.size
rank    = globCom.rank

jeton = 0

sender = (rank - 1 + nbp) % nbp
receiver = (rank + 1) % nbp

if rank == 0:
    jeton = 1
    globCom.send(jeton, dest=receiver, tag=0)
    
jeton = globCom.recv(source=sender, tag=0)
print(f"Process {rank} received token {jeton}")
if rank != 0:
    jeton += 1
    globCom.send(jeton, dest=receiver, tag=0)
