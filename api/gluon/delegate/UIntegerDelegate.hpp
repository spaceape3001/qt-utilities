////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/delegate/Delegate.hpp>

namespace yq::gluon {

    /*! \brief Delegate for an unsigned integer
    
        Editor is a spin box
    */
    class UIntegerDelegate : public Delegate {
        Q_OBJECT
        YQ_OBJECT_DECLARE(UIntegerDelegate, Delegate)
    public:
        using DataType  = unsigned int;
        
        //! Constructor
        UIntegerDelegate(QObject* parent=nullptr);
        
        //! Destructor
        virtual ~UIntegerDelegate();
      
        //! Render the data into text/visual data
        virtual QVariant    render(const QVariant&) const override;
        
        //! Compares two values
        virtual Compare     compare(const QVariant&, const QVariant&) const override; 
        
        //! Creates the editor
        virtual QWidget*    createEditor(QWidget* parent=nullptr) const override;
        
        //! Sets the editor data
        virtual bool        setEditorData(QWidget*, const QVariant&) const override;
        
        //! Gets the editor data
        virtual QVariant    getEditorData(const QWidget*) const override;
        
        //! Connects the edited signal
        virtual void        connectEditedSignal(QWidget*, QObject*, const char*) const override;

        //! Minimum value for the spinbox
        unsigned int        minValue() const { return m_minValue; }
        
        //! Maximum value for the spinbox
        unsigned int        maxValue() const { return m_maxValue; }
        
        //! Step size for the spin box
        unsigned int        step() const { return m_step; }
        
        //! If true, ZERO is interpreted as null rather than zero
        bool                zeroNull() const { return m_zeroNull; }

        static void init_info();
        
    public slots:
    
        //! Sets the minimum value for the spin box
        void                setMinValue(unsigned int);
        
        //! Sets the maximum value for the spin box
        void                setMaxValue(unsigned int);
        
        //! Sets the step size for the spin box
        void                setStep(unsigned int);
        
        //! Sets if ZERO will be interpreted as NULL
        void                setZeroNull(bool);
        
    private:
        unsigned int        m_minValue, m_maxValue, m_step;
        bool                m_zeroNull;
    };
}
