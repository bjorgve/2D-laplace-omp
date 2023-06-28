#!/bin/sh
#SBATCH --job-name=omp-test
#SBATCH --qos=devel
#SBATCH --time=00:30:00
#SBATCH --nodes=1 --cpus-per-task=128


ml purge
ml CMake/3.23.1-GCCcore-11.3.0

./build/laplace-omp.x 10
./build/laplace-omp.x 100
./build/laplace-omp.x 1000
./build/laplace-omp.x 10000