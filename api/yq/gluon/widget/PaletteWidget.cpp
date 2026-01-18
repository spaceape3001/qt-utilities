////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "PaletteWidget.hpp"
#include <yq/core/Any.hpp>
#include <QMimeData>
#include <QDrag>

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
        connect(p, &QListWidget::itemPressed, this, &PaletteWidget::itemPressed);
        
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

    void    PaletteWidget::itemPressed(QListWidgetItem* qwi)
    {
        if(!m_dragEnabled)
            return;

        Item* it = dynamic_cast<Item*>(qwi);
        if(!it)
            return;

        QMimeData*  data    = mimeData(it);
        if(!data)
            return;
                
        QDrag*  drag    = new QDrag(this);
        drag -> setMimeData(data);
        drag -> setPixmap(it->icon().pixmap(QSize(64,64)));
        drag -> exec();
        drag -> deleteLater();
    }

    void    PaletteWidget::setDragEnabled(bool v)
    {
        m_dragEnabled   = v;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    PaletteWidget::Item::Item(const QString& txt) : QListWidgetItem(txt)
    {
    }
    
    PaletteWidget::Item::~Item()
    {
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    PaletteWidget::Pane::Pane(PaletteWidget* pw, QWidget*parent) : QListWidget(parent), m_widget(pw)
    {
        setSupportedDragActions(Qt::CopyAction);
        setViewMode(pw->m_viewMode);
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
}

#include "moc_PaletteWidget.cpp"


