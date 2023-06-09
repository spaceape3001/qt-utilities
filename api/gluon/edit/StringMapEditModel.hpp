////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/edit/StringMapEdit.hpp>
#include <QAbstractTableModel>
#include <vector>
#include <basic/Vector.hpp>

namespace yq::gluon {
    /*! \brief String Map's Model
    */
    class StringMapEdit::Model : public QAbstractTableModel {
        Q_OBJECT
    public:
        Model();
        ~Model();
        
        int             columnCount(const QModelIndex&) const override;
        int             rowCount(const QModelIndex&) const override;
        QVariant        data(const QModelIndex&, int) const override;
        bool            setData(const QModelIndex&, const QVariant&, int) override;
        QVariant        headerData(int, Qt::Orientation, int) const override;
        Qt::ItemFlags   flags(const QModelIndex&) const override;
        
        QStringMap		get() const;
        void			set(const QStringMap&);
        
        bool			has(const QString&) const;
        void			removeRows(std::span<int>);
        
        void            setKeyLabel(const QString&);
        void            setValueLabel(const QString&);
        
        void            setKeyValidator(Validator);
        void            setValueValidator(Validator);

    public slots:
        void			addRow();
        
    private:
        yq::Vector<Item>	m_items;
        
        struct Col {
            QString     label;
            Validator   validator   = {};
        }   m_key, m_value;
    };

}
