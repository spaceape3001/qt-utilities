////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/delegate/Delegate.hpp>

namespace yq::gluon {

    /*! \brief Date Time Delegate
    
        This date time delegate allows for null date times, assumes the data is QDateTime
    */
    class NullableDateTimeDelegate : public Delegate {
        Q_OBJECT
        YQ_OBJECT_DECLARE(NullableDateTimeDelegate, Delegate)
    public:

        using DataType  = QDateTime;
        
        //! Constructor
        NullableDateTimeDelegate(QObject* parent=nullptr);
        
        //! Destructor
        virtual ~NullableDateTimeDelegate();
        
        //! Renders data into string
        virtual QVariant    render(const QVariant&) const override;
        
        //! Compares two values
        virtual Compare     compare(const QVariant&, const QVariant&) const override; 
        
        //! Creates the editor
        virtual QWidget*    createEditor(QWidget* parent=nullptr) const override;
        
        //! Sets the editor's data
        virtual bool        setEditorData(QWidget*, const QVariant&) const override;
        
        //! Gets the editor's data
        virtual QVariant    getEditorData(const QWidget*) const override;
        
        //! Connects the edited signal
        virtual void        connectEditedSignal(QWidget*, QObject*, const char*) const override;

        static void init_info();
    };

}
