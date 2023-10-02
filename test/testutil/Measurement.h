#include <chrono>
#include <vector>
#include <thread>
#include <fstream>
#include <iostream>

using namespace std::chrono_literals;

class MeasurementReport : public std::vector<std::chrono::nanoseconds> {
public:
	MeasurementReport(const std::string& filename) : filename(filename) {}
	~MeasurementReport() {
		dump();
	}
private:
	std::string filename;
	void dump() {
		std::ofstream file(filename);
		if (!file.good()) {
			std::cerr << "[ERROR|MeasurementReport] cannot create file" << std::endl;
			return;
		}
		for (const auto meas : *this) {
			file << "[INFO|Measurement] " << meas.count() << "ns" << std::endl;
		}
		file.close();
	}
};


class Measurement {
public:
	Measurement(MeasurementReport& collection) : collection(collection), start(std::chrono::steady_clock::now()) {}
	~Measurement() {
		auto elapsed = std::chrono::steady_clock::now() - start;
		collection.push_back(elapsed);
	}
private:
	MeasurementReport& collection;
	std::chrono::steady_clock::time_point start;
};

int main() {
	MeasurementReport report("measures1.log");

	{
		Measurement meas(report);
		std::this_thread::sleep_for(1000ms);
	}

	{
		Measurement meas(report);
		std::this_thread::sleep_for(500ms);
	}
}
