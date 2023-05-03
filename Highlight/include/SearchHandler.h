/*
* Search Handler class encapsulates search behavior for
* locating desired textual units via use of unordered map
* of such names and their transliterated forms (if applicable).
* Performs a case-agnostic search for desired prefix,
* suffix, root, and/or disqualifier.
*
*/
#pragma once

#include <unordered_map>                        //Desired textual units
#include <vector>                               //Tokens
#include <string>                               //Token Contents
#include "Tokenizer.h"                          //Token class

class SearchHandler {
public:
    /*searchTokens() will search the contents of 
    * the provided vector for the the key extracted from
    * the prefix, suffix, root, and dq .txt files.
    * Supports multithreading with a numThreads argument.
    */
    static void searchTokens(std::vector<std::vector<Tokenizer::Token>>& tokens,
        size_t numThreads);

private:
    /*_searchChunk() is a helper function for searchTokens.
    * Uses the provided maps and searches a chunk of the
    * provided vector.
    */
    static void _searchChunk(std::vector<std::vector<Tokenizer::Token>>&tokens,
            const std::unordered_map<std::wstring, std::wstring>& pMap,
            const std::unordered_map<std::wstring, std::wstring>& sMap,
            const std::unordered_map<std::wstring, std::wstring>& rMap,
            const std::unordered_map<std::wstring, std::wstring>& dqMap, size_t start, size_t end);

    /*_searchPrefix is a helper function that is tasked
    * with finding matches from the prefix map and the
    * provided vector.
    */
    static void _searchPrefix(std::vector<Tokenizer::Token>& tokens,
            const std::unordered_map<std::wstring, std::wstring>& prefixMap);
    
    /*_searchSuffix() is a helper function that is tasked
    * with finding matches from the suffix map and the
    * the provided vector.
    */
    static void _searchSuffix(std::vector<Tokenizer::Token>& tokens,
            const std::unordered_map<std::wstring, std::wstring>& suffixMap);

    /*_searchRoot is a helper function that is tasked
    * with finding matches from the root map and
    * the provided vector.
    */
    static void _searchRoot(std::vector<Tokenizer::Token>& tokens,
            const std::unordered_map<std::wstring, std::wstring>& rootMap);

    /*_searchDisq() is a helper function that is tasked
    * with finding matches from the DQ map and
    * the provided vector.
    */
    static void _searchDisq(std::vector<Tokenizer::Token>& tokens,
            const std::unordered_map<std::wstring, std::wstring>& dqMap);

    /*_toLowerCase() is a helper function that
    * converts the passed wstring into all
    * lower case, for all available chars.
    */
    static std::wstring _toLowerCase(const std::wstring& input);
};//end SearchHandler class