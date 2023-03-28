/* C. DUSTIN WILKIE
 * COMP 360 001
 * PROJECT 01
 * LEXICAL ANALYZER
*/


/* MAIN - Drives the lexical analyzer.  
 * File name string may be stored in
 * char array FILENAME.
 * Collects first char of sourcefile string
 * then calls lexical analyzer and syntax
 * analyzer to parse tokens.
*/

#include "front.h"
#include "rdparse.h"

FILE *in_fp, *fopen();                          //Create pointer for file input stream

//----------------------------------------//

/* main driver
 */
int main () {
    
    char fileName[] = "front.in";               //FILE NAME can be inserted here

    if ((in_fp = fopen(fileName, "r")) == NULL) {//Try to open filestream in read mode
        std::cout << "Error - cannot open " <<std::endl;
    }//end if file open
    else {                                      //Else Begin Parse
        std::cout << "ANALYZING\n";
        getChar();                              //Get first character of source string/file
        do {
            lex();                              //Call lexical analyzer to generate token
            program();                          //Call Syntax analyzer subprogram to parse
        } while (nextToken != EOF);             //Continue until end of file
    }//end else tokenize

    std::cout << "\nError Count: " << errorCount << std::endl;//Display Error Count
    return 0;
}//end main
