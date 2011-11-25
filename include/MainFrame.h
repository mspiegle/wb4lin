#ifndef MAINFRAME_H_
#define MAINFRAME_H_

#include <wx/wxprec.h>
#include <map>
using namespace std;

#include "Common.h"
#include "TEWBClient.h"
using namespace TEWB;

//this is for the controls
#include "wbGraph.h"
#include "wbDigit.h"
#include "wbGauge.h"

namespace WB4LinGUI {
	
	class MainFrame : public wxFrame {
		private:
			wxStatusBar *mainStatus;
			TEWBClient *wbClient;
			
			wxBoxSizer *gaugeSizer;
			wxBoxSizer *digitSizer;
			wxBoxSizer *masterSizer;
			wbGraph *graph;
			
			map<wbGauge *, unsigned> *gaugeMap;
			//map<wbMeter *, unsigned> *meterMap;
			map<wbDigit *, unsigned> *digitMap;
			//map<wbGraph *, unsigned> *graphMap;
			
			bool isConnected;
			bool first;
			unsigned int rui;
			
	    public:
	    	//frame
	    	MainFrame( const wxString& title, const wxPoint& pos, const wxSize& size, long style);
	    	~MainFrame();
	    	
	    	//menu bits
	    	void OnFileOpen(wxCommandEvent& event);
	    	void OnFileSave(wxCommandEvent& event);
	    	void OnFileExport(wxCommandEvent& event);
	    	void OnFileQuit(wxCommandEvent& event);
	    	void OnWidebandConnect(wxCommandEvent& event);
	    	void OnWidebandConfig(wxCommandEvent& event);
	    	
	    	void OnDashboardAddGauge(wxCommandEvent& event);
	    	void OnDashboardAddMeter(wxCommandEvent& event);
	    	void OnDashboardAddDigit(wxCommandEvent& event);
	    	void OnDashboardAddGraph(wxCommandEvent& event);
	    	
	    	void OnHelpAbout(wxCommandEvent& event);
	    	
	    	//This is where we'll do all of the control-updating
	    	void OnIdle(wxIdleEvent& event);
	    	
	    	//custom stuff
	    	void DestroyGauge(wxCommandEvent &event);
	    	void DestroyDigit(wxCommandEvent &event);
	
	    	DECLARE_EVENT_TABLE()
	};
}

#endif /*MAINFRAME_H_*/
