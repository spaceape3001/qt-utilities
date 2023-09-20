#pragma once

#include <QAbstractTableModel>
#include <QTableView>
#include <QVariant>
#include "core/Array2.hpp"
#include "core/Vector.hpp"


/*! \brief Simple Qt table

    Meant for a fast view of data
*/
class  SimpleTable : public QTableView {
    Q_OBJECT
public:

    //! Constructor
    SimpleTable(QWidget*parent=nullptr);

    //! Sets the specified data
    bool    set(int,int,const QVariant&);
    
    //! Sets the header (also primes the array to the right column width)
    void    setHeader(const Vector<QString>&);

    class Model;
    
    //! Model
    Model*  model() { return m_model; }
    
    //! Model
    const Model* model() const { return m_model; }

public slots:

    //! Clears the data
    void        clear();
//    void        fit();

private:
    Model*      m_model;
};

/*! \brief Simple Table Model
*/
class SimpleTable::Model : public QAbstractTableModel {
    Q_OBJECT
public:

    //! Constructor
    Model(QObject* parent=nullptr);
    
    //! Destructor
    ~Model();

    //! Sets the header
    void        setHeader(const Vector<QString>&);
    
    //! Current row count
    int         rowCount(const QModelIndex&) const override { return m_data.rowCount(); }
    
    //! Column count
    int         columnCount(const QModelIndex&) const override { return m_data.columnCount(); }
    
    //! Data
    QVariant    data(const QModelIndex&, int) const override;
    
    //! Gets header data
    QVariant    headerData(int, Qt::Orientation, int) const override;

    //! Sets data
    bool        set(int,int,const QVariant&);

public slots:

    //! Clears the data
    void        clear();

private:
    Vector<QString>     m_headers;
    Array2<QVariant>    m_data;
};
