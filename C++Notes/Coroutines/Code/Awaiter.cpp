#include <coroutine>
#include <iostream>

struct CoroutineTask {
    struct promise_type {
        auto initial_suspend() {
            std::cout << "initial_suspend called" << std::endl;
            return std::suspend_always{};
        }
        auto final_suspend() noexcept {
            std::cout << "final_suspend called" << std::endl;
            return std::suspend_always{};
        }
        CoroutineTask get_return_object() {
            std::cout << "get_return_object called" << std::endl;
            return CoroutineTask{
                std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        void return_void() { std::cout << "co_return called" << std::endl; }
        void unhandled_exception() {}
        ~promise_type() {
            std::cout << "Promise Destructor called" << std::endl;
        }
        int value = 0;
    };

    struct Awaiter {
        int value;
        bool await_ready() const noexcept { return false; }
        void await_suspend(std::coroutine_handle<promise_type> handle) noexcept {
            handle.promise().value = value;
            std::cout << "Awaiter await_suspend execute" << std::endl;
        }
        void await_resume() const noexcept { std::cout << "Awaiter await_resume execute" << std::endl; }
    };
    std::coroutine_handle<promise_type> coro_handle;

    // 为了避免协程所有权混乱，注意将协程类型仅允许移动构造;
    //  Making Task move-only:
    CoroutineTask(std::coroutine_handle<promise_type> handle)
        : coro_handle(handle){};
    CoroutineTask(const CoroutineTask&) = delete;
    CoroutineTask& operator=(const CoroutineTask&) = delete;
    CoroutineTask(CoroutineTask&& task) noexcept
        : coro_handle(task.coro_handle) {
        task.coro_handle = {};
    }
    CoroutineTask& operator=(CoroutineTask&& task) noexcept {
        if (this == &task) return *this;
        if (coro_handle) coro_handle.destroy();
        coro_handle = task.coro_handle;
        task.coro_handle = {};
        return *this;
    }
    ~CoroutineTask() {
        if (coro_handle) coro_handle.destroy();
        std::cout << "Destructor called" << std::endl;
    }
    void resume() {
        std::cout << "Call Coroutine resume" << std::endl;
        coro_handle.resume();
    }
    int getValue(){
        return coro_handle.promise().value;
    }
};
auto operator co_await(CoroutineTask::Awaiter&& awaiter) {
    awaiter.value = 2;
    std::cout << "co_await awaiter.value modified;" << std::endl;
    return awaiter;
}
CoroutineTask simpleCoroutine() {
    std::cout << "Coroutine body started" << std::endl;
    co_await std::move(CoroutineTask::Awaiter{});
    std::cout << "Coroutine co_return started" << std::endl;
    co_return;
}

int main() {
    std::cout << "Main function" << std::endl;
    auto coro = simpleCoroutine();
    std::cout << "coroutine initial_suspend : value = "<< coro.getValue() << std::endl;
    std::cout << "Main function resume coroutine" << std::endl;
    coro.resume();
    std::cout << "coroutine await_suspend : value = "<< coro.getValue() << std::endl;
    coro.resume();
    std::cout << "Main function end" << std::endl;
    return 0;
}