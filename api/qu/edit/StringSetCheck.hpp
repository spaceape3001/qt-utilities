////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/preamble.hpp>
#include <qu/core/IgCase.hpp>
#include <qu/undo/UndoBase.hpp>
#include <basic/Map.hpp>
#include <QWidget>

namespace qu {

    class CheckBox;
    class FlowLayout;

    class StringSetCheck : public QWidget, public UndoBase {
        Q_OBJECT
    public:
        
        StringSetCheck(QWidget* parent=nullptr);
        ~StringSetCheck();
        
        void                setItems(const StringSet&);
        void                setChecked(const StringSet&);
        void                setFixed(const StringSet&);
        StringSet           checked(bool fIncFixed=false) const;

    public slots:
        void                clear();
        void                setReadOnly(bool);
        
    signals:
        void                changed();
        
    private:
        FlowLayout*                         m_layout;
        yq::Map<QString,CheckBox*,IgCase>   m_checks;
    };
}
