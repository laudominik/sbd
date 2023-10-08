#pragma once

#include <iostream>

#include <time/Measurement.h>
#include <impl/CarTape.h>
#include <sorting/mergesort.h>
#include <util/FilePrinter.h>


namespace sbd::sorting {
    inline void runSort(std::unique_ptr<impl::CarTape>& tape, std::ostream& out) {
        time::Measurement meas(out);
        mergesort(*tape);
        tape.reset();
        if(util::Config::instance().isDebugModeEnabled()){
            util::fileprinter::print(constants::MAIN_TAPE_NAME);
        }
    }
}

