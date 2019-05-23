#pragma once

#pragma once
#include <mutex>
#include "deque"
#include "CommonDefine.h"

template<class T>
class BlockQueue
{
public:
	typedef std::unique_lock<std::mutex> TLock;

	explicit BlockQueue(const int maxCapacity = -1) :m_maxCapacity(maxCapacity) {}
	size_t size()
	{
		TLock lock(m_mutex);
		return m_list.size();
	}
	void push_back(const T& item)
	{
		{
			TLock lock(m_mutex);
			if (true == hasCapacity())
			{
				while (m_list.size() >= m_maxCapacity)
				{
					m_notFull.wait(lock);
				}
			}

			m_list.push_back(item);
			m_notEmpty.notify_all();
		}
	}
	T pop()
	{
		TLock lock(m_mutex);
		while (m_list.empty())
		{
			m_notEmpty.wait(lock);
		}

		T temp = *m_list.begin();
		m_list.pop_front();
		m_notFull.notify_all();
		lock.unlock();
		return temp;
	}
	auto getStdDeque() {
		return m_list;
	}
	bool empty()
	{
		TLock lock(m_mutex);
		return m_list.empty();
	}
	bool full()
	{
		if (false == hasCapacity)
		{
			return false;
		}

		TLock lock(m_mutex);
		return m_list.size() >= m_maxCapacity;
	}
	void clear() {
		TLock lock(m_mutex);
		m_list.clear();
	};
private:
	inline bool hasCapacity() const { return m_maxCapacity > 0; }
	typedef std::deque<T> TList;
	TList m_list;
	const int m_maxCapacity;
	std::mutex m_mutex;
	std::condition_variable m_notEmpty;
	std::condition_variable m_notFull;
};
