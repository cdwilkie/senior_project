#include<iostream>

#include "UserInterface.h"


void UserInterface::greetUser() {
    std::cout<<"\n\n\t\tWelcome"<<std::endl;
    std::cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _"<<std::endl;
    std::cout<<"\nThis program identifies and highlights user-defined\n"<<
    "textual units contained within a specified text file (.txt).\n"<<
    "Search parameters may be stored in the 'Data' directory, within\n"<<
    "the 'prefix.txt', 'suffix.txt', 'root.txt', and 'dq.txt' files.\n"<<
    "All search parameters should adhere to ''Key'' ''Value'' format, where\n"<<
    "''Key'' is the desired search parameter and ''Value'' is the standard\n"<<
    "or transliterated form. ''Null'' may also be used for ''Value'' if no\n"<<
    "standard or transliteration transformation should occur."<<std::endl;
    std::cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n"<<std::endl;
}

void UserInterface::tokenizeStatus(const std::string& filename) {
    std::cout<<"\n* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"<<std::endl;
    std::cout<<"\t\tTokenizing Source - " << filename<<"\n"<<std::endl;
}

void UserInterface::searchingSource(const std::string& filename) {
    std::cout<<"\n\t\tSearching Source - "<<filename<<"\n"<<std::endl;
}

void UserInterface::highlightWrite(const std::string& filename) {
    std::cout<<"\n\t\tHighlighting & Writing to - " << filename<<"\n"<<std::endl;
}

void UserInterface::programEnd() {
    std::cout<<"\n\t\t---Program Terminated---\n"<<std::endl;
}