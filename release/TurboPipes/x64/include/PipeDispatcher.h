#pragma once
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
#include <windows.h>
#include <string>
#include "Pipeable.h"
#include "Threadable.h"
#include "PipesExceptions.h"
#include <codecvt>


#include <iostream>

namespace TurboPipes {
	using namespace std;

	class PipeDispatcher : public Threadable {
	private:
		static const DWORD TIMEOUT = 5000;
		static const DWORD BUFFER_SIZE = 1024;
	private:
		HANDLE hNamedPipe;
		DWORD cbWritten;
		DWORD cbRead;
		wstring szBuf;
		wstring pipeName;

		bool is_server;
	protected:
		Pipeable* object;
	public:
		PipeDispatcher(wstring szPipeName, bool is_server, Pipeable* object);
		~PipeDispatcher();
		void throwMessage(byte* message, DWORD length);
	protected:
		byte* catchMessage();
		void messagesHandler();
		void threadFunction() override;
	protected:  // copying restricted
		PipeDispatcher(const PipeDispatcher& reference) {}
		PipeDispatcher& operator= (const PipeDispatcher& reference) {}
	};
}
