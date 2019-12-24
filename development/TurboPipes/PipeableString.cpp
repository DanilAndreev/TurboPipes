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
   version 1.1.3
*/
#include "PipeableString.h"


namespace TurboPipes {
	PipeableString::PipeableString() {
		this->dispatcher = nullptr;
	}


	PipeableString::~PipeableString() {
		this->dispatcher = nullptr;
	}

	void PipeableString::connect(PipeDispatcherString* dispatcher) {
		this->dispatcher = dispatcher;
	}

	void PipeableString::queueMessage(wstring message) {
		byte* byte_message = new byte[(message.length() + 1) * sizeof(wchar_t)];
		Pipeable::queueMessage(byte_message);
	}


	void PipeableString::handleMessage(byte* message) {
		wstring string_message = reinterpret_cast<wchar_t*>(message);
		this->handleMessage(string_message);
	}
}
