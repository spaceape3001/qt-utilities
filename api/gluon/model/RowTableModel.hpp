////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QAbstractTableModel>
#include <yq/trait/indices.hpp>
#include <gluon/keywords.hpp>
#include <variant>
#include <yq/core/Compare.hpp>

namespace yq::gluon {

    template <typename T, typename ... P> class ColumnModel;

    //! Row Table Model
    //! \note it's templated, so no QObject magic...
    template <typename T, typename ... P>
    class RowTableModel : public QAbstractTableModel {
    public:
    
        enum class AddPolicy;
    
        using data_t        = T;
        using row_table_t   = RowTableModel;
        using param_t       = std::tuple<P...>;
        using column_t      = ColumnModel<T,P...>;
        using VariantFN     = std::function<QVariant(const T&, P ... args)>;
        using VHeaderSpec   = std::variant<std::monostate, rows_k, VariantFN>;
        
    
        static constexpr const size_t   ARG_COUNT   = sizeof...(P);

        RowTableModel(P...);
        RowTableModel(QObject*parent, P...);
        RowTableModel(std::initializer_list<const char*>, P...);
        RowTableModel(std::initializer_list<const char*>, QObject*parent, P...);
        ~RowTableModel();

        virtual int     rowCount(const QModelIndex&) const override;
        virtual int     columnCount(const QModelIndex&) const override;
        
        struct Column;
        
        virtual QVariant        data(const QModelIndex&, int) const override;
        virtual Qt::ItemFlags   flags(const QModelIndex&) const override;
        
        /*! \brief Horizontal Header Enabled
        
            TRUE if the horizontal header's been enabled
        */
        bool            hasHorizontalHeader() const;

        /*! \brief Vertical Header Enabled
        
            TRUE if the vertical header's been enabled
        */
        bool            hasVerticalHeader() const;

        //! Header data (see QAbstractItemModel)
        virtual QVariant        headerData(int, Qt::Orientation, int) const override;

        //! TRUE if read-only is enabled
        bool            readOnly() const;

        void            setColumns(std::initializer_list<const char*>);
        void            setColumns(std::span<const std::string>);

        //! Sets data (see QAbstractItemModel)
        bool            setData(const QModelIndex&, const QVariant&, int ) override;
        
        //! Set the row data (this will cause a reset-model)
        void            setRows(const std::vector<T>& newData);

        //! Set the row data (this will cause a reset-model)
        void            setRows(std::vector<T>&& newData);

        //! Enabled the showing of horizontal header data
        void            showHorizontalHeader(bool);

        //! Enabled the showing of vertical  header data
        void            showVerticalHeader(bool);

        void 	        sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

        //! Updates the row data, with a combination of adds/deletes
        void            updateRows(const std::vector<T>& newData);

    protected:
        struct Repo;

        enum class F {
            //! Obvious, in read only mode
            ReadOnly    = 0,
            
            ReloadEnabled,
            
            //! TRUE if any columns are detected to be add-capable
            AnyAdd,     
            
            //! TRUE if any columns are detected to be drop-capable
            AnyDrop,
            
            DropPolicy,
            
            HorizontalHeader,
            VerticalHeader
            
        };
    
        param_t                 m_params;
        std::vector<Column>     m_columns;
        std::vector<T>          m_rows;
        VHeaderSpec             m_vHeader;
        Flags<F>                m_flags         = {};
        
        T*              row(const QModelIndex& mi);
        const T*        row(const QModelIndex& mi) const;
        T*              row(int);
        const T*        row(int) const;
        const Column*   column(const QModelIndex&) const;
        const Column*   column(int) const;
        Column*         column(int);

        void            _changed();
        
        Delegate*       delegate(create_k, int);
        Delegate*       delegate(int);
        const Delegate* delegate(int) const;
        
    private:

        template <unsigned... Is>
        QVariant verticalData(const VariantFN&, const T&, indices<Is...>) const;
        
    };
}
