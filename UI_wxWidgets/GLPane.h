#pragma once


#include <MC3dExplorerLib_MC3dExplorer.h>

#include <wx/wx.h>
#include <wx/glcanvas.h>


class BasicGLPane : public wxGLCanvas
{
public:
	wxGLContext* m_context;
	std::shared_ptr<MC3dExplorerLib::MC3dExplorer> m_MC3dExplorer;

public:
	BasicGLPane(wxFrame* parent, int* args);
	virtual ~BasicGLPane();

	void resized(wxSizeEvent& evt);

	int getWidth();
	int getHeight();

	void render(wxPaintEvent& evt);

	// events
	auto OnEnterWindow(wxMouseEvent& event) -> void;
	auto OnMotion(wxMouseEvent& event) -> void;
	auto OnMouseWheel(wxMouseEvent& event) -> void;
	//void mouseMoved(wxMouseEvent& event);
	auto OnLeftDown(wxMouseEvent& event) -> void;
	//void mouseWheelMoved(wxMouseEvent& event);
	//void mouseReleased(wxMouseEvent& event);
	void OnRightDown(wxMouseEvent& event);
	//void mouseLeftWindow(wxMouseEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	//void keyReleased(wxKeyEvent& event);

	void OnRightClickMenuMadeSelection(wxCommandEvent& event);

	DECLARE_EVENT_TABLE()
};
