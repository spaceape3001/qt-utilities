////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

class QIcon;
class QString;

#include <string_view>

namespace yq::gluon {

    /*!
        Gets an icon from a filename.  Any %1 notation will be replaced by 
        common icon sizes and tested.
        
        \note Qt restriction requires this to run on the MAIN THREAD.  Any
        other thread will simply return an empty icon
    */
    QIcon           fetchIcon(const QString&);
}

namespace yq {
    QIcon           qIcon(std::string_view);
}
