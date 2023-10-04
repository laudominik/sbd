#pragma once

#include <memory>

#include <impl/CarTape.h>

namespace sbd::impl::carloader {
	std::unique_ptr<CarTape> fromFile(const std::string& filename);
	std::unique_ptr<CarTape> fromCli();
	std::unique_ptr<CarTape> fromGenerator(uint64_t n);
}

