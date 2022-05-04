#include "GLPane.h"

#include "App.h"

#include <wx/colordlg.h>


BEGIN_EVENT_TABLE(BasicGLPane, wxGLCanvas)
EVT_MOTION(BasicGLPane::OnMotion)
EVT_ENTER_WINDOW(BasicGLPane::OnEnterWindow)
EVT_LEFT_DOWN(BasicGLPane::OnLeftDown)
//EVT_LEFT_UP(BasicGLPane::mouseReleased)
EVT_RIGHT_DOWN(BasicGLPane::OnRightDown)
//EVT_LEAVE_WINDOW(BasicGLPane::mouseLeftWindow)
EVT_SIZE(BasicGLPane::resized)
EVT_KEY_DOWN(BasicGLPane::OnKeyDown)
//EVT_KEY_UP(BasicGLPane::keyReleased)
EVT_MOUSEWHEEL(BasicGLPane::OnMouseWheel)
EVT_PAINT(BasicGLPane::render)
END_EVENT_TABLE()


//void BasicGLPane::mouseMoved(wxMouseEvent& event) {}
//void BasicGLPane::mouseDown(wxMouseEvent& event) {}
//void BasicGLPane::mouseWheelMoved(wxMouseEvent& event) {}
//void BasicGLPane::mouseReleased(wxMouseEvent& event) {}
//void BasicGLPane::rightClick(wxMouseEvent& event) {}
//void BasicGLPane::mouseLeftWindow(wxMouseEvent& event) {}
//void BasicGLPane::keyPressed(wxKeyEvent& event) {}
//void BasicGLPane::keyReleased(wxKeyEvent& event) {}


BasicGLPane::BasicGLPane(wxFrame* parent, int* args) :
    wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
    m_context = new wxGLContext(this);
    wxGLCanvas::SetCurrent(*m_context);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}


BasicGLPane::~BasicGLPane()
{
    delete m_context;
}


auto BasicGLPane::OnEnterWindow(wxMouseEvent& event) -> void
{
    wxGetApp().GetMiddleman().OnEnterWindow(event);
    Refresh();
}


auto BasicGLPane::OnMotion(wxMouseEvent& event) -> void
{
    wxGetApp().GetMiddleman().OnMotion(event);
    Refresh();
}


auto BasicGLPane::OnMouseWheel(wxMouseEvent& event) -> void
{
    wxGetApp().GetMiddleman().OnMouseWheel(event);
    Refresh();
}


auto BasicGLPane::OnLeftDown(wxMouseEvent& event) -> void
{
    wxGetApp().GetMiddleman().OnLeftDown(event);
    Refresh();
}


enum class PopupMenuIds
{
    ColorChangeBackground,
    ColorChangeSelected,
    Test
};


void BasicGLPane::OnRightClickMenuMadeSelection(wxCommandEvent& event)
{
    switch (event.GetId())
    {
    case (int)PopupMenuIds::ColorChangeBackground:
        wxGetApp().GetMiddleman().OnColorChangeBackground();
        Refresh();
        break;
    case (int)PopupMenuIds::ColorChangeSelected:
    {
        wxGetApp().GetMiddleman().OnColorChangeSelected();
        Refresh();
    }
        break;
    case (int)PopupMenuIds::Test:
        wxMessageBox("Test");
        break;
    default:
        wxMessageBox("How are we even here right now?");
        break;
    }
}


void BasicGLPane::OnRightDown(wxMouseEvent& event)
{
    wxMenu menu;

    auto menuColor = new wxMenu();
    wxMenuItem* menuColorItem = new wxMenuItem(&menu, wxID_ANY, wxT("Color"), wxEmptyString, wxITEM_NORMAL, menuColor);
    
    wxMenuItem* menuColorChangeBackground;
    menuColorChangeBackground = new wxMenuItem(menuColor, (int)PopupMenuIds::ColorChangeBackground, wxString(wxT("Change Background")), wxEmptyString, wxITEM_NORMAL);
    menuColor->Append(menuColorChangeBackground);

    wxMenuItem* menuColorChangeSelected;
    menuColorChangeSelected = new wxMenuItem(menuColor, (int)PopupMenuIds::ColorChangeSelected, wxString(wxT("Change Selected")), wxEmptyString, wxITEM_NORMAL);
    menuColor->Append(menuColorChangeSelected);

    menu.Append(menuColorItem);

    menu.Append((int)PopupMenuIds::Test, "Test");
    menu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(BasicGLPane::OnRightClickMenuMadeSelection), NULL, this);
    PopupMenu(&menu);
}


void BasicGLPane::OnKeyDown(wxKeyEvent& event)
{
    wxGetApp().GetMiddleman().OnKeyDown(event);
    Refresh();
}


void BasicGLPane::resized(wxSizeEvent& evt)
{
    wxGetApp().GetMiddleman().OnSize();
    Refresh();
}


int BasicGLPane::getWidth()
{
    return GetSize().x;
}


int BasicGLPane::getHeight()
{
    return GetSize().y;
}


void BasicGLPane::render(wxPaintEvent& evt)
{
    if (!IsShown()) return;

    static bool firstTime = true;
    if (firstTime)
    {
        firstTime = false;
        m_MC3dExplorer->SetWindowSize(getWidth(), getHeight());
        m_MC3dExplorer->ZoomFit();
    }

    wxGLCanvas::SetCurrent(*m_context);
    wxPaintDC(this);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto size = GetSize();
    glViewport(0, 0, size.x, size.y);

    //MC3dExplorerLib::DemoTriangle demoTriangle;
    //demoTriangle.Draw();

    m_MC3dExplorer->Draw();

    glFlush();
    SwapBuffers();
}
