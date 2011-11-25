#ifndef WBGAUGE_H_
#define WBGAUGE_H_

#include <wx/wxprec.h>

namespace WB4LinGUI {
	
	class wbGauge : public wxWindow {
		public:
			wbGauge(wxWindow *, int limit = 200);
			~wbGauge();
			
			wxStaticText *myLabel;
			wxStaticText *minLabel;
			wxStaticText *maxLabel;
			wxGauge *gauge;
			
			int limit;
			unsigned type;
			
			void SetValue( double value );
			
			void OnContextMenu(wxContextMenuEvent &event);
			void OnRemoveMe(wxCommandEvent &event);
			void OnConfigMe(wxCommandEvent &event);
			void Configure();
		
		DECLARE_EVENT_TABLE()
	};
	
}

#endif /*WBGAUGE_H_*/
