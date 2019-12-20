#pragma once
/* Copyright 2019 Andrieiev Danil */
#include <exception>


namespace TurboPipes {
	using namespace std;

	class PipeException : public exception {
		const char* what() const override { return "Error: PipeException"; }
	};

	class PipeCreationException : public PipeException {
		const char* what() const override { return "Error: PipeCreationException"; }
	};

	class PipeConnectionException : public PipeException {
		const char* what() const override { return "Error: PipeConnectionException"; }
	};

	class PipeWritingException : public PipeException {
		const char* what() const override { return "Error: PipeWritingException"; }
	};

	class PipeNoDataException : public PipeConnectionException {
		const char* what() const override { return "Error: PipeNoDataException"; }
	};

	class PipeConnectedException : public PipeConnectionException {
		const char* what() const override { return "Error: PipeConnectedException"; }
	};

	class PipeListeningException : public PipeConnectionException {
		const char* what() const override { return "Error: PipeListeningException"; }
	};

	class PipeCallNotImplementedException : public PipeConnectionException {
		const char* what() const override { return "Error: PipeCallNotImplementedException"; }
	};

	class PipeReadingException : public PipeConnectionException {
		const char* what() const override { return "Error: PipeReadingException"; }
	};

	class PipeLostConnectionException : public PipeConnectionException {
		const char* what() const override { return "Error: PipeLostConnectionException"; }
	};
}
