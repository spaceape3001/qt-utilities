////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>

class QObject;

namespace yq::gluon {
    std::vector<const QObject*>   lineage(const QObject*, bool fIncSelf=false);
    std::vector<const QObject*>   qobjectLineage(const QObject*, bool fIncSelf=false);
}
