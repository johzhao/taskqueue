#include <iostream>
#include "TaskQueue.h"

const int EndTaskQueueCommand = -1;

TaskQueue::TaskQueue(void)
{
}

TaskQueue::~TaskQueue(void)
{
	pthread_mutex_destroy(&m_queueMutex);
	pthread_cond_destroy(&m_threadCond);
}

int TaskQueue::Initialize(void)
{
	int result = 0;
	result = (result == 0) ? pthread_mutex_init(&m_queueMutex, NULL) : result;
	result = (result == 0) ? pthread_cond_init(&m_threadCond, NULL) : result;

	return result;
}

void TaskQueue::ExecuteQueue(void)
{
	while (true)
	{
		pthread_mutex_lock(&m_queueMutex);
		if (m_taskQueue.size() > 0)
		{
			int nValue = m_taskQueue.front();
			m_taskQueue.pop();
			if (nValue == EndTaskQueueCommand)
			{
				std::cout << "Receive end command from thread " << pthread_self() << std::endl;
				break;
			}
			else
			{
				std::cout << "Receive task: " << nValue << " from thread " << pthread_self() << std::endl;
			}
		}
		else
		{
			pthread_cond_wait(&m_threadCond, &m_queueMutex);
		}
		pthread_mutex_unlock(&m_queueMutex);
	}
}

int TaskQueue::AddTask(int nTask)
{
	pthread_mutex_lock(&m_queueMutex);
	m_taskQueue.push(nTask);
	std::cout << "Add task: " << nTask << " from thread " << pthread_self() << std::endl;
	if (m_taskQueue.size() == 1)
	{
		pthread_cond_signal(&m_threadCond);
	}
	pthread_mutex_unlock(&m_queueMutex);

	return 0;
}

void TaskQueue::Stop(void)
{
	AddTask(EndTaskQueueCommand);
}
