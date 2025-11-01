////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "GraphCodec.hpp"

namespace yq::gluon {
    GraphCodec::GraphCodec(QObject*parent) : QObject(parent)
    {
    }
    
    GraphCodec::GraphCodec(g::Document&&doc, QObject*parent) : GraphCodec(parent)
    {
        set_document(std::move(doc));
    }
    
    void        GraphCodec::set_document(g::Document&& doc)
    {
        m_document      = std::move(doc);
        emit codecChanged();
    }
}
