////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Action.hpp"
#include <QAction>

namespace yq::gluon {
    QAction*    createAction(const ActionInfo& ai, QObject*parent)
    {
        QAction* act    = new QAction(parent);
        act->setText(ai.label);
        act->setIcon(ai.icon);
        act->setShortcut(ai.shortcut);
        act->setToolTip(ai.toolTip);
        act->setCheckable(ai.checkable);
        if(ai.checkable)
            act->setChecked(ai.checked);
        return act;
    }
}
