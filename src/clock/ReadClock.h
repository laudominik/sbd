#pragma once

#include "Clock.h"

namespace sbd::time {
	Clock& getReadClock() {
		static Clock clock;
		return clock;
	}
}