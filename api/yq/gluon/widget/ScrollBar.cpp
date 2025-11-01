////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ScrollBar.hpp"
#include <QGuiApplication>
#include <QScreen>

namespace yq::gluon {
    ScrollBar::ScrollBar(QWidget *parent) : QScrollBar(parent)
    {
    }
    
    ScrollBar::ScrollBar(Qt::Orientation orientation, QWidget *parent) : QScrollBar(orientation, parent)
    {
    }
    
    ScrollBar::~ScrollBar()
    {
    }
    
    QSize ScrollBar::sizeHint() const 
    {
        QSize   vs  = QGuiApplication::primaryScreen()->virtualSize();
        QSize   sh  = QScrollBar::sizeHint();
        if(orientation() == Qt::Horizontal){
            return QSize(vs.width(), sh.height());
        } else {
            return QSize(sh.width(), vs.height());
        }
    }
}

#include "moc_ScrollBar.cpp"
