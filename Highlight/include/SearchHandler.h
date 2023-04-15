#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include "Tokenizer.h"

class SearchHandler {
public:
    static void searchTokens(std::vector<std::vector<Tokenizer::Token>>& tokens,
        size_t numThreads);
    
    //searchSuffix
    //searchRoot
    //searchDQ

private:
    static void _searchChunk(std::vector<std::vector<Tokenizer::Token>>&tokens,
            const std::unordered_map<std::wstring, std::wstring>& pMap,
            const std::unordered_map<std::wstring, std::wstring>& sMap,
            const std::unordered_map<std::wstring, std::wstring>&rMap, size_t start, size_t end);

    static void _searchPrefix(std::vector<Tokenizer::Token>& tokens,
            const std::unordered_map<std::wstring, std::wstring>& prefixMap);
    
    static void _searchSuffix(std::vector<Tokenizer::Token>& tokens,
            const std::unordered_map<std::wstring, std::wstring>& suffixMap);

    static void _searchRoot(std::vector<Tokenizer::Token>& tokens,
            const std::unordered_map<std::wstring, std::wstring>& rootMap);

    static bool caseCompare(const std::wstring& str1, const std::wstring& str2);
};