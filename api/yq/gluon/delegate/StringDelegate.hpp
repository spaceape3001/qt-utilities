////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/delegate/Delegate.hpp>

namespace yq::gluon {

    /*! \brief String Delegate
    
        This is a string-edit delegate using a line-edit with a validator
    */
    class StringDelegate : public Delegate {
        Q_OBJECT
        YQ_OBJECT_DECLARE(StringDelegate, Delegate)
    public:
        using DataType      = QString;

        //virtual QVariant    render(const QVariant&) const override;
        //! Compares the two items (ignores the case)
        virtual Compare     compare(const QVariant&, const QVariant&) const override; 
        
        //! Creates the editor
        virtual QWidget*    createEditor(QWidget* parent=nullptr) const override;
        
        //! Sets the editor's data
        virtual bool        setEditorData(QWidget*, const QVariant&) const override;
        
        //! Gets the editor's data
        virtual QVariant    getEditorData(const QWidget*) const override;
        
        //! Connects the edited signal
        virtual void        connectEditedSignal(QWidget*, QObject*, const char*) const override;

        //! Standard constructor
        StringDelegate(QObject*parent=nullptr);
        
        //! Constructor with a validator
        StringDelegate(QValidator*, QObject*parent=nullptr);
        
        //! Destructor
        virtual ~StringDelegate();

        static void init_meta();
    private:
        QValidator*         m_validator;
    };
}
