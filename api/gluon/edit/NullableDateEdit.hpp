////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/undo/UndoBase.hpp>
#include <QWidget>

class QDate;

namespace yq::gluon {
    class CheckBox;
    class DateEdit;
    
    /*! \brief Data Edit Allowigng for Null
    
        This is a date edit that allows for a null (non-set) date
    */
    class NullableDateEdit : public QWidget, public UndoBase {
        Q_OBJECT
    public:

        //! Constructor
        NullableDateEdit(QWidget*parent=nullptr);
        
        //! Destructor
        ~NullableDateEdit();
        
        //! Current date
        QDate       date() const;
        
        //! Sets the date
        void        setDate(const QDate&);
    
        //! Sets the Display format (defaults to ISO)
        void        setDisplayFormat(const QString&);

        //  TODO: Currently, the *ACTUAL* undo tie in is not yet implemented

    private slots:
        void        stateChanged(int);

    signals:
        //! Triggered when editing is finished
        void        editingFinished();
    private:

        CheckBox*   m_good;
        DateEdit*   m_date;    
        bool        m_null;
    };
}
