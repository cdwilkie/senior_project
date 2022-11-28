#pragma once

#include <iostream>
#include <fstream>
#include <string>


//Struct to hold token data
struct Token {
    int tokenType;
    std::string word;
};
/* Global Variables */
extern int charClass;                           //Numeric code for character class
extern char lexeme[60];                        //Holds lexeme to be tokenized
extern char nextChar;                           //Holds value of next character in source string
extern int lexLen;                              //Current length of the lexeme[]                              
extern int nextToken;                           //Numeric code for token type, defined in TOKEN CODES
extern FILE *in_fp, *fopen();                   //File pointer to source file

/* Character Classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token Codes */
#define UNKNWN 98                               //Symbol not defined in TOKEN CODES
#define INT_LIT 10                              //Int literal
#define LET_NUM 11                              // Letters & Nums
#define KEYWORD 15                              // Keyword from User
#define ASSIGN_OP 20                            // Assignment Operator =
#define LEFT_PAREN 21                           // Left Parenthesis (
#define RIGHT_PAREN 22                          // Right Parenthesis )
#define ASTERISK 23                             // *
#define DIV_OP 24                               // Division /
#define HASH_TAG 25                             // HashTag/Octothorpe #
#define ADD_OP 26                               // Addition +
#define PERCENT 27                              // Percent %
#define SEMI_COLON 30                           // SemiColon ;
#define LEFT_BRACE 31                           // Left Curly Brace {
#define RIGHT_BRACE 32                          // Right Curly Brace }
#define PERIOD 33                               // Period .
#define COMMA 34                                // Comma ,
#define HYPHEN 35                               // Hyphen -
#define EXCLAIM 36                              // Exclaimation Point
#define COLON 37                                // Colon :
#define ASPERAND 40                             // Asperand @
#define AMPERSAND 41                            // Ampersand &
#define CARAT 42                                // Carat ^



void addChar();

void getChar();

void getNonBlank();

int lex() ;