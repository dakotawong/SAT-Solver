#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

// Token definition
struct Token
{
    std::string content;
    std::string type;
};

// Tokenzier class that will break a string into tokens
class Tokenizer
{
    std::string line; // Stores line to tokenize
    std::string content; // Stores content of scanned token
    std::string type; // Stores type of scanned token
    char *ptr; // Pointer for strings
    bool advanceToken(); // Advance to the next token; return false if no more token exist
    bool hasToken() const; // Check whether there is a current token
    Token createToken(); // Creates the token being processed
    std::vector<Token> tokens; // Vector of tokens
  public:
    Tokenizer(std::string ln); // Constructor
    Token getToken(int index) const; // Returns token at tokens[index]
    int getSizeTokens() const; // Returns the size of tokens
};

#endif
