///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-200-g253ddd4d)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MainFrameParentGeneratedDoNotEdit.h"

///////////////////////////////////////////////////////////////////////////

MainFrameParentGeneratedDoNotEdit::MainFrameParentGeneratedDoNotEdit(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	m_StatusBar = this->CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);
	m_menubar1 = new wxMenuBar(0);
	m_MenuFile = new wxMenu();
	wxMenuItem* m_MenuFileLoad;
	m_MenuFileLoad = new wxMenuItem(m_MenuFile, wxID_ANY, wxString(wxT("Load Object...")), wxEmptyString, wxITEM_NORMAL);
	m_MenuFile->Append(m_MenuFileLoad);

	m_menubar1->Append(m_MenuFile, wxT("File"));

	m_MenuView = new wxMenu();
	m_MenuViewAppearance = new wxMenu();
	wxMenuItem* m_MenuViewAppearanceItem = new wxMenuItem(m_MenuView, wxID_ANY, wxT("Appearance"), wxEmptyString, wxITEM_NORMAL, m_MenuViewAppearance);
	wxMenuItem* m_MenuViewAppearanceWireframe;
	m_MenuViewAppearanceWireframe = new wxMenuItem(m_MenuViewAppearance, wxID_ANY, wxString(wxT("Wireframe")), wxEmptyString, wxITEM_NORMAL);
	m_MenuViewAppearance->Append(m_MenuViewAppearanceWireframe);

	wxMenuItem* m_MenuViewAppearanceShaded;
	m_MenuViewAppearanceShaded = new wxMenuItem(m_MenuViewAppearance, wxID_ANY, wxString(wxT("Shaded")), wxEmptyString, wxITEM_NORMAL);
	m_MenuViewAppearance->Append(m_MenuViewAppearanceShaded);

	m_MenuView->Append(m_MenuViewAppearanceItem);

	m_MenuViewGraphicsView = new wxMenu();
	wxMenuItem* m_MenuViewGraphicsViewItem = new wxMenuItem(m_MenuView, wxID_ANY, wxT("Graphics View"), wxEmptyString, wxITEM_NORMAL, m_MenuViewGraphicsView);
	wxMenuItem* m_MenuViewGraphicsViewTop;
	m_MenuViewGraphicsViewTop = new wxMenuItem(m_MenuViewGraphicsView, wxID_ANY, wxString(wxT("Top")), wxEmptyString, wxITEM_NORMAL);
	m_MenuViewGraphicsView->Append(m_MenuViewGraphicsViewTop);

	wxMenuItem* m_MenuViewGraphicsViewFront;
	m_MenuViewGraphicsViewFront = new wxMenuItem(m_MenuViewGraphicsView, wxID_ANY, wxString(wxT("Front")), wxEmptyString, wxITEM_NORMAL);
	m_MenuViewGraphicsView->Append(m_MenuViewGraphicsViewFront);

	wxMenuItem* m_MenuViewGraphicsViewBack;
	m_MenuViewGraphicsViewBack = new wxMenuItem(m_MenuViewGraphicsView, wxID_ANY, wxString(wxT("Back")), wxEmptyString, wxITEM_NORMAL);
	m_MenuViewGraphicsView->Append(m_MenuViewGraphicsViewBack);

	wxMenuItem* m_MenuViewGraphicsViewBottom;
	m_MenuViewGraphicsViewBottom = new wxMenuItem(m_MenuViewGraphicsView, wxID_ANY, wxString(wxT("Bottom")), wxEmptyString, wxITEM_NORMAL);
	m_MenuViewGraphicsView->Append(m_MenuViewGraphicsViewBottom);

	wxMenuItem* m_MenuViewGraphicsViewRight;
	m_MenuViewGraphicsViewRight = new wxMenuItem(m_MenuViewGraphicsView, wxID_ANY, wxString(wxT("Right")), wxEmptyString, wxITEM_NORMAL);
	m_MenuViewGraphicsView->Append(m_MenuViewGraphicsViewRight);

	wxMenuItem* m_MenuViewGraphicsViewLeft;
	m_MenuViewGraphicsViewLeft = new wxMenuItem(m_MenuViewGraphicsView, wxID_ANY, wxString(wxT("Left")), wxEmptyString, wxITEM_NORMAL);
	m_MenuViewGraphicsView->Append(m_MenuViewGraphicsViewLeft);

	wxMenuItem* m_MenuViewGraphicsViewIsometric;
	m_MenuViewGraphicsViewIsometric = new wxMenuItem(m_MenuViewGraphicsView, wxID_ANY, wxString(wxT("Isometric")), wxEmptyString, wxITEM_NORMAL);
	m_MenuViewGraphicsView->Append(m_MenuViewGraphicsViewIsometric);

	wxMenuItem* m_MenuViewGraphicsViewIsometricReverse;
	m_MenuViewGraphicsViewIsometricReverse = new wxMenuItem(m_MenuViewGraphicsView, wxID_ANY, wxString(wxT("Isometric reverse")), wxEmptyString, wxITEM_NORMAL);
	m_MenuViewGraphicsView->Append(m_MenuViewGraphicsViewIsometricReverse);

	wxMenuItem* m_MenuViewGraphicsViewTrimetric;
	m_MenuViewGraphicsViewTrimetric = new wxMenuItem(m_MenuViewGraphicsView, wxID_ANY, wxString(wxT("Trimetric")), wxEmptyString, wxITEM_NORMAL);
	m_MenuViewGraphicsView->Append(m_MenuViewGraphicsViewTrimetric);

	m_MenuView->Append(m_MenuViewGraphicsViewItem);

	m_MenuViewZoom = new wxMenu();
	wxMenuItem* m_MenuViewZoomItem = new wxMenuItem(m_MenuView, wxID_ANY, wxT("&Zoom"), wxEmptyString, wxITEM_NORMAL, m_MenuViewZoom);
	wxMenuItem* m_MenuViewZoomFit;
	m_MenuViewZoomFit = new wxMenuItem(m_MenuViewZoom, wxID_ZOOM_FIT, wxString(wxEmptyString), wxEmptyString, wxITEM_NORMAL);
	m_MenuViewZoom->Append(m_MenuViewZoomFit);

	m_MenuView->Append(m_MenuViewZoomItem);

	m_menubar1->Append(m_MenuView, wxT("&View"));

	this->SetMenuBar(m_menubar1);


	this->Centre(wxBOTH);

	// Connect Events
	m_MenuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameParentGeneratedDoNotEdit::MenuFileLoadOnMenuSelection), this, m_MenuFileLoad->GetId());
	m_MenuViewAppearance->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameParentGeneratedDoNotEdit::MenuViewAppearanceWireframeOnMenuSelection), this, m_MenuViewAppearanceWireframe->GetId());
	m_MenuViewAppearance->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameParentGeneratedDoNotEdit::MenuViewAppearanceShadedOnMenuSelection), this, m_MenuViewAppearanceShaded->GetId());
	m_MenuViewGraphicsView->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameParentGeneratedDoNotEdit::MenuViewGraphicsViewTopOnMenuSelection), this, m_MenuViewGraphicsViewTop->GetId());
	m_MenuViewGraphicsView->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameParentGeneratedDoNotEdit::MenuViewGraphicsViewFrontOnMenuSelection), this, m_MenuViewGraphicsViewFront->GetId());
	m_MenuViewGraphicsView->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameParentGeneratedDoNotEdit::MenuViewGraphicsViewBackOnMenuSelection), this, m_MenuViewGraphicsViewBack->GetId());
	m_MenuViewGraphicsView->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameParentGeneratedDoNotEdit::MenuViewGraphicsViewBottomOnMenuSelection), this, m_MenuViewGraphicsViewBottom->GetId());
	m_MenuViewGraphicsView->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameParentGeneratedDoNotEdit::MenuViewGraphicsViewRightOnMenuSelection), this, m_MenuViewGraphicsViewRight->GetId());
	m_MenuViewGraphicsView->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameParentGeneratedDoNotEdit::MenuViewGraphicsViewLeftOnMenuSelection), this, m_MenuViewGraphicsViewLeft->GetId());
	m_MenuViewGraphicsView->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameParentGeneratedDoNotEdit::MenuViewGraphicsViewIsometricOnMenuSelection), this, m_MenuViewGraphicsViewIsometric->GetId());
	m_MenuViewGraphicsView->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameParentGeneratedDoNotEdit::MenuViewGraphicsViewIsometricReverseOnMenuSelection), this, m_MenuViewGraphicsViewIsometricReverse->GetId());
	m_MenuViewGraphicsView->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameParentGeneratedDoNotEdit::MenuViewGraphicsViewTrimetricOnMenuSelection), this, m_MenuViewGraphicsViewTrimetric->GetId());
	m_MenuViewZoom->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameParentGeneratedDoNotEdit::MenuViewZoomFitOnMenuSelection), this, m_MenuViewZoomFit->GetId());
}

MainFrameParentGeneratedDoNotEdit::~MainFrameParentGeneratedDoNotEdit()
{
	// Disconnect Events

}
