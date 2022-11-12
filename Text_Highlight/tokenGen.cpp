#include "tokenGen.h"

int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int nextToken;

/* addChar - Function to add nextChar to 
 * lexeme array and prepare the next array 
 * index for use
*/
void addChar() {
    if (lexLen <= 98) {                         //If lexeme[] is not full
        lexeme[lexLen++] = nextChar;            //Add char to lexeme & inc lngth
        lexeme[lexLen] = 0;                     //Clear data in last index
    }//end if lexeme not full
    else {                                      //Else lexeme[] is full
        std::cout << "Error - lexeme is too long \n";
    }//else lexeme array full
}//end addChar()
/******************************************/

/* getNonBlank - Function to call getChar
 * until it retrieves a non-whitespace character.
 */
void getNonBlank() {
    while (isspace(nextChar)) {                 //If char is white space, skip
        getChar();                              //Get first non whitespace
    }//end while whitespace
}//end getNonBlank()
/******************************************/

//----------------------------------------//
/* getChar - Function to retrive next character,
 * (nextChar), of input and determine its 
 * character class, (charClass)
 */
void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {      //If not eof, get available char
        if (isalpha(nextChar)){                 //If char is letter
            charClass = LETTER;
        }//end if letter
        else if (isdigit(nextChar)) {           //Else if char is digit
            charClass = DIGIT;
        }//end if digit
        else {                                  //Else char is unknown
            charClass = UNKNOWN;
        }//end if unknown
    }//end if !EOF
    else {                                      //Else set end of file flag
        charClass = EOF;
    }//end else EOF  
}//end getChar()

int lookup (char ch) {
    switch (ch) {
        case '=':
            addChar();
            nextToken = ASSIGN_OP;
            break;
        case ';':
            addChar();
            nextToken = SEMI_COLON;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '{':
            addChar();
            nextToken = LEFT_BRACE;
            break;
        case '}':
            addChar();
            nextToken = RIGHT_BRACE;
            break;
        default:
            addChar();
            nextToken = UNKNWN;
            break;
    }//end switch(ch)
    return nextToken;
}//end lookup()
/******************************************/


/* lex - Simple LEXICAL ANALYZER for arithmetic
* exprssions.  Analyzes the lexeme and returns
* token type
*/
int lex() {
    lexLen = 0;                                 //Intlze new lexeme length to 0
    getNonBlank();                              //Find first non whitespace char
    switch (charClass) {                        //Determine charClass
        case LETTER:                            //is Letter
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) { //Ltters or nums
                addChar();
                getChar();
            }//end while next char lett | digit
            if (strcmp(lexeme,"float") != 0) {  //If lexeme != float
                nextToken = IDENT;              //Token is Ident
            }
            else {                              //Else lexeme is float
                nextToken = KEYWORD;            //Token is keyword
            }//end else lexeme keyword
            break;
        case DIGIT:                             //First char digit
            addChar();
            getChar();
            while (charClass == DIGIT) {        //While more digits
                addChar();
                getChar();
            }//end while next digit
            nextToken = INT_LIT;                //Token is INT_LIT
            break;
        case UNKNOWN:                           //Unknown Symbol
            lookup(nextChar);                   //Check lookup Table
            getChar();                          //Get next char
            break;
        case EOF:                               //END OF FILE FLAG
            nextToken = EOF;                    //Set EOF flag in nextToken
            lexeme[0] = 'E';                    //lexeme[] = "EOF0"
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    }//end switch(charClass)
    std::cout << "Next token is: " << nextToken //Output Results of Lex Anlyzr
            << ", Next lexeme is " << lexeme <<"\n";
    return nextToken;                           //Return nextToken to caller
}//end lex()