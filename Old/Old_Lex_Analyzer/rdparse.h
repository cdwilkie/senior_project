/* C. DUSTIN WILKIE
 * COMP 360 001
 * PROJECT 01
 * LEXICAL ANALYZER
*/


/* rdparse.h - header file for Recurse-Down Parser
*/
#pragma once

//Global
extern int errorCount;

void program();

void keyword();

void ident();

void declares();

void stmts();

void assign();

void expr();

