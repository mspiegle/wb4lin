//gui stuff
#include <wx/wxprec.h>

//common stuff
#include "Common.h"

//my header
#include "ConnectDialog.h"

//std stuff
#include <list>
#include <string>
using namespace std;

//utility stuff
#include "Utility.h"
using namespace Utility;

namespace WB4LinGUI {
	
	BEGIN_EVENT_TABLE(ConnectDialog, wxDialog)
		EVT_BUTTON(ID_ConnectOkButton, ConnectDialog::OnOkButton)
		EVT_TEXT_ENTER(ID_ConnectOkButton, ConnectDialog::OnOkButton)
		EVT_BUTTON(ID_ConnectCancelButton, ConnectDialog::OnCancelButton)
		EVT_BUTTON(ID_FindSerialsButton, ConnectDialog::OnFindSerialsButton)
	END_EVENT_TABLE()
	
	ConnectDialog::ConnectDialog(const wxString& title, const wxPoint& pos, const wxSize& size, long style = wxDEFAULT_DIALOG_STYLE) : wxDialog((wxWindow *)NULL, -1, title, pos, size, style) {
		
		//make the sizers
		wxBoxSizer *masterSizer = new wxBoxSizer( wxVERTICAL );
		wxBoxSizer *topSizer = new wxBoxSizer( wxHORIZONTAL );
		wxBoxSizer *midSizer = new wxBoxSizer( wxHORIZONTAL );
		wxBoxSizer *bottomSizer = new wxBoxSizer ( wxHORIZONTAL );
		
		//make the controls
		//combobox
		wxSize comSize = wxDefaultSize;
		comSize.SetWidth(125);
		this->comMenu = new wxComboBox(this, ID_ConnectOkButton, wxEmptyString, wxDefaultPosition, comSize, 0, NULL, wxCB_DROPDOWN );
		//buttons
		wxButton *okButton = new wxButton(this, ID_ConnectOkButton, wxT("Ok"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
		wxButton *findSerialsButton = new wxButton(this, ID_FindSerialsButton, wxT("Find Serials"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
		wxButton *cancelButton = new wxButton(this, ID_ConnectCancelButton, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
		
		//add the controls to the various sizers
		//master
		masterSizer->Add(topSizer, wxSizerFlags().Border(wxALL, 7));
		masterSizer->Add(midSizer, wxSizerFlags().Border(wxLEFT | wxRIGHT, 7));
		masterSizer->Add(bottomSizer, wxSizerFlags().Align(wxALIGN_RIGHT | wxALIGN_BOTTOM).Border(wxALL, 7));
		
		//top
		topSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Serial Port:")), wxSizerFlags().Align(wxALIGN_LEFT));
		
		//middle
		midSizer->Add(findSerialsButton);
		midSizer->Add(this->comMenu);
		
		//bottom
		bottomSizer->Add(okButton);
		bottomSizer->Add(cancelButton);
		
		//set the master sizer
		SetSizer(masterSizer);
		masterSizer->SetSizeHints(this);
		
	}
	
	ConnectDialog::~ConnectDialog() {
	}
	
	void ConnectDialog::OnCancelButton(wxCommandEvent& WXUNUSED(event)) {
	    EndModal(0);
	}
	
	void ConnectDialog::OnOkButton(wxCommandEvent& WXUNUSED(event)) {
		//TODO: Something to save options...
	    EndModal(0);
	}
	
	void ConnectDialog::OnFindSerialsButton(wxCommandEvent& WXUNUSED(event)) {
		//Do something to get the list of serial ports...
		//TODO: There's probably a cleaner/faster way to do this
		list<string> serialList = Utility::SerialUtility::GetSerials();
		wxArrayString serialArray;
		
		list<string>::const_iterator i;
		for ( i = serialList.begin(); i != serialList.end(); i++ ) {
			wxString *temp = new wxString(i->c_str(), wxConvUTF8);
			serialArray.Add( *temp );
			delete temp;
		}
		
		//assign the items to the box
		this->comMenu->Append(serialArray);
	}
	
}
