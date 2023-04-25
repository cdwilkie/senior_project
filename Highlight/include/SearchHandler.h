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
    static void searchTokens(std::vector<std::vector<Tokenizer::Token>>& tokens,
        size_t numThreads);

private:
    static void _searchChunk(std::vector<std::vector<Tokenizer::Token>>&tokens,
            const std::unordered_map<std::wstring, std::wstring>& pMap,
            const std::unordered_map<std::wstring, std::wstring>& sMap,
            const std::unordered_map<std::wstring, std::wstring>& rMap,
            const std::unordered_map<std::wstring, std::wstring>& dqMap, size_t start, size_t end);

    static void _searchPrefix(std::vector<Tokenizer::Token>& tokens,
            const std::unordered_map<std::wstring, std::wstring>& prefixMap);
    
    static void _searchSuffix(std::vector<Tokenizer::Token>& tokens,
            const std::unordered_map<std::wstring, std::wstring>& suffixMap);

    static void _searchRoot(std::vector<Tokenizer::Token>& tokens,
            const std::unordered_map<std::wstring, std::wstring>& rootMap);

    static void _searchDisq(std::vector<Tokenizer::Token>& tokens,
            const std::unordered_map<std::wstring, std::wstring>& dqMap);

    static std::wstring _toLowerCase(const std::wstring& input);
};//end SearchHandler class