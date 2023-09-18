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

        //! Constructor
        WidgetTabBar(QWidget* parent=nullptr);
        
        //! Destructor
        virtual ~WidgetTabBar();
        
        using QTabBar::addTab;
        
        //! Add tab
        int                 addTab(QWidget*);
        
        //! Get all tabs
        Vector<QWidget*>    allWidgets() const;
        
        //! Current widget
        QWidget*            currentWidget() const;
        
        //! TRUE if drag is enabled
        bool                dragEnabled() const { return m_dragEnable; }
        
        //! Drag mime type
        const QString&      dragMimeType() const { return m_dragMimeType; }
        
        //! TRUE if drop enabled
        bool                dropEnabled() const { return m_dropEnable; }
        
        using QTabBar::removeTab;
        
        //! Remove specified tab
        void                removeTab(QWidget*);
        
        //! Tab index for widget
        int                 tabIndex(QWidget*) const;
        
        //! Widget for tab index
        QWidget*            tabWidget(int) const;
        
    public slots:
        //! Set the mime type
        void                setDragMimeType(const QString&);
        
        //! Set the drag-enabled flag
        void                setDragEnabled(bool);
        
        //! Set the drop-enabled tag
        void                setDropEnabled(bool);
        
        //! Update the tab's icon for widget
        void                updateTabIcon(QWidget*);
        
        //! Update the tab's text for widget
        void                updateTabText(QWidget*);


    protected:
    
        //! Mouse press event handler
        virtual void        mousePressEvent(QMouseEvent*) override;
        
        //! Mouse move event handler
        virtual void        mouseMoveEvent(QMouseEvent*) override;
        
        //! Mouse release event handler
        virtual void        mouseReleaseEvent(QMouseEvent*) override;
        
        //! Drag enter (widget) event handler
        virtual void        dragEnterEvent(QDragEnterEvent*) override;
        
        //! Drag move event handler
        virtual void        dragMoveEvent(QDragMoveEvent*) override;
        
        //! Drop event handler
        virtual void        dropEvent(QDropEvent*) override;

        //! Tab inserted event handler
        virtual void        tabInserted(int) override;
        
        //! Tab removed event handler
        virtual void        tabRemoved(int) override;
        
        //void    dragMoveEvent(QDragMoveEvent*) override;

    signals:
        //! Emitted that the drag has started of tab
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
