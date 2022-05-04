#pragma once


#include "MainFrameParentGeneratedDoNotEdit.h"


class MainFrame : public MainFrameParentGeneratedDoNotEdit
{
public:
	MainFrame(
		wxWindow* parent, 
		wxWindowID id = wxID_ANY, 
		const wxString& title = wxT("MC3dExplorer"), 
		const wxPoint& pos = wxDefaultPosition, 
		const wxSize& size = wxSize(500, 300), 
		long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	auto MenuFileLoadOnMenuSelection(wxCommandEvent& event)						-> void;
	auto MenuViewAppearanceShadedOnMenuSelection(wxCommandEvent& event)			-> void;
	auto MenuViewAppearanceWireframeOnMenuSelection(wxCommandEvent& event)		-> void;
	auto MenuViewGraphicsViewBackOnMenuSelection(wxCommandEvent& event)			-> void;
	auto MenuViewGraphicsViewBottomOnMenuSelection(wxCommandEvent& event)		-> void;
	auto MenuViewGraphicsViewFrontOnMenuSelection(wxCommandEvent& event)		-> void;
	auto MenuViewGraphicsViewIsometricOnMenuSelection(wxCommandEvent& event)	-> void;
	auto MenuViewGraphicsViewLeftOnMenuSelection(wxCommandEvent& event)			-> void;
	auto MenuViewGraphicsViewRightOnMenuSelection(wxCommandEvent& event)		-> void;
	auto MenuViewGraphicsViewTopOnMenuSelection(wxCommandEvent& event)			-> void;
	auto MenuViewZoomFitOnMenuSelection(wxCommandEvent& event)					-> void;

	void MenuViewGraphicsViewIsometricReverseOnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	void MenuViewGraphicsViewTrimetricOnMenuSelection(wxCommandEvent& event) { event.Skip(); }

private:
};
