////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ulog.hpp"
#include "Logging.hpp"
#include <QDirIterator>

namespace yq::gluon {
    void    logAllResources()
    {
        logAllResources(qtInfo);
    }
    
    void    logAllResources(log4cpp::CategoryStream&&log)
    {
        log << "All Registered Qt Resources:\n";
        size_t n    = 0;
        QDirIterator it(":", QDirIterator::Subdirectories);
        while (it.hasNext()){
            log << "+ " << it.next() << '\n';
            ++n;
        }
        log << "Found " << n << " items.";
    }
}
