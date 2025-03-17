import time
import numpy as np

from mpi4py import MPI

globCom = MPI.COMM_WORLD.Dup()
nbp     = globCom.size
rank    = globCom.rank

total_samples = 40000000
nb_samples = total_samples // nbp

beg = time.time()
x = 2.*np.random.random_sample((nb_samples,))-1.
y = 2.*np.random.random_sample((nb_samples,))-1.
filter = np.array(x*x + y*y < 1.)
sum = np.add.reduce(filter, 0)

sum = globCom.allreduce(sum, op=MPI.SUM)

if rank == 0:
    approx_pi = 4.*sum/total_samples
    end = time.time()

    print(f"Time to compute pi: {end - beg} seconds")
    print(f"Pi is approximately {approx_pi}")
