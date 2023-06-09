////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "WidgetTabWidget.hpp"
#include "WidgetTabBar.hpp"
#include <QBoxLayout>
#include <QMenu>
#include <QMetaMethod>
#include <QStackedLayout>
#include <QToolButton>

namespace yq::gluon {

    WidgetTabWidget::WidgetTabWidget(QWidget*parent) : QWidget(parent),
        m_add(nullptr), m_addCount(-1), m_layout(nullptr), m_list(nullptr),
        m_stack(nullptr), m_tabs(nullptr)
    {
        m_layout    = new QBoxLayout(QBoxLayout::TopToBottom);
        m_layout -> setContentsMargins(0,0,0,0);
        m_layout -> setSpacing(0);
        
        QHBoxLayout*        tline   = new QHBoxLayout;
        tline -> setSpacing(0);
        tline -> setContentsMargins(0,0,0,0);

        m_add = new QToolButton(this);
        m_add -> setText("+");
        
        m_list = new QToolButton(this);
        m_list -> setText("V");
        
        m_tabs  = new WidgetTabBar(this);
        m_tabs -> setShape( QTabBar::RoundedNorth );
        
        tline -> addWidget(m_tabs);
        tline -> addWidget(m_add);
        tline -> addStretch();
        tline -> addWidget(m_list);
        
        m_add -> setVisible(false);
        m_list -> setVisible(false);
        
        m_layout -> addLayout(tline, 0);
        m_stack = new QStackedLayout;
        m_stack -> setContentsMargins(0,0,0,0);
        m_stack -> setSpacing(0);
        m_layout -> addLayout(m_stack, 1);
        
        setLayout(m_layout);
        
        connect(m_add, &QToolButton::clicked, this, &WidgetTabWidget::addRequest);
        connect(m_tabs, &WidgetTabBar::tabBarClicked, this, &WidgetTabWidget::tabClicked);
        connect(m_tabs, &WidgetTabBar::currentChanged, this, &WidgetTabWidget::tabClicked);
        connect(m_tabs, &WidgetTabBar::tabCloseRequested, this, &WidgetTabWidget::tabCloseRequest);
        connect(m_list, &QToolButton::clicked, this, &WidgetTabWidget::listWidgets);
        connect(m_tabs, &WidgetTabBar::dragStarted, this, &WidgetTabWidget::dragStarted);
        
        m_addCount  =    0;
    }

    WidgetTabWidget::~WidgetTabWidget()
    {
    }

    void    WidgetTabWidget::_incAdd()
    {
        if(++m_addCount == 1)
            m_add -> setVisible(true);
    }

    void    WidgetTabWidget::_decAdd()
    {
        if(--m_addCount == 0)
            m_add -> setVisible(false);
    }

    void    WidgetTabWidget::addWidget(QWidget* w)
    {
        m_tabs -> addTab(w);
        m_stack -> addWidget(w);
        m_stack -> setCurrentWidget(w);
        w->setAttribute(Qt::WA_DeleteOnClose, true);
        currentChanged();
    }

    void    WidgetTabWidget::closeAll()
    {
        for(QWidget*w : m_tabs->allWidgets())
            w -> close();
    }

    int         WidgetTabWidget::count() const
    {
        return m_tabs -> count();
    }

    QWidget*    WidgetTabWidget::currentWidget() const
    {
        return m_tabs -> currentWidget();
    }

    void    WidgetTabWidget::connectNotify(const QMetaMethod& mm)
    {
        if(mm == QMetaMethod::fromSignal(&WidgetTabWidget::addRequest)){
            _incAdd();
        }
    }

    void    WidgetTabWidget::delWidget(QWidget* w)
    {
        if(w){
            bool    f   = m_stack -> currentWidget() == w;
            m_stack -> removeWidget(w);
            m_tabs -> removeTab(w);
            if(f)
                emit currentChanged();
        }
    }

    void    WidgetTabWidget::disconnectNotify(const QMetaMethod& mm)
    {
        //if(!mm.isValid()){
            //_decAdd();
        //} else if(mm == QMetaMethod::fromSignal(&WidgetTabWidget::addRequest)){
            //_decAdd();
        //}
    }


    bool    WidgetTabWidget::listEnabled() const
    {
        return m_list -> isVisible();
    }

    void    WidgetTabWidget::listWidgets()
    {
        QMenu*  m   = new QMenu;
        Hash<QAction*, QWidget*>    act2wid;
        for(QWidget* w : m_tabs -> allWidgets()){
            QAction*    act = m -> addAction( w->windowIcon(), w->windowTitle());
            act2wid[act]  = w;
        }
        QAction* act = m -> exec();
        delete m;
        if(act){
            QWidget*w   = act2wid.get(act, nullptr);
            if(w){
                setCurrent(w);
            }
        }
    }

    void    WidgetTabWidget::removeTab(int n)
    {
        delWidget(widget(n));
    }

    void    WidgetTabWidget::removeTab(QWidget*w)
    {
        delWidget(w);
    }

    void    WidgetTabWidget::setCurrent(QWidget*w)
    {
        int idx = m_tabs -> tabIndex(w);
        if((idx >= 0) && (w != currentWidget())){
            m_tabs -> setCurrentIndex(idx);
            m_stack -> setCurrentWidget(w);
            emit currentChanged();
        }
    }

    void    WidgetTabWidget::setTopSide(bool f)
    {
        m_layout -> setDirection( f ? QBoxLayout::TopToBottom : QBoxLayout::BottomToTop );
        m_tabs -> setShape(f ? QTabBar::RoundedNorth : QTabBar::RoundedSouth);
    }

    void    WidgetTabWidget::setListEnable(bool f)
    {
        m_list -> setVisible(f);
    }

    void    WidgetTabWidget::tabClicked(int n)
    {
        QWidget* wi = m_tabs -> tabWidget(n);
        if(wi){
            m_stack -> setCurrentWidget(wi);
            emit currentChanged();
        }
    }

    void    WidgetTabWidget::tabCloseRequest(int n)
    {
        QWidget*wi  = m_tabs -> tabWidget(n);
        if(wi)
            wi -> close();
    }

    bool    WidgetTabWidget::topSide() const
    {
        return m_layout -> direction() == QBoxLayout::TopToBottom;
    }

    QWidget*    WidgetTabWidget::widget(int n) const
    {
        return m_tabs -> tabWidget(n);
    }
}
