#include <gtest/gtest.h>

#include <time/Measurement.h>
#include <sorting/runsort.h>
#include <impl/CarLoader.h>
#include <cmath>

using namespace sbd::time;
using namespace sbd::sorting;
using namespace sbd::impl;

inline void theoretical(uint64_t n){
    std::cout << "[Theoretical] i/o: "
    << 4 * n * static_cast<uint64_t>(ceil(log2(n)-1u)) * constants::RECORD_SIZE / constants::PAGE_SIZE
    << std::endl;
}

TEST(Perf1, testCase1){
    static constexpr auto records = {10, 100, 1000, 10000, 100000};
    std::srand(std::time(nullptr));
    for(const auto n : records){
        std::cout << "OoOoOoOoOoOoOo " << n << " RECORDS oOoOoOoOoOoOoO" << std::endl;
        theoretical(n);
        runSort(*sbd::impl::carloader::fromGenerator(n), std::cout);
    }
}