////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "MainWindow.hpp"

#include <yq/basic/ThreadId.hpp>
#include <gluon/app/SubWindow.hpp>
#include <gluon/core/Utilities.hpp>
#include <gluon/widget/WidgetTabBar.hpp>
#include <gluon/widget/WidgetTabWidget.hpp>

#include <QCloseEvent>
#include <QDockWidget>
#include <QDrag>
#include <QMenu>
#include <QMenuBar>
#include <QMetaMethod>
#include <QMimeData>
#include <QStatusBar>

namespace yq::gluon {
    namespace {
        static const char* szMime_TabDrag = "application/x-window-drag";

        template <typename T>
        T*                   ownerFor(QObject* obj)
        {
            for(QObject* q = obj; q; q = q -> parent()){
                T* w   = qobject_cast<T*>(q);
                if(w)
                    return w;
            }
            return nullptr;
        }
    }

    struct MainWindow::WinInfo {
        QWidget*    const           widget;
        SubWindow*     const        subwin;
        Map<QString,QMetaMethod>    act2slot;
        Set<QString>                actions;
        WidgetTabWidget*            tabs;
        QDockWidget*                dock;
        
        explicit WinInfo(QWidget* w) : widget(w), subwin(qobject_cast<SubWindow*>(w)), tabs(nullptr), dock(nullptr)
        {
            const QMetaObject* mo = w -> metaObject();
            for(int i=0;i<mo->methodCount();++i){
                QMetaMethod mm  = mo -> method(i);
                if(mm.parameterCount() > 0)
                    continue;
                if((mm.methodType() == QMetaMethod::Slot) || (mm.methodType() == QMetaMethod::Signal)){
                    QString s   = QString::fromLatin1(mm.name());
                    act2slot[s] = mm;
                    actions << s;
                }
            }
            
            QObject::connect(w, &QWidget::windowIconChanged, [this](const QIcon& ico){
                if(tabs && tabs->bar())
                    tabs->bar()->updateTabIcon(widget);
                if(dock)
                    dock -> setWindowIcon(ico);
            });
         
            QObject::connect(w, &QWidget::windowTitleChanged, [this](const QString& text){
                if(tabs && tabs->bar())
                    tabs->bar()->updateTabText(widget);
                if(dock)
                    dock -> setWindowTitle(text);
            });
        }
    };
        
    struct MainWindow::Repo {
        Hash<QObject*,WinInfo*>     winInfo;
        
        WinInfo*    info(QObject* obj)
        {
            return winInfo.get(obj, nullptr);
        }
        
        WinInfo*    info(QWidget*obj, bool fCreate=false)
        {
            WinInfo*    ret = winInfo.get(obj, nullptr);
            if(ret || !fCreate)
                return ret;
            
            ret = winInfo[obj] = new WinInfo(obj);
            
                //  take care of the "destroyed" signal here... btw, signal is 
                //  issued right before the delete, so obj is still valid
            QObject::connect(obj, &QObject::destroyed, [this, ret ](QObject*obj){
                if(ret -> tabs)
                    ret -> tabs -> removeTab(ret->widget);
                winInfo.erase(obj);
                delete ret;
            });
            return ret;
        }
    };

    MainWindow::Repo& MainWindow::repo()
    {
        static Repo s_repo;
        return s_repo;
    }

