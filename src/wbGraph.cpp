//wx gui
#include <wx/wxprec.h>

//common
#include "Common.h"

//my header
#include "wbGraph.h"

namespace WB4LinGUI {
	
	BEGIN_EVENT_TABLE(wbGraph, wxWindow)
		EVT_PAINT(wbGraph::OnPaint)
		EVT_CONTEXT_MENU(wbGraph::OnContextMenu)
		EVT_MENU(ID_GraphMenuRemove, wbGraph::OnRemoveMe)
		EVT_MENU(ID_GraphMenuConfig, wbGraph::OnConfigMe)
	END_EVENT_TABLE()
	
	wbGraph::wbGraph(wxWindow *parent, const wxSize &size = wxDefaultSize) : wxWindow(parent, wxID_ANY, wxDefaultPosition, size) {
		this->SetOwnBackgroundColour(wxColour(0, 0, 0));
	}
	
	wbGraph::~wbGraph() {
	}
	
	void wbGraph::OnPaint(wxPaintEvent &event) {
		wxPaintDC dc(this);
	}
	
	void wbGraph::SetValue(double value) {
		wxClientDC dc(this);
		dc.DrawCircle(wxPoint(0, 0), value);
	}
	
	void wbGraph::OnContextMenu(wxContextMenuEvent &event) {
		wxMenu *context = new wxMenu;
		context->Append( ID_GraphMenuConfig, wxT("&Configure") );
		context->Append( ID_GraphMenuRemove, wxT("&Remove") );
		this->PopupMenu(context);
	}
	
	void wbGraph::OnConfigMe(wxCommandEvent &event) {
		this->Destroy();
	}
		
	void wbGraph::OnRemoveMe(wxCommandEvent &event) {
		this->Destroy();
	}
	
}
