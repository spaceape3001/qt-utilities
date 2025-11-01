////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/app/SubWindow.hpp>
#include <yq/core/ThreadId.hpp>
#include <QTimer>
#include <QVBoxLayout>

namespace yq::gluon {
    SubWindow::SubWindow(QWidget*parent) : QWidget(parent), m_statusTimer(nullptr)
    {
        connect(this, &SubWindow::threadSync_status, this, &SubWindow::status);
        //setAttribute(Qt::WA_DeleteOnClose);
    }

    SubWindow::~SubWindow()
    {
    }

    void    SubWindow::clearStatus()
    {
        if(m_statusTimer)
            m_statusTimer -> stop();
        m_status.clear();
        statusMessage(QString());
    }

    void    SubWindow::status(const QString& txt, unsigned int kTimeout)
    {
        if(is_main_thread()){
            if(m_statusTimer)
                m_statusTimer -> stop();

            if(kTimeout > 0){
                if(!m_statusTimer){
                    m_statusTimer   = new QTimer(this);
                    connect(m_statusTimer, &QTimer::timeout, this, &SubWindow::clearStatus);
                    m_statusTimer -> setSingleShot(true);
                } 
                m_statusTimer -> setInterval(kTimeout);
                m_statusTimer -> start();
            }
            m_status    = txt;
            statusMessage(txt);
        } else
            threadSync_status(txt, kTimeout);
    }

    void    SubWindow::setWidget(QWidget* w)
    {
        if(!m_layout){
            m_layout    = new QVBoxLayout;
            setLayout(m_layout);
        } else {
            //  clear out the old widget
            QLayoutItem*    child;
            while((child = m_layout->takeAt(0)) != nullptr){
                QWidget*    w   = child -> widget();
                if(w)
                    w -> deleteLater();
                delete child;
            }
        }
        
        m_layout -> addWidget(w);
    }
}

#include "moc_SubWindow.cpp"
