#pragma once


#include <memory>

#include <MC3dExplorerLib_MC3dExplorer.h>

#include <wx/wx.h>


class Middleman
{
public:
    Middleman();

    auto OnColorChangeBackground()          const -> void;
    auto OnColorChangeSelected()            const -> void;
    auto OnEnterWindow(wxMouseEvent& event) const -> void;
    auto OnFileLoad()                       const -> void;
    auto OnKeyDown(wxKeyEvent& event)       const -> void;
    auto OnLeftDown(wxMouseEvent& event)    const -> void;
    auto OnMotion(wxMouseEvent& event)      const -> void;
    auto OnMouseWheel(wxMouseEvent& event)  const -> void;
    auto OnSize()                           const -> void;
    auto OnViewBack()                       const -> void;
    auto OnViewBottom()                     const -> void;
    auto OnViewFront()                      const -> void;
    auto OnViewIsometric()                  const -> void;
    auto OnViewLeft()                       const -> void;
    auto OnViewRight()                      const -> void;
    auto OnViewShaded()                     const -> void;
    auto OnViewTop()                        const -> void;
    auto OnViewWireframe()                  const -> void;
    auto OnZoomFit()                        const -> void;

    std::shared_ptr<MC3dExplorerLib::MC3dExplorer> m_MC3dExplorer;
};
