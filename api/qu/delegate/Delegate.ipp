////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/delegate/Delegate.hpp>
//#include "core/Map.hpp"
//#include "core/Vector.hpp"

namespace qu {

    #if 0
    struct Delegate::Repo {
        Vector<const Info*>   all;
        Map<int, const Info*>  byType;
    };

    Delegate::Repo& Delegate::repo()
    {
        static Repo*    _r  = new Repo;
        return *_r;
    }

    const Vector<const Delegate::Info*>&   Delegate::allInfo()
    {
        return repo().all;
    }

    Delegate*    Delegate::make(int dataType, QObject* parent)
    {
        const Info* i = repo().byType.get(dataType);
        if(!i)
            return nullptr;
        return i->create(parent);
    }
    #endif


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    #if 0
    Delegate::Info::Info(int type, const char* name, const char* file) : 
        m_dataType(type), m_name(name), m_sourceFile(file)
    {
        Repo &  r   = repo();
        r.all << this;
        assert(!r.byType.get(type) && "Duplicate registration for type!");
        r.byType[type]  = this;
    }

    Delegate::Info::~Info()
    {
    }
    #endif

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    Delegate::Delegate(QObject*parent) : QStyledItemDelegate(parent)
    {
    }

    Delegate:: ~Delegate()
    {
    }

    QVariant    Delegate::addDisplayVariant() const
    {
        return tr("(add new)");
    }

    yq::Compare Delegate::compare(const QVariant&, const QVariant&) const
    {
        return yq::Compare::UNCOMPARABLE;
    }

    QWidget*    Delegate::createEditor(QWidget* parent) const
    {
        return nullptr;
    }

    bool        Delegate::setEditorData(QWidget*, const QVariant&) const
    {
        return false;
    }

    QVariant    Delegate::getEditorData(const QWidget*) const
    {
        return QVariant();
    }

    bool        Delegate::paint(QPainter*, const QStyleOptionViewItem&, const QVariant&) const
    {
        return false;
    }

    QVariant    Delegate::render(const QVariant&in) const
    {
        return in;
    }

    QVariant    Delegate::render(const QVariant&in, const QModelIndex&idx) const
    {
        return render(in);
    }


    //  ------------------------------------------------------------------------
    //  These are the QItemDelegate ones
    void        Delegate::updateEditorGeometry(
                    QWidget*editor, 
                    const QStyleOptionViewItem&option, 
                    const QModelIndex& idx
                ) const
    {
        QStyledItemDelegate::updateEditorGeometry(editor, option, idx);
        //editor->setGeometry(option.rect);
    }

    QWidget*  Delegate::createEditor ( QWidget * parent, const QStyleOptionViewItem & option, 
                        const QModelIndex & index ) const 
    {
        QWidget* w  =  createEditor(parent);
        if(!w)
            w       = QStyledItemDelegate::createEditor(parent, option, index);
        return w;
    }


    void    Delegate::setEditorData (QWidget * editor, const QModelIndex & index ) const 
    {
        if(!setEditorData(editor, index.data(Qt::EditRole))){
            QStyledItemDelegate::setEditorData(editor, index);
        }
    }

    void    Delegate::setModelData  (QWidget * editor, QAbstractItemModel * model, 
                const QModelIndex & index ) const 
    {
        QVariant    data    = getEditorData(editor);
        if(data.isValid()){
            model->setData(index, data, Qt::EditRole);
        } else {
            QStyledItemDelegate::setModelData(editor, model, index);
        }
    }

    void    Delegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, 
                const QModelIndex & index ) const 
    {
        if(!paint(painter, option, index.data(Qt::DisplayRole))){
            QStyledItemDelegate::paint(painter, option, index);
        }
    }

    bool 	    Delegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) 
    {
        return QStyledItemDelegate::editorEvent(event, model, option, index);
    }

    bool 	    Delegate::helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index) 
    {
        return QStyledItemDelegate::helpEvent(event, view, option, index);
    }
}

