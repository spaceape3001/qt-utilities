////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "StringListWidget.hpp"
#include <QKeyEvent>

namespace yq::gluon {
    StringListWidget::StringListWidget(QWidget*parent) 
        : QListView(parent)
    {
        m_model     = new Model(this);
        setModel(m_model);
        setAlternatingRowColors(true);
        
        connect(m_model, &StringListWidget::Model::edited, this, &StringListWidget::edited);
    }

    StringListWidget::~StringListWidget()
    {
    }

    QStringList        StringListWidget::list() const
    {
        return m_model->list();
    }

    void            StringListWidget::setList(const QStringList&sl)
    {
        m_model->setList(sl);
    }

    void  StringListWidget::keyPressEvent ( QKeyEvent * event )
    {
        switch(event->key()){
        case Qt::Key_PageDown:
            moveDown();
            event->accept();
            break;
        case Qt::Key_PageUp:
            moveUp();
            event->accept();
            break;
        default:
            QListView::keyPressEvent(event);
            break;
        }
    }

    void        StringListWidget::moveDown()
    {
        QModelIndex     idx = currentIndex();
        int     r   = idx.row();
        if(idx.isValid() && !m_model->readOnly() && (r < (int) m_model->rows()) && (r>0)){
            m_model->move(r, r-1);
            setCurrentIndex(m_model->indexOf(r-1));
        }
    }

    void        StringListWidget::moveUp()
    {
        QModelIndex     idx = currentIndex();
        int     r   = idx.row();
        if(idx.isValid() && !m_model->readOnly() && (r < (int)(m_model->rows()-1)) && (r>=0)){
            m_model->move(r, r+1);
            setCurrentIndex(m_model->indexOf(r+1));
        }
    }


    // ==========================================================================

    StringListWidget::Model::Model(QObject*parent) : QAbstractListModel(parent), 
        m_readOnly(false)
    {
    }

    StringListWidget::Model::~Model()
    {
    }

    void            StringListWidget::Model::setList(const QStringList&sl)
    {
        beginResetModel();
        m_data.clear();
        m_data.reserve(sl.size());
        for(const QString& s : sl){
            if(!s.isEmpty())
                m_data << s;
        }
        endResetModel();
    }

    void            StringListWidget::Model::setReadOnly(bool f)
    {
        if(f){
            if(!m_readOnly){
                beginRemoveRows(QModelIndex(), m_data.size(), m_data.size());
                endRemoveRows();
                m_readOnly      = true;
            }
        } else {
            if(m_readOnly){
                beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
                endInsertRows();
                m_readOnly      = false;
            }
        }
    }

    int             StringListWidget::Model::rowCount(const QModelIndex&) const
    {
        if(m_readOnly)
            return (int) m_data.size();
        else
            return (int)(m_data.size()+1);
    }

    QVariant        StringListWidget::Model::data(const QModelIndex&idx, int role) const
    {
        if(role != Qt::DisplayRole && role != Qt::EditRole){
            return QVariant();
        }
        int     r   = idx.row();
        if(r < (int) m_data.size())
            return m_data[r];
        else
            return QVariant();
    }

    Qt::ItemFlags   StringListWidget::Model::flags(const QModelIndex&) const
    {
        if(m_readOnly)
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        else
            return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
    }

    bool  StringListWidget::Model::setData(const QModelIndex& idx, const QVariant& value, int role)
    {
        if(role != Qt::EditRole)
            return false;

        int         r   = idx.row();
        QString     text    = value.toString();
        if(text.isEmpty()){
            if(r >= (int) m_data.size())
                return false;
                
            beginRemoveRows(QModelIndex(), r,r);
            m_data.removeAt(r);
            endRemoveRows();
            emit edited();
            return true;
        }
        
        if(r >= (int) m_data.size()){
            beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
            m_data << text;
            endInsertRows();
            emit edited();
            return true;
        }
        
        if(text != m_data[r]){
            m_data[r] = text;
            dataChanged(idx,idx);
            emit edited();
            return true;
        }
        
        return false;
    }

    QVariant        StringListWidget::Model::headerData(int,Qt::Orientation,int) const
    {
        return QVariant();
    }

    void            StringListWidget::Model::move(int row, int newRow)
    {
        if((row != newRow) && (row < (int) m_data.size()) && (newRow < (int) m_data.size())){
            beginMoveRows(QModelIndex(), row, row, QModelIndex(), newRow);
            m_data.move(row, newRow);
            emit edited();
        }    
    }
}

#include "moc_StringListWidget.cpp"
