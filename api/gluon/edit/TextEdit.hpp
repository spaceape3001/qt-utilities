////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/undo/UndoBase.hpp>
#include <QTextEdit>

namespace yq::gluon {
    /*! \brief A text edit that ties into the undo-system
    */
    class TextEdit : public QTextEdit, public UndoBase {
        Q_OBJECT
    public:
        TextEdit(QWidget*parent=nullptr);
        ~TextEdit();

        //  TODO: Currently, the *ACTUAL* tie in is not yet implemented
    };
}
