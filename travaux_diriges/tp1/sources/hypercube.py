from mpi4py import MPI
import numpy as np

globCom = MPI.COMM_WORLD
nbp     = globCom.size
rank    = globCom.rank

d = int(np.log2(nbp))

if np.log2(nbp) != d:
    print("The number of processors must be a power of 2.")
    exit()

x = np.random.random(1)[0]
if rank == 0:
    # print(f"Process {rank} is sending {x}")
    for i in range(0, d):
        globCom.send(x, dest=int(2**i))

b = format(rank, f'0{d}b')

msb = len(b) - b.find('1') - 1
sender = rank - (2 ** msb)

# print(rank, msb, b)

if sender >= 0:
    # print(f"Process {rank} is waiting from {sender}")
    val = globCom.recv(source=sender)

if rank != 0:
    print(f"Process {rank} received {val}")

    for i in range(1, d):
        dest = 2 ** i + rank
        if dest < nbp:
            # print("Process", rank, "sending", val, "to", dest)
            globCom.send(val, dest=dest)
