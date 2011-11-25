//wx gui
#include <wx/wxprec.h>

//common
#include "Common.h"

//my header
#include "WB4Lin.h"

//my frame
#include "MainFrame.h"

namespace WB4LinGUI {
	
	bool WB4Lin::OnInit() {
	    MainFrame *frame = new MainFrame( wxT( APP_NAME ), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE);
	    frame->Show(TRUE);
	    SetTopWindow(frame);
	    
	    wxIdleEvent::SetMode(wxIDLE_PROCESS_SPECIFIED);
	    
	    return TRUE;
	}

}
