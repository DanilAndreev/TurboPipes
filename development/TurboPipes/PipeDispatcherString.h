#pragma once
#include "PipeDispatcher.h"
#include "PipeableString.h"


namespace TurboPipes {
	class PipeDispatcherString : private PipeDispatcher {
	public:
		PipeDispatcherString(wstring szPipeName, bool is_server, PipeableString* object);
		~PipeDispatcherString();
		void throwMessage(wstring& message);
		using Threadable::getThreadHandle;
	protected:
		wstring catchMessage();
	protected:
		PipeDispatcherString(const PipeDispatcherString& reference) : PipeDispatcher(reference) {}
		PipeDispatcherString& operator= (const PipeDispatcherString& reference) {}
	};
}
