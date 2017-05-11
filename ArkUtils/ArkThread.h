#pragma once

#include <thread>
#include <mutex>
#include <list>
#include "BuildOptions.h"
#include "ArkString.h"

#define SCOPE_LOCKER ArkThreading::ScopeLock


namespace ArkThreading
{
	class Task
	{
	public:
		Task() : m_isDone(false) {}
		bool isDone() const { return m_isDone; }
	protected:
		virtual void doWork() = 0;
	private:
		bool m_isDone = false;
	};

	/////////////////////////////////////////////

	class TaskQueue
	{
	public:
		Task * takeTask()
		{
			Task * task = *(m_tasks.begin());
			m_tasks.pop_front();
			return task;
		}

		void addTask(Task * task) { m_tasks.push_back(task); }
		bool isEmpty() const { return m_tasks.size() == 0; }

	private:
		std::list<Task*> m_tasks;
	};

	/////////////////////////////////////////////

	class ArkThread
	{
	public:
		ArkThread(TaskQueue * q) : m_thread(NULL), m_taskQueue(q)
		{
		}
		~ArkThread()
		{
			m_thread->join();
			m_thread = 0;
		}

		void start() { m_thread = new std::thread(&ArkThread::run, this); }
		void run()
		{
			Sleep(1);
		}
		void stop()
		{
			m_thread->join();
		}

	private:
		std::thread * m_thread;
		TaskQueue * m_taskQueue;

	};

	/////////////////////////////////////////////

	class ArkMutex : public std::mutex
	{
	};

	/////////////////////////////////////////////

	class ScopeLock
	{
	public:
		ScopeLock(ArkMutex * mutex, ArkString reason = "ScopeLock")
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