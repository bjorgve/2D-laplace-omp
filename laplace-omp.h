#ifndef LAPLACE_OMP_H
#define LAPLACE_OMP_H

namespace omp {
    void jacobi(float* old_solution, float* new_solution, int num_elements);
    void check_error(float* old_solution, float* new_solution, int num_elements, float& error);
} // namespace omp

#endif // LAPLACE_OMP_H
