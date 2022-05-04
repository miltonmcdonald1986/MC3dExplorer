#pragma once


#include <MC3dExplorerLib_MC3dExplorer.h>

#include <wx/wx.h>

#include "GLPane.h"
#include "MainFrame.h"
#include "Middleman.h"


class MyApp : public wxApp
{
public:
    virtual bool OnInit();

    MainFrame* m_MainFrame;
    BasicGLPane* m_GLPane;
    Middleman m_Middleman;

public:
    std::shared_ptr<MC3dExplorerLib::MC3dExplorer> m_MC3dExplorer;

    inline auto GetMiddleman() const -> Middleman { return m_Middleman; }
};


DECLARE_APP(MyApp);
