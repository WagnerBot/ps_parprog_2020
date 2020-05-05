#!/bin/bash

# Executes job in the queue "std.q" unless you have special requirements.
#$ -q std.q

# Changes to the current working directory before performing any further action
#$ -cwd

# Name of your job. Unless you use the -o and -e options, output will
# go to a unique file name.ojob_id for each job.
#$ -N had1

# Redirect output stream to this file.
#$ -o output_task5_1.dat

# Join the error stream to the output stream.
#$ -j yes

# Parallel environment for using OpenMP, allocates 8 cores on a single node
#$ -pe openmp 4

# Increase the virtual memory per slot to 4GB
#$ -l h_vmem=4G

# Use gcc 8.2.0 as the default gcc
#module load gcc/8.2.0

# Set up any environment variables
#export ENVIRONMENT_VARIABLE=foobar
echo "bind=true, places=threads/cores/sockets" >> output_task5_1.dat
OMP_PROC_BIND=true OMP_PLACES=threads ./ex1 4 100000000
OMP_PROC_BIND=true OMP_PLACES=cores ./ex1 4 100000000
OMP_PROC_BIND=true OMP_PLACES=sockets ./ex1 4 100000000

echo "bind=false, places=threads/cores/sockets" >> output_task5_1.dat
OMP_PROC_BIND=false OMP_PLACES=threads ./ex1 4 100000000
OMP_PROC_BIND=false OMP_PLACES=cores ./ex1 4 100000000
OMP_PROC_BIND=false OMP_PLACES=sockets ./ex1 4 100000000

echo "bind=close, places=threads/cores/sockets" >> output_task5_1.dat
OMP_PROC_BIND=close OMP_PLACES=threads ./ex1 4 100000000
OMP_PROC_BIND=close OMP_PLACES=cores ./ex1 4 100000000
OMP_PROC_BIND=close OMP_PLACES=sockets ./ex1 4 100000000

echo "bind=master, places=threads/cores/sockets" >> output_task5_1.dat
OMP_PROC_BIND=master OMP_PLACES=threads ./ex1 4 100000000
OMP_PROC_BIND=master OMP_PLACES=cores ./ex1 4 100000000
OMP_PROC_BIND=master OMP_PLACES=sockets ./ex1 4 100000000

echo "bind=spread, places=threads/cores/sockets" >> output_task5_1.dat
OMP_PROC_BIND=spread OMP_PLACES=threads ./ex1 4 100000000
OMP_PROC_BIND=spread OMP_PLACES=cores ./ex1 4 100000000
OMP_PROC_BIND=spread OMP_PLACES=sockets ./ex1 4 100000000
