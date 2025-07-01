////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <gluon/delegate/Delegate.hpp>
#include <yq/meta/ObjectMetaWriter.hpp>

namespace yq::gluon {
    template <typename C>
    class DelegateInfo::Writer : public ObjectMeta::Writer<C> {
    public:
        
        Writer(DelegateInfo* obj) : ObjectMeta::Writer<C>(obj) 
        {
            assert(obj);
        }
        
        Writer(DelegateInfo& obj) : Writer(&obj)
        {
        }
        
        template <typename T>
        Writer&     declare_type()
        {
            DelegateInfo*   delInfo   = static_cast<DelegateInfo*>(Meta::Writer::m_meta);
            if constexpr (is_type_v<T>){
                if(!delInfo->m_yqType){
                    delInfo->m_yqType   = &meta<T>();
                }
            }
            if constexpr (QMetaTypeId<T>::Defined){
                if(!(delInfo->m_qtType.isValid())){
                    delInfo->m_qtType   = QMetaType(qMetaTypeId<T>());
                    delInfo->registerQtMapping();
                }
            }
            
            return *this;
        }
    };
}
