////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/edit/StringMapEdit.hpp>
#include <QAbstractTableModel>
#include <vector>
#include <yq-toolbox/container/Vector.hpp>

namespace yq::gluon {
    /*! \brief String Map's Model
    */
    class StringMapEdit::Model : public QAbstractTableModel {
        Q_OBJECT
    public:
    
        //! Constructor
        Model();
        
        //! Destructor
        ~Model();
        
        //! Column count
        int             columnCount(const QModelIndex&) const override;
        
        //! Row count
        int             rowCount(const QModelIndex&) const override;
        
        //! Data for cell
        QVariant        data(const QModelIndex&, int) const override;
        
        //! Sets the data for cell
        bool            setData(const QModelIndex&, const QVariant&, int) override;
        
        //! Header data for section (ie, row or column)
        QVariant        headerData(int, Qt::Orientation, int) const override;
        
        //! Flags for cell
        Qt::ItemFlags   flags(const QModelIndex&) const override;
        
        //! Get the data
        QStringMap		get() const;
        
        //! Sets the data
        void			set(const QStringMap&);
        
        //! Tests for key
        bool			has(const QString&) const;
        
        //! Removes rows
        void			removeRows(std::span<int>);
        
        //! Sets the column label for keys
        void            setKeyLabel(const QString&);
        
        //! Sets the column label for values
        void            setValueLabel(const QString&);
        
        //! Sets the key validator
        void            setKeyValidator(Validator);
        
        //! Sets the value validator
        void            setValueValidator(Validator);

    public slots:
        //! Adds a row
        void			addRow();
        
    private:
        yq::Vector<Item>	m_items;
        
        struct Col {
            QString     label;
            Validator   validator   = {};
        }   m_key, m_value;
    };

}
