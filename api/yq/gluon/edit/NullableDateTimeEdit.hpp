////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/undo/UndoBase.hpp>
#include <QWidget>

class QDateTime;

namespace yq::gluon {

    class CheckBox;
    class DateTimeEdit;
    
    /*! \brief Date Time Widget with Null option
    */
    class NullableDateTimeEdit : public QWidget, public UndoBase {
        Q_OBJECT
    public:

        //! Constructor
        NullableDateTimeEdit(QWidget*parent=nullptr);
        
        //! Destructor
        ~NullableDateTimeEdit();
        
        //! Current date-time of the widget
        QDateTime   dateTime() const;
        
        //! Set date time of the widget
        void        setDateTime(const QDateTime&);

        //! Set the display format (defaults to ISO)
        void        setDisplayFormat(const QString&);

        //  TODO: Currently, the *ACTUAL* undo tie in is not yet implemented

    private slots:
        void        stateChanged(int);

    signals:
        //! Signal for editing-is-finished
        void        editingFinished();
    private:

        CheckBox*       m_good;
        DateTimeEdit*   m_date;    
        bool            m_null;
    };

}
