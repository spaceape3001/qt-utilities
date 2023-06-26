////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QWidget>

class QTimer;
class QLayout;

namespace yq::gluon {

    class SubWindow : public QWidget {
        Q_OBJECT
    public:
        SubWindow(QWidget*parent=nullptr);
        virtual ~SubWindow();
        
        const QString&  currentStatus() const { return m_status; }
        
    signals:
        void    statusMessage(const QString&);
        void    threadSync_status(const QString&, unsigned int);
    protected:
        void    status(const QString& msg=QString(), unsigned int kTimeout=0);
        
        //! Helper, equiv to QVBoxLayout* wrapped
        void    setWidget(QWidget*);
        
    private slots:
        void    clearStatus();
    private:
        QString         m_status;
        QTimer*         m_statusTimer = nullptr;
        QLayout*        m_layout    = nullptr;
    };
}
