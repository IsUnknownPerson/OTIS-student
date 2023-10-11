#include <algorithm>
#include <chrono>
#include <coroutine>
#include <format>
#include <functional>
#include <iostream>
#include <list>
#include <ranges>
#include <thread>

using namespace std::chrono_literals;

using Clock = std::chrono::steady_clock;

struct Timer {
  Clock::time_point start;
  Clock::duration duration;
  std::function<void()> callback;
};

class TimerExecutor {
 public:
  void schedule(Clock::duration duration, std::function<void()> callback) {
    timers.emplace_back(Clock::now(), duration, std::move(callback));
  }

  void run() {
    while (!timers.empty()) {
      auto now = Clock::now();
      auto is_active = [&now](const Timer& timer) {
        return timer.start + timer.duration < now;
      };
      for (auto timer = timers.begin(); timer != timers.end();) {
        if (is_active(*timer)) {
          timer->callback();
          timer = timers.erase(timer);
        } else {
          timer++;
        }
      }
    }
  }

 private:
  std::list<Timer> timers;
};

template <typename Duration, typename Callback>
void sleep_for(TimerExecutor& exec, Duration duration, Callback&& cb) {
  exec.schedule(duration, std::forward<Callback>(cb));
}

void f(TimerExecutor& exec, std::string_view name) {
  std::cout << name << " start\n";
  // heavy async task
  sleep_for(exec, 1s, [&exec, name]() mutable {
    std::cout << name << " 1\n";
    sleep_for(exec, 1s, [&exec, name]() mutable {
      std::cout << name << " 2\n";
      sleep_for(exec, 1s, [name]() { std::cout << name << " end\n"; });
    });
  });
}

class Task {
 public:
  struct promise_type {
    std::suspend_never initial_suspend() { return {}; }

    std::suspend_never final_suspend() noexcept { return {}; }

    void unhandled_exception() { std::abort(); }

    Task get_return_object() { return {}; }

    void return_void() {}
  };
};

struct TimerAwaitible {
  TimerAwaitible(TimerAwaitible&&) = default;
  TimerAwaitible(TimerExecutor& exec, Clock::duration dur)
      : exec{exec}, dur{dur} {}

  bool await_ready() { return false; }
  void await_suspend(std::coroutine_handle<> handle) {
    exec.schedule(dur, [handle]() { handle.resume(); });
  }
  void await_resume() {}

  TimerExecutor& exec;
  Clock::duration dur;
};

TimerAwaitible coro_sleep_for(TimerExecutor& exec, Clock::duration dur) {
  return TimerAwaitible{exec, dur};
}

Task coro_f(TimerExecutor& exec, std::string_view name) {
  std::cout << name << " start\n";
  co_await coro_sleep_for(exec, 1s);
  std::cout << name << " 1\n";
  co_await coro_sleep_for(exec, 1s);
  std::cout << name << " 2\n";
  co_await coro_sleep_for(exec, 1s);
  std::cout << name << " end\n";
}

struct f_frame;

void continue_f(std::shared_ptr<f_frame> frame);

struct f_coroutine_handle {
  f_coroutine_handle(std::shared_ptr<f_frame> frame) : frame{frame} {}

  void resume() { continue_f(frame); }

 private:
  std::shared_ptr<f_frame> frame;
};


struct AnotherTimerAwaitible {
  AnotherTimerAwaitible(AnotherTimerAwaitible&&) = default;
  AnotherTimerAwaitible(TimerExecutor& exec, Clock::duration dur)
      : exec{exec}, dur{dur} {}

  bool await_ready() { return false; }
  void await_suspend(f_coroutine_handle handle) {
    exec.schedule(dur, [handle]() mutable { handle.resume(); });
  }
  void await_resume() {}

  TimerExecutor& exec;
  Clock::duration dur;
};

struct f_frame {
  f_frame(TimerExecutor& exec, std::string_view name)
      : step{0},
        promise{},
        task{promise.get_return_object()},
        exec{exec},
        name{name} {}

  int step;
  Task::promise_type promise;
  Task task;

  // local variables
  TimerExecutor& exec;
  std::string_view name;

  std::optional<AnotherTimerAwaitible> await_0{};
  std::optional<AnotherTimerAwaitible> await_1{};
  std::optional<AnotherTimerAwaitible> await_2{};
};

auto another_sleep_for(TimerExecutor& exec, Clock::duration dur) {
  return AnotherTimerAwaitible{exec, dur};
}

f_coroutine_handle dissected_f(TimerExecutor& exec, std::string_view name) {
  auto frame = std::make_shared<f_frame>(exec, name);

  continue_f(frame);

  return f_coroutine_handle{frame};
}

template <typename Awaitible>
bool await(std::shared_ptr<f_frame> frame, Awaitible& await) {
  if (await.await_ready()) return false;
  await.await_suspend(f_coroutine_handle{frame});
  return true;
}

void continue_f(std::shared_ptr<f_frame> frame) {
  switch (frame->step) {
    case 0: {
      std::cout << frame->name << " start\n";
      frame->await_0.emplace(another_sleep_for(frame->exec, 1s));
      bool suspended_0 = await(frame, *frame->await_0);
      // always true
      break;
    }
    case 1: {
      frame->await_0->await_ready();
      std::cout << frame->name << " 1\n";
      frame->await_1.emplace(another_sleep_for(frame->exec, 1s));
      bool suspended_1 = await(frame, *frame->await_1);
      // always true
      break;
    }
    case 2: {
      frame->await_1->await_ready();
      std::cout << frame->name << " 2\n";
      frame->await_2.emplace(another_sleep_for(frame->exec, 1s));
      bool suspended_2 = await(frame, *frame->await_2);
      // always true
      break;
    }
    case 3: {
      frame->await_2->await_ready();
      std::cout << frame->name << " end\n";
      // auto final_awaitable = frame->promise.final_suspend();
      // bool suspended_3 = await(frame, final_awaitable);
      // always true
      break;
    }
  }
  frame->step++;
}

int main() {
  TimerExecutor exec;

  auto start = Clock::now();
  f(exec, "a");
  f(exec, "b");
  exec.run();
  auto end = Clock::now();
  std::cout << std::format(
                   "Duration: {}",
                   std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                         start))
            << "\n";
  return 0;
}
