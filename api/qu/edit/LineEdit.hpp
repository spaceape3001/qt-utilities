////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QLineEdit>
#include <qu/undo/UndoBase.hpp>
#include <optional>

namespace qu {

    /*! \brief Line edit that ties into the undo system
    */
    class LineEdit : public QLineEdit, public UndoBase {
        Q_OBJECT
    public:
        LineEdit(QWidget* parent=nullptr);
        ~LineEdit();
        
            //  returns an unset optional if the line edit is blank
        std::optional<QString>  get() const;
        void                    set(const std::optional<QString>&);

    private slots:
        void    createUndo();

    private:
        class Undo;
        //  TODO: Currently, the *ACTUAL* undo tie in is not yet implemented
    };
}
