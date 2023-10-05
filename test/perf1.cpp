#include <gtest/gtest.h>

#include <time/Measurement.h>
#include <sorting/runsort.h>
#include <impl/CarLoader.h>

using namespace sbd::time;
using namespace sbd::sorting;
using namespace sbd::impl;

TEST(Perf1, testCase1){

    runSort(*sbd::impl::carloader::fromGenerator(100), std::cout);
    runSort(*sbd::impl::carloader::fromGenerator(1000), std::cout);
}