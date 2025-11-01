////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QLineEdit>
#include <yq/gluon/undo/UndoBase.hpp>
#include <optional>

namespace yq::gluon {

    /*! \brief Line edit that ties into the undo system
    */
    class LineEdit : public QLineEdit, public UndoBase {
        Q_OBJECT
    public:
    
        //! Constructor
        LineEdit(QWidget* parent=nullptr);
        
        //! Destructor
        ~LineEdit();
        
        //! Returns an unset optional if the line edit is blank
        std::optional<QString>  get() const;
        
        //! Sets the contents (unset will be blank)
        void                    set(const std::optional<QString>&);

    private slots:
        void    createUndo();

    private:
        class Undo;
        //  TODO: Currently, the *ACTUAL* undo tie in is not yet implemented
    };
}
