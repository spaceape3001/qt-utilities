////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsToolBar.hpp"
#include "GraphicsTool.hpp"
#include "GraphicsToolBar.hxx"

#include <yq/gluon/core/ustring.hpp>
#include <yq/gluon/core/uicon.hpp>
#include <yq/gluon/util/UInt64SignalMapper.hpp>
#include <QToolButton>

namespace yq::gluon {
    GraphicsToolBar::GraphicsToolBar(QWidget*parent) : QToolBar(parent)
    {
        m_mapper    = new UInt64SignalMapper(this);
        connect(m_mapper, &UInt64SignalMapper::mapped, this, &GraphicsToolBar::clicked);
    }
    
    GraphicsToolBar::~GraphicsToolBar()
    {
    }

    void    GraphicsToolBar::add(tool_k, const GraphicsToolMeta& gtm)
    {
        if(m_buttons.contains(gtm.id()))
            return ;
        
        QToolButton*   tb  = new QToolButton;
        tb -> setText(qString(gtm.label()));
        tb -> setIcon(qIcon(gtm.icon(0)));
        
        connect(tb, &QToolButton::clicked, m_mapper, &UInt64SignalMapper::map);
        m_mapper -> setMapping(tb, gtm.id());
        m_buttons[gtm.id()] = tb;
        m_tools.push_back(gtm.id());
        
        addWidget(tb);
    }
    
    void    GraphicsToolBar::add(tool_k, std::string_view k)
    {
        const GraphicsToolMeta* gtm = GraphicsToolMeta::find(k);
        if(!gtm)
            return;
        add(TOOL, *gtm);
    }
    
    void    GraphicsToolBar::add(separator_k)
    {
        addSeparator();
    }

    void    GraphicsToolBar::setActive(uint64_t id)
    {
        for(auto& itr : m_buttons){
            if(!itr.second)
                continue;
            itr.second->setDown(id == itr.first);
        }
    }
}

#include "moc_GraphicsToolBar.cpp"
