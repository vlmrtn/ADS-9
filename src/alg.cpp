// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <memory>
#include <algorithm>
#include <vector>
#include  "tree.h"
PermutationTree::PermutationTree(
    const std::vector<char>& elements) : total_count(0) {
  if (elements.empty()) return;
  total_count = 1;
  for (size_t i = 2; i <= elements.size(); i++) {
    total_count *= i;
  }
  root = std::make_unique<PermNode>('\0');
  buildSubtree(root.get(), elements);
}

void PermutationTree::buildSubtree(
     PermNode* node, std::vector<char> remaining) {
  std::sort(remaining.begin(), remaining.end());
  for (size_t i = 0; i < remaining.size(); i++) {
    node->branches.emplace_back(std::make_unique<PermNode>(remaining[i]));
    PermNode* child = node->branches.back().get();
    std::vector<char> new_remaining;
    for (size_t j = 0; j < remaining.size(); j++) {
      if (j != i) {
        new_remaining.push_back(remaining[j]);
      }
    }
    buildSubtree(child, new_remaining);
    if (child->branches.empty()) {
      child->subtree_count = 1;
    } else {
      child->subtree_count = 0;
      for (const auto& branch : child->branches) {
        child->subtree_count += branch->subtree_count;
      }
    }
  }
}

void traverseForPermutations(const PermutationTree::PermNode* node,
     std::vector<char>& current, std::vector<std::vector<char>>& result) {
  if (node->symbol != '\0') {
    current.push_back(node->symbol);
  }
  if (node->branches.empty()) {
        result.push_back(current);
  } else {
    for (const auto& child : node->branches) {
      traverseForPermutations(child.get(), current, result);
    }
  }
  if (node->symbol != '\0') {
    current.pop_back();
  }
}

std::vector<std::vector<char>> generateAllPermutations(
    const PermutationTree& tree) {
  std::vector<std::vector<char>> result;
  if (!tree.getRoot()) return result;
  std::vector<char> path;
  traverseForPermutations(tree.getRoot(), path, result);
  return result;
}

std::vector<char> getPermutationByIndex1(
    const PermutationTree& tree, int index) {
  if (index < 1 || static_cast<size_t>(index) > tree.count()) {
    return {};
  }
  auto all = generateAllPermutations(tree);
  return all[index-1];
}

std::vector<char> getPermutationByIndex2(
    const PermutationTree& tree, int index) {
  if (index < 1 || !tree.getRoot() ||
      static_cast<size_t>(index) > tree.count()) {
    return {};
  }
  std::vector<char> permutation;
  const PermutationTree::PermNode* current = tree.getRoot();
  int remaining = index - 1;
  while (!current->branches.empty()) {
    size_t selected = 0;
    while (selected < current->branches.size() && 
          remaining >= static_cast<int>(
              current->branches[selected]->subtree_count)) {
      remaining -= current->branches[selected]->subtree_count;
      selected++;
    }
    if (selected >= current->branches.size()) {
      return {};
    }
    current = current->branches[selected].get();
    permutation.push_back(current->symbol);
  }
  return permutation;
}



