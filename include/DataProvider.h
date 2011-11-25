#ifndef DATAPROVIDER_H_
#define DATAPROVIDER_H_

//system gui stuff
#include <wx/wxprec.h>

//tewb stuff
#include "TEWBClient.h"
using namespace TEWB;

namespace WB4LinData {
	
	class DataProvider {
		public:
			DataProvider();
			~DataProvider();
			
			//the comm library
			TEWBClient *wbClient;			
			
			//control lists
			
			//various switches
			bool isConnected;
			
			//device
			wxString device;
			
			void AddGauge(wxGauge *);
	};	
}

#endif /*DATAPROVIDER_H_*/
