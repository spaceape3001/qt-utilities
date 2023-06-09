////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "WidgetTabBar.hpp"
#include <QDragEnterEvent>
#include <QIcon>
#include <QMimeData>

namespace yq::gluon {
    WidgetTabBar::WidgetTabBar(QWidget* parent) : QTabBar(parent), 
        m_height(30),
        m_tab(-1),
        m_dragEnable(false),
        m_dropEnable(false)
    {
        connect(this, &QTabBar::tabMoved, this, &WidgetTabBar::_recalc);
    }

    WidgetTabBar::~WidgetTabBar()
    {
    }

    void        WidgetTabBar::_recalc()
    {
        m_wid2idx.clear();
        for(int i=0;i<count();++i){
            QWidget*w   = tabWidget(i);
            if(w)
                m_wid2idx[w]    = i;
        }
    }

    int         WidgetTabBar::addTab(QWidget* w)
    {
        int i   = QTabBar::addTab(w->windowIcon(), w->windowTitle());
        setTabData(i, QVariant::fromValue(w));
        m_wid2idx[w]    = i;
        return i;
    }

    Vector<QWidget*>    WidgetTabBar::allWidgets() const
    {
        Vector<QWidget*>    ret;
        for(int i=0;i<count();++i){
            QWidget*    w   = tabWidget(i);
            if(w)
                ret << w;
        }
        return ret;
    }

    QWidget*    WidgetTabBar::currentWidget() const
    {
        return tabWidget(currentIndex());
    }

    void    WidgetTabBar::dragEnterEvent(QDragEnterEvent* evt)
    {
            //  TODO: Add FILE Support....
        if(m_dropEnable){
            const QMimeData*    data    = evt -> mimeData();
            if(data && data->hasFormat(m_dragMimeType)){
                evt -> acceptProposedAction();
            } else
                evt -> ignore();
        } else
            evt -> ignore();
    }

    void    WidgetTabBar::dragMoveEvent(QDragMoveEvent*evt) 
    {
        if(m_dropEnable){
            const QMimeData*    data    = evt -> mimeData();
            if(data && data->hasFormat(m_dragMimeType)){
                evt -> acceptProposedAction();
            } else
                evt -> ignore();
        } else
            evt -> ignore();
    }


    #if 0
    void    WidgetTabBar::dragMoveEvent(QDragMoveEvent* evt) 
    {
        qDebug() << "DragMoveEvent";
        
        if(m_tab >= 0){
            QPoint      gp  = QCursor::pos(); // evt -> globalPos();
            if(abs(gp.y() - m_start.y()) >= m_height)
                QMessageBox::information(nullptr, tr("Drag Detected"), 
                    tr("A drag action was detected!"));
        }
        QTabBar::dragMoveEvent(evt);
    }
    #endif


    void    WidgetTabBar::dropEvent(QDropEvent*evt)
    {
        if(m_dropEnable){
            const QMimeData*    data    = evt -> mimeData();
            if(data && data->hasFormat(m_dragMimeType)){
                evt -> acceptProposedAction();
            } else
                evt -> ignore();
        } else
            evt -> ignore();
    }

    void    WidgetTabBar::mousePressEvent(QMouseEvent*evt) 
    {
        m_inDrag    = false;
        if(m_dragEnable){
            if(evt->button() == Qt::LeftButton){
                QPoint      p   = evt->pos();
                QPoint      gp  = evt->globalPos();
                m_start         = gp;
                m_tab           = tabAt(p);
                if(m_tab >= 0)
                    m_height     = tabRect(m_tab).height();
                //qDebug() << "Mouse Press, " << p.x() << p.y() << " [global " << gp.x() << gp.y() << "] tab " << m_tab;
            }
        }
        QTabBar::mousePressEvent(evt);
    }

    void    WidgetTabBar::mouseMoveEvent(QMouseEvent* evt) 
    {
        if(m_dragEnable){
            if(m_inDrag){
                evt -> ignore();
                return ;
            }
            
            QSize       sz  = size();
            if(m_tab >= 0){
                //QPoint      p   = evt->pos();
                QPoint      gp  = evt->globalPos();
                if(abs(m_start.y() - gp.y()) >= sz.height()){
                    int     tab = m_tab;
                    m_tab       = -1;
                    emit dragStarted(tab);
                    m_inDrag    = true;
                }
            }
        }
        QTabBar::mouseMoveEvent(evt);
    }

    void    WidgetTabBar::mouseReleaseEvent(QMouseEvent*evt) 
    {
        if(m_dragEnable){
            if(m_inDrag)
                evt -> ignore();
            else
                QTabBar::mouseReleaseEvent(evt);

            m_tab        = -1;
            m_inDrag    = false;
        } else
            QTabBar::mouseMoveEvent(evt);
    }

    void        WidgetTabBar::removeTab(QWidget* w)
    {
        int i   = m_wid2idx.get(w, -1);
        if(i>=0){
            QTabBar::removeTab(i);
            _recalc();
        }
    }

    void        WidgetTabBar::setDragMimeType(const QString& t)
    {
        m_dragMimeType  = t;
    }

    void        WidgetTabBar::setDragEnabled(bool f)
    {
        m_dragEnable   = f;
    }

    void        WidgetTabBar::setDropEnabled(bool f)
    {
        m_dropEnable   = f;
        setAcceptDrops(f);
    }

    int         WidgetTabBar::tabIndex(QWidget*w) const
    {
        return m_wid2idx.get(w,-1);
    }

    void        WidgetTabBar::tabInserted(int) 
    {
        _recalc();
    }

    void        WidgetTabBar::tabRemoved(int) 
    {
        _recalc();
    }
        
    QWidget*    WidgetTabBar::tabWidget(int i) const
    {
        static const int    utWidget    = qMetaTypeId<QWidget*>();
        if(i<0)
            return nullptr;
        QVariant    var = tabData(i);
        if(var.userType() != utWidget)
            return nullptr;
        return var.value<QWidget*>();
    }


    void        WidgetTabBar::updateTabIcon(QWidget*w)
    {
        int i   = tabIndex(w);
        if(i>=0){
            setTabIcon(i, w->windowIcon());
        }
    }
        

    void        WidgetTabBar::updateTabText(QWidget*w)
    {
        int i   = tabIndex(w);
        if(i>=0){
            setTabText(i, w->windowTitle());
        }
    }
}

