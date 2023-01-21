#include "treeNode.h"
#include <iostream>

TreeNode::TreeNode(std::string cntt): content {cntt} {}

// Returns content of node
std::string TreeNode::getContent() const {
  return content;
}

// Returns left child node
TreeNode *TreeNode::getLeftChild() const {
  return leftChild;
}

// Returns right child node
TreeNode *TreeNode::getRightChild() const {
  return rightChild;
}

// Updates the left child node
void TreeNode::updateLeftChild(TreeNode *lChild) {
  leftChild = lChild;
}

// Updates the right child node
void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild) {
  leftChild = lChild;
  rightChild = rChild;
}

// Function to get node ID
int TreeNode::getID() const {
  return id;
}

// Function to set node ID
void TreeNode::setID(int newID) {
  if (id != -1) {throw "Error:";}
  id = newID;
  return;
}

OperatorNode::OperatorNode(std::string cntt): TreeNode{cntt} {}

// Returns false for non-variable treeNode
bool OperatorNode::isVariable() const {
  return false;
}

ConstantNode::ConstantNode(std::string cntt): TreeNode{cntt} {}

// Returns false for non-variable treeNode
bool ConstantNode::isVariable() const {
  return false;
}

VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}

// Returns true for variable treeNode
bool VariableNode::isVariable() const {
  return true;
}

TreeNode::~TreeNode() {
  delete leftChild;
  delete rightChild;
}