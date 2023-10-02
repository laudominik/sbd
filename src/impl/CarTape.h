#pragma once

#include <generic/Tape.h>
#include <impl/CarRecord.h>

namespace sbd::impl {
	using CarTape = sbd::basic::Tape<sbd::impl::CarRecord>;
}
