////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Delegate.hpp"

namespace yq::gluon {

    /*! \brief String Delegate with Combo Box
    
        This implements the string editor as a combo box allowing for 
        drop down capability
    */
    class StringComboDelegate : public Delegate {
        Q_OBJECT
        YQ_OBJECT_DECLARE(StringComboDelegate, Delegate)
    public:

        //! Constructor
        StringComboDelegate(QObject* parent=nullptr);
        
        //! Destructor
        virtual ~StringComboDelegate();
        
        //! Compares two values
        virtual Compare     compare(const QVariant&, const QVariant&) const override; 
        
        //! Creates the editor
        virtual QWidget*    createEditor(QWidget* parent=nullptr) const override;
        
        //! Sets the editor data
        virtual bool        setEditorData(QWidget*, const QVariant&) const override;
        
        //! Gets the editor data
        virtual QVariant    getEditorData(const QWidget*) const override;
        
        //! Connects up the edited signal
        virtual void        connectEditedSignal(QWidget*, QObject*, const char*) const override;

        //! List of items for the combo box
        const QStringList&  suggest() const { return m_suggest; }
        
        //! If TRUE allows for free-form entry by the user (otherwise it's a restricted list)
        bool                freeEdit() const { return m_freeEdit; }
    public slots:
    
        //! Sets the free-edit option
        void                setFreeEdit(bool);
        
        //! Sets the combo item list
        void                setSuggest(const QStringList&);
        
    signals:
        void                newEntry(const QString&);
    private:
        QStringList         m_suggest;
        bool                m_freeEdit;
    };

}
