////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/delegate/Delegate.hpp>

namespace yq::gluon {

    /*! \brief Date Delegate
    
        This date delegate allows for null dates, assumes the data is QDate
    */
    class NullableDateDelegate : public Delegate {
        Q_OBJECT
        YQ_OBJECT_DECLARE(NullableDateDelegate, Delegate)
    public:

        using DataType  = QDate;

        //! Constructor
        NullableDateDelegate(QObject*parent=nullptr);
        
        //! Destructor
        virtual ~NullableDateDelegate();

        //! Renders the variant to something that can be displayed (ie text)
        virtual QVariant    render(const QVariant&) const override;
        
        //! Compares two values
        virtual Compare     compare(const QVariant&, const QVariant&) const override; 
        
        //! Creates an editor
        virtual QWidget*    createEditor(QWidget* parent=nullptr) const override;
        
        //! Sets the editor data
        virtual bool        setEditorData(QWidget*, const QVariant&) const override;
        
        //! Gets the editor data
        virtual QVariant    getEditorData(const QWidget*) const override;
        
        //! Connects the "edited" signal
        virtual void        connectEditedSignal(QWidget*, QObject*, const char*) const override;

        static void init_meta();
    };
}
