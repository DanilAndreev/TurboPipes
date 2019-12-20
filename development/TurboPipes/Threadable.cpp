#include "Threadable.h"

namespace TurboPipes {
	Threadable::Threadable() {
		this->running = false;
		this->threadHandle = INVALID_HANDLE_VALUE;
		this->startThread();
	}

	Threadable::~Threadable() {
		this->running = false;
	}

	void Threadable::startThread() {
		this->running = true;
		this->threadHandle = (HANDLE)_beginthreadex(0, 0, &Threadable::recieveMessageThread, this, 0, 0);
	}

	void Threadable::stopThread() {
		this->running = 0;
	}

	HANDLE Threadable::getThreadHandle() {
		return this->threadHandle;
	}

	bool Threadable::isRunning() {
		return this->running;
	}

	unsigned int _stdcall Threadable::recieveMessageThread(void* pthis) {
		Threadable* pThreadable = static_cast<Threadable*>(pthis);
		pThreadable->threadFunction();
		delete pThreadable;
		return 0;
	}

	void Threadable::threadFunctionDispathcer() {
		this->threadFunction();
		_endthreadex(0);
		CloseHandle(threadHandle);
	}
}
