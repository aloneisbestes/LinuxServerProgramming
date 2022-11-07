#ifndef __SAFE_QUEUE_H__
#define __SAFE_QUEUE_H__

/**
 * @brief 
 * 安全的队列
 */

#include <queue>
#include <mutex>

template<typename T>
class SafeQueue {
private:
    std::queue<T> m_queue;          // 任务队列
    std::mutex m_mutex;             // 互斥锁

public:
    /** 构造与析构 **/
    SafeQueue() {   // 空的默认构造
    }

    SafeQueue(const SafeQueue &other) { // 拷贝构造函数
    }

    ~SafeQueue() {  // 析构函数
    }

public:
    /** 成员方法 **/
    bool empty() {  // 队列是否为空
        std::unique_lock<std::mutex> lock(m_mutex);     // std::unique_lock 是锁管理类，当前对象生命周期存在时，会一直占用该锁，生命周期结束后会自动释放锁
        return m_queue.empty();
    }

    size_t size() {   // 队列大小
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.size();
    }

    bool enqueue(const T &t) {  // 队列添加元素
        std::unique_lock<std::mutex> lock()
        m_queue.push(t);
    }

    bool dequeue(T &t) {    // 出队
        std::unique_lock<std::mutex> lock(m_mutex);
        if (m_queue.empty())    
            return false;
        t = std::move(m_queue.front());    // 将一个左值强制转化为右值引用，继而可以通过右值引用使用该值
        m_queue.pop();

        return true;
    }
};

#endif // __SAFE_QUEUE_H__