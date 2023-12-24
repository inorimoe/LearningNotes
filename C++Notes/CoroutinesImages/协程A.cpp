//
//https://godbolt.org/z/5cshvjWh8
//

#include <coroutine>
#include <iostream>

struct CoroutineTask {
    struct promise_type {
        auto initial_suspend() { 
            std::cout << "initial_suspend called" << std::endl;
            return std::suspend_never{}; }
        auto final_suspend() noexcept {
            std::cout << "final_suspend called" << std::endl;
            return std::suspend_always{};
        }
        CoroutineTask get_return_object() {
            std::cout << "get_return_object called" << std::endl;
            return CoroutineTask{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        void return_void() { std::cout << "co_return called" << std::endl; }
        void unhandled_exception() {}
        ~promise_type() {
            std::cout << "Promise Destructor called" << std::endl;
        }
    };
    std::coroutine_handle<promise_type> coro_handle;
    CoroutineTask(std::coroutine_handle<promise_type> h) : coro_handle(h) {}
    ~CoroutineTask() {
        std::cout << "Destructor called" << std::endl;
    }
    void resume() {
        std::cout << "Call Coroutine resume" << std::endl;
        coro_handle.resume();
    }
};
CoroutineTask simpleCoroutine() {
    std::cout << "Coroutine started" << std::endl;
    co_return;
}

int main() {
    std::cout << "Main function" << std::endl;
    auto coro = simpleCoroutine();
    std::cout << "Main function end" << std::endl;
    return 0;
}