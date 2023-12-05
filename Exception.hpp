#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include "Libraries.hpp"

template<typename T>
class BadAllocException : std::bad_alloc {
	std::shared_ptr<T> exception;
	static inline int errorsCount = 0;
public:
	BadAllocException() {
		++errorsCount;
	}

	BadAllocException(T exception) : std::bad_alloc() {
		++errorsCount;
		this->exception = std::make_shared<T>(exception);
	}

	T getException() const { return *this->exception.get(); }
};

#endif