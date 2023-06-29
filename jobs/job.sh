#!/bin/sh
#SBATCH --job-name=omp-test
#SBATCH --time=00:30:00
#SBATCH --mem-per-cpu=1G
#SBATCH --nodes=1 --cpus-per-task=16


ml purge
ml CMake/3.23.1-GCCcore-11.3.0

./build/laplace-omp.x 128
./build/laplace-omp.x 1000
./build/laplace-omp.x 2000
./build/laplace-omp.x 4000
