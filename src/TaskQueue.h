#ifndef TASKQUEUE_H_
#define TASKQUEUE_H_

#include <pthread.h>
#include <queue>

class TaskQueue
{
public:
	TaskQueue(void);
	virtual ~TaskQueue(void);

public:
	int Initialize(void);
	void ExecuteQueue(void);
	int AddTask(int nTask);
	void Stop(void);

private:
	pthread_cond_t		m_threadCond;
	pthread_mutex_t		m_queueMutex;
	std::queue<int>		m_taskQueue;
};

#endif /* TASKQUEUE_H_ */
