////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/delegate/Delegate.hpp>

namespace yq::gluon {

    /*! \brief Browsable Directory Delegate
    
        This is a delegate that interprets its data as a directory path, 
        and when editing, uses a DirBox with a "..." browse button
    */
    class DirBoxDelegate : public Delegate {
        Q_OBJECT
        YQ_OBJECT_DECLARE(DirBoxDelegate, Delegate)
    public:
    
        //! Constructor
        DirBoxDelegate(QObject*parent =nullptr);
        
        //! Destructor
        ~DirBoxDelegate();
        
        //! Compares two values
        virtual yq::Compare compare(const QVariant&, const QVariant&) const override; 
        
        //! Creates an editor
        virtual QWidget*    createEditor(QWidget* parent=nullptr) const;
        
        //! Sets the editor data
        virtual bool        setEditorData(QWidget*, const QVariant&) const;
        
        //! Gets the editor data
        virtual QVariant    getEditorData(const QWidget*) const;
        //virtual bool        paint(QPainter*, const QStyleOptionViewItem& option, const QVariant&) const;
        //! Connects the given the slot to the editor's edited signal
        virtual void        connectEditedSignal(QWidget*, QObject*, const char*) const;

        static void init_meta();
    };

}


