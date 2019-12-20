#pragma once
/* Copyright 2019 Andrieiev Danil */
#include <queue>
#include <string>
#include "Threadable.h"

namespace TurboPipes {
	using namespace std;

	class PipeDispatcher;

	class Pipeable : public Threadable {
	private:
		queue<byte*> messages;
	protected:
		PipeDispatcher* dispatcher;
	public:
		Pipeable();
		~Pipeable();
		void connect(PipeDispatcher* dispatcher);
		void queueMessage(byte* message);
		using Threadable::getThreadHandle;
	private:
		void threadFunction() override;
		void handler();
	public:
		virtual void handleMessage(byte* message) = 0;
	};
}
