////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/delegate/Delegate.hpp>

namespace yq::gluon {

    /*! \brief File Box Delegate for browsing files
    
        This makes a file-box as a delegate for browsing files
    */
    class FileBoxDelegate : public Delegate {
        Q_OBJECT
        YQ_OBJECT_DECLARE(FileBoxDelegate, Delegate)
    public:
    
        //! Constructor
        FileBoxDelegate(QObject*parent =nullptr);
        
        //! Destructor
        ~FileBoxDelegate();
        
        //! Compare two values
        virtual Compare     compare(const QVariant&, const QVariant&) const override; 
        
        //! Create editor
        virtual QWidget*    createEditor(QWidget* parent=nullptr) const;
        
        //! Set editor data
        virtual bool        setEditorData(QWidget*, const QVariant&) const;
        
        //! Get editor data
        virtual QVariant    getEditorData(const QWidget*) const;
        //virtual bool        paint(QPainter*, const QStyleOptionViewItem& option, const QVariant&) const;
        
        //! Connect edited signal
        virtual void        connectEditedSignal(QWidget*, QObject*, const char*) const;
        
        
        //  TODO: File Name Filter (propagated into file box itself)
        //  TODO: File Dialog Title
        //  TODO: Consistent Directory location
    };
}



