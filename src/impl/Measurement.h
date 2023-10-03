#include <chrono>
#include <vector>
#include <thread>
#include <fstream>
#include <iostream>

#include <clock/ReadClock.h>
#include <clock/WriteClock.h>

namespace sbd::impl::measurement {
	class MeasurementReport : public std::vector<std::chrono::nanoseconds> {
	public:
		MeasurementReport(const std::string& filename) : filename(filename) {}
		~MeasurementReport() {
			dump();
		}
	private:
		std::string filename;
		void dump() {
			/*std::ofstream file(filename);
			if (!file.good()) {
				std::cerr << "[ERROR|MeasurementReport] cannot create file" << std::endl;
				return;
			}
			for (const auto meas : *this) {
				file << "[INFO|Measurement] " << meas.count() << "ns" << std::endl;
			}
			file.close();*/
		}
	};


	class Measurement {
	public:
		Measurement(MeasurementReport& collection) : collection(collection), start({sbd::time::getWriteClock(), sbd::time::getReadClock()}) {}
		~Measurement() {
			auto elapsed = std::chrono::steady_clock::now() - start;
			collection.push_back(elapsed);
		}
	private:
		MeasurementReport& collection;
		struct Timestamp {
			uint64_t write, read;
		};
		std::pair<uint64_t, uint64_t> start;
	};
}
