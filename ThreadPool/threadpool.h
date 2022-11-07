#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <thread>
#include <functional>
#include <vector>
#include <utility>
#include <mutex>
#include <future>
#include "safe_queue.h"

class ThreadPool {
private:
    bool m_shutdown;                                // 是否关闭线程池
    SafeQueue<std::function<void ()>> m_queue;      // 任务队列
    std::vector<std::thread> m_threads;             // 工作线程队列
    std::mutex m_conditional_mutex;                 // 线程休眠互斥锁变量
    std::condition_variable m_conditional_cond;     // 线程环境锁，让线程可以处于休眠或者唤醒状态，条件变量

public:
    // 构造函数
    ThreadPool(int size) 
    :m_threads(std::vector<std::thread>(size)), m_shutdown(false){

    }
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool(ThreadPool &&) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;
    ThreadPool &operator=(ThreadPool &&) = delete;
};


#endif // __THREAD_POOL_H__