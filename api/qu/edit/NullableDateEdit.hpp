////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/undo/UndoBase.hpp>
#include <QWidget>

class QDate;

namespace qu {
    class CheckBox;
    class DateEdit;
    
    class NullableDateEdit : public QWidget, public UndoBase {
        Q_OBJECT
    public:

        NullableDateEdit(QWidget*parent=nullptr);
        ~NullableDateEdit();
        
        QDate       date() const;
        void        setDate(const QDate&);

        void        setDisplayFormat(const QString&);

        //  TODO: Currently, the *ACTUAL* undo tie in is not yet implemented

    private slots:
        void        stateChanged(int);

    signals:
        void        editingFinished();
    private:

        CheckBox*   m_good;
        DateEdit*   m_date;    
        bool        m_null;
    };
}
