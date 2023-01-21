#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include "tokenizer.h"

class TreeNode;
class Tokenizer;

// Parser for the Boolean Formula
class FormulaParser {
  private:
    int this_token; // Index to current token
    int next_token; // Index to next token
    Tokenizer *tknzr; // Pointer to Tokenizer
    TreeNode *parseFormula(); // Parse non-terminal Formula in the grammar
    TreeNode *parseConjTerm(); // Parse non-terminal ConjTerm in the grammar
    TreeNode *parseTerm(); // Parse non-terminal Term in the grammar
    void incrementTokens(); // Increments 'this_token' and 'next_token'
  public:
    FormulaParser(std::string ln); // Constructor
    TreeNode *getTreeRoot(); // Parse the Boolean formula and return the root node of the formula syntax tree
    ~FormulaParser(); // Deconstructor
};

#endif
