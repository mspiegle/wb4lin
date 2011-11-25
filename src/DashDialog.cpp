#include <wx/wxprec.h>

#include "DashDialog.h"
#include "Common.h"

namespace WB4LinGUI {

	BEGIN_EVENT_TABLE(DashDialog, wxDialog)
			EVT_BUTTON(ID_TestButton, DashDialog::OnTestButton)
	END_EVENT_TABLE()
	
	DashDialog::DashDialog(const wxString& title, const wxPoint& pos, const wxSize& size, long style = wxDEFAULT_DIALOG_STYLE) : wxDialog((wxWindow *)NULL, -1, title, pos, size, style) {
		wxButton *button = new wxButton(this, ID_TestButton, wxT("Button"));
	}
	
	DashDialog::~DashDialog() {
	}
	
	void DashDialog::OnTestButton(wxCommandEvent& WXUNUSED(event)) {
		EndModal(0);
	}
	
}
