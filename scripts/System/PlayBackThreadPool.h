#include <queue>
#include <vector>
#include <chrono>
#include <thread>
#include <functional>
#include <iostream>
#include <mutex>
#include <condition_variable>

class PlaybackThreadPool {
public:
    struct ScheduledTask {
        std::chrono::steady_clock::time_point time;
        std::function<void()> task;

        bool operator>(const ScheduledTask& other) const {
            return time > other.time;
        }
    };

    PlaybackThreadPool(size_t numThreads) {
        // スレッドプールの作成
        for (size_t i = 0; i < numThreads; ++i) {
            workers.push_back(std::thread(&PlaybackThreadPool::workerThread, this));
        }
    }

    ~PlaybackThreadPool() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();
        for (auto& worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    // タスクをスケジュール
    void scheduleTask(std::chrono::steady_clock::time_point time, std::function<void()> task) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            tasks.push({ time, task });
        }
        cv.notify_one();
    }

private:
    void workerThread() {
        while (true) {
            ScheduledTask task;
            {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [this] { return stop || !tasks.empty(); });

                if (stop && tasks.empty()) {
                    return;
                }

                if (!tasks.empty()) {
                    task = tasks.top();
                    tasks.pop();
                }
            }

            // 次のタスクの実行時刻まで待機
            auto now = std::chrono::steady_clock::now();
            if (task.time > now) {
                // sleep_untilを使って、正確に次のタスク実行時刻までスリープ
                std::this_thread::sleep_until(task.time);
            }

            task.task(); // タスクの実行
        }
    }

    std::priority_queue<ScheduledTask, std::vector<ScheduledTask>, std::greater<ScheduledTask>> tasks;
    std::vector<std::thread> workers;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop = false;
};
