////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QStyledItemDelegate>
#include <basic/Compare.hpp>
#include <source_location>
#include <qu/preamble.hpp>

namespace qu {

    /*! \brief Generic delegate to wrapper the idiosyncracies of the Qt's delegate
    */
    class Delegate : public QStyledItemDelegate {
        Q_OBJECT
    public:
    
        using data_t    = yq::disabled;

        //  Bringing in the dynamic in (later) via a registration system....
        class Info;
        template <typename D>  class TypedInfo;
        
        static const Vector<const Info*>&   allInfo();
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
        
    protected:
        Delegate(QObject* parent=nullptr);
        virtual ~Delegate();

    private:
        struct Repo;
        static Repo&    repo();
        static void         reg(const QMetaObject*, int, const std::source_location&);
    };

#if 0
    class Delegate::Info : public DelayInit {
    public:
        virtual Delegate*       create(QObject* parent=nullptr) const = 0;
        int                     dataType() const { return m_dataType; }
        QString                 name() const { return m_name; }
        QString                 sourceFile() const { return m_sourceFile; }
    protected:
        Info(int, const char* name, const char* file);
        ~Info();
    private:
        int             m_dataType;
        QString         m_name;
        QString         m_sourceFile;
    };
#endif

    #define YQ_DELEGATE(cls, ... )                                                  \
        template <> void Delegate::TypedInfo<cls>::doInit() { __VA_ARGS__ }         \
        template <> Delegate::TypedInfo<cls>* Delegate::TypedInfo<cls>::s_meta =    \
            new Delegate::TypedInfo<cls>(#cls, __FILE__ );                          \

#if 0
    template <typename D>
    class Delegate::TypedInfo : public Info {
    public:

        Delegate* create(QObject* parent) const 
            { return new D(parent); }
        

    private:
        TypedInfo(const char*cls, const char* file) :
            Info(qMetaTypeId<typename D::DataType>(), cls, file)
        {
        }
        
        void        initialize()
        {
            doInit();
        }
        
        void            doInit();
        
        
        static TypedInfo*       s_meta;
        
    };
#endif
}
