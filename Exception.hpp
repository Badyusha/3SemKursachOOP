#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include "Libraries.hpp"

template<typename T>
class BadAllocException : std::bad_alloc {
	std::shared_ptr<T> exception;
public:
	BadAllocException() {}
	BadAllocException(T exception) : std::bad_alloc() {
		this->exception = std::make_shared<T>(exception);
	}

	T getException() const { return *this->exception.get(); }
};

#endif