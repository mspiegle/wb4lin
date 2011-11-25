//wx gui
#include <wx/wxprec.h>

//common
#include "Common.h"

//my header
#include "wbGauge.h"

//my dialog
#include "wbGaugeDialog.h"

//unix stuff
#include "stdio.h"

namespace WB4LinGUI {
	
	BEGIN_EVENT_TABLE(wbGauge, wxWindow)
		EVT_CONTEXT_MENU(wbGauge::OnContextMenu)
		EVT_MENU(ID_GaugeMenuRemove, wbGauge::OnRemoveMe)
		EVT_MENU(ID_GaugeMenuConfig, wbGauge::OnConfigMe)
	END_EVENT_TABLE()

	wbGauge::wbGauge(wxWindow *parent, int limit) : wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize) {
		//setup some sizers
		wxBoxSizer *masterSizer	= new wxBoxSizer( wxVERTICAL );
		wxGridSizer *gridSizer	= new wxFlexGridSizer( 2, 3, 2, 2 );
		
		//build text + gauge
		this->myLabel	= new wxStaticText( this, wxID_ANY, wxT("Gauge") );
		this->minLabel	= new wxStaticText( this, wxID_ANY, wxT("Min") );
		this->maxLabel	= new wxStaticText( this, wxID_ANY, wxT("Max") );
		this->gauge		= new wxGauge( this, wxID_ANY, limit, wxDefaultPosition, wxSize(200, 20), wxGA_SMOOTH);
		
		//mount controls to sizer.  we need to skip the first and 3rd grid box, so we use spacer(0)
		gridSizer->AddSpacer(0);
		gridSizer->Add(myLabel, wxSizerFlags(0).Border(wxALL, 2));
		gridSizer->AddSpacer(0);
		gridSizer->Add(minLabel, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 2));
		gridSizer->Add(gauge);
		gridSizer->Add(maxLabel, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 2));
		
		//wrap the gridsizer in a mastersizer so we can apply a border around the entire control
		masterSizer->Add(gridSizer, wxSizerFlags().Border(wxALL, 5));
		
		//limit
		this->limit = limit;
		
		//type
		this->type = TEWB_DEFAULT;
		
		//set the sizer
		SetSizer(masterSizer);
		Layout();
	}
	
	wbGauge::~wbGauge() {
	}
	
	void wbGauge::SetValue( double value ) {
		gauge->SetValue(value);
	}
	
	void wbGauge::OnContextMenu(wxContextMenuEvent &event) {
		wxMenu *context = new wxMenu;
		context->Append( ID_GaugeMenuConfig, wxT("&Configure") );
		context->Append( ID_GaugeMenuRemove, wxT("&Remove") );
		this->PopupMenu(context);
	}
	
	void wbGauge::OnRemoveMe(wxCommandEvent &event) {
		wxCommandEvent evt( wxEVT_COMMAND_MENU_SELECTED, ID_DestroyGauge );
		evt.SetEventObject(this);
		GetParent()->ProcessEvent(evt);
	}
	
	void wbGauge::OnConfigMe(wxCommandEvent &event) {
		this->Configure();
	}
	
	void wbGauge::Configure() {
		wbGaugeDialog dialog( wxT("Configure"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE );
		dialog.ShowModal();
		
		if ( dialog.isOk && ( dialog.typeBox->GetValue() != wxEmptyString ) ) {
			myLabel->SetLabel( dialog.typeBox->GetValue() );
			this->type = (unsigned)dialog.typeBox->GetClientData(dialog.typeBox->GetSelection());
		}
		
		Layout();
	}
	
}
