////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

namespace yq::gluon {

    /*! \brief Abstract Graphics Item
    
        This is the abstract top level for custom graphics items.   
        Bind it as a PUBLIC second class to your inheritance 
        (to whatever the QGraphicsItem is)
        
        This is a logical binder, not required for the layers 
        to work.
    */
    class GraphicsItem {
    public:
        
        constexpr uint64_t    id() const { return m_id; }
        
    protected:
        GraphicsItem(uint64_t theId=0ULL);
        virtual ~GraphicsItem();
        
    private:
        const uint64_t m_id;
    };
}
