////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GNodeNewMimeData.hpp"

namespace yq::gluon {
    GNodeNewMimeData::GNodeNewMimeData(const GNodeTemplateCPtr& ptr) : m_node(ptr)
    {
    }
    
    GNodeNewMimeData::~GNodeNewMimeData()
    {
    }
}

#include "moc_GNodeNewMimeData.cpp"

