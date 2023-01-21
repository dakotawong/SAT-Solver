#include <map>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <vector>
#include "solver.h"

Solver::Solver() {}

bool Solver::isUnitClause(std::vector<int> clause) {
    return clause.size() == 1;
}

bool Solver::isSAT(std::vector<std::vector<int>> cnf) {
    // Returns true if there are no more clauses
    return cnf.empty();
}

bool Solver::isUNSAT(std::vector<std::vector<int>> cnf, std::map<int, bool> A) {
    for (size_t clause=0; clause<cnf.size(); clause++) {
        // Returns true if an empty clause is found (indicating a contradiction)
        if (cnf[clause].empty()) {
            return true;
        }
    }
    return false;
}

int Solver::choose_literal(std::map<int, bool> A, unsigned int numVars) {
    // Iterate through literals in map and choose the first unassigned literal
    for (unsigned int var=1; var<=numVars; var++) {
        if (A.find(var) == A.end()) {
            return var;
        }
    }
    // Throw error if all literals are already assigned
    throw "Error: could not choose varibale as all have been assigned";
    return -1;
}

std::vector<std::vector<int>> Solver::BCP(std::vector<std::vector<int>> cnf, std::map<int, bool> &A) {

    // Declare variables for each iteration of the assignment map (literal and truth value)
    int var;
    bool val;

    // Iterator to iterate the assignment map
    std::map<int, bool>::iterator it = A.begin();

    // Iterates through assignments in assignment map
    while (it != A.end()) {

        // Iterates through the clauses in CNF 
        for (size_t clause = 0; clause < cnf.size(); clause++) {
            
            // Flag used to return to the start of the for loop (in case we remove a satisfied clause)
            bool removed = false;

            // Store the variable name (var) and truth value (val) of the current iteration of the assignment map
            var = it->first;
            val = it->second;

            // CASE #1: Removing satisfied clauses
            for (size_t lit=0; lit<cnf[clause].size(); lit++) {
                // If satisfied remove clause
                if ((cnf[clause][lit] == var && val) || (cnf[clause][lit] == -var && !val)) {
                    cnf.erase(cnf.begin()+clause);
                    removed = true; // Set flag to return to top of for-loop
                    clause--; // Important as returning to top for-loop increments clause (without this we skip clauses in CNF)
                    break;
                }
            }

            // Check flag to see if clause was removed (if removed return to top of for-loop)
            if (removed) {
                continue;
            }

            // CASE #2: Removing unsatisfied literals from the current clause
            for (size_t lit=0; lit<cnf[clause].size(); lit++) {
                // If unsatisfied remove literal from clause
                if ((cnf[clause][lit] == var && !val) || (cnf[clause][lit] == -var && val)) {
                    cnf[clause].erase(cnf[clause].begin()+lit);
                    lit--; // So we don't skip literals when removing a literal
                }
                
            }

            // CASE #3: Removing unit clauses and adding the approriate assignment to the assignemnt map
            if (isUnitClause(cnf[clause]) && A.find(std::abs(cnf[clause][0])) == A.end()) {
                // Reading the clause
                int unit = cnf[clause][0];

                // Assign approriate truth value to literal
                if (unit < 0) {
                    // Assign false truth value
                    A[std::abs(unit)] = false;
                } else {
                    // Assign true truth value
                    A[std::abs(unit)] = true;
                }

                // Remove clause
                cnf.erase(cnf.begin()+clause);
                clause--;
            }

        }
        // Iterate to next assignment
        it++;
    }
    // Return the modified CNF
    return cnf;

}

bool Solver::DPLL(std::vector<std::vector<int>> cnf, std::map<int, bool> A, unsigned int numVars) {
    // Begin with BCP
    cnf = BCP(cnf, A);

    // Check whether CNF is SAT or UNSAT (if UNKOWN continue) 
    if (isSAT(cnf)) {return true;}
    else if (isUNSAT(cnf, A)) {return false;}

    // Choose a decision literal to branch on 
    int var = choose_literal(A, numVars);

    // Make recurssive calls to DPLL with both true and false assignments for the decision literal
    A[var] = true;
    if (DPLL(cnf, A, numVars)) {
        return true;
    } else {
        A[var] = false;
        return DPLL(cnf, A, numVars);
    }
}

bool Solver::solve(std::vector<std::vector<int>> cnf, unsigned int numVars) {
    // Declare a map for literals
    std::map<int, bool> A;
    // Return results of the DPLL algorithm
    return DPLL(cnf, A, numVars);
}

Solver::~Solver() {}