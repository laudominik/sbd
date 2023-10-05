#pragma once

#include <time/Measurement.h>
#include <impl/CarTape.h>
#include <sorting/mergesort.h>
#include <iostream>

namespace sbd::sorting {
    inline void runSort(impl::CarTape& tape, std::ostream& out) {
        time::Measurement meas(out);
        mergesort(tape);
    }
}

