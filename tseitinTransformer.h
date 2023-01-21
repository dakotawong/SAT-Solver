#ifndef TSEITIN_H
#define TSEITIN_H

#include <vector>
#include <map>
#include <string>
#include "treeNode.h"

// Class for transforming a formula to an equisatisfiable CNF in polynomial time
class TseitinTransformer
{
  private:
    TreeNode *formulaRoot; // Root node of the target formula tree 
    std::vector<std::vector<int>> cnf; // Represent CNF in vector of vector
    std::map<std::string, int> varIdTable; // Stores the ID associated with the variable
    int varIdCounter = 1; // Tracking how many ID have been used; -0 = 0; so start id with 1
    int transSubformula(TreeNode *subRoot); // Recursive function called on each subformula
    void addNegEq(int curID, int childID); // Add clauses for a negation subformula
    void addOrEq(int curID, int leftID, int rightID); // Add clauses for an or subformula
    void addAndEq(int curID, int leftID, int rightID); // Add clauses for an and subformula

  public:
    TseitinTransformer(TreeNode *root); // Constructor
    std::vector<std::vector<int>> transform(); // Transforms the target formula to equisatisfiable CNF
    std::string cnfString() const; // A debug helper function to check whehter the correctness of transformation
    unsigned int getVarNum() const; // Returns the number of variables
};

#endif
