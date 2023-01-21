#include <vector>
#include <map>

// Solver for solving satisfiability of CNFs
class Solver
{   
    private:
        bool isUnitClause(std::vector<int> clause); // Returns whether clause is unit clause or not
        bool isSAT(std::vector<std::vector<int>> cnf); // Returns whether CNF is SAT or not
        bool isUNSAT(std::vector<std::vector<int>> cnf, std::map<int, bool> A); // Returns whether CNF is UNSAT or not 
        int choose_literal(std::map<int, bool> A, unsigned int numVars); // Chooses an unassigned decision literal
        std::vector<std::vector<int>> BCP(std::vector<std::vector<int>> cnf, std::map<int, bool> &A); // Does Boolean Constraint Propagation on CNF
        bool DPLL(std::vector<std::vector<int>> cnf, std::map<int, bool> A, unsigned int numVars); // DPLL SAT solving algorithm
    public:
        Solver(); // Constructor
        bool solve(std::vector<std::vector<int>> cnf, unsigned int numVars); // Public function for solving satisfiability of CNF
        ~Solver(); // Deconstructor
};      