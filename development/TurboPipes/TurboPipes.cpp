#include <windows.h>

#include <iostream>
#include "TurboPipes.h"

class TPipeableString : public PipeableString {
	void handleMessage(wstring& message) override {
		wcout << "recieved message: " << message << endl;
		this->dispatcher->throwMessage(message);
	}
};


using namespace std;

const LPCWSTR PIPE_NAME = L"\\\\.\\pipe\\$MyPipe$";


int main() {
	TPipeableString p;
	wcout << "waiting for a client: " << endl;
	PipeDispatcherString dispatcher(PIPE_NAME, true, &p);
	wcout << "connected" << endl;

	WaitForSingleObject(p.getThreadHandle(), INFINITE);
}