////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/graphics/GraphicsLayer.hpp>
#include <type_traits>

namespace yq::gluon {
    template <typename T>
    auto        GraphicsLayer::for_items(uint64_t itemId, Pred&& pred)
    {
        using result_t  = decltype(pred((QGraphicsItem*) 0));
        auto r  = m_items.equal_range(itemId);
        for(auto itr = r.first; itr != r.second; ++itr){
            if(!r.second)
                continue;
            if constexpr (!std::is_same_v<result_t,void>){
                result_t ret = pred(r.second);
                if(ret != result_t{})
                    return ret;
            } else {
                pred(r.second);
            }
        }
        
        if constexpr (!std::is_same_v<result_t,void>){
            return result_t{};
        }
    }
}
