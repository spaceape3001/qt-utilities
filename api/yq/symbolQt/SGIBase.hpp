////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq::gluon {
    struct SGIBase {
        virtual ~SGIBase(){}
        virtual void adjust(){}
    };

    template <typename T>
    struct SGIAdapter : public T, public SGIBase {
        using adapter_t = SGIAdapter;
    
        template <typename ... Arg>
        SGIAdapter(Arg... args) : T(args...) {}
    };
}
