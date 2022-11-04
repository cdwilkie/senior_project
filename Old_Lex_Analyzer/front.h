/* C. DUSTIN WILKIE
 * COMP 360 001
 * PROJECT 01
 * LEXICAL ANALYZER
*/

/* front.h - Header file for front.cpp.
 * Contains global variables used for
 * parsing.  Also defines TOKEN CODES.
*/

#pragma once
#include <iostream>
#include <fstream>
#include <string.h>

/* Global Variables */
extern int charClass;                           //Numeric code for character class
extern char lexeme[100];                        //Holds lexeme to be tokenized
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
#define IDENT 11                                //Identifier
#define ASSIGN_OP 20                            //Assignment Operator =
#define SEMI_COLON 30                           // ;
#define MULT_OP 23                              // *
#define DIV_OP 24                               // Division /
#define LEFT_PAREN 21                           // Left Parenthesis (
#define RIGHT_PAREN 22                          // Right Parenthesis )
#define LEFT_BRACE 31                           // Left Curly Brace {
#define RIGHT_BRACE 32                          // Right Curly Brace }
#define KEYWORD 15                              // Keyword FLOAT

/* Global Functions */
void addChar();

void getChar();

void getNonBlank();

int lex() ;