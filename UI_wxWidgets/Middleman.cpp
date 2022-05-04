#include "Middleman.h"

#include <wx/colordlg.h>

#include <MC3dExplorerLib_MC3dExplorer.h>

#include "App.h"


Middleman::Middleman()
{
}


auto Middleman::OnColorChangeBackground() const -> void
{
	wxColourDialog dlg(nullptr);
	auto userSelected = dlg.ShowModal();
	if (userSelected == wxID_CANCEL)
		return;

	auto selectedColor = dlg.GetColourData().GetColour();

	auto r = selectedColor.GetRed() / 255.f;
	auto g = selectedColor.GetGreen() / 255.f;
	auto b = selectedColor.GetBlue() / 255.f;

	m_MC3dExplorer->ChangeColorOfBackground(glm::vec3(r, g, b));
}


auto Middleman::OnColorChangeSelected() const -> void
{
	wxColourDialog dlg(nullptr);
	auto userSelected = dlg.ShowModal();
	if (userSelected == wxID_CANCEL)
		return;

	auto selectedColor = dlg.GetColourData().GetColour();

	auto r = selectedColor.GetRed() / 255.f;
	auto g = selectedColor.GetGreen() / 255.f;
	auto b = selectedColor.GetBlue() / 255.f;

	m_MC3dExplorer->ChangeColorOfSelected(glm::vec3(r, g, b));
	m_MC3dExplorer->UnselectAll();
}


auto Middleman::OnEnterWindow(wxMouseEvent& event) const -> void
{
	auto pos = event.GetPosition();
	m_MC3dExplorer->SetCursorPos(pos.x, pos.y);
}


auto Middleman::OnFileLoad() const -> void
{
	wxFileDialog
		openFileDialog(nullptr, _("Open file"), "", "",
			"STL files (*.stl)|*.stl", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;

	m_MC3dExplorer->LoadObjectFromFile(openFileDialog.GetPath().ToStdString());
}


auto Middleman::OnKeyDown(wxKeyEvent& event) const -> void
{
	switch (event.GetKeyCode())
	{
	case WXK_ESCAPE:
		m_MC3dExplorer->UnselectAll();
		break;
	default:
		break;
	}
}


auto Middleman::OnLeftDown(wxMouseEvent& event) const -> void
{
	m_MC3dExplorer->Select();
}


auto Middleman::OnMotion(wxMouseEvent& event) const -> void
{
	auto pos = event.GetPosition();
	m_MC3dExplorer->SetCursorPos(pos.x, pos.y);

	auto leftIsDown = event.ButtonIsDown(wxMouseButton::wxMOUSE_BTN_LEFT);
	auto middleIsDown = event.ButtonIsDown(wxMouseButton::wxMOUSE_BTN_MIDDLE);

	if (leftIsDown)
		m_MC3dExplorer->Pan();
	else if (middleIsDown)
		m_MC3dExplorer->ArcballRotate();
	else
		m_MC3dExplorer->Hover();
}


auto Middleman::OnMouseWheel(wxMouseEvent& event) const -> void
{
	m_MC3dExplorer->CursorZoom(event.GetWheelRotation());
}


auto Middleman::OnSize() const -> void
{
	auto size = wxGetApp().m_GLPane->GetSize();
	m_MC3dExplorer->SetWindowSize(size.x, size.y);
}


auto Middleman::OnViewBack() const -> void
{
	m_MC3dExplorer->SetViewBack();
}


auto Middleman::OnViewBottom() const -> void
{
	m_MC3dExplorer->SetViewBottom();
}


auto Middleman::OnViewFront() const -> void
{
	m_MC3dExplorer->SetViewFront();
}


auto Middleman::OnViewIsometric() const -> void
{
	m_MC3dExplorer->SetViewIsometric();
}


auto Middleman::OnViewLeft() const -> void
{
	m_MC3dExplorer->SetViewLeft();
}


auto Middleman::OnViewRight() const -> void
{
	m_MC3dExplorer->SetViewRight();
}


auto Middleman::OnViewShaded() const -> void
{
	m_MC3dExplorer->SetGLPolygonMode(MC3dExplorerLib::GLPolygonMode::Shaded);
}


auto Middleman::OnViewTop() const -> void
{ 
	m_MC3dExplorer->SetViewTop(); 
}


auto Middleman::OnViewWireframe() const -> void
{
	m_MC3dExplorer->SetGLPolygonMode(MC3dExplorerLib::GLPolygonMode::Wireframe);
}


auto Middleman::OnZoomFit() const -> void
{
	m_MC3dExplorer->ZoomFit();
}
