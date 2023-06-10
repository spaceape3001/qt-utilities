////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/app/SubWindow.hpp>
#include <gluon/undo/UndoCallback.hpp>

class QUndoCommand;
class QUndoStack;

namespace yq::gluon {

    class UndoSubWindow : public SubWindow, public UndoCallback {
        Q_OBJECT
    public:

        void                pushUndo(QUndoCommand*) override;

        bool                isClean() const;
        bool                canRedo() const;
        bool                canUndo() const;
        QString             redoText() const;
        QString             undoText() const;

    signals:    
        void                canRedoChanged(bool);
        void                canUndoChanged(bool);
        void                redoTextChanged(const QString&);
        void                undoTextChanged(const QString&);
        void                cleanChanged(bool);

    public slots:
        void                undo();
        void                redo();
        
    protected:
        UndoSubWindow(QWidget*parent=nullptr);
        virtual ~UndoSubWindow();
        
        virtual void    connectNotify(const QMetaMethod&) override;
        void                setClean();
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
