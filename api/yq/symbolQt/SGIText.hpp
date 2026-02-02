////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/symbolQt/SGIBase.hpp>
#include <QGraphicsSimpleTextItem>

namespace yq::symbol {
    struct text_t;
}

namespace yq::gluon {
    class SGIText : public SGIAdapter<QGraphicsSimpleTextItem> {
    public:
        
        SGIText(const symbol::text_t& txt, float scale=1.);
        ~SGIText();
        void adjust() override;
        
    private:
        const symbol::text_t&   m_text;
        float                   m_scale;
    };
}
