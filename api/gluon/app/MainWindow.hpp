////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QAction>
#include <QMainWindow>

#include <basic/Hash.hpp>
#include <basic/Map.hpp>
#include <basic/Set.hpp>
#include <basic/Vector.hpp>
#include <gluon/core/IgCaseQ.hpp>

class QMenu;
class QMenuBar;
class QString;
class QStringList;

namespace yq::gluon {

    class WidgetTabWidget;

    /*! \brief Main Window Class

        This is the main window class that provides standard utilities
        for a main window (above/beyond QMainWindow).
        
        The main things this adds are:
        +   Easy actions/menus
        +   Thread-safe status message
        +   Tabbing interface
        
        \note Tab interface requires "activateTabs()" to be called in the
        deriving class' constructor!
    */
    class MainWindow : public QMainWindow {
        Q_OBJECT
    public:

        /*! \brief Returns the main window that owns said widget
        
            \param[in]  w   Widget to query
            \return Relevant MainWindow if the widget is owned by one, NULL otherwise
        */
        static MainWindow* mainWinFor(QWidget* w);

        /*! \brief Returns the current active window
            \note   This is only valid when TDI has been activated, and 
                    will *never* return a dock widget!
        */
        QWidget*                activeWindow() const;
        
        /*! \brief Adds a dock widget 
        
            Use sparingly....
        */
        QDockWidget*            addDock(Qt::DockWidgetArea, QWidget*);
        
        /*! \brief Adds a widget to the main window
        
            \note   This is only valid when TDI has been activated.  Uses outside of this will be ignored.
        */
        void                    addWindow(QWidget*);

    public slots:

        /*! \brief Thread-safe status
        
            This will set the status of the main window.  If the caller is *not*
            in the GUI thread, the message will be queued, appropriately, for the
            GUI thread to handle.
            
            \param[in] msg          The message to be displayed
            \param[in] timeout      Timeout (in milliseconds), zero to disable
        */
        void        status(const QString& msg, unsigned int timeout=0);

    signals:
        void        threadSync_status(const QString&, unsigned int);

    protected:
        MainWindow();
        virtual ~MainWindow();

        class Action;

        const Vector<QString>&  actionKeys() const { return m_actionKeys; }

        void                    activateTabs();
        
        /*! \brief Called when the active tab/window is changed 
        
            When overriding, call base, then do your changes.  Be prepared, in
            corner cases, for there to be no real change (ie, same as before).
        */
        virtual void            activeChanged();

        Action                  addAction(
                                    const QString& name,
                                    const QString& text
                                );
        
        void                    addToMenu(QMenu*, const QStringList&);

        virtual void            closeEvent(QCloseEvent*) override;
        const Set<QString>&     defConnected() const { return m_defConnected; }

        virtual void            doCommand(const QString&);

        void                    enableAutoEnableCmds();
        void                    enableClosableTabs();
        /*! \brief Enables specified commands
        
            \note By corollary, any defaults *not* in this set
            will be disabled
        */
        void                    enableDefaultedCommands(const Set<QString>& enableThese);
        void                    enableDetachableTabs(); // implies moveable
        void                    enableMoveableTabs();
        bool                    isAutoEnableCmdsEnabled() const { return m_autoEnableCmds; }

        QMenu*                  makeMenu(const QString&, const QString&, const QStringList&, bool fAddToMenuBar=true);
        QMenu*                  makeMenu(const QString&, const QString&, bool fAddToMenuBar=true);

        virtual MainWindow*        newMain() { return nullptr; }

        virtual bool            okayToClose() { return true; }
        

        virtual void            reconnect(QWidget*);
        //  EVENTS

        WidgetTabWidget*        tdi() const { return m_tdi; }
        
            
    private slots:
        void                    mapAction();
        void                    mapStatus(const QString&);
        void                    tabChanged();
        void                    tabDragStarted(int);

    private:    

        struct WinInfo;
        struct Repo;
        static Repo&        repo();
        
        WinInfo*                activeWinInfo() const;
        WinInfo*                tabWinInfo(int) const;
        QWidget*                tabWidget(int) const;

        Hash<QObject*,QString>          m_act2str;
        Map<QString,QAction*,IgCaseQ>   m_actions;
        Vector<QString>                 m_actionKeys;
        bool                            m_autoEnableCmds;
        Set<QString>                    m_defConnected;
        bool                            m_detachableTabs;
        Map<QString,QMenu*>             m_menus;
        WidgetTabWidget*                m_tdi;
    };

    class MainWindow::Action {
    public:
        Action(Action&&);
        Action& operator=(Action&&);
        ~Action();
        
        operator QAction*() { return m_action; }
        QAction* operator->() { return m_action; }
        
        template <typename FN>
        Action&     connect(FN fn);
        template <class A>
        Action&     connect(A* obj, void (A::*fn)());
        
        Action&     icon(const QString&);
        Action&     icon(const QIcon&);
        
        Action&     shortcut(const QString&);
        Action&     shortcut(const QKeySequence&);
        
    private:
        friend class MainWindow;
        Action(MainWindow*, QAction*, const QString&);
        
        Action(const Action&) = delete;
        Action& operator=(const Action&) = delete;
        
        MainWindow*        m_win;
        QAction*        m_action;
        QString         m_command;
        bool            m_connected;
    };

    template <typename FN>
    MainWindow::Action&     MainWindow::Action::connect(FN fn)
    {
        if(m_action){
            QObject::connect(m_action, &QAction::triggered, fn);
            m_connected = true;
        }
        return *this;
    }

    template <class A>
    MainWindow::Action&     MainWindow::Action::connect(A* obj, void (A::*fn)())
    {
        if(m_action){
            QObject::connect(m_action, &QAction::triggered, obj, fn);
            m_connected = true;
        }
        return *this;
    }


}
