#include <iostream>
#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"

FormulaParser::FormulaParser(std::string ln): tknzr {new Tokenizer{ln}} {}

TreeNode *FormulaParser::parseConjTerm() {
  TreeNode *leftChild = parseTerm();

  // RULE #1: '*' OPERATOR
  if (tknzr->getToken(next_token).content == "*") {
    incrementTokens();
    TreeNode *rightChild = parseConjTerm();
    OperatorNode *newNode = new OperatorNode("*");
    newNode->updateChildren(leftChild, rightChild);
    return newNode;
  }

  return leftChild;
}

TreeNode *FormulaParser::parseTerm() {
  // RULE #1: VARIABLE
  if (tknzr->getToken(next_token).type == "variable") { 
    incrementTokens();
    VariableNode *newNode = new VariableNode(tknzr->getToken(this_token).content);
    return newNode;
  } 
  
  // RULE #2: '-' SYMBOL
  else if(tknzr->getToken(next_token).content == "-") { 
    incrementTokens();
    OperatorNode *newNode = new OperatorNode("-");
    newNode->updateLeftChild(parseTerm());
    return newNode;
  } 

  // RULE #3: '(' SYMBOL
  else if (tknzr->getToken(next_token).content == "(") { 
    incrementTokens();
    TreeNode *newNode = parseFormula();
    // Check for closing brakcet
    if (tknzr->getToken(next_token).content == ")") {
      incrementTokens();
      return newNode;
    } else {
      throw "Error: missing a closing ')'";
    }
  }

  // Unexpected token
  throw "Error: invalid input";
}

TreeNode *FormulaParser::parseFormula() {
  TreeNode *leftChild = parseConjTerm();

  // RULE #1: '+' OPERATOR
  if (tknzr->getToken(next_token).content == "+") {
    incrementTokens();
    TreeNode *rightChild = parseFormula();
    TreeNode *newNode = new OperatorNode("+");
    newNode->updateChildren(leftChild, rightChild);
    return newNode;
  }

  return leftChild;
}

TreeNode * FormulaParser::getTreeRoot() {
  // Reset token indices
  this_token = -1;
  next_token = 0;

  // Ensure more then just END token exists
  if (tknzr->getSizeTokens() == 1) {
    throw "Error: invalid input";
  }

  // Parse the formula
  TreeNode *root = parseFormula();

  // Ensure END token is reached
  if (tknzr->getToken(next_token).type != "END") {
    throw "Error: invalid input";
  }

  // Return root node
  return root;
}

void FormulaParser::incrementTokens() {
  this_token++;
  next_token++;
}

FormulaParser::~FormulaParser() {
  delete tknzr;
}

