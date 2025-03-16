////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "UndoSubWindow.hpp"
#include <QMetaMethod>
#include <QUndoStack>

namespace yq::gluon {
    UndoSubWindow::UndoSubWindow(QWidget*parent) : SubWindow(parent), m_undo(nullptr), m_connected(0)
    {
        m_undo  = new QUndoStack(this);
        m_undo -> setClean();
    }

    UndoSubWindow::~UndoSubWindow()
    {
    }

    bool        UndoSubWindow::canRedo() const
    {
        return m_undo -> canRedo();
    }

    bool        UndoSubWindow::canUndo() const
    {
        return m_undo -> canUndo();
    }

    void    UndoSubWindow::clearUndo()
    {
        m_undo -> clear();
    }

    void    UndoSubWindow::connectNotify(const QMetaMethod&mm)
    {
        SubWindow::connectNotify(mm);
            
            //  Given that we don't actually need to connect the signals to the 
            //  undo stack until the client explicitly connected to our signals, 
            //  we defer this until here... just one way, don't bother with
            //  the disconnect.
        
        if(mm == QMetaMethod::fromSignal(&UndoSubWindow::cleanChanged) && !(m_connected & CC)){
            connect(m_undo, &QUndoStack::cleanChanged, this, &UndoSubWindow::cleanChanged);
            m_connected |= CC;
        }
        if(mm == QMetaMethod::fromSignal(&UndoSubWindow::canRedoChanged) && !(m_connected & RC)){
            connect(m_undo, &QUndoStack::canRedoChanged, this, &UndoSubWindow::canRedoChanged);
            m_connected |= RC;
        }
        if(mm == QMetaMethod::fromSignal(&UndoSubWindow::canUndoChanged) && !(m_connected & UC)){
            connect(m_undo, &QUndoStack::canUndoChanged, this, &UndoSubWindow::canUndoChanged);
            m_connected |= UC;
        }
        if(mm == QMetaMethod::fromSignal(&UndoSubWindow::redoTextChanged) && !(m_connected & RT)){
            connect(m_undo, &QUndoStack::redoTextChanged, this, &UndoSubWindow::redoTextChanged);
            m_connected |= RT;
        }
        if(mm == QMetaMethod::fromSignal(&UndoSubWindow::undoTextChanged) && !(m_connected & UT)){
            connect(m_undo, &QUndoStack::undoTextChanged, this, &UndoSubWindow::undoTextChanged);
            m_connected |= UT;
        }
    }

        
    bool                UndoSubWindow::isClean() const
    {
        return m_undo -> isClean();
    }

    void                UndoSubWindow::pushUndo(QUndoCommand* cmd) 
    {
        m_undo -> push(cmd);
    }

    void                UndoSubWindow::redo()
    {
        m_undo -> redo();
    }

    QString             UndoSubWindow::redoText() const
    {
        return m_undo -> redoText();
    }

    void                UndoSubWindow::setClean()
    {
        m_undo -> setClean();
    }

    void                UndoSubWindow::undo()
    {
        m_undo -> undo();
    }

    QString             UndoSubWindow::undoText() const
    {
        return m_undo -> undoText();
    }
}


#include "moc_UndoSubWindow.cpp"

