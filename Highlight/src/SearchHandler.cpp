//#include <locale> //test
//#include <algorithm>
//#include <codecvt> //test
#include <cwctype> //test

#include "SearchHandler.h"
#include "FileHandler.h"


/*
* Helper function for searchTokens. _searchChunk accepts unorderedmaps of
* the prefix, suffix, root, and disqualifier textual units and calls
* the approrpiate function for each index of the vector of tokens.
* Performs the search on chunks to facilitate multithreading.
*/
void SearchHandler::_searchChunk(std::vector<std::vector<Tokenizer::Token>>&tokens, 
        const std::unordered_map<std::wstring,std::wstring>&pMap,
        const std::unordered_map<std::wstring, std::wstring>& sMap, 
        const std::unordered_map<std::wstring, std::wstring>& rMap,
        const std::unordered_map<std::wstring, std::wstring>& dqMap, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i) {      //Iterrate through the chunk
        _searchDisq(tokens[i], dqMap);          //Find Disqualfied term match
        _searchPrefix(tokens[i], pMap);         //Find prefix match
        _searchSuffix(tokens[i], sMap);         //Find Suffix match
        _searchRoot(tokens[i], rMap);           //Find Root match
        
    }//end for chunk
}//end _searchChunk


/*
* searchTokens encapsulates the driving logic that initiates the search
* of desired textual units. Opens filestreams using the specified
* paths via FileHandler class to generate unordered maps of desired
* textual units and their transliterated values. Creates a vector of
* threads using the provided numThreads to chunk the provided vector
* of tokens and search for the textual units.
*/
void SearchHandler::searchTokens(
        std::vector<std::vector<Tokenizer::Token>>& tokens, size_t numThreads) {

    std::string prefixFile = "../data/prefix.txt";//Location user prefix
    std::unordered_map<std::wstring, std::wstring>
        prefixKeyVal = FileHandler::readKeyValues(prefixFile);//Build prefix map

    std::string suffixFile = "../data/suffix.txt";//Location user suffix
    std::unordered_map<std::wstring, std::wstring>
        suffixKeyVal = FileHandler::readKeyValues(suffixFile);//Build suffix map

    std::string rootFile = "../data/root.txt";  //Location user root
    std::unordered_map<std::wstring, std::wstring> 
        rootKeyVal = FileHandler::readKeyValues(rootFile);//Build root map

    std::string dqFile = "../data/dq.txt";      //Location user DQ
    std::unordered_map<std::wstring, std::wstring>
        dqKeyVal = FileHandler::readKeyValues(dqFile);//Build DQ map


    const size_t chunkSize = (tokens.size() + numThreads - 1) / numThreads;//Chunk
    std::vector<std::thread> threads(numThreads);//Create vector for threads

    for (size_t i = 0; i < numThreads; ++i) {   //Iterrate through threads to assign task
        const int start = i * chunkSize;        //Initialize start index
        const int end = std::min(start + chunkSize, tokens.size());//ensure desired chunk size
        threads[i] = std::thread(               //Assign tasks
            _searchChunk, std::ref(tokens), std::cref(prefixKeyVal),
            std::cref(suffixKeyVal), std::cref(rootKeyVal), 
            std::cref(dqKeyVal), start, end);
    }//end for threads

    for (size_t i = 0; i < threads.size(); ++i) {//Iterrate through threads
        threads[i].join();                      //Join each thread
    }//for join threads

}// end searchTokens


/*
* Helper function for searchTokens that compares each token of
* the provided vector to an unordered map of desired textual
* units. Each seach is converted to lowercase before comparison.
* Matching tokens are have tokenID value updated.
*/
void SearchHandler::_searchPrefix(std::vector<Tokenizer::Token>& tokens,
        const std::unordered_map<std::wstring, std::wstring>& prefixMap) {
    std::wstring lowerToken;                    //Stores lowercase for comparison
    std::wstring lowerPrefix;                   //Stores lowercase for comparison

    for (auto& token : tokens) {                //Iterrate to compare each token
        for (auto const& [key, value] : prefixMap) {//Iterrate to compare each map entry
            lowerToken = _toLowerCase(token.word);//Preprocess token for comparison
            lowerPrefix = _toLowerCase(key);    //Preprocess prefix for comparison
            if (lowerToken.length() >= lowerPrefix.length() &&
                lowerToken.substr(0, lowerPrefix.length()) == lowerPrefix) {

                if (token.tokenID != 404) {
                    token.tokenID = 200;        //Token Match ID 200
                }

                if (token.tokenID != 404 && value != L"null") {//If token can be transliterated/normalized
                    token.word = value;         //Transliterate/normalize
                }//end if transliterate
            }//end if token matches
        }//end for every key
    }//end for every token
}//end _searchPrefix


