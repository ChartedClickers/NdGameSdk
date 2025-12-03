#pragma once

#include <exception>
#include <string>

class NdModClientException : public std::runtime_error {
public:
	NdModClientException(const std::string& msg) : std::runtime_error(msg) {}
};