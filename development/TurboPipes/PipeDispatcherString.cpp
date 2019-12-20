#include "PipeDispatcherString.h"



PipeDispatcherString::PipeDispatcherString(wstring szPipeName, bool is_server, PipeableString* object) : PipeDispatcher(szPipeName, is_server, (Pipeable*)object) {}

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
