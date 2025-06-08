// Copyright 2022 NNTU-CS
#include <chrono>
#include <random>
#include <fstream>
#include <iostream>
#include <vector>
#include "tree.h"
void runPerformanceTest() {
  std::ofstream results("performance_results.csv");
  results << "n,generateAll,getByIndex1,getByIndex2\n";
  std::random_device rd;
  std::mt19937 gen(rd());
  for (int n = 1; n <= 10; n++) {
    std::vector<char> elements(n);
    for (int i = 0; i < n; i++) {
      elements[i] = 'A' + i;
    }
    PermutationTree tree(elements);
    size_t total = tree.count();
    if (total == 0) continue;
    std::uniform_int_distribution<int> dist(1, total);
    int test_index = dist(gen);
    // Test generateAllPermutations
    auto start = std::chrono::high_resolution_clock::now();
    auto all = generateAllPermutations(tree);
    auto end = std::chrono::high_resolution_clock::now();
    double time_all = std::chrono::duration<double>(end - start).count();
    // Test getPermutationByIndex1
    start = std::chrono::high_resolution_clock::now();
    auto perm1 = getPermutationByIndex1(tree, test_index);
    end = std::chrono::high_resolution_clock::now();
    double time_idx1 = std::chrono::duration<double>(end - start).count();
    // Test getPermutationByIndex2
    start = std::chrono::high_resolution_clock::now();
    auto perm2 = getPermutationByIndex2(tree, test_index);
    end = std::chrono::high_resolution_clock::now();
    double time_idx2 = std::chrono::duration<double>(end - start).count();
    results << n << "," <<
        time_all << "," << time_idx1 << "," << time_idx2 << "\n";
    std::cout
        << "Tested n=" << n << " | Times: " << time_all << "s,"
            << time_idx1 << "s, " << time_idx2 << "s\n";
  }
  results.close();
}
int main() {
  std::vector<char> test = {'1', '2', '3'};
  PermutationTree tree(test);
  auto perms = generateAllPermutations(tree);
  for (const auto& p : perms) {
    for (char c : p) std::cout << c;
    std::cout << " ";
  }
  auto p2 = getPermutationByIndex2(tree, 2);
  for (char c : p2) std::cout << c;
  std::cout << "\n"

  runPerformanceTest();
  return 0;
}
