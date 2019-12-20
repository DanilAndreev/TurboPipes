#include "Pipeable.h"

namespace TurboPipes {
	Pipeable::Pipeable() : Threadable() {
		this->dispatcher = nullptr;
	}

	Pipeable::~Pipeable() {}

	void Pipeable::connect(PipeDispatcher* dispatcher) {
		this->dispatcher = dispatcher;
	}

	void Pipeable::queueMessage(byte* message) {
		this->messages.push(message);
	}

	void Pipeable::threadFunction() {
		this->handler();
	}

	void Pipeable::handler() {
		while (this->isRunning()) {
			if (this->messages.empty() || !this->dispatcher) {
				Sleep(10);
			}
			else {
				byte* message = this->messages.back();
				this->messages.pop();
				this->handleMessage(message);
			}
		}
	}
}
