#pragma once
#include "Pipeable.h"

namespace TurboPipes {
	class PipeDispatcherString;

	class PipeableString : private Pipeable {
	protected:
		PipeDispatcherString* dispatcher;
	public:
		PipeableString();
		~PipeableString();
		void connect(PipeDispatcherString* dispatcher);
		void queueMessage(wstring message);
		using Pipeable::queueMessage;
		using Pipeable::getThreadHandle;
	public:
		virtual void handleMessage(wstring& message) = 0;
	private:
		void handleMessage(byte* message) override;
	};
}
