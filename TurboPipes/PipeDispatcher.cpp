#include "PipeDispatcher.h"

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
			1024, 
			1024,
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
		this->hNamedPipe = CreateFile(
			this->pipeName.c_str(),
			GENERIC_READ | GENERIC_WRITE,
			0, 
			NULL, 
			OPEN_EXISTING, 
			0, 
			NULL);
		if (this->hNamedPipe == INVALID_HANDLE_VALUE) {
			throw PipeConnectionException();
		}
	}
}

PipeDispatcher::~PipeDispatcher() {
	this->object->connect(nullptr);
	CloseHandle(this->hNamedPipe);
}

void PipeDispatcher::throwMessage(wstring message) {
	BOOL isWritten = WriteFile(hNamedPipe, message.c_str(), message.length() + 1, &cbWritten, NULL);
	if (!isWritten) {
		throw PipeWritingException();
	}
}

wstring PipeDispatcher::catchMessage() {
	//wchar_t buff[1024];
	wstring buffer;

	DWORD bytesAvail = 0;
	DWORD bytesMessage = 0;

	while (!bytesAvail) {
		PeekNamedPipe(hNamedPipe, NULL, 0, NULL, &bytesAvail, &bytesMessage);
		if (bytesAvail) {
			byte* data = new byte[bytesAvail];
			BOOL isRead = ReadFile(hNamedPipe, data, bytesAvail, &cbRead, NULL);
			if (!isRead) {
				throw PipeReadingException();
			}
			//buffer = reinterpret_cast<wchar_t*>(data);
			wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
			buffer = converter.from_bytes((char*)data);
			delete[] data;
			return buffer;
		}
		else {
			Sleep(10);
		}
	}
	return buffer;
}

void PipeDispatcher::messagesHandler() {
	while (this->isRunning()) {
		try {
			wstring message = this->catchMessage();
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
