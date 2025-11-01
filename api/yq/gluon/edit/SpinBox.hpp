////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/undo/UndoBase.hpp>

#include <QSpinBox>
#include <optional>

namespace yq::gluon {

    //! \brief Spin box with undo
    //!
    //! Well, once implemeneted, this will be a spin box with  the undo
    //! capability, we're using this in the meanwhile so it's a single 
    //! point addition.
    class SpinBox : public QSpinBox, public UndoBase {
        Q_OBJECT
    public:
    
        //! Spin box constructor
        SpinBox(QWidget*parent=nullptr);
        
        //! Destructor
        ~SpinBox();
        
        //  TODO: Currently, the *ACTUAL* undo tie in is not yet implemented
        
        //! Set the value (along with a parameter in case it's undefined)
        void                        set(const std::optional<unsigned int>& zValue, unsigned int zDefault=0);
        
        //! Gets the value
        std::optional<unsigned int> getUInt(unsigned int zDefault=0) const;

    public slots:   
        virtual void    reset();
    };
}
