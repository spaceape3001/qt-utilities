////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/app/SubWindow.hpp>
#include <yq/gluon/undo/UndoCallback.hpp>

class QUndoCommand;
class QUndoStack;

namespace yq::gluon {

    /*! \brief Subwindow with its own Undo stack
    */
    class UndoSubWindow : public SubWindow, public UndoCallback {
        Q_OBJECT
    public:

        //! Push a new undo onto the stack
        void                pushUndo(QUndoCommand*) override;

        //! TRUE if clean
        bool                isClean() const;
        
        //! True if can redo
        bool                canRedo() const;
        
        //! True if we can currently undo
        bool                canUndo() const;
        
        //! Text for redo'ing
        QString             redoText() const;
        
        //! Text for undo'ing
        QString             undoText() const;

    signals:    
        //! Emitted with redo capability changed
        void                canRedoChanged(bool);

        //! Emitted with undo capability changed
        void                canUndoChanged(bool);

        //! Emitted with redo text changed
        void                redoTextChanged(const QString&);

        //! Emitted with undo text changed
        void                undoTextChanged(const QString&);
        
        //! Emitted when clean changed
        void                cleanChanged(bool);

    public slots:
    
        //! Undo last thing on stack
        void                undo();
        
        //! Redo next thing on stack
        void                redo();
        
    protected:
    
        //! Constructor
        UndoSubWindow(QWidget*parent=nullptr);
        
        //! Destructor
        virtual ~UndoSubWindow();
        
        virtual void    connectNotify(const QMetaMethod&) override;
        
        //! Set the clean status
        void                setClean();
        
        //! Clear the undo stack
        void                clearUndo();

    private:
        QUndoStack*     m_undo;
        
        enum {
            CC      =  1,
            RC      =  2,
            UC      =  4,
            RT      =  8,
            UT      = 16
        };
        unsigned int    m_connected;
    };
}
