#pragma once

#include <thread>
#include <atomic>
#include <functional>
#include <mutex>

class Thread
{
public:
	Thread(const std::function<void(void)> &p_fHandler)
	{
		SetHandler(p_fHandler);
	}

	bool isRunning()
	{
		std::lock_guard<std::mutex> lock{m_oStateMutex};
		return m_bIsRunning;
	}

	void Start()
	{
		std::lock_guard<std::mutex> lock{m_oStateMutex};
		if (m_bIsRunning)
		{
			return;
		}
		m_bIsRunning = true;
		m_oThread = std::thread(m_fWorker);
	}

	void Wait()
	{
		std::lock_guard<std::mutex> lock{m_oStateMutex};
		m_bIsRunning = false;
		if (m_oThread.joinable())
		{
			m_oThread.join();
		}
	}

	void Stop()
	{
		std::lock_guard<std::mutex> lock{m_oStateMutex};
		m_bIsRunning = false;
	}

	void SetHandler(const std::function<void(void)> &p_fHandler)
	{
		m_fWorker = p_fHandler;
	}

	~Thread()
	{
		std::lock_guard<std::mutex> lock{m_oStateMutex};
		m_bIsRunning = false;
		if (m_oThread.joinable())
		{
			m_oThread.join();
		}
	}

private:
	std::mutex m_oStateMutex;
	bool m_bIsRunning;
	std::thread m_oThread;
	std::function<void(void)> m_fWorker;
};