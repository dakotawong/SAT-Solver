#include "tseitinTransformer.h"
#include "treeNode.h"
#include <vector>
#include <string>
#include <iostream>

TseitinTransformer::TseitinTransformer(TreeNode *root): formulaRoot{root} {}

int TseitinTransformer::transSubformula(TreeNode* subRoot) {
  // If root is nullptr return
  if (subRoot == nullptr) {
    return 0;
  }
  
  // Check if current node needs to be assigned an ID
  if (subRoot->getID() == -1) {

    // If node is variable follow protocol for variable ID assignment
    if (subRoot->isVariable()) {

      // Check map to see if variable arleady has an ID
      if (varIdTable.find(subRoot->getContent()) == varIdTable.end()) {
        // No existing ID, so assign new ID
        subRoot->setID(varIdCounter);
        varIdTable[subRoot->getContent()] = varIdCounter;
        varIdCounter++;
      } else {
        // Assign the existing ID from the map 
        subRoot->setID(varIdTable.at(subRoot->getContent()));
      }
    } else {
      // If not a variable assign a new ID
      subRoot->setID(varIdCounter);
      varIdCounter++;
    }
  }

  // Check if left child node exists
  if (subRoot->getLeftChild() != nullptr) {

    // Check if left child node needs to be assigned an ID
    if (subRoot->getLeftChild()->getID() == -1) {

      // If node is variable follow protocol for variable ID assignment
      if (subRoot->getLeftChild()->isVariable()) {

        // Check map to see if variable arleady has an ID
        if (varIdTable.find(subRoot->getLeftChild()->getContent()) == varIdTable.end()) {
          // No existing ID, so assign new ID
          subRoot->getLeftChild()->setID(varIdCounter);
          varIdTable[subRoot->getLeftChild()->getContent()] = varIdCounter;
          varIdCounter++;
        } else {
          // Assign the existing ID from the map
          subRoot->getLeftChild()->setID(varIdTable.at(subRoot->getLeftChild()->getContent()));       
        }
      } else {
        // If not a variable assign a new ID
        subRoot->getLeftChild()->setID(varIdCounter);
        varIdCounter++;
      }
    } 
  }

  // Check if right child node exists
  if (subRoot->getRightChild() != nullptr) {

    // Check if right child node needs to be assigned an ID
    if (subRoot->getRightChild()->getID() == -1) {

      // If node is variable follow protocol for variable ID assignment
      if (subRoot->getRightChild()->isVariable()) {

        // Check map to see if variable arleady has an ID
        if (varIdTable.find(subRoot->getRightChild()->getContent()) == varIdTable.end()) {
          // No existing ID, so assign new ID
          subRoot->getRightChild()->setID(varIdCounter);
          varIdTable[subRoot->getRightChild()->getContent()] = varIdCounter;
          varIdCounter++;
        } else {
          // Assign the existing ID from the map
          subRoot->getRightChild()->setID(varIdTable.at(subRoot->getRightChild()->getContent()));       
        }
      } else {
        // If not a variable assign a new ID
        subRoot->getRightChild()->setID(varIdCounter);
        varIdCounter++;
      }
    }
  }

  // If the node is an operator node apply the appropriate Tseitin Transform
  if (subRoot->getContent() == "-") {
    // For a NOT operator
    addNegEq(subRoot->getID(), subRoot->getLeftChild()->getID());
  } else if (subRoot->getContent() == "+") {
    // For a AND operator
    addOrEq(subRoot->getID(), subRoot->getLeftChild()->getID(), subRoot->getRightChild()->getID());
  } else if (subRoot->getContent() == "*") {
    // For a AND operator
    addAndEq(subRoot->getID(), subRoot->getLeftChild()->getID(), subRoot->getRightChild()->getID());
  }

  // Recurssive call on child nodes
  transSubformula(subRoot->getLeftChild());
  transSubformula(subRoot->getRightChild());

  return 0;
}

// Adds a CNF clause for NOT operator
void TseitinTransformer::addNegEq(int curID, int childID) {
  int c1_1, c1_2, c2_1, c2_2;
  c1_1 = -1 * curID;
  c1_2 = -1 * childID;
  c2_1 = curID;
  c2_2 = childID;
  std::vector<int> c1 = {c1_1, c1_2};
  std::vector<int> c2 = {c2_1, c2_2};
  cnf.push_back(c1);
  cnf.push_back(c2);
}

// Adds a CNF clause for OR operator
void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  int c1_1, c1_2, c1_3, c2_1, c2_2, c3_1, c3_2;
  c1_1 = -1 * curID;
  c1_2 = leftID;
  c1_3 = rightID;
  c2_1 = -1 * leftID;
  c2_2 = curID;
  c3_1 = -1 * rightID;
  c3_2 = curID;
  std::vector<int> c1 = {c1_1, c1_2, c1_3};
  std::vector<int> c2 = {c2_1, c2_2};
  std::vector<int> c3 = {c3_1, c3_2};
  cnf.push_back(c1);
  cnf.push_back(c2);
  cnf.push_back(c3);
}

// Adds a CNF clause for AND operator
void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  int c1_1, c1_2, c1_3, c2_1, c2_2, c3_1, c3_2;
  c1_1 = -1 * leftID;
  c1_2 = -1 * rightID;
  c1_3 = curID;
  c2_1 = -1 * curID;
  c2_2 = rightID;
  c3_1 = -1 * curID;
  c3_2 = leftID;
  std::vector<int> c1 = {c1_1, c1_2, c1_3};
  std::vector<int> c2 = {c2_1, c2_2};
  std::vector<int> c3 = {c3_1, c3_2};
  cnf.push_back(c1);
  cnf.push_back(c2);
  cnf.push_back(c3);
}

// Transforms root node formula to equiSAT CNF formula
std::vector<std::vector<int>> TseitinTransformer::transform() {
  transSubformula(formulaRoot);
  std::vector<int> base_clause = {1};
  cnf.push_back(base_clause);
  return cnf;
}

// Debug function for printing CNF clauses
std::string TseitinTransformer::cnfString() const {
  std::string result = "";
  for(size_t i=0; i < cnf.size(); i++) {
    result += "[";
    for(size_t j=0; j < cnf.at(i).size(); j++) {
      result += std::to_string(cnf.at(i).at(j));
      if (j != cnf.at(i).size()-1) {
        result += ",";
      }
    }
    result += "]";
  }
  return result;
}

// Returns the number or variables
unsigned int TseitinTransformer::getVarNum() const {
    return varIdCounter;
}
