#ifndef DASHDIALOG_H_
#define DASHDIALOG_H_

/*
enum {
	ID_TestButton = wxID_HIGHEST + 1
};
*/

namespace WB4LinGUI {
	
	class DashDialog : public wxDialog {
		
		public:
			DashDialog(const wxString& title, const wxPoint& pos, const wxSize& size, long style);
			~DashDialog();
			
			void OnTestButton(wxCommandEvent& event);
			
			DECLARE_EVENT_TABLE()
	};
	
}

#endif /*DASHDIALOG_H_*/
