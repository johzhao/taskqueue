#include <cstdlib>
#include <iostream>
#include "TaskQueue.h"

void* WorkThread(void* pUserData)
{
	TaskQueue* taskQueue = static_cast<TaskQueue*>(pUserData);
	for (int i=0; i<100; ++i)
	{
		taskQueue->AddTask(i);
	}
	taskQueue->AddTask(-1);
	return NULL;
}

int main(int argc, char *argv[])
{
	TaskQueue* taskQueue = new TaskQueue();
	taskQueue->Initialize();

	pthread_t thread;
	pthread_create(&thread, NULL, WorkThread, taskQueue);

	taskQueue->ExecuteQueue();

	pthread_join(thread, NULL);
	delete taskQueue;

	return EXIT_SUCCESS;
}
