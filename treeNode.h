#ifndef TNODE_H
#define TNODE_H

#include <string>
#include <map>

// abstract superclass of the syntax tree node
class TreeNode {
    std::string content;
    int id = -1;
    TreeNode *leftChild = nullptr;
    TreeNode *rightChild = nullptr;
  public:
    TreeNode(std::string cntt);
    std::string getContent() const;
    int getID() const;
    void setID(int newID);
    virtual bool isVariable() const = 0;
    TreeNode *getLeftChild() const;
    TreeNode *getRightChild() const;
    void updateLeftChild(TreeNode *lChild); // for the operator "-", the operand is stored in leftChild
    void updateChildren(TreeNode *lChild, TreeNode *rChild);
    virtual ~TreeNode();

};

// concrete tree node of opertaor type
class OperatorNode : public TreeNode {
  public:
    OperatorNode(std::string cntt);
    bool isVariable() const override;
};

// concrete tree node of constant type
class ConstantNode : public TreeNode {
  public:
    ConstantNode(std::string cntt);
    bool isVariable() const override;
};

// concrete tree node of varibale type
class VariableNode : public TreeNode {
  public:
    VariableNode(std::string cntt);
    bool isVariable() const override;
};

#endif
