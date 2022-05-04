///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-200-g253ddd4d)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/statusbr.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameParentGeneratedDoNotEdit
///////////////////////////////////////////////////////////////////////////////
class MainFrameParentGeneratedDoNotEdit : public wxFrame
{
	private:

	protected:
		wxStatusBar* m_StatusBar;
		wxMenuBar* m_menubar1;
		wxMenu* m_MenuView;
		wxMenu* m_MenuViewAppearance;
		wxMenu* m_MenuViewGraphicsView;
		wxMenu* m_MenuViewZoom;

		// Virtual event handlers, override them in your derived class
		virtual void MenuViewAppearanceWireframeOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuViewAppearanceShadedOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuViewGraphicsViewTopOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuViewGraphicsViewFrontOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuViewGraphicsViewBackOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuViewGraphicsViewBottomOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuViewGraphicsViewRightOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuViewGraphicsViewLeftOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuViewGraphicsViewIsometricOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuViewGraphicsViewIsometricReverseOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuViewGraphicsViewTrimetricOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuViewZoomFitOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainFrameParentGeneratedDoNotEdit( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("MC3dExplorer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainFrameParentGeneratedDoNotEdit();

};

