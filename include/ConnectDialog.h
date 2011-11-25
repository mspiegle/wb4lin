#ifndef CONNECTDIALOG_H_
#define CONNECTDIALOG_H_

#include <wx/wxprec.h>

namespace WB4LinGUI {
	
	class ConnectDialog : public wxDialog {
	    public:
	    	//frame
	    	ConnectDialog(const wxString& title, const wxPoint& pos, const wxSize& size, long style);
	    	~ConnectDialog();
	    	
	    	void OnOkButton(wxCommandEvent& event);
	    	void OnCancelButton(wxCommandEvent& event);
	    	void OnFindSerialsButton(wxCommandEvent& event);
	    	
			wxComboBox *comMenu;
	    	
	    	DECLARE_EVENT_TABLE()
	};
}

#endif /*CONNECTDIALOG_H_*/
