////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/preamble.hpp>
#include <gluon/core/IgCase.hpp>
#include <gluon/undo/UndoBase.hpp>
#include <basic/Map.hpp>
#include <QWidget>

namespace yq::gluon {

    class CheckBox;
    class FlowLayout;

    class StringSetCheck : public QWidget, public UndoBase {
        Q_OBJECT
    public:
        
        StringSetCheck(QWidget* parent=nullptr);
        ~StringSetCheck();
        
        void                setItems(const QStringSet&);
        void                setChecked(const QStringSet&);
        void                setFixed(const QStringSet&);
        QStringSet          checked(bool fIncFixed=false) const;

    public slots:
        void                clear();
        void                setReadOnly(bool);
        
    signals:
        void                changed();
        
    private:
        FlowLayout*                         m_layout;
        Map<QString,CheckBox*,IgCaseQ>      m_checks;
    };
}
