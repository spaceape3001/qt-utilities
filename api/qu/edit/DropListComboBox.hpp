////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/preamble.hpp>
#include <qu/edit/ComboBox.hpp>
#include <basic/Vector.hpp>

class QStandardItem;
class QStandardItemModel;

namespace qu {

    class DropListComboBox : public ComboBox {
        Q_OBJECT
    public:

        DropListComboBox(QWidget* parent=nullptr);
        ~DropListComboBox();
        
        void        setItems(const Set<QString,IgCase>&);

        QString     separator() const { return QString(); }
        void        setSeparator(const QString&);

        Set<QString,IgCase> checked() const;
        
    public slots:
        void        setChecked(const Set<QString,IgCase>&);
        void        update();
    private slots:
        void        handlePressed(const QModelIndex&);
    private:
        struct Item;
        
        bool                isSame(const Set<QString,IgCase>&) const;

        QStandardItemModel* m_model = nullptr;
        Vector<Item>        m_items;
        QString             m_separator;
    };
}
