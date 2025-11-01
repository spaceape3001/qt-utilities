////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/edit/NullableDateTimeEdit.hpp>
#include <yq/gluon/edit/CheckBox.hpp>
#include <yq/gluon/edit/DateTimeEdit.hpp>

#include <QDateEdit>
#include <QDateTimeEdit>
#include <QHBoxLayout>

namespace yq::gluon {
    NullableDateTimeEdit::NullableDateTimeEdit(QWidget*parent) : QWidget(parent)
    {
        QHBoxLayout*    lay = new QHBoxLayout;
        m_good      = new CheckBox;
        m_date      = new DateTimeEdit;
        
        m_null      = true;
        m_good->setChecked(false);
        m_date->setEnabled(false);

        setContentsMargins(0,0,0,0);
        lay->setContentsMargins(0,0,0,0);

        lay->addWidget(m_good, 0);
        lay->addWidget(m_date, 1);
        setLayout(lay);
        connect(m_good, &CheckBox::checkStateChanged, this, &NullableDateTimeEdit::stateChanged);
        connect(m_date, &QDateTimeEdit::editingFinished, this, &NullableDateTimeEdit::editingFinished);

        m_date->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    }


    NullableDateTimeEdit::~NullableDateTimeEdit()
    {
    }

    void        NullableDateTimeEdit::setDisplayFormat(const QString&s)
    {
        m_date->setDisplayFormat(s);
    }


    QDateTime       NullableDateTimeEdit::dateTime() const
    {
        if(m_null)
            return QDateTime();
        return m_date->dateTime();
    }

    void        NullableDateTimeEdit::stateChanged(int ch)
    {
        if(ch){
            if(m_null){
                m_date->setEnabled(true);
                m_null  = false;
                emit editingFinished();
            }
        } else {
            if(!m_null){
                m_date->setEnabled(false);
                m_null  = true;
                emit    editingFinished();
            }
        }
    }

    void        NullableDateTimeEdit::setDateTime(const QDateTime&dt)
    {
        if(dt != dateTime()){
            if(dt.isNull()){
                m_null  = true;
                m_good  ->setChecked(false);
                m_date  ->setEnabled(false);
            } else {
                m_null  = false;
                m_good  ->setChecked(true);
                m_date  ->setEnabled(true);
                m_date  ->setDateTime(dt);
            }
        }
    }
}

#include "moc_NullableDateTimeEdit.cpp"
