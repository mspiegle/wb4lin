#ifndef WBGAUGEDIALOG_H_
#define WBGAUGEDIALOG_H_

#include <wx/wxprec.h>

/*
enum {
	ID_GaugeDialogOk = wxID_HIGHEST + 1,
	ID_GaugeDialogCancel
};
*/

namespace WB4LinGUI {
	
	class wbGaugeDialog : public wxDialog {
		
		public:
			wbGaugeDialog(const wxString& title, const wxPoint& pos, const wxSize& size, long style);
			~wbGaugeDialog();
			
			wxComboBox *typeBox;
			bool isOk;
			
			void OnOkButton( wxCommandEvent &event );
			void OnCancelButton( wxCommandEvent &event );
			
		DECLARE_EVENT_TABLE()
	};
	
}

#endif /*WBGAUGEDIALOG_H_*/
