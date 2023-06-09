////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/undo/UndoBase.hpp>
#include <QWidget>

class QDateTime;

namespace yq::gluon {

    class CheckBox;
    class DateTimeEdit;
    
    /*! \brief Date Time Widget with Null
    */
    class NullableDateTimeEdit : public QWidget, public UndoBase {
        Q_OBJECT
    public:

        NullableDateTimeEdit(QWidget*parent=nullptr);
        ~NullableDateTimeEdit();
        
        QDateTime   dateTime() const;
        void        setDateTime(const QDateTime&);

        void        setDisplayFormat(const QString&);

        //  TODO: Currently, the *ACTUAL* undo tie in is not yet implemented

    private slots:
        void        stateChanged(int);

    signals:
        void        editingFinished();
    private:

        CheckBox*       m_good;
        DateTimeEdit*   m_date;    
        bool            m_null;
    };

}
