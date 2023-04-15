#include <locale>
#include <algorithm>
#include <codecvt>

#include "SearchHandler.h"
#include "FileHandler.h"

void SearchHandler::_searchChunk(std::vector<std::vector<Tokenizer::Token>>&tokens, 
        const std::unordered_map<std::wstring,std::wstring>&pMap,
        const std::unordered_map<std::wstring, std::wstring>& sMap, 
        const std::unordered_map<std::wstring, std::wstring>& rMap, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i) {
        _searchPrefix(tokens[i], pMap);
        _searchSuffix(tokens[i], sMap);
        _searchRoot(tokens[i], rMap);
    }
}

void SearchHandler::searchTokens(
        std::vector<std::vector<Tokenizer::Token>>& tokens, size_t numThreads) {

    std::string prefixFile = "../data/prefix.txt";
    std::unordered_map<std::wstring, std::wstring>
        prefixKeyVal = FileHandler::readKeyValues(prefixFile);

    std::string suffixFile = "../data/suffix.txt";
    std::unordered_map<std::wstring, std::wstring>
        suffixKeyVal = FileHandler::readKeyValues(suffixFile);

    std::string rootFile = "../data/root.txt";
    std::unordered_map<std::wstring, std::wstring> 
        rootKeyVal = FileHandler::readKeyValues(rootFile);



    const size_t chunkSize = (tokens.size() + numThreads - 1) / numThreads;
    std::vector<std::thread> threads(numThreads);

    for (size_t i = 0; i < numThreads; ++i) {
        const int start = i * chunkSize;
        const int end = std::min(start + chunkSize, tokens.size());
        threads[i] = std::thread(
            _searchChunk, std::ref(tokens), std::cref(prefixKeyVal),
            std::cref(suffixKeyVal), std::cref(rootKeyVal), start, end);
    }

    for (size_t i = 0; i < threads.size(); ++i) {
        threads[i].join();
    }

}

void SearchHandler::_searchPrefix(std::vector<Tokenizer::Token>& tokens,
        const std::unordered_map<std::wstring, std::wstring>& prefixMap) {
    for (int i = 0; i < tokens.size(); ++i) {
        for (auto const& [key, value]: prefixMap) {
            if (tokens[i].word.length() >= key.length() &&
                tokens[i].word.substr(0, key.length()) == key) {

                if (caseCompare(tokens[i].word.substr(0, key.length()), key)) {
                    tokens[i].tokenID=200;
                }
                
            }
        }
    }
}

void SearchHandler::_searchSuffix(std::vector<Tokenizer::Token>& tokens,
        const std::unordered_map<std::wstring, std::wstring>& suffixMap) {
    for (int i = 0; i < tokens.size(); ++i) {
        for (auto const& [key, value] : suffixMap) {
            if (tokens[i].word.length() >= key.length() &&
                tokens[i].word.substr(tokens[i].word.length() - key.length()) == key) {
                    tokens[i].tokenID = 200;
            }
        }
    }
}

void SearchHandler::_searchRoot(std::vector<Tokenizer::Token>& tokens,
        const std::unordered_map<std::wstring, std::wstring>& rootMap) {
    for (int i = 0; i < tokens.size(); ++i) {
        for (auto const& [key, value] : rootMap) {
            if (tokens[i].word.find(key) != std::string::npos) {
                tokens[i].tokenID = 200;
            }
        }
    }
}

// searchDQ

bool SearchHandler::caseCompare(const std::wstring& str1, const std::wstring& str2) {
    std::wstring result1 = str1;
    for (int i = 0; i < result1.length(); ++i) {
        result1[i] = std::towlower(result1[i]);
    }

    std::wstring result2 = str2;
    for (int i = 0; i < result2.length(); ++i) {
        result2[i] = std::towlower(result2[i]);
    }

    return result1 == result2;
}
