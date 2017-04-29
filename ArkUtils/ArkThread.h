#pragma once

#include <thread>
#include <mutex>

#include "ArkString.h"

#define SCOPE_LOCKER ArkThreading::ScopeLock


namespace ArkThreading
{
	class WorkerTask
	{
	public:
		void initialize() { init(); }
		void runTask() { mIsRunning = true; run(); }
	protected:
		virtual void init() = 0;
		virtual void run() = 0;

	private:
		bool mIsRunning = false;
	};

	class ArkThread
	{
	public:
		ArkThread() : mThread(NULL) {}
		void start() { mThread = new std::thread(&ArkThread::run, this); }
		void join() { mThread->join(); }
		virtual void run() = 0;

	private:
		std::thread * mThread;
	};

	class ArkMutex : public std::mutex
	{
	};

	class ScopeLock
	{
	public:
		ScopeLock(ArkMutex * mutex, ArkString reason)
			: m_lock(mutex)
			, m_reason(reason)
		{
			m_lock->lock();
		}

		~ScopeLock()
		{
			m_lock->unlock();
		}
	private:
		ArkMutex * m_lock;
		ArkString m_reason;
	};
}

