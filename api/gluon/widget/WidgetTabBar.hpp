////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Hash.hpp>
#include <basic/Vector.hpp>

#include <QPoint>
#include <QTabBar>

namespace yq::gluon {

    /*! \brief Tab Bar where tabs represent widgets
    */
    class WidgetTabBar : public QTabBar {
        Q_OBJECT
        
    public:

        WidgetTabBar(QWidget* parent=nullptr);
        virtual ~WidgetTabBar();
        
        using QTabBar::addTab;
        
        int                 addTab(QWidget*);
        Vector<QWidget*>    allWidgets() const;
        QWidget*            currentWidget() const;
        bool                dragEnabled() const { return m_dragEnable; }
        const QString&      dragMimeType() const { return m_dragMimeType; }
        bool                dropEnabled() const { return m_dropEnable; }
        
        using QTabBar::removeTab;
        void                removeTab(QWidget*);
        int                 tabIndex(QWidget*) const;
        QWidget*            tabWidget(int) const;
        
    public slots:
        void                setDragMimeType(const QString&);
        void                setDragEnabled(bool);
        void                setDropEnabled(bool);
        void                updateTabIcon(QWidget*);
        void                updateTabText(QWidget*);


    protected:
        virtual void        mousePressEvent(QMouseEvent*) override;
        virtual void        mouseMoveEvent(QMouseEvent*) override;
        virtual void        mouseReleaseEvent(QMouseEvent*) override;
        
        virtual void        dragEnterEvent(QDragEnterEvent*) override;
        virtual void        dragMoveEvent(QDragMoveEvent*) override;
        virtual void        dropEvent(QDropEvent*) override;

        virtual void        tabInserted(int) override;
        virtual void        tabRemoved(int) override;
        
        //void    dragMoveEvent(QDragMoveEvent*) override;

    signals:
        void    dragStarted(int tab);
    private:
    //    friend class TDIWidget;
        
        QString     m_dragMimeType;
        QPointF     m_start;
        int         m_height;
        int         m_tab;
        bool        m_inDrag;
        bool        m_dragEnable;
        bool        m_dropEnable;

        Hash<QWidget*,int>  m_wid2idx;
        void        _recalc();
    };
}
