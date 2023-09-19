////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QWidget>
#include <basic/Hash.hpp>

class QAction;
class QBoxLayout;
class QMenu;
class QToolButton;
class QStackedLayout;

namespace yq::gluon {
    class WidgetTabBar;

    /*! \brief Tab widget
    
        Tab widget that holds widgets (like windows)
    */
    class WidgetTabWidget : public QWidget {
        Q_OBJECT
    public:
    
        //! Constructor
        WidgetTabWidget(QWidget*parent=nullptr);
        
        //! Destructor
        ~WidgetTabWidget();
        
        //! The tab bar
        WidgetTabBar*   bar() const { return m_tabs; }
        
        //! Adds a widget
        void            addWidget(QWidget*);
        
        //! Count of widgets
        int             count() const;
        
        //! Currently active widget
        QWidget*        currentWidget() const;
        
        //! Deletes widget
        void            delWidget(QWidget*);
        
        //! True if Widget list is showing
        bool            listEnabled() const;
        
        //! Tab bar (alternate accessor)
        WidgetTabBar*   tabs() const { return m_tabs; }
        
        //! TRUE if tabs are on top
        bool            topSide() const;
        
        //! Removes the specified tab by index
        void            removeTab(int);
        
        //! Removes the specified tab by pointer
        void            removeTab(QWidget*);
        
        //! Gets the specified widget by index
        QWidget*        widget(int) const;
        
    public slots:
    
        //! TRUE sets the tabs to the top side
        void    setTopSide(bool);
        
        //! Enables the list if true
        void    setListEnable(bool);
        
        //! Close all tabs
        void    closeAll();
        
        //! Sets the current widget
        void    setCurrent(QWidget*);
        
    signals:
    
        //! Add button pressed
        void    addRequest();
        
        //! Drag started
        void    dragStarted(int);
        
        //! Current tab changed
        void    currentChanged();
        
    private slots:
        
        void    listWidgets();
        void    tabClicked(int);
        void    tabCloseRequest(int);
        
    protected:
    
        void    connectNotify(const QMetaMethod&) override;
        void    disconnectNotify(const QMetaMethod&) override;

    private:
        QToolButton*                m_add;
        int                         m_addCount;
        QBoxLayout*                 m_layout;
        QToolButton*                m_list;
        QStackedLayout*             m_stack;
        WidgetTabBar*               m_tabs;
        
        void    _incAdd();
        void    _decAdd();
    };
}

