#pragma once
/* Copyright 2019 Andrieiev Danil */
#include <windows.h>
#include <string>
#include "Pipeable.h"
#include "Threadable.h"
#include "PipesExceptions.h"
#include <codecvt>


#include <iostream>

using namespace std;

class PipeDispatcher : public Threadable{
private:
	static const DWORD TIMEOUT = 5000;
private:
	HANDLE hNamedPipe;
	DWORD cbWritten;
	DWORD cbRead;
	wstring szBuf;
	wstring pipeName;

	bool is_server;
protected:
	Pipeable* object;
public:
	PipeDispatcher(wstring szPipeName, bool is_server, Pipeable* object);
	~PipeDispatcher();
	void throwMessage(wstring message);
protected:
	wstring catchMessage();
	void messagesHandler();
	void threadFunction() override;
};
