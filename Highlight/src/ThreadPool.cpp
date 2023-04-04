#include "../include/ThreadPool.h"

    ThreadPool::ThreadPool(int threadCount) {
        for (int i = 0; i < threadCount; ++i) {
            threads_.emplace_back([this] {
                while (true) {
                    std::unique_lock<std::mutex> lock(taskMutex_);
                    condition_.wait(lock, [this] {return stop_ || !tasks_.empty();});
                    if (stop_ && tasks_.empty()) {
                        return;
                    }
                    auto task = std::move(tasks_.front());
                    tasks_.pop();
                    lock.unlock();
                    task();
                }
            });
        }
    }

    ThreadPool::~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(taskMutex_);
            stop_ = true;
        }
        condition_.notify_all();
        for (int i = 0; i < threads_.size(); ++i) {
            if (threads_[i].joinable()) {
                threads_[i].join();
            }
        }
    }
   
        
    std::future<std::vector<Tokenizer::Token>> ThreadPool::enqueueTokenize(const std::wstring& line) {
        auto task = std::make_shared<std::packaged_task<std::vector<Tokenizer::Token>()>>(
            [line]() {return Tokenizer::tokenize(line);}
        );
        std::future<std::vector<Tokenizer::Token>> result = task->get_future();
        {
            std::unique_lock<std::mutex> lock(taskMutex_);
            tasks_.emplace([task]() { (*task)(); });
        }
        condition_.notify_one();
        return result;
    }


