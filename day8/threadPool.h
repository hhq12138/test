#ifndef THREADPOOL_H
#define THREADPOOL_H
 
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <functional>
class ThreadPool {
public:
    explicit ThreadPool(size_t threadCount = 8): pool_(std::make_shared<Pool>()) {
            assert(threadCount > 0);    //断言
            for(size_t i = 0; i < threadCount; i++) {  //创建 threadCount个工作线程
                std::thread([pool = pool_] {    //创建线程  将pool_ 赋值给 pool
                    std::unique_lock<std::mutex> locker(pool->mtx); //创建一个锁
                    //工作线程的逻辑
                    while(true) {       //不断的去向工作队列请求
                        if(!pool->tasks.empty()) { //如果工作队列不为空
                            auto task = std::move(pool->tasks.front());//获取一个任务
                            pool->tasks.pop();  //队列弹出已经被获取的任务
                            locker.unlock();    //解锁
                            task();             //处理任务
                            locker.lock();      //上锁
                        } 
                        else if(pool->isClosed) break; //如果工作队列为空,并且池子已经关闭,退出
                        else pool->cond.wait(locker);  //如果工作队列为空并且线程池没有关闭,则设置该工作线程阻塞等待 条件变量-1
                    }
                }).detach();    //设置线程分离
            }
    }
 
    ThreadPool() = default;         //采用默认的构造函数
 
    ThreadPool(ThreadPool&&) = default;     //采用默认的拷贝构造函数
    
    ~ThreadPool() {
        if(static_cast<bool>(pool_)) {
            {
                std::lock_guard<std::mutex> locker(pool_->mtx);     //创建一个锁
                pool_->isClosed = true;             //关闭线程池
            }       
            pool_->cond.notify_all();               //唤醒线程池中所以的线程,线程最终就会进入  else if(pool->isClosed) break; 逻辑,最后退出
        }
    }
 
    template<class F>
    void AddTask(F&& task) {    //向线程池中添加任务
        {
            std::lock_guard<std::mutex> locker(pool_->mtx);  //创建一个锁
            pool_->tasks.emplace(std::forward<F>(task));     //向工作队列中插入一个任务
        }
        pool_->cond.notify_one();   //唤醒一个线程  条件变量+1 
    }
 
private:
    struct Pool {           
        std::mutex mtx;                 //互斥锁    
        std::condition_variable cond;  //条件变量
        bool isClosed;                 //线程池是否关闭
        std::queue<std::function<void()>> tasks; //工作队列
    };
    std::shared_ptr<Pool> pool_;        //定义一个 Pool指针
};
 
 
#endif //THREADPOOL_H