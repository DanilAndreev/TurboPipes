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
#include "PipeDispatcherString.h"


namespace TurboPipes {
	PipeDispatcherString::PipeDispatcherString(wstring szPipeName, bool is_server, PipeableString* object) : PipeDispatcher(szPipeName, is_server, (Pipeable*)object) {
		object->connect(this);
	}

	PipeDispatcherString::~PipeDispatcherString() {}

	void PipeDispatcherString::throwMessage(wstring& message) {
		PipeDispatcher::throwMessage((byte*)message.c_str(), (message.length() + 1) * sizeof(wchar_t));
	}

	wstring PipeDispatcherString::catchMessage() {
		byte* byte_massage = PipeDispatcher::catchMessage();
		wstring string_message((wchar_t*)byte_massage);
		delete[] byte_massage;
		return string_message;
	}
}
