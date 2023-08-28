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

    /*! \brief Combo Box where Items are check boxes
    
        This is a combo box where all the items are check boxes
    */
    class DropListComboBox : public ComboBox {
        Q_OBJECT
    public:

        //! Constructor
        DropListComboBox(QWidget* parent=nullptr);
        
        //! Destructor
        ~DropListComboBox();
        
        //! Sets the items
        void        setItems(const QStringSet&);

        //! Separator for items in the text
        const QString&  separator() const { return m_separator; }
        
        //! Sets the separator
        void        setSeparator(const QString&);

        //! List of checked strings
        QStringSet  checked() const;
        
    public slots:
        //! Sets the checked strings
        void        setChecked(const QStringSet&);
        
        //! Updates
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
