// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>
#include <algorithm>
class PermutationTree {
 public:
  struct PermNode {
    char symbol;
    std::vector<std::unique_ptr<PermNode>> branches;
    size_t subtree_count;
    explicit PermNode(char sym) : symbol(sym), subtree_count(0) {}
  };
  explicit PermutationTree(const std::vector<char>& elements);
  size_t count() const {return total_count;}
  const PermNode* getRoot() const {return root.get();}
 private:
  std::unique_ptr<PermNode> root;
  size_t total_count;
  void buildSubtree(PermNode* node, std::vector<char> remaining);
};
std::vector<std::vector<char>> generateAllPermutations(
    const PermutationTree& tree);
std::vector<char> getPermutationByIndex1(
    const PermutationTree& tree, int index);
std::vector<char> getPermutationByIndex2(
    const PermutationTree& tree, int index);
#endif  // INCLUDE_TREE_H_
