////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/preamble.hpp>
#include <gluon/edit/ComboBox.hpp>
#include <basic/Vector.hpp>

class QStandardItem;
class QStandardItemModel;

namespace yq::gluon {

    class DropListComboBox : public ComboBox {
        Q_OBJECT
    public:

        DropListComboBox(QWidget* parent=nullptr);
        ~DropListComboBox();
        
        void        setItems(const QStringSet&);

        QString     separator() const { return QString(); }
        void        setSeparator(const QString&);

        QStringSet  checked() const;
        
    public slots:
        void        setChecked(const QStringSet&);
        void        update();
    private slots:
        void        handlePressed(const QModelIndex&);
    private:
        struct Item;
        
        bool                isSame(const QStringSet&) const;

        QStandardItemModel* m_model = nullptr;
        Vector<Item>        m_items;
        QString             m_separator;
    };
}
