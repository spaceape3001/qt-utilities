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

    class StringListWidget : public QListView {
        Q_OBJECT
    public:
        class Model;

        StringListWidget(QWidget*parent=nullptr);
        ~StringListWidget();
        
        Model*          model () { return m_model; }
        const Model*    model() const { return m_model; }

        QStringList     list() const;
        void            setList(const QStringList&);

    signals:
        void        edited();
    protected:

        virtual void  keyPressEvent ( QKeyEvent * event );

    private:

        void        moveDown();
        void        moveUp();

        Model*      m_model;
    };

    class StringListWidget::Model : public QAbstractListModel {
        Q_OBJECT
    public:
        Model(QObject*parent=nullptr);
        ~Model();

        QStringList      list() const { return m_data; }
        void            setList(const QStringList&);
        
        bool            readOnly() const { return m_readOnly; }
        void            setReadOnly(bool);

    //    bool            deleteEmpties() const { return m_deleteEmpties; }
    //    void            setDeleteEmpties(bool);

        int             rowCount(const QModelIndex&) const;
        QVariant        data(const QModelIndex&, int) const;
        Qt::ItemFlags   flags(const QModelIndex&) const;
        bool            setData(const QModelIndex&,const QVariant&,int role=Qt::EditRole);
        QVariant        headerData(int,Qt::Orientation,int) const;

        void            move(int row, int newRow);

        size_t          rows() const { return m_data.size(); }

        QModelIndex     indexOf(int row) const { return createIndex(row, 0); }

        //void            reset();

    signals:
        void            edited();

    private:
        QStringList        m_data;
        bool            m_readOnly;
    //    bool            m_deleteEmpties;
    };

}
