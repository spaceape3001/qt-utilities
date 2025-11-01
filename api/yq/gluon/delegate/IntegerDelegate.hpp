////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/delegate/Delegate.hpp>

namespace yq::gluon {

    /*! \brief Delegate for integers
    
        When the data is an integer, use this delegate
    */
    class IntegerDelegate : public Delegate {
        Q_OBJECT
        YQ_OBJECT_DECLARE(IntegerDelegate, Delegate)
    public:
        using DataType      = int;
        
        //! Constructor
        IntegerDelegate(QObject* parent=nullptr);
        
        //! Destructor
        virtual ~IntegerDelegate();
        
        //! Renders the data into display
        virtual QVariant    render(const QVariant&) const override;
        
        //! Compares two values
        virtual Compare     compare(const QVariant&, const QVariant&) const override; 
        
        //! Creates an editor
        virtual QWidget*    createEditor(QWidget* parent=nullptr) const override;
        
        //! Sets the given editor's data
        virtual bool        setEditorData(QWidget*, const QVariant&) const override;
        
        //! Gets the given editor's data
        virtual QVariant    getEditorData(const QWidget*) const override;
        
        //! Connect an edited signal
        virtual void        connectEditedSignal(QWidget*, QObject*, const char*) const override;

        //! Min value of the editing spin box
        int                 minValue() const { return m_minValue; }
        
        //! Max value of the editing spin box
        int                 maxValue() const { return m_maxValue; }
        
        //! Step for the spin box
        int                 step() const { return m_step; }
        
        //! TRUE if zero value results in NULL variant
        bool                zeroNull() const { return m_zeroNull; }

        static void init_meta();
        
    public slots:
    
        //! Sets the minimum value of the editing spin box
        void                setMinValue(int);
        
        //! Sets the maximum value of the editing spin box
        void                setMaxValue(int);
        
        //! Sets the step of the editing spin box
        void                setStep(int);
        
        //! Sets the zero-value-null option
        void                setZeroNull(bool);
        
    private:
        int                 m_minValue, m_maxValue, m_step;
        bool                m_zeroNull;
    };
}
