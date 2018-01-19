#include "Timer.h"

template <typename T>
Timer<T>::Timer()
{
	for (int i = 0; i < 4; ++i) {
		m_Timers.push_back(nullptr);
	}

	head = m_Timers.begin();
	size = 0;
	limit = 4;
	
}

template <typename T>
Timer<T>::~Timer()
{
}

template <typename T>
void Timer<T>::CreateTimer(double duration, CallBack<T> func, bool repeat)
{
	if (size == limit) {
		// resize vector
		m_Timers.resize(m_Timers.size() + 4);
		head = m_Timers.begin() + limit;
		limit += 4;
	}
	if (head != m_Timers.end()) // vector not full
	{
		while (*head != nullptr) { // is used move on
			++head;
			if (head == m_Timers.end()) {
				// hit the end
				head = m_Timers.begin();
				CreateTimer(duration, func, repeat);
			}
		}

		//empty slot found
		size_t pos = head - m_Timers.begin();
		*head = new CountDownTimer<T>(pos, duration, func);
		++head;
		++size;
	}
}

template <typename T>
void Timer<T>::Update()
{
}
