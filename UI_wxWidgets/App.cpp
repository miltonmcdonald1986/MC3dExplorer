#include "App.h"

#include <wx/glcanvas.h>


IMPLEMENT_APP(MyApp)


bool MyApp::OnInit()
{
    //m_MC3dExplorer = MC3dExplorerLib::MC3dExplorer();

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    m_MainFrame = new MainFrame(nullptr);

    int args[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_SAMPLE_BUFFERS, GL_TRUE, WX_GL_DEPTH_SIZE, 16, 0 };

    m_GLPane = new BasicGLPane((wxFrame*)m_MainFrame, args);
    sizer->Add(m_GLPane, 1, wxEXPAND);

    m_MC3dExplorer = std::make_shared<MC3dExplorerLib::MC3dExplorer>();
    m_GLPane->m_MC3dExplorer = m_MC3dExplorer;
    m_Middleman.m_MC3dExplorer = m_MC3dExplorer;

    m_MainFrame->SetSizer(sizer);
    m_MainFrame->SetAutoLayout(true);

    m_MainFrame->Show(true);
    return true;
}
