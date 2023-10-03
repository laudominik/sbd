#pragma once

#include "Clock.h"

namespace sbd::time {
	Clock& getWriteClock() {
		static Clock clock;
		return clock;
	}
}