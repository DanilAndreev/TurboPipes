/*
   Pipeable.cpp, PipeableString.cpp PipeDispatcher.cpp, PipeDispatcherString.cpp Threadable.cpp
   Pipeable.h PipeableString.h PipeDispatcher.h PipeDispatcherString.h PipesException.h Threadable.h TurboPipes.h
   Copyright (C) 2019 Andrieiev Danil
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.
   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:
   1. The origin of this source code must not be misrepresented; you must not
	  claim that you wrote the original source code. If you use this source code
	  in a product, an acknowledgment in the product documentation would be
	  appreciated but is not required.
   2. Altered source versions must be plainly marked as such, and must not be
	  misrepresented as being the original source code.
   3. This notice may not be removed or altered from any source distribution.
   Andrieiev Danil danssg08@gmail.com
   version 1.1.2
*/
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
