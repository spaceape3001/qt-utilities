////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QListView>
#include <QAbstractListModel>

#include <QStringList>

namespace yq::gluon {

    /*! \brief Widget to edit a string list
    
        This widget can be used to edit a string list
    */
    class StringListWidget : public QListView {
        Q_OBJECT
    public:
        class Model;

        //! Constructor
        StringListWidget(QWidget*parent=nullptr);
        
        //! Destructor
        ~StringListWidget();
        
        //! Our model
        Model*          model () { return m_model; }
        
        //! Our model (const)
        const Model*    model() const { return m_model; }

        //! Current list
        QStringList     list() const;
        
        //! Sets the current list
        void            setList(const QStringList&);

    signals:
        //! Signal for editing the list
        void        edited();
    protected:

        virtual void  keyPressEvent ( QKeyEvent * event ) override;

    private:

        void        moveDown();
        void        moveUp();

        Model*      m_model;
    };

    /*! \brief Data model for the string list widget
    */
    class StringListWidget::Model : public QAbstractListModel {
        Q_OBJECT
    public:
    
        //! Constructor
        Model(QObject*parent=nullptr);
        
        //! Destructor
        ~Model();

        //! Current list
        QStringList      list() const { return m_data; }
        
        //! Sets the current list
        void            setList(const QStringList&);
        
        //! TRUE if this model is read only
        bool            readOnly() const { return m_readOnly; }
        
        //! Sets the read-only flag
        void            setReadOnly(bool);

    //    bool            deleteEmpties() const { return m_deleteEmpties; }
    //    void            setDeleteEmpties(bool);

        //! Number of items
        int             rowCount(const QModelIndex&) const override;
        
        //! Data for the model item
        QVariant        data(const QModelIndex&, int) const override;
        
        //! Flags for the model item
        Qt::ItemFlags   flags(const QModelIndex&) const override;
        
        //! Sets the data for the model item
        bool            setData(const QModelIndex&,const QVariant&,int role=Qt::EditRole) override;
        
        //! Gets the header data for section/role
        QVariant        headerData(int,Qt::Orientation,int) const;

        //! Moves the specified row to the new location (things in between shift)
        void            move(int row, int newRow);

        //! Number of rows
        size_t          rows() const { return m_data.size(); }

        //! Index for row
        QModelIndex     indexOf(int row) const { return createIndex(row, 0); }

        //void            reset();

    signals:
        //! Signal that something's been edited
        void            edited();

    private:
        QStringList        m_data;
        bool            m_readOnly;
    //    bool            m_deleteEmpties;
    };

}
