#ifndef WBGRAPH_H_
#define WBGRAPH_H_

#include <wx/wxprec.h>
/*
enum {
	ID_GraphMenuRemove = wxID_HIGHEST + 1,
	ID_GraphMenuConfig
};
*/
namespace WB4LinGUI {

	class wbGraph : public wxWindow {
		public:
			wbGraph(wxWindow *, const wxSize &size);
			~wbGraph();
			
			void OnPaint(wxPaintEvent &event);
			void SetValue(double value);
			
			void OnContextMenu(wxContextMenuEvent &event);
			void OnConfigMe(wxCommandEvent &event);
			void OnRemoveMe(wxCommandEvent &event);
					
			
		DECLARE_EVENT_TABLE()
			
	};
}

#endif /*WBGRAPH_H_*/
