////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "PaletteWidget.hpp"
#include <yq/core/Any.hpp>

namespace yq::gluon {
    PaletteWidget::PaletteWidget(QWidget*parent) : QToolBox(parent)
    {
    }
    
    PaletteWidget::~PaletteWidget()
    {
    }

    PaletteWidget::Pane&       PaletteWidget::category(const QString& cat, const QIcon& ico)
    {
        auto itr = m_panes.find(cat);
        if(itr != m_panes.end())
            return *(itr->second);
        
        Pane*p  = new Pane;
        m_panes[cat]    = p;
        
        if(ico.isNull()){
            p->m_index  = addItem(p, cat);
        } else {
            p->m_index  = addItem(p, ico, cat);
        }
        return *p;
    }


    PaletteWidget::Item::Item(const QString& txt) : QListWidgetItem(txt)
    {
    }
    
    PaletteWidget::Item::~Item()
    {
    }

    PaletteWidget::Pane::Pane(QWidget*parent)
    {
    }
    
    PaletteWidget::Pane::~Pane()
    {
    }

    PaletteWidget::Item&   PaletteWidget::Pane::addItem(const QString&txt)
    {
        Item*   it  = new Item(txt);
        QListWidget::addItem(it);
        return *it;
    }
}

#include "moc_PaletteWidget.cpp"


