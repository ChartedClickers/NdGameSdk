#pragma once

#include <exception>
#include <string>

class NdRuntimeClientException : public std::runtime_error {
public:
	NdRuntimeClientException(const std::string& msg) : std::runtime_error(msg) {}
};