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

    /*! \brief A marker for a TDI/MDI widget
    
        This marks the widget as being a TDI/MDI type of widget, 
        something that's sort of application like, but not quite,
        it's a complex widget with signals/slots/state.
    */
    class SubWindow : public QWidget {
        Q_OBJECT
    public:
    
        //! Default constructor
        SubWindow(QWidget*parent=nullptr);
        
        //! Destructor
        virtual ~SubWindow();
        
        //! Current status message
        const QString&  currentStatus() const { return m_status; }
        
    signals:
        //!     Status message changed (gui-thread only)
        void    statusMessage(const QString&);
        
        //!     Used to force the status message to the main thread
        void    threadSync_status(const QString&, unsigned int);
    protected:
        //!     Set the status message
        void    status(const QString& msg=QString(), unsigned int kTimeout=0);
        
        //!     Helper, equiv to QVBoxLayout* wrapped
        void    setWidget(QWidget*);
        
    private slots:
        //!     Clear the status
        void    clearStatus();
        
    private:
        QString         m_status;
        QTimer*         m_statusTimer = nullptr;
        QLayout*        m_layout    = nullptr;
    };
}
