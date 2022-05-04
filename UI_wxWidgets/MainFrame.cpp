#include "MainFrame.h"

#include "App.h"


MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: MainFrameParentGeneratedDoNotEdit(parent, id, title, pos, size, style)
{
}


auto MainFrame::MenuFileLoadOnMenuSelection(wxCommandEvent& event) -> void
{
	wxGetApp().GetMiddleman().OnFileLoad();
	Refresh();
}


auto MainFrame::MenuViewAppearanceShadedOnMenuSelection(wxCommandEvent& event) -> void
{
	wxGetApp().GetMiddleman().OnViewShaded();
	Refresh();
}


auto MainFrame::MenuViewAppearanceWireframeOnMenuSelection(wxCommandEvent& event) -> void
{
	wxGetApp().GetMiddleman().OnViewWireframe();
	Refresh();
}


auto MainFrame::MenuViewGraphicsViewBackOnMenuSelection(wxCommandEvent& event) -> void
{
	wxGetApp().GetMiddleman().OnViewBack();
	Refresh();
}


auto MainFrame::MenuViewGraphicsViewBottomOnMenuSelection(wxCommandEvent& event) -> void
{
	wxGetApp().GetMiddleman().OnViewBottom();
	Refresh();
}


auto MainFrame::MenuViewGraphicsViewFrontOnMenuSelection(wxCommandEvent& event) -> void
{
	wxGetApp().GetMiddleman().OnViewFront();
	Refresh();
}


auto MainFrame::MenuViewGraphicsViewIsometricOnMenuSelection(wxCommandEvent& event) -> void
{
	wxGetApp().GetMiddleman().OnViewIsometric();
	Refresh();
}


auto MainFrame::MenuViewGraphicsViewLeftOnMenuSelection(wxCommandEvent& event) -> void
{
	wxGetApp().GetMiddleman().OnViewLeft();
	Refresh();
}


auto MainFrame::MenuViewGraphicsViewRightOnMenuSelection(wxCommandEvent& event) -> void
{
	wxGetApp().GetMiddleman().OnViewRight();
	Refresh();
}


auto MainFrame::MenuViewGraphicsViewTopOnMenuSelection(wxCommandEvent& event) -> void
{
	wxGetApp().GetMiddleman().OnViewTop();
	Refresh();
}


auto MainFrame::MenuViewZoomFitOnMenuSelection(wxCommandEvent& event) -> void
{
	wxGetApp().GetMiddleman().OnZoomFit();
	Refresh();
}