    MainWindow* MainWindow::mainWinFor(QWidget* w)
    {
        return ownerFor<MainWindow>(w);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    MainWindow::MainWindow() : 
        m_autoEnableCmds(false), m_detachableTabs(false), m_tdi(nullptr)
    {
        is_main_thread();   // ensuring this is set correctly
        connect(this, &MainWindow::threadSync_status, this, &MainWindow::status, Qt::QueuedConnection);
    }

    MainWindow::~MainWindow()
    {
    }

    void            MainWindow::activeChanged()
    {
            //  temporary until the GUI gets more complex....
        WinInfo*    wi  = activeWinInfo();
        if(wi){
            if(m_autoEnableCmds)
                enableDefaultedCommands( wi -> actions);
            if(wi -> subwin && !wi -> subwin -> currentStatus().isEmpty())
                status(wi->subwin->currentStatus());
        }
    }


    void     MainWindow::activateTabs()
    {
        if(m_tdi)   // already activated
            return ;
        m_tdi       = new WidgetTabWidget(this);
        setCentralWidget(m_tdi);
        m_tdi -> bar() -> setUsesScrollButtons(true);
        connect(m_tdi, &WidgetTabWidget::currentChanged, this, &MainWindow::tabChanged);
    }

    QWidget*        MainWindow::activeWindow() const
    {
        if(m_tdi)
            return m_tdi -> currentWidget();
        return nullptr;
    }


    MainWindow::WinInfo*   MainWindow::activeWinInfo() const
    {
        QWidget*w   = activeWindow();
        if(w)
            return repo().info(w);
        return nullptr;
    }


    MainWindow::Action          MainWindow::addAction(const QString& name,const QString& text)
    {
        QAction*act = m_actions.get(name, nullptr);
        if(act)
            return Action(nullptr, act, QString());
        act = new QAction(text, this);
        m_actions[name]  = act;
        m_actionKeys << name;
        m_act2str[act]  = name;
        return Action(this, act, name);
    }

    QDockWidget*    MainWindow::addDock(Qt::DockWidgetArea a, QWidget*w)
    {
        QDockWidget*    dw  = qobject_cast<QDockWidget*>(w);
        if(dw){
            addDockWidget(a, dw);
        } else {
            dw      = new QDockWidget;
            dw->setWidget(w);
            dw->setWindowTitle(w->windowTitle());
            dw->setWindowIcon(w->windowIcon());
            connect(w, &QWidget::windowTitleChanged, dw, &QWidget::setWindowTitle);
            connect(w, &QWidget::windowIconChanged, dw, &QWidget::setWindowIcon);
            addDockWidget(a, dw);
        }
        return dw;
    }

    void            MainWindow::addToMenu(QMenu* men, const QStringList& cmds)
    {
        for(const QString& c : cmds){
            if(c == "--"){
                men -> addSeparator();
                continue;
            }
            QMenu*      m2 = m_menus.get(c, nullptr);
            if(m2){
                men->addMenu(m2);
                continue;
            }
            QAction*    act = m_actions.get(c, nullptr);
            if(act){
                men->addAction(act);
                continue;
            }
        }
    }

    void            MainWindow::addWindow(QWidget* w)
    {
        if(m_tdi){
            WinInfo*    wi  = repo().info(w, true);
            wi -> tabs  = m_tdi;
            wi -> dock  = nullptr;
            m_tdi -> addWidget(w);
            reconnect(w);
        }
    }


    void   MainWindow::closeEvent(QCloseEvent*evt)
    {
        if(okayToClose())
            evt -> accept();
        else
            evt -> ignore();
    }


    void    MainWindow::doCommand(const QString&k)
    {
        WinInfo*    wi  = activeWinInfo();
        if(wi){
            QMetaMethod mm = wi->act2slot.get(k);
            if(mm.isValid())
                mm.invoke(wi->widget);
        }
    }


    void            MainWindow::enableAutoEnableCmds()
    {
        m_autoEnableCmds    = true;
    }

    void            MainWindow::enableClosableTabs()
    {
        if(m_tdi && m_tdi -> bar())
            m_tdi -> bar() -> setTabsClosable(true);
    }

    void            MainWindow::enableDefaultedCommands(const Set<QString>& enableThese)
    {
        for(auto& i : m_actions){
            if(m_defConnected.has(i.first))
                i.second -> setEnabled(enableThese.has(i.first));
        }
    }

    void            MainWindow::enableDetachableTabs()
    {
        if(m_tdi && m_tdi -> bar()){
            WidgetTabBar* tb  = m_tdi -> bar();
            tb -> setMovable(true);
            tb -> setDragEnabled(true);
            tb -> setDropEnabled(true);
            tb -> setDragMimeType(szMime_TabDrag);

            QObject::connect(m_tdi, &WidgetTabWidget::dragStarted, this, &MainWindow::tabDragStarted);
        }
    }

    void            MainWindow::enableMoveableTabs()
    {
        if(m_tdi && m_tdi -> bar())
            m_tdi -> bar() -> setMovable(true);
    }
    
    

    QMenu*          MainWindow::makeMenu(const QString&name, const QString&label, const QStringList&cmds, bool fAddToMenuBar)
    {
        QMenu* men  = m_menus.get(name, nullptr);
        if(men)
            return men;
        men     = new QMenu(label);
        m_menus[name]   = men;
        addToMenu(men, cmds);
        if(fAddToMenuBar)
            menuBar() -> addMenu(men);

        return men;
    }

    QMenu*          MainWindow::makeMenu(const QString&name, const QString&label, bool fAddToMenuBar)
    {
        return makeMenu(name, label, QStringList(), fAddToMenuBar);
    }

    void            MainWindow::mapAction()
    {
        QString     s   = m_act2str.get(sender());
        if(!s.isEmpty())
            doCommand(s);
    }

    void            MainWindow::mapStatus(const QString&msg)
    {
        WinInfo*    wi  = repo().info(sender());
        if(!wi)
            return ;
        if(wi != activeWinInfo())
            return ;
        status(msg);
    }

    QMenu*          MainWindow::menu(const QString&name)
    {
        return m_menus.get(name, nullptr);
    }

    void            MainWindow::reconnect(QWidget*w)
    {
        connect(w, &QObject::destroyed, this, &MainWindow::widgetDeleted);
        WinInfo*    wi  = repo().info(w,true);
        if(wi -> subwin)
            connect(wi -> subwin, &SubWindow::statusMessage, this, &MainWindow::mapStatus);
    }


    void            MainWindow::status(const QString& msg, unsigned int timeout)
    {
        if(is_main_thread()){
            statusBar() -> showMessage(msg, (int) timeout);
        } else
            emit threadSync_status(msg, timeout);
    }

    void            MainWindow::tabChanged()
    {
        activeChanged();
    }

    void        MainWindow::tabDragStarted(int tab)
    {
        QWidget*w   = tabWidget(tab);
        if(!w)
            return ;
            
        QRect       rect    = QRect(QPoint(0,0), w -> size());
        QPixmap pixmap(rect.size());
        w -> render(&pixmap, QPoint(), QRegion(rect));
        
        //Mime*       mimeData    = new Mime(w);
        QMimeData*  mimeData    = new QMimeData;
        mimeData -> setData(szMime_TabDrag, QByteArray());
        QDrag*      drag        = new QDrag(this);
        drag -> setMimeData(mimeData);
        drag -> setPixmap(pixmap);
        drag -> exec();
        
            /*
                This may or may not be the best implementation, however, I just
                need a basic one to work (doesn't have to be perfect...)
            */
        
        MainWindow*        tgt  = ownerFor<MainWindow>(drag -> target());
        MainWindow*        mw   = this;
        if(!tgt){
            QPoint  gp  = QCursor::pos();
            
            // relocate the tab....
            mw  = newMain();
            m_tdi -> removeTab(tab);
            mw -> resize(size());
            mw -> move(gp);
            
            disconnect(w);
            w -> disconnect(this);
            mw -> addWindow(w);
            mw -> show();
        } else if(tgt != this){
            m_tdi-> removeTab(tab);
            tgt  -> addWindow(w);
            disconnect(w);
            w -> disconnect(this);
        }
        
        if(m_tdi -> count() <= 0)
            close();
    }

    QWidget*        MainWindow::tabWidget(int tab) const
    {
        if(!m_tdi)
            return nullptr;
        return m_tdi -> widget(tab);
    }

    MainWindow::WinInfo*   MainWindow::tabWinInfo(int tab) const
    {
        if(!m_tdi)
            return nullptr;
        return repo().info(m_tdi -> currentWidget());
    }

    void            MainWindow::widgetDeleted(QObject* obj)
    {
        if(m_tdi)
            m_tdi -> removeTab(static_cast<QWidget*>(obj));
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    MainWindow::Action::Action(Action&& mv) : 
        m_win(mv.m_win), m_action(mv.m_action), m_command(mv.m_command), m_connected(mv.m_connected)
    {
        mv.m_win    = nullptr;
        mv.m_action = nullptr;
    }

    MainWindow::Action& MainWindow::Action::operator=(Action&&mv )
    {
        if(&mv != this){
            m_win   = mv.m_win;
            m_action    = mv.m_action;
            m_command   = mv.m_command;
            m_connected = mv.m_connected;
            mv.m_win    = nullptr;
            mv.m_action = nullptr;
        }
        return *this;
    }

    MainWindow::Action::~Action()
    {
        if(m_win && m_action && !m_connected){
            QObject::connect(m_action, &QAction::triggered, m_win, &MainWindow::mapAction );
            m_win -> m_defConnected << m_command;
        }
    }


    MainWindow::Action::Action(MainWindow*mw, QAction*act, const QString&cmd) : 
        m_win(mw), m_action(act), m_command(cmd), m_connected(false)
    {
    }

    MainWindow::Action&     MainWindow::Action::icon(const QString& ico)
    {
        if(!ico.isEmpty())
            icon(fetchIcon(ico));
        return *this;
    }

    MainWindow::Action&     MainWindow::Action::icon(const QIcon& ico)
    {
        if(!ico.isNull())
            m_action -> setIcon(ico);
        return *this;
    }


    MainWindow::Action&     MainWindow::Action::shortcut(const QString& scut)
    {
        if(!scut.isEmpty())
            m_action -> setShortcut(scut);
        return *this;
    }

    MainWindow::Action&     MainWindow::Action::shortcut(const QKeySequence& kseq)
    {
        m_action -> setShortcut(kseq);
        return *this;
    }

}
