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
    struct SGITextOptions {
        float   scale = 1.;
        QString text;       //!< Override
    };
    
    class SGIText : public SGIAdapter<QGraphicsSimpleTextItem> {
    public:
        
        SGIText(const symbol::text_t& txt, const SGITextOptions& opts={});
        ~SGIText();
        void adjust() override;
        
    private:
        const symbol::text_t&   m_text;
        float                   m_scale;
    };
}
