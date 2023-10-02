#include <generic/RecordIfc.h>
#include <generic/Tape.h>
#include "sorting/mergesort.h"
#include <impl/CarRecord.h>
#include <impl/CarTape.h>

using namespace sbd;

class IntRecord : public basic::RecordIfc<int> {
public:
	IntRecord() : RecordIfc(std::numeric_limits<int>::min()) {};
};

int main(){
	impl::CarTape tape("chuj");
	tape.addRecord(impl::CarRecord("ABI"));
	tape.addRecord(impl::CarRecord("CHYYY"));
	tape.addRecord(impl::CarRecord("XDD"));
	tape.addRecord(impl::CarRecord("POGG"));
	tape.addRecord(impl::CarRecord("UWU"));
	tape.addRecord(impl::CarRecord("KIWI"));
	tape.addRecord(impl::CarRecord("POMELO"));
	tape.addRecord(impl::CarRecord("GRANAT"));
	tape.addRecord(impl::CarRecord("GRUSZKA"));
	tape.addRecord(impl::CarRecord("JAPKO"));
	tape.addRecord(impl::CarRecord("JABLKO"));
	tape.addRecord(impl::CarRecord("DYNIA"));

	/*basic::Tape<IntRecord> tape("chuj");
	tape.addRecord(IntRecord(3));
	tape.addRecord(IntRecord(2));
	tape.addRecord(IntRecord(7));
	tape.addRecord(IntRecord(10));
	tape.addRecord(IntRecord(1));
	tape.addRecord(IntRecord(1));*/

	sorting::mergesort(tape);
}
