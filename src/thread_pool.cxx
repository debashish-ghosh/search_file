export module thread_pool;

import std;

export class ThreadPool {
public:
  ThreadPool(std::size_t numThreads);
  ~ThreadPool();

  void enqueue(std::function<void()> task);
  bool has_pending_tasks();
  void wait();

private:
  std::vector<std::thread> workers;
  std::queue<std::function<void()>> tasks;

  std::mutex queueMutex;
  std::condition_variable condition;
  bool stop;

  void worker();
};