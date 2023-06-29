#include <iostream>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <omp.h>

#include "laplace-omp.h"

int main(int argc, char** argv) {
  auto start = std::chrono::high_resolution_clock::now();

  // Check if the user provided a command line argument
  if (argc < 2) {
    std::cout << "Please provide the number of elements as a command line argument.\n";
    return 1; // Return an error code
  }

  // Constants and initializations
  const auto num_elements = std::stoi(argv[1]);
  const auto max_iter = 10000;
  const auto max_error = 0.01f;
  srand(12345);

  // Memory allocation
  auto* old_solution = new float[num_elements * num_elements];
  auto* new_solution = new float[num_elements * num_elements];

  // Fill old_solution with random values between [0, 1]
  for (auto i = 0u; i < num_elements; i++) {
    for (auto j = 0u; j < num_elements; j++) {
      old_solution[i + num_elements * j] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }
  }

  // Copy the boundary conditions from the old_solution to the new_solution
  for (auto i = 0u; i < num_elements; i++) {
    new_solution[i] = old_solution[i];
    new_solution[i + num_elements * (num_elements - 1)] = old_solution[i + num_elements * (num_elements - 1)];
    new_solution[i * num_elements] = old_solution[i * num_elements];
    new_solution[(i + 1) * num_elements - 1] = old_solution[(i + 1) * num_elements - 1];
  }

  auto error = 10.0f; // Random initial value
  auto iterations = 0;

  // Perform Jacobi iterations until we either have low enough error or too
  // many iterations
  while (error > max_error && iterations < max_iter) {
    error = 0.0f;
    omp::jacobi(old_solution, new_solution, num_elements);
    omp::check_error(old_solution, new_solution, num_elements, error);
    // transfer_solution(old_solution, new_solution, num_elements);
    // Swap the pointers between old_solution and new_solution
    std::swap(old_solution, new_solution);
    iterations += 1;
  }

  auto finish = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::seconds>(finish - start);

  int max_threads = omp_get_max_threads();
  std::cout << "Solution value at [20][20]: " << old_solution[20 + num_elements * 20] << std::endl;
  std::cout << "New solution value at [20][20]: " << new_solution[20 + num_elements * 20] << std::endl;
  std::cout << "Number of iterations: " << iterations << std::endl;
  std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

  // Free memory
  delete[] old_solution;
  delete[] new_solution;


  return 0;
}
