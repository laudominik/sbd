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
    << " phases: " << ceil(log2(n)-1u)
    << std::endl;
}

TEST(Perf1, testCase1){
    static constexpr auto records = {10, 100, 1000, 5000, 10000, 25000, 50000, 100000, 200000};
    std::srand(std::time(nullptr));
    std::cout << "b = " << constants::PAGE_SIZE / constants::RECORD_SIZE << std::endl;
    for(const auto n : records){
        std::cout << "OoOoOoOoOoOoOo " << n << " RECORDS oOoOoOoOoOoOoO" << std::endl;
        theoretical(n);
        runSort(*sbd::impl::carloader::fromGenerator(n), std::cout);
    }
}