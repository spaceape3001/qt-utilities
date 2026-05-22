////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "uurl.hpp"
#include "ustring.hpp"
#include <yq/net/Url.hpp>
#include <QUrl>

namespace yq {
    QUrl    qUrl(const Url& u)
    {
        QUrl    ret;
        ret.setScheme(qString(u.scheme));
        ret.setUserName(qString(u.user));
        ret.setPassword(qString(u.pwd));
        ret.setHost(qString(u.host));
        ret.setPort(u.port);
        ret.setPath(qString(u.path));
        ret.setFragment(qString(u.fragment));
        ret.setQuery(qString(u.query));
        return ret;
    }
    
    QUrl    qUrl(const UrlView& u)
    {
        QUrl    ret;
        ret.setScheme(qString(u.scheme));
        ret.setUserName(qString(u.user));
        ret.setPassword(qString(u.pwd));
        ret.setHost(qString(u.host));
        ret.setPort(u.port);
        ret.setPath(qString(u.path));
        ret.setFragment(qString(u.fragment));
        ret.setQuery(qString(u.query));
        return ret;
    }
    

    Url     yUrl(const QUrl& u)
    {
        return Url{
            .scheme=sString(u.scheme()), 
            .user=sString(u.userName()), 
            .pwd=sString(u.password()), 
            .host=sString(u.host()), 
            .path=sString(u.path()),
            .query=sString(u.query()),
            .fragment=sString(u.fragment()),
            .port=u.port()
        };
    }
}
