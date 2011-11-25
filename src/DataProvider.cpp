//system gui stuff
#include <wx/wxprec.h>
#include <list>
using namespace std;

//data provider stuff
#include "DataProvider.h"

//tewb stuff
#include "TEWBClient.h"
using namespace TEWB;

namespace WB4LinData {
	
	DataProvider::DataProvider() {
		
		//gaugeList = new list<wxGauge *>;
	}
	
	DataProvider::~DataProvider() {
		
		//delete gaugeList;
	}
	
	void DataProvider::AddGauge(wxGauge *gauge) {
		//gaugeList->push_front(gauge);parent
	}
	
}
