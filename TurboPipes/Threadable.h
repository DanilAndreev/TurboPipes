#pragma once
/* Copyright 2019 Andrieiev Danil */
#include <windows.h>
#include <process.h>

class Threadable {
private:
	bool running;
	HANDLE threadHandle;
public:
	Threadable();
	~Threadable();
	void startThread();
	void stopThread();
	HANDLE getThreadHandle();
	bool isRunning();
	virtual void threadFunction() = 0;
private:
	static unsigned int _stdcall recieveMessageThread(void* pthis);
	void threadFunctionDispathcer();
};

