#pragma once

#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <future>
#include <functional>
#include <condition_variable>
#include "../include/Tokenizer.h"

class ThreadPool {
public:
    ThreadPool(int threads);
    std::future<std::vector<Tokenizer::Token>> enqueueTokenize(const std::wstring& line);
    ~ThreadPool();

private:
    std::vector<std::thread> threads_;
    std::queue<std::function<void()>> tasks_;
    std::mutex taskMutex_;
    std::condition_variable condition_;
    bool stop_ = false;
};