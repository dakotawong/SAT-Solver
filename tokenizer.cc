#include "tokenizer.h"

Tokenizer::Tokenizer(std::string ln) {

  // Assign a pointer to begining of string
  line = ln;

  // Pointer to string chars
  ptr = &line[0];

  // Reset vector
  tokens = {};

  // Get tokens
  while (advanceToken()) {
    Token t = createToken();
    tokens.push_back(t);
  }

  // Add end token
  Token end;
  end.type = "END";
  end.content = "\0";
  tokens.push_back(end);
}

// Scans the next token into the 'type' and 'content' members
bool Tokenizer::advanceToken() {

  // Clear members to store token data
  content = "";
  type = "";
  
  // Symbol
  if (*ptr == '*' || *ptr == '+' || *ptr == '-' || *ptr == '(' || *ptr == ')') {
      content = content + *ptr;
      type = "symbol";
      ptr++;
      while (*ptr == ' ') {
          ptr++;
      }
      return true;
  }
  
  // Variable
  if (('a' <= *ptr && *ptr <= 'z') || ('A' <= *ptr && *ptr <= 'Z')) {
      type = "variable";
      int cnt = 1;
      while (*ptr != '*' && *ptr != '+' && *ptr != '-' && *ptr != '(' && *ptr != ')' && *ptr != ' ' && *ptr != '\0') {
          if (cnt > 10) {
            throw "Error: variable names should have a length of less than 10 characters";
          }
          if (('a' <= *ptr && *ptr <= 'z') || ('A' <= *ptr && *ptr <= 'Z') || ('0' <= *ptr && *ptr <= '9')) {
            content = content + *ptr;
            ptr++;
            cnt++;
          } else {
            throw "Error: invalid character/symbol";
          }
      }
      while (*ptr == ' ') {
          ptr++;
      }
      return true;
  }
  
  // Stop if end of line is read
  if (*ptr == '\0') {
    return false;
  }

  // Tokenizer has read and invalid character
  throw "Error: an invalid character/symbol was found in the input";
  
}

// Returns the currently scanned token
Token Tokenizer::createToken() {
  Token resultToken;
  resultToken.content = content;
  resultToken.type = type;
  return resultToken;
}

// Returns token at specified index
Token Tokenizer::getToken(int index) const {
  return tokens[index];
}

// Returns the size of tokens
int Tokenizer::getSizeTokens() const {
  return tokens.size();
}
