////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/delegate/Delegate.hpp>
//#include "core/Map.hpp"
//#include "core/Vector.hpp"

namespace yq::gluon {

    struct DelegateRepo {
        std::vector<const DelegateInfo*>            all;
        std::unordered_map<int,const DelegateInfo*> byQtType;
        tbb::spin_rw_mutex                          mutex;
    };
    
    namespace {
        DelegateRepo&   delegateRepo()
        {
            static DelegateRepo s_ret;
            return s_ret;
        }
    }

    #define LOCK                                                    \
        DelegateRepo& _r = delegateRepo();                          \
        tbb::spin_rw_mutex::scoped_lock _lock(_r.mutex, false);

    #define WLOCK                                                   \
        DelegateRepo& _r = delegateRepo();                          \
        tbb::spin_rw_mutex::scoped_lock _lock(_r.mutex, true);

        

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    std::vector<const DelegateInfo*>   DelegateInfo::all()
    {
        LOCK
        return _r.all;
    }

    const DelegateInfo*              DelegateInfo::byQtType(int t)
    {
        LOCK
        auto i = _r.byQtType.find(t);
        if(i != _r.byQtType.end())
            return i->second;
        return nullptr;
    }

    DelegateInfo::DelegateInfo(std::string_view name, const ObjectInfo&par, const std::source_location& sl ) : 
        ObjectInfo(name, par, sl)
    {
        WLOCK
        _r.all.push_back(this);
    }
    
    void    DelegateInfo::registerQtMapping()
    {
        if(m_qtType.isValid()){
            WLOCK
            _r.byQtType[m_qtType.id()] = this;
        }
    }
    

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    Delegate*    Delegate::make(int dataType, QObject* parent)
    {
    
        const DelegateInfo* info    = nullptr;
        {
            LOCK
            auto i = _r.byQtType.find(dataType);
            if(i!=_r.byQtType.end())
                info    = i->second;
        }
        
        if(!info)
            return nullptr;
        
        Delegate*   d   = static_cast<Delegate*>(info->create());
        if(d && parent)
            d -> setParent(parent);
        return d;
    }

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

