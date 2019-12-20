#pragma once
/* Copyright 2019 Andrieiev Danil */
#include <queue>
#include <string>
#include "Threadable.h"

using namespace std;

class PipeDispatcher;

class Pipeable : private Threadable{
private:
	queue<byte*> messages;
protected:
	PipeDispatcher* dispatcher;
public:
	Pipeable();
	~Pipeable();
	void connect(PipeDispatcher* dispatcher);
	void queueMessage(byte* message);
private:
	void threadFunction() override;
	void handler();
public:
	virtual void handleMessage(byte* message) = 0;
};
