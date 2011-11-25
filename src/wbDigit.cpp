//wx gui
#include <wx/wxprec.h>

//common
#include "Common.h"

//my header
#include "wbDigit.h"

//my dialog
//#include "wbDigitDialog.h"

#include "stdio.h"

namespace WB4LinGUI {
	
	BEGIN_EVENT_TABLE(wbDigit, wxWindow)
		EVT_CONTEXT_MENU(wbDigit::OnContextMenu)		
		EVT_MENU(ID_DigitMenuRemove, wbDigit::OnRemoveMe)
		EVT_MENU(ID_DigitMenuConfig, wbDigit::OnConfigMe)
		EVT_PAINT(wbDigit::OnPaint)
	END_EVENT_TABLE()

	wbDigit::wbDigit(wxWindow *parent) : wxWindow(parent, wxID_ANY, wxDefaultPosition, wxSize(25, 25) ) {
	}
	
	wbDigit::~wbDigit() {
	}
	
	void wbDigit::OnPaint(wxPaintEvent &event) {
		wxPaintDC dc(this);
	}
	
	void wbDigit::SetValue( double value ) {
		wxClientDC dc(this);
		dc.SetFont( wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT) );
		wxString text = wxString::Format( wxT("%u"), value);
		dc.Clear();
		dc.DrawText( text, 0, 0);
		printf("Set value... %f\n", value);
	}
	
	void wbDigit::OnContextMenu(wxContextMenuEvent &event) {
		wxMenu *context = new wxMenu;
		context->Append( ID_DigitMenuConfig, wxT("&Configure") );
		context->Append( ID_DigitMenuRemove, wxT("&Remove") );
		this->PopupMenu(context);
	}
	
	void wbDigit::OnRemoveMe(wxCommandEvent &event) {
		wxCommandEvent evt( wxEVT_COMMAND_MENU_SELECTED, ID_DestroyDigit );
		evt.SetEventObject(this);
		GetParent()->ProcessEvent(evt);
	}
	
	void wbDigit::OnConfigMe(wxCommandEvent &event) {
		this->Configure();
	}
	
	void wbDigit::Configure() {
		//wbGaugeDialog dialog( wxT("Configure"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE );
		//dialog.ShowModal();
		
		//wxString test( wxT("Gauge Type") );
		//if ( dialog.isOk && ( dialog.typeBox->GetValue() != wxEmptyString ) ) {
		//	myLabel->SetLabel( dialog.typeBox->GetValue() );
		//}
		Layout();
	}
	
}
