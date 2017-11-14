#pragma once
#include <queue>
#include <mutex>

namespace az
{
    template<typename T>
    struct queue
    {
        T pop() 
        {
            std::unique_lock<std::mutex> lock{ mutex };
            if (m_queue.empty()) 
                condition.wait(lock);
            auto front = m_queue.front();
            m_queue.pop();
            return front;
        }
        void push(T& obj) 
        {
            std::lock_guard<std::mutex> lock{ mutex };
			m_queue.push(obj);
			condition.notify_one();
        }
    private:
        std::queue<T> m_queue;
        std::mutex mutex;
        std::condition_variable condition;
    };
}