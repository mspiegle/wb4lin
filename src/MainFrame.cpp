//wx stuff
#include <wx/wxprec.h>

//common
#include "Common.h"

//my header
#include "MainFrame.h"

//my dialogs
#include "DashDialog.h"
#include "ConnectDialog.h"

//stl stuff
#include <list>
using namespace std;

//custom controls
#include "wbGauge.h"
#include "wbDigit.h"
#include "wbGraph.h"

//utility
#include "Utility.h"
using namespace Utility;

//TEWB Client
#include "TEWBClient.h"
using namespace TEWB;

#include "stdio.h"

namespace WB4LinGUI {
	
	BEGIN_EVENT_TABLE(MainFrame, wxFrame)
		EVT_MENU(ID_FileOpen, MainFrame::OnFileOpen)
		EVT_MENU(ID_FileSave, MainFrame::OnFileSave)
		EVT_MENU(ID_FileExport, MainFrame::OnFileExport)
		EVT_MENU(ID_FileQuit, MainFrame::OnFileQuit)
		EVT_MENU(ID_WidebandConnect, MainFrame::OnWidebandConnect)
		EVT_MENU(ID_WidebandConfig, MainFrame::OnWidebandConfig)
		EVT_MENU(ID_DashboardAddGauge, MainFrame::OnDashboardAddGauge)
		EVT_MENU(ID_DashboardAddMeter, MainFrame::OnDashboardAddMeter)
		EVT_MENU(ID_DashboardAddDigit, MainFrame::OnDashboardAddDigit)
		EVT_MENU(ID_DashboardAddGraph, MainFrame::OnDashboardAddGraph)
		EVT_MENU(ID_HelpAbout, MainFrame::OnHelpAbout)
		EVT_IDLE(MainFrame::OnIdle)
		EVT_MENU( ID_DestroyGauge, MainFrame::DestroyGauge )
		EVT_MENU( ID_DestroyDigit, MainFrame::DestroyDigit )
	END_EVENT_TABLE()

	MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame((wxFrame *)NULL, wxID_ANY, title, pos, size, style) {
		//build frame in center
		Centre(wxBOTH);
		
		//event stuff
		SetExtraStyle(wxWS_EX_PROCESS_IDLE);
		
		//make some menu widgets
	    wxMenu *menuFile = new wxMenu;
	    wxMenu *menuWideband = new wxMenu;
	    wxMenu *menuDashboard = new wxMenu;
	    wxMenu *menuHelp = new wxMenu;
	
	    //menu -> file
	    menuFile->Append( ID_FileOpen, _T("&Open") );
	    menuFile->Append( ID_FileSave, _T("&Save") );
	    menuFile->Append( ID_FileExport, _T("&Export") );
	    menuFile->AppendSeparator();
	    menuFile->Append( ID_FileQuit, _T("E&xit") );
	    
	    //menu -> wideband
	    menuWideband->Append( ID_WidebandConnect, _T("&Connect") );
	    menuWideband->Append( ID_WidebandConfig, _T("Configure") );
	    
	    //menu -> dashboard
	    menuDashboard->Append( ID_DashboardAddGauge, wxT("Add &Gauge") );
	    menuDashboard->Append( ID_DashboardAddMeter, wxT("Add &Meter") );
	    menuDashboard->Append( ID_DashboardAddDigit, wxT("Add &Digit") );
	    menuDashboard->Append( ID_DashboardAddGraph, wxT("Add G&raph") );
	    
	    //menu -> help
	    menuHelp->Append( ID_HelpAbout, _T("&About") );
	
	    //Build the menubar with the menu widgets
	    wxMenuBar *menuBar = new wxMenuBar;
	    menuBar->Append( menuFile, _T("&File") );
	    menuBar->Append( menuWideband, _T("&Wideband") );
	    menuBar->Append( menuDashboard, _T("&Dashboard") );
	    menuBar->Append( menuHelp, _T("&Help") );
	
	    //set the menubar for the frame
	    SetMenuBar( menuBar );
	    
	    //status bar
	    this->mainStatus = CreateStatusBar();
	    
	    //the sizer that all other sizers mount to
	    masterSizer = new wxBoxSizer( wxVERTICAL );
	    
	    //this is so we can create a 5px frame around all controls
	    wxBoxSizer *frameSizer = new wxBoxSizer ( wxVERTICAL );
	    
	    //this is for the top area
	    wxBoxSizer *topSizer = new wxBoxSizer ( wxHORIZONTAL );
	    
	    //this is for the middle area
	    wxBoxSizer *midSizer = new wxBoxSizer ( wxHORIZONTAL );
	    
	    //this is for the controls
	    gaugeSizer = new wxBoxSizer ( wxVERTICAL );
	    digitSizer = new wxBoxSizer ( wxHORIZONTAL );
	    
	    //this is the info section
	    wxBoxSizer *infoSizer = new wxBoxSizer ( wxVERTICAL );
	    
	    //this is for the graph at the bottom
	    wxBoxSizer *graphSizer = new wxBoxSizer ( wxVERTICAL );
	    
	    //Ok, now lets put it all together
	    masterSizer->Add(frameSizer, wxSizerFlags().Border(wxALL, 5));
	    frameSizer->Add(topSizer);
	    frameSizer->Add(midSizer);
	    frameSizer->Add(infoSizer);
	    topSizer->Add(digitSizer, wxSizerFlags().Align(wxALIGN_LEFT).Border(wxALL, 5));
	    midSizer->Add(graphSizer, wxSizerFlags().Align(wxALIGN_LEFT).Border(wxALL, 5));
	    midSizer->Add(gaugeSizer, wxSizerFlags().Align(wxALIGN_RIGHT).Border(wxALL, 5));
	    
	    //Wideband Client
	    wbClient = new TEWBClient();
	    isConnected = false;
	   
	    //test shit
	    wbGraph *graph = new wbGraph(this, wxSize(600,300));
	    graphSizer->Add(graph);
	    
	    //list stuff
	    gaugeMap = new map<wbGauge *, unsigned>();
	    digitMap = new map<wbDigit *, unsigned>();
	    
	    //Set our master sizer
	    SetSizerAndFit(masterSizer);
	    rui = 0;
	    this->first = true;
	}

	MainFrame::~MainFrame() {
		delete wbClient;
	}
	
	void MainFrame::OnIdle(wxIdleEvent& event) {
		if( isConnected ) {
			mainStatus->SetStatusText( wxT("Currently Connected...") );
			//unsigned int *packet = wbClient->GetHumanFrame();
			unsigned int *packet = wbClient->GetTestFrame();
			
			map<wbGauge *, unsigned>::const_iterator gi;
			map<wbDigit *, unsigned>::const_iterator di;
			
			for ( gi = gaugeMap->begin(); gi != gaugeMap->end(); gi++ ) {
				wbGauge *g = gi->first;
				g->SetValue(DataUtility::ToRealValue(packet[gi->second], gi->second));
			}
			
			for ( di = digitMap->begin(); di != digitMap->end(); di++ ) {
				wbDigit *d = di->first;
				d->SetValue(DataUtility::ToRealValue(packet[di->second], di->second));
			}
			event.RequestMore(TRUE);
		} else {
			mainStatus->SetStatusText( wxT("Not connected.  Goto Wideband -> Connect.") );
			
			if ( this->first ) {
				map<wbDigit *, unsigned>::const_iterator di;
				for ( di = digitMap->begin(); di != digitMap->end(); di++ ) {
					wbDigit *d = di->first;
					d->SetValue(0);
				}
				this->first = false;
			}
			
		}
		
		wxMilliSleep(10);
	}
	
	void MainFrame::OnFileOpen(wxCommandEvent& WXUNUSED(event)) {
		
	}
	
