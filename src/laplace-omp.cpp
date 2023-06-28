#include <cmath>
#include "laplace-omp.h"

namespace omp {
// Jacobi iteration
void jacobi(float* old_solution, float* new_solution, int num_elements) {
    // For each element take the average of the surrounding elements
    #pragma omp parallel for
    for (auto i = 1; i < num_elements - 1; i++) {
        for (auto j = 1; j < num_elements - 1; j++) {
            new_solution[i + num_elements * j] = 0.25 * (old_solution[i + num_elements * (j + 1)] +
                                                         old_solution[i + num_elements * (j - 1)] +
                                                         old_solution[(i - 1) + num_elements * j] +
                                                         old_solution[(i + 1) + num_elements * j]);
        }
    }
}

void check_error(float* old_solution, float* new_solution, int num_elements, float& error) {
    #pragma omp parallel for reduction(max : error)
    for (auto i = 1; i < num_elements - 1; i++) {
        for (auto j = 1; j < num_elements - 1; j++) {
            error = std::max(error, std::abs(new_solution[i + num_elements * j] - old_solution[i + num_elements * j]));
        }
    }
}

} // namespace omp