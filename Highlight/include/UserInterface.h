#pragma once

#include <string>


class UserInterface {
public:
    /*
    *
    */
   static void greetUser();

   static void tokenizeStatus(const std::string& filename);

   static void searchingSource(const std::string& filename);

   static void highlightWrite(const std::string& filename);

   static void programEnd();

};