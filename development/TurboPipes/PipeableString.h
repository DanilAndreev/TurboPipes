#pragma once
#include "Pipeable.h"

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
public:
	virtual void handleMessage(wstring& message) = 0;
private:
	void handleMessage(byte* message) override;
};

