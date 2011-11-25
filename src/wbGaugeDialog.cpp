//wx gui
#include <wx/wxprec.h>

//common
#include "Common.h"

//my header
#include "wbGaugeDialog.h"

namespace WB4LinGUI {
	
	BEGIN_EVENT_TABLE(wbGaugeDialog, wxDialog)
			EVT_BUTTON(ID_GaugeDialogOk, wbGaugeDialog::OnOkButton)
			EVT_TEXT_ENTER(ID_GaugeDialogOk, wbGaugeDialog::OnOkButton)
			EVT_BUTTON(ID_GaugeDialogCancel, wbGaugeDialog::OnCancelButton)
	END_EVENT_TABLE()
	
	wbGaugeDialog::wbGaugeDialog(const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE)
	: wxDialog((wxWindow *)NULL, -1, title, pos, size, style) {
		//master sizer
		wxBoxSizer *masterSizer = new wxBoxSizer( wxVERTICAL );
		
		//data type
		wxStaticText *typeLabel = new wxStaticText( this, wxID_ANY, wxT("Select Gauge Type:") );
		typeBox = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
		typeBox->Append( wxT("Wideband A/F Ratio"), (void *)TEWB_AFR_IPX);
		typeBox->Append( wxT("User Input 1"), (void *)TEWB_U1);
		typeBox->Append( wxT("User Input 2"), (void *)TEWB_U2);
		typeBox->Append( wxT("User Input 3"), (void *)TEWB_U3);
		typeBox->Append( wxT("Thermocouple 1"), (void *)TEWB_T1);
		typeBox->Append( wxT("Thermocouple 2"), (void *)TEWB_T2);
		typeBox->Append( wxT("Thermocouple 3"), (void *)TEWB_T3);
		typeBox->Append( wxT("RPM"), (void *)TEWB_RPM);
		
		//ok button
		wxButton *okButton = new wxButton( this, ID_GaugeDialogOk, wxT("Ok") );
		wxButton *cancelButton = new wxButton( this, ID_GaugeDialogCancel, wxT("Cancel") );
		
		//lay it out
		masterSizer->Add(typeLabel);
		masterSizer->Add(typeBox);
		masterSizer->Add(okButton);
		masterSizer->Add(cancelButton);
		
		//default = cancel
		isOk = false;
		
		SetSizerAndFit(masterSizer);
	}
	
	wbGaugeDialog::~wbGaugeDialog() {
	}
	
	void wbGaugeDialog::OnOkButton( wxCommandEvent &event ) {
		isOk = true;
		EndModal(0);
	}
	
	void wbGaugeDialog::OnCancelButton( wxCommandEvent &event ) {
		isOk = false;
		EndModal(0);
	}
	
}
