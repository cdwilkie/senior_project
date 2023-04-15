#include <locale>
#include <algorithm>
#include <codecvt>
#include <cctype>

#include "SearchHandler.h"
#include "FileHandler.h"

void SearchHandler::_searchChunk(std::vector<std::vector<Tokenizer::Token>>&tokens, 
        const std::unordered_map<std::wstring,std::wstring>&pMap,
        const std::unordered_map<std::wstring, std::wstring>& sMap, 
        const std::unordered_map<std::wstring, std::wstring>& rMap,
        const std::unordered_map<std::wstring, std::wstring>& dqMap, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i) {
        _searchPrefix(tokens[i], pMap);
        _searchSuffix(tokens[i], sMap);
        _searchRoot(tokens[i], rMap);
        _searchDisq(tokens[i], dqMap);
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

    std::string dqFile = "../data/dq.txt";
    std::unordered_map<std::wstring, std::wstring>
        dqKeyVal = FileHandler::readKeyValues(dqFile);



    const size_t chunkSize = (tokens.size() + numThreads - 1) / numThreads;
    std::vector<std::thread> threads(numThreads);

    for (size_t i = 0; i < numThreads; ++i) {
        const int start = i * chunkSize;
        const int end = std::min(start + chunkSize, tokens.size());
        threads[i] = std::thread(
            _searchChunk, std::ref(tokens), std::cref(prefixKeyVal),
            std::cref(suffixKeyVal), std::cref(rootKeyVal), 
            std::cref(dqKeyVal), start, end);
    }

    for (size_t i = 0; i < threads.size(); ++i) {
        threads[i].join();
    }

}

void SearchHandler::_searchPrefix(std::vector<Tokenizer::Token>& tokens,
        const std::unordered_map<std::wstring, std::wstring>& prefixMap) {
    std::wstring lowerToken;
    std::wstring lowerPrefix;

    for (auto& token : tokens) {
        for (auto const& [key, value]: prefixMap) {
            lowerToken = _toLowerCase(token.word);
            lowerPrefix = _toLowerCase(key);
            if (lowerToken.length() >= lowerPrefix.length() &&
                lowerToken.substr(0, lowerPrefix.length()) == lowerPrefix) {

                    token.tokenID = 200;
                
            }
        }
    }
}

void SearchHandler::_searchSuffix(std::vector<Tokenizer::Token>& tokens,
        const std::unordered_map<std::wstring, std::wstring>& suffixMap) {
    std::wstring lowerToken;
    std::wstring lowerSuffix;
    for (auto& token : tokens) {
        for (auto const& [key, value] : suffixMap) {
            lowerToken = _toLowerCase(token.word);
            lowerSuffix = _toLowerCase(key);
            if (lowerToken.length() >= lowerSuffix.length() &&
                lowerToken.substr(lowerToken.length() - lowerSuffix.length()) == lowerSuffix) {
                    token.tokenID = 200;
            }
        }
    }
}

void SearchHandler::_searchRoot(std::vector<Tokenizer::Token>& tokens,
        const std::unordered_map<std::wstring, std::wstring>& rootMap) {
    std::wstring lowerToken;
    std::wstring lowerRoot;
    for (auto& token : tokens) {
        for (auto const& [key, value] : rootMap) {
            lowerToken = _toLowerCase(token.word);
            lowerRoot = _toLowerCase(key);
            if (lowerToken.find(lowerRoot) != std::string::npos) {
                token.tokenID = 200;
            }
        }
    }
}

void SearchHandler::_searchDisq(std::vector<Tokenizer::Token>& tokens,
        const std::unordered_map<std::wstring, std::wstring>& dqMap) {
    std::wstring lowerToken;
    std::wstring lowerDQ;
    for (auto& token : tokens) {
        for (auto const& [key, value] : dqMap) {
            lowerToken = _toLowerCase(token.word);
            lowerDQ = _toLowerCase(key);
            if (lowerToken.find(lowerDQ) != std::string::npos) {
                token.tokenID = 404;
            }
        }
    }
}

std::wstring SearchHandler::_toLowerCase(const std::wstring& input) {
    std::wstring results;

    
    for (const auto& letters : input) {
        results += std::towlower(letters);
    }

    return results;
}


