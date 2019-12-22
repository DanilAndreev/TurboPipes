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
#include "PipeDispatcher.h"

const int TIMEOUT_CONNECT_ATTEMPTS = 30;
const size_t CONNECTING_SLEEP_TIME = 100;

namespace TurboPipes {
	PipeDispatcher::PipeDispatcher(wstring szPipeName, bool is_server, Pipeable* object) : pipeName(szPipeName), object(object) {
		this->object->connect(this);
		this->cbWritten = 0;
		this->cbRead = 0;
		this->hNamedPipe = INVALID_HANDLE_VALUE;

		this->is_server = is_server;
		if (this->is_server) {
			this->hNamedPipe = CreateNamedPipe(
				this->pipeName.c_str(),
				PIPE_ACCESS_DUPLEX,
				PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
				PIPE_UNLIMITED_INSTANCES,
				BUFFER_SIZE,
				BUFFER_SIZE,
				TIMEOUT,
				NULL);
			if (this->hNamedPipe == INVALID_HANDLE_VALUE) {
				throw PipeCreationException();
			}
			BOOL fConnected = ConnectNamedPipe(hNamedPipe, NULL);
			if (!fConnected) {
				switch (GetLastError()) {
				case ERROR_NO_DATA:
					CloseHandle(hNamedPipe);
					throw PipeNoDataException();
					break;

				case ERROR_PIPE_CONNECTED:
					CloseHandle(hNamedPipe);
					throw PipeConnectedException();
					break;

				case ERROR_PIPE_LISTENING:
					CloseHandle(hNamedPipe);
					throw PipeListeningException();
					break;

				case ERROR_CALL_NOT_IMPLEMENTED:
					CloseHandle(hNamedPipe);
					throw PipeCallNotImplementedException();
					break;

				default:
					CloseHandle(hNamedPipe);
					throw PipeException();
					break;
				}
				CloseHandle(hNamedPipe);
			}
		}
		else {
			int attempts = 0;
			bool connecting_flag = true;
			while (attempts <= TIMEOUT_CONNECT_ATTEMPTS + 1 && connecting_flag) {
				this->hNamedPipe = CreateFile(
					this->pipeName.c_str(),
					GENERIC_READ | GENERIC_WRITE,
					0,
					NULL,
					OPEN_EXISTING,
					0,
					NULL);
				if (this->hNamedPipe == INVALID_HANDLE_VALUE && attempts >= TIMEOUT_CONNECT_ATTEMPTS) {
					throw PipeConnectionException();
				}
				if (this->hNamedPipe != INVALID_HANDLE_VALUE) {
					connecting_flag = false;
				}
			}
		}
	}

	PipeDispatcher::~PipeDispatcher() {
		this->object->connect(nullptr);
		CloseHandle(this->hNamedPipe);
	}

	void PipeDispatcher::throwMessage(byte* message, DWORD length) {
		BOOL isWritten = WriteFile(hNamedPipe, message, length, &cbWritten, NULL);
		if (!isWritten) {
			throw PipeWritingException();
		}
	}

	byte* PipeDispatcher::catchMessage() {
		DWORD bytesAvail = 0;
		DWORD bytesMessage = 0;
		byte* message = nullptr;

		while (!bytesAvail) {
			PeekNamedPipe(hNamedPipe, NULL, 0, NULL, &bytesAvail, &bytesMessage);
			if (bytesAvail) {
				message = new byte[bytesAvail];
				BOOL isRead = ReadFile(hNamedPipe, message, bytesAvail, &cbRead, NULL);
				if (!isRead) {
					throw PipeReadingException();
				}
				return message;
			}
			else {
				Sleep(10);
			}
		}
		return message;
	}

	void PipeDispatcher::messagesHandler() {
		while (this->isRunning()) {
			try {
				byte* message = this->catchMessage();
				this->object->queueMessage(message);
			}
			catch (PipeReadingException e) {
				throw PipeLostConnectionException();
			}
		}
	}

	void PipeDispatcher::threadFunction() {
		this->messagesHandler();
	}
}
