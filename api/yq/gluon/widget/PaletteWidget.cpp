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
        
        Pane*p  = new Pane(this);
        m_panes[cat]    = p;
        
        if(ico.isNull()){
            p->m_index  = addItem(p, cat);
        } else {
            p->m_index  = addItem(p, ico, cat);
        }
        return *p;
    }

    PaletteWidget::Item*   PaletteWidget::createItem(const QString& s)
    {
        return new Item(s);
    }


    PaletteWidget::Item::Item(const QString& txt) : QListWidgetItem(txt)
    {
    }
    
    PaletteWidget::Item::~Item()
    {
    }

    PaletteWidget::Pane::Pane(PaletteWidget* pw, QWidget*parent) : QListWidget(parent), m_widget(pw)
    {
        setSupportedDragActions(Qt::CopyAction);
    }
    
    PaletteWidget::Pane::~Pane()
    {
    }

    PaletteWidget::Item*   PaletteWidget::Pane::addItem(Item*it)
    {
        if(it)
            QListWidget::addItem(it);
        return it;
    }

    PaletteWidget::Item*   PaletteWidget::Pane::addItem(const QString&txt)
    {
        return addItem( m_widget->createItem(txt) );
    }

    QMimeData *	PaletteWidget::Pane::mimeData(const QList<QListWidgetItem *> &items) const
    {
        return m_widget -> mimeData(items);
    }
}

#include "moc_PaletteWidget.cpp"


