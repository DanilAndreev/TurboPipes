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
