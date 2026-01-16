////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "uobject.hpp"
#include <QObject>

namespace yq::gluon {
    std::vector<const QObject*>   lineage(const QObject* obj, bool fIncSelf)
    {
        std::vector<const QObject*>   ret;
        if(obj){
            if(fIncSelf)
                ret.push_back(obj);
            for(QObject*p   = obj->parent(); p; p=p->parent())
                ret.push_back(p);
        }
        return std::vector<const QObject*>(ret.rbegin(), ret.rend());
    }
    
    std::vector<const QObject*>   qobjectLineage(const QObject* obj, bool fIncSelf)
    {
        return lineage(obj, fIncSelf);
    }
}