	void MainFrame::OnFileSave(wxCommandEvent& WXUNUSED(event)) {
		
	}
	
	void MainFrame::OnFileExport(wxCommandEvent& WXUNUSED(event)) {
		
	}
	
	void MainFrame::OnFileQuit(wxCommandEvent& WXUNUSED(event)) {
	    Close(TRUE);
	}
	
	void MainFrame::OnWidebandConnect(wxCommandEvent& WXUNUSED(event)) {
		//do something to launch the connect frame
		ConnectDialog dialog( _T("Configure Connection..."), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP );
		dialog.ShowModal();
		
		//user hit 'ok'
		wxString devicestring = dialog.comMenu->GetValue();
		if ( wbClient->Connect(strdup(devicestring.mb_str(wxConvUTF8))) ) {
			isConnected = true;
		}
	}
	
	void MainFrame::OnWidebandConfig(wxCommandEvent& WXUNUSED(event)) {

	}
	
	void MainFrame::OnDashboardAddGauge(wxCommandEvent& WXUNUSED(event)) {
		//Create new control
		wbGauge *x = new wbGauge(this);
		
		//add it to the sizer and the control list
		gaugeSizer->Add(x);
		this->Fit();
		
		//run the config dialog
		x->Configure();
		unsigned type = x->type;
		gaugeMap->insert( pair<wbGauge *, unsigned>(x, type) );
	}
	
	void MainFrame::OnDashboardAddMeter(wxCommandEvent& WXUNUSED(event)) {
		//Create new control
		wbGauge *x = new wbGauge(this, TEWB_U1);
		
		//add it to the sizer and the control list
		printf("Adding to sizer...\n");
		gaugeSizer->Add(x);
		gaugeMap->insert( pair<wbGauge *, unsigned>(x, TEWB_U1) );
		this->Fit();
		
		//run the config dialog
		x->Configure();
	}
	
	void MainFrame::OnDashboardAddDigit(wxCommandEvent& WXUNUSED(event)) {
		//Create new control
		wbDigit *x = new wbDigit(this);
		
		//add it to the sizer and the control list
		digitSizer->Add(x);
		digitMap->insert( pair<wbDigit *, unsigned>(x, TEWB_U1) );
		this->Fit();
		
		//run the config dialog
		x->Configure();
		x->SetValue(0);
	}
	
	void MainFrame::OnDashboardAddGraph(wxCommandEvent& WXUNUSED(event)) {
		//Create new control
		wbGauge *x = new wbGauge(this, TEWB_U1);
		
		//add it to the sizer and the control list
		printf("Adding to sizer...\n");
		gaugeSizer->Add(x);
		gaugeMap->insert( pair<wbGauge *, unsigned>(x, TEWB_U1) );
		this->Fit();
		
		//run the config dialog
		x->Configure();
	}
	
	void MainFrame::DestroyGauge(wxCommandEvent &event) {
		wbGauge *gauge = (wbGauge *)event.GetEventObject();
		gaugeMap->erase(gauge);
		wxString message = wxT( "Removed Gauge: " );
		message += gauge->myLabel->GetLabel();
		gauge->Destroy();
		this->Fit();
		mainStatus->SetStatusText( message );
	}
	
	void MainFrame::DestroyDigit(wxCommandEvent &event) {
		wbDigit *digit = (wbDigit *)event.GetEventObject();
		digitMap->erase(digit);
		wxString message = wxT( "Removed digit: " );
		//message += digit->myLabel->GetLabel();
		digit->Destroy();
		this->Fit();
		mainStatus->SetStatusText( message );
	}
	
	void MainFrame::OnHelpAbout(wxCommandEvent& WXUNUSED(event)) {
		//TODO: There has to be a better way to do this...
		wxString messageText = wxT(APP_NAME);
		messageText += wxT("\nby Michael Spiegle\nmike@nauticaltech.com");
	    wxMessageBox( messageText, wxT("About..."), wxOK | wxICON_INFORMATION, this);
	}
	
}
