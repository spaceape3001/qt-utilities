////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/core/WidgetQ.hpp>
#include <yq/meta/ObjectMetaWriter.hpp>

namespace yq::gluon {
    /*! \brief Writer of trigger information
    */
    template <typename C>
    class WidgetQInfo::Writer : public ObjectMeta::Writer<C> {
    public:
    
        Writer(WidgetQInfo* pInfo) : ObjectMeta::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        Writer(WidgetQInfo& pInfo) : Writer(&pInfo)
        {
        }

    private:
        WidgetQInfo* m_meta;
    };

    template <typename C> 
    class WidgetQFixer : public ObjectFixer<C> {
    public:
        WidgetQFixer(std::string_view szName, typename C::MyBase::MyInfo& myBase, std::source_location sl=std::source_location::current()) : 
            ObjectFixer<C>(szName, myBase, sl) 
        {
        }

        virtual C* create() const override 
        { 
            if constexpr (!C::kAbstract && !std::is_abstract_v<C>) {
                return new C(nullptr); 
            } else
                return nullptr;
        }

        
        virtual C* create(QWidget* parent) const override
        {
            //  While the std::is_constructible_v<> test seemed nice, it unfortunately requires 
            //  PUBLIC constructors & destructors, which we do *NOT* want here.  Instead, we 
            //  have to do the macro trick with abstract, and mark appropriately.
            if constexpr (!C::kAbstract && !std::is_abstract_v<C>) {
                if(ObjectMeta::is_abstract()){
                    return nullptr;
                }
                return new C(parent);
            } else {
                return nullptr;
            }
        }
    };
}


