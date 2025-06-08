// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>
#include <algorithm>
class PMTree {
 public:
  struct PMNode {
    char symbol;
    std::vector<std::unique_ptr<PermNode>> branches;
    size_t subtree_count;
    explicit PMNode(char sym) : symbol(sym), subtree_count(0) {}
  };
  explicit PMTree(const std::vector<char>& elements);
  size_t count() const {return total_count;}
  const PMNode* getRoot() const {return root.get();}
 private:
  std::unique_ptr<PMNode> root;
  size_t total_count;
  void buildSubtree(PMNode* node, std::vector<char> remaining);
};
std::vector<std::vector<char>> generateAllPermutations(
    const PMTree& tree);
std::vector<char> getPerm1(
    const PMTree& tree, int index);
std::vector<char> getPerm2(
    const PMTree& tree, int index);
#endif  // INCLUDE_TREE_H_
