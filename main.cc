#include <iostream>
#include <string>
#include <vector>
#include "tseitinTransformer.h"
#include "treeNode.h"
#include "solver.h"
#include "parser.h"

void parseLine(const std::string &line, std::string &formulaStr) {
    // Declare start index
    size_t index = 0;
    
    // Check for empty line
    if (line.length() == 0) {
        return;
    }

    // Remove whitespace before formula string
    while (line.at(index) == ' ') {
        index++;
        if (index >= line.length()) {
            return;
        }
    }   

    // Process formula string
    for (size_t i = index; i < line.length(); i++) {
        formulaStr += line.at(i);
    }
}

// The program continuously gets new inputs from standard input and outputs to the standard output
// Terminates once it sees EOF (CTRL+D)
int main() {
    while (true) // continuously asking for new inputs from standard input
    {
        std::string line; // store each input line
        std::string formulaStr; // store the formula string
    
        // get line from user
        std::getline(std::cin, line);
        if (!std::cin) { // Check for EOF
            return 0;
        }

        try {
            // Parse line
            parseLine(line, formulaStr);

            // Formula Parser
            FormulaParser *formula_parser = new FormulaParser(formulaStr);

            // Get root node of formula tree
            TreeNode *root = formula_parser->getTreeRoot();

            // Use tseitins transformation
            TseitinTransformer tseitins = TseitinTransformer(root);
            std::vector<std::vector<int>> cnf = tseitins.transform();
            
            // Check SAT or UNSAT of equiSAT formula
            Solver *SAT_Solver = new Solver(); 
            bool res = SAT_Solver->solve(cnf, tseitins.getVarNum());
            
            // Output results
            if (res == true) {
                std::cout << "sat" << std::endl;                    
            } else {
                std::cout << "unsat" << std::endl;
            }
            
        } catch (const char *message) {
            // Print any error messages
            std::cout << message << std::endl;
        }
    }
}
