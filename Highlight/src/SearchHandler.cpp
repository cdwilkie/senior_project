#include "SearchHandler.h"
#include "FileHandler.h"

void SearchHandler::_searchChunk(std::vector<std::vector<Tokenizer::Token>>&tokens, 
        const std::unordered_map<std::wstring,std::wstring>&pMap,
        const std::unordered_map<std::wstring, std::wstring>& sMap, 
        const std::unordered_map<std::wstring, std::wstring>& rMap, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i) {
        _searchPrefix(tokens[i], pMap);
        //_searchSuffix();
        //_searchRoot();
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

void SearchHandler::_searchPrefix(std::vector<Tokenizer::Token> &data,
        const std::unordered_map<std::wstring, std::wstring> &map) {
    for (int i = 0; i < data.size(); ++i) {
        for (auto const& [key, value]: map) {
            if (data[i].word.substr(0, key.length()) == key) {
                data[i].tokenID=200;
            }
        }
    }
}
// searchSuffix
// searchRoot
// searchDQ
