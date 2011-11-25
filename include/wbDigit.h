#ifndef WBDIGIT_H_
#define WBDIGIT_H_

#include <wx/wxprec.h>

namespace WB4LinGUI {
	
	class wbDigit : public wxWindow {
		public:
			wbDigit(wxWindow *parent);
			~wbDigit();
			
			//wxStaticText *text;
			
			void SetValue( double value );
			
			void OnContextMenu(wxContextMenuEvent &event);
			void OnRemoveMe(wxCommandEvent &event);
			void OnConfigMe(wxCommandEvent &event);
			void Configure();
			
			void OnPaint(wxPaintEvent &event);
		
		DECLARE_EVENT_TABLE()
	};
	
}

#endif /*WBDIGIT_H_*/
