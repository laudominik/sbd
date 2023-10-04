#pragma once

#include <impl/CarTape.h>

namespace sbd::impl {
	class CarLoader {
		void fromFile(std::string filename);
		void fromCli();
		void fromGenerator();
	};
}

