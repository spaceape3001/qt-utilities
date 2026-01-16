////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/preamble.hpp>
#include <yq/gluon/core/ucompare.hpp>
#include <yq/gluon/core/uicon.hpp>
#include <yq/gluon/core/ujoin.hpp>
#include <yq/gluon/core/ulog.hpp>
#include <yq/gluon/core/umatch.hpp>
#include <yq/gluon/core/ustring.hpp>

#include <QString>
#include <QList>

#include <span>

class QIcon;
class QObject;

namespace yq::gluon {

    QStringList         qStringList(std::span<const std::string>);
    QStringList         qStringList(std::span<const std::string_view>);
    
    std::vector<std::string>    yStringVector(const QStringList&);

    
    template <typename T>
    std::vector<const T*>  toCVector(const QList<T*>& list)
    {
        return std::vector<const T*>(list.begin(), list.end());
    }

    template <typename T>
    std::vector<T>  toVector(const QList<T>& list)
    {
        return std::vector<T>(list.begin(), list.end());
    }
}

