////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QStyledItemDelegate>
#include <yq/keywords.hpp>
#include <yq/core/Compare.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/core/Object.hpp>
#include <source_location>
#include <gluon/preamble.hpp>
#include <gluon/core/RefQ.hpp>
#include <QMetaType>

namespace yq::gluon {

    class DelegateInfo : public ObjectInfo {
    public:
        template <typename C> class Writer;
        
        const TypeInfo*     dataType() const { return m_yqType; }
        QMetaType           metaType() const { return m_qtType; }
        
        static std::vector<const DelegateInfo*>  all();
        
        static const DelegateInfo*              byQtType(int);

    protected:
        DelegateInfo(std::string_view, ObjectInfo&, const std::source_location& sl = std::source_location::current());
        
    private:
        const TypeInfo*     m_yqType    = nullptr;
        QMetaType           m_qtType;
        
        void            registerQtMapping();
    };

    /*! \brief Generic delegate to wrapper the idiosyncracies of the Qt's delegate
    */
    class Delegate : public QStyledItemDelegate, public Object{
        Q_OBJECT
        
        YQ_OBJECT_INFO(DelegateInfo)
        YQ_OBJECT_DECLARE(Delegate, Object)
        
    public:
    
        // override in the derived classes...
        using data_t    = yq::disabled_k;

        //  Bringing in the dynamic in (later) via a registration system....
        
        static Delegate*    make(int dataType, QObject* parent=nullptr);
        
        //template <typename>
        //static TypedInfo<D>&
        
        //  ------------------------------------------------------------------------
        //  These are what the derived class are expected to extend....
        
        
        //! Returns what to display in case it's an (add) situation
        virtual QVariant    addDisplayVariant() const;

        //! Less than comparison (same as a sort, etc)
        virtual yq::Compare compare(const QVariant&, const QVariant&) const; 
        virtual QWidget*    createEditor(QWidget* parent=nullptr) const;
        virtual bool        setEditorData(QWidget*, const QVariant&) const;
        virtual QVariant    getEditorData(const QWidget*) const;
        virtual bool        paint(QPainter*, const QStyleOptionViewItem& option, const QVariant&) const;
        
        //  In case there are any needed formatting (to string)
        virtual QVariant    render(const QVariant&) const;
        virtual QVariant    render(const QVariant&, const QModelIndex&) const;
        
        //virtual QString 	displayText(const QVariant &value, const QLocale &locale) const;    
        
        //  Yes, this means using the older macros....
        virtual void        connectEditedSignal(QWidget*, QObject*, const char*) const {}
        
        //virtual QSize       sizeHint(const QStyleOptionViewItem&) const;

        //  ------------------------------------------------------------------------
        //  These are the QItemDelegate ones
        virtual QWidget*  createEditor ( QWidget * parent, const QStyleOptionViewItem & option, 
                            const QModelIndex & index ) const override;

        virtual void        setEditorData (QWidget * editor, const QModelIndex & index ) const override;
        virtual void        setModelData  (QWidget * editor, QAbstractItemModel * model, 
                                const QModelIndex & index ) const override;
        virtual void        updateEditorGeometry ( QWidget * editor, 
                                const QStyleOptionViewItem & option, 
                                const QModelIndex & index ) const override;
        virtual void        paint ( QPainter * painter, const QStyleOptionViewItem & option, 
                                const QModelIndex & index ) const override;
        virtual bool 	    editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
        virtual bool 	    helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index) override;
        
        static void init_info();

    protected:
        Delegate(QObject* parent=nullptr);
        virtual ~Delegate();

    private:
        friend class DelegateInfo;
        
        struct Repo;
        static Repo&    repo();
        static void         reg(const QMetaObject*, int, const std::source_location&);
    };
}