/*
* Helper function for searchTokens that compares each token of
* the provided vector to an unordered map of desired textual
* units. Each seach is converted to lowercase before comparison.
* Matching tokens are have tokenID value updated.
*/
void SearchHandler::_searchSuffix(std::vector<Tokenizer::Token>& tokens,
        const std::unordered_map<std::wstring, std::wstring>& suffixMap) {
    std::wstring lowerToken;                    //Stores lowercase for comparison
    std::wstring lowerSuffix;                   //Stores lowercase for comparison

    for (auto& token : tokens) {                //Iterrate to compare each token
        for (auto const& [key, value] : suffixMap) {//Iterrate to compare each map entry
            lowerToken = _toLowerCase(token.word);//Preprocess token for comparison
            lowerSuffix = _toLowerCase(key);    //Preprocess suffix for comparison
            if (lowerToken.length() >= lowerSuffix.length() &&
                lowerToken.substr(lowerToken.length() - lowerSuffix.length()) == lowerSuffix) {
                
                if (token.tokenID != 404) {
                    token.tokenID = 200;        //Token Match ID 200
                }

                if (token.tokenID != 404 && value != L"null") {//If token can be transliterated
                    token.word = value;         //Transliterate token
                }//end if transliterated
            }//end if token match
        }//end for every key
    }//end for every token
}//end _searchSuffix


/*
* Helper function for searchTokens that compares each token of
* the provided vector to an unordered map of desired textual
* units. Each seach is converted to lowercase before comparison.
* Matching tokens are have tokenID value updated.
*/
void SearchHandler::_searchRoot(std::vector<Tokenizer::Token>& tokens,
        const std::unordered_map<std::wstring, std::wstring>& rootMap) {
    std::wstring lowerToken;                    //Stores lowercase token for comparison
    std::wstring lowerRoot;                     //Stores lowercase root for comparison
    for (auto& token : tokens) {                //Iterrate through every token
        for (auto const& [key, value] : rootMap) {//Iterrate through every map key
            lowerToken = _toLowerCase(token.word);//Preprocess token for comparison
            lowerRoot = _toLowerCase(key);      //Preprocess root for comparison
            if (lowerToken.find(lowerRoot) != std::string::npos) {

                if (token.tokenID != 404) {
                    token.tokenID = 200;        //Token Match ID 200
                }

                if (token.tokenID != 404 && value != L"null") {//If token can be transliterated
                    token.word = value;         //Transliterate token
                }//end if transliterate
            }//end if token match
        }//end for every key
    }//end for every token
}//end _searchRoot

/*_searchDisq is a helper function to find matches
* from map and vector contents. Iterates through
* contents of vector to compare keys to each
* token. Matches are updated accordingly and
* assigned a disqualifed ID.
*/
void SearchHandler::_searchDisq(std::vector<Tokenizer::Token>& tokens,
        const std::unordered_map<std::wstring, std::wstring>& dqMap) {
    std::wstring lowerToken;                    //Stores lowercase token for comparison
    std::wstring lowerDQ;                       //Stores lowercase dq for comparison
    for (auto& token : tokens) {                //For each token in vector
        for (auto const& [key, value] : dqMap) {//For each key, value in map
            lowerToken = _toLowerCase(token.word);//Convert token to lowercase
            lowerDQ = _toLowerCase(key);        //Convert key to lowercase
            if (lowerToken.find(lowerDQ) != std::string::npos) {//If token contains dq
                token.tokenID = 404;            //Update tokenId ID=404
            }//end if token match
        }//end for every key in map
    }//end for every token in vector
}//end _searchDisq()

/*_toLowerCase() is a helper function that converts the 
* passed string to all lower case, if there exists
* a known associated lower case char with which to 
* convert. Returns the converted wstring.
*/
std::wstring SearchHandler::_toLowerCase(const std::wstring& word) {
    std::wstring results;                       //Holds modified string

    for (const auto& letter : word) {           //For every char in word
        results += std::towlower(letter);       //Convert and concatenate
    }//end for every char

    return results;                             //Return lowercase word
}//end _toLowerCase()


