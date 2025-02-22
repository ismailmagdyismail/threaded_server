#pragma once

//! threading
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <Thread.hpp>

//! Tasks
#include <queue>
#include <functional>

class ThreadPool
{
public:
  ThreadPool()
  {
    unsigned int iThreadsAvailable = std::thread::hardware_concurrency();
    for (int i = 0; i < iThreadsAvailable; i++)
    {
      std::shared_ptr<Thread> pThread = std::make_shared<Thread>(std::bind(&ThreadPool::ProcessTask, this));
      m_vThreads.push_back(pThread);
      m_vThreads[i]->Start();
    }
  }

  ~ThreadPool()
  {
    Stop();
  }

  void AddTask(std::function<void(void)> p_fTask)
  {
    {
      std::lock_guard<std::mutex> lock{m_oTasksMutex};
      m_qTasks.emplace(p_fTask);
    }
    m_cvTasksConditionVariable.notify_one();
  }

  void Stop()
  {
    std::lock_guard<std::mutex> lock{m_oTasksMutex};
    m_bIsRunning = false;
    m_cvTasksConditionVariable.notify_all();
    for (int i = 0; i < m_vThreads.size(); i++)
    {
      m_vThreads[i]->Stop();
      m_vThreads[i]->Wait();
    }
  }

private:
  void ProcessTask()
  {
    while (true)
    {
      std::unique_lock<std::mutex> lock{m_oTasksMutex};
      m_cvTasksConditionVariable.wait(lock, [this]()
                                      { return !m_qTasks.empty() || !m_bIsRunning; });
      if (!m_bIsRunning && m_qTasks.empty())
      {
        return;
      }
      auto task = m_qTasks.front();
      m_qTasks.pop();
      task();
    }
  }

  std::atomic<bool> m_bIsRunning{true};
  std::mutex m_oTasksMutex;
  std::condition_variable m_cvTasksConditionVariable;
  std::queue<std::function<void(void)>> m_qTasks;
  std::vector<std::shared_ptr<Thread>> m_vThreads;
};