////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/app/MainWindow.hpp>
#include <gluon/undo/UndoCallback.hpp>

class QUndoCommand;
class QUndoStack;

namespace yq::gluon {

    class UndoMainWindow : public MainWindow, public UndoCallback {
        Q_OBJECT
    public:

        void                pushUndo(QUndoCommand*) override;

        bool                isClean() const;
        bool                canRedo() const;
        bool                canUndo() const;
        QString             redoText() const;
        QString             undoText() const;

    signals:
        void                cleanChanged(bool);

    protected:
        UndoMainWindow(QWidget* editor=nullptr);
        virtual ~UndoMainWindow();
        
        virtual void        connectNotify(const QMetaMethod&);
        void                setClean();
        void                clearUndo();
        
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
