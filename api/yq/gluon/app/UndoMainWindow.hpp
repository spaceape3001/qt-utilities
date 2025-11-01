////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/app/MainWindow.hpp>
#include <yq/gluon/undo/UndoCallback.hpp>

class QUndoCommand;
class QUndoStack;

namespace yq::gluon {

    /*! \brief Main window with Undo stack
    
        This is a main window with a primary editor and an undo stack.
    */
    class UndoMainWindow : public MainWindow, public UndoCallback {
        Q_OBJECT
    public:

        //! Push an undo command onto the stack
        void                pushUndo(QUndoCommand*) override;

        //! TRUE if the undo stack is clean
        bool                isClean() const;
        
        //! TRUE if we can redo
        bool                canRedo() const;
        
        //! TRUE if we can undo
        bool                canUndo() const;
        
        //! Current redo text
        QString             redoText() const;
        
        //! Current undo text
        QString             undoText() const;

    signals:
        //! Activated if the clean changed
        void                cleanChanged(bool);

    protected:
        //! Constructor, taking in the editor
        UndoMainWindow(QWidget* editor=nullptr);
        
        //! Destructor
        virtual ~UndoMainWindow();
        
        //! Called when connected to
        virtual void        connectNotify(const QMetaMethod&) override;
        
        //! Force to be "clean"
        void                setClean();
        
        //! Clear undo stack
        void                clearUndo();
        
        //! Current undo
        QWidget*            editor() const { return m_editor; }

    private:    
        QWidget*        m_editor;
        QUndoStack*     m_undo;

        enum {
            CC      = 1
        };
        unsigned int    m_connected;
    };

}
