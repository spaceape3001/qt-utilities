////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "UndoMainWindow.hpp"
#include <gluon/undo/UndoBase.hpp>
#include <QMetaMethod>
#include <QUndoStack>

namespace yq::gluon {
    UndoMainWindow::UndoMainWindow(QWidget* editor) : MainWindow(), m_editor(editor), m_undo(nullptr), m_connected(0)
    {
        m_undo      = new QUndoStack(this);
        
        QAction * undo = addAction("undo", tr("Undo")).shortcut(tr("Ctrl+Z")).connect(m_undo, &QUndoStack::undo);
        QAction * redo = addAction("redo", tr("Redo")).shortcut(tr("Ctrl+Shift+Z")).connect(m_undo, &QUndoStack::redo);
        connect(m_undo, &QUndoStack::canRedoChanged, redo, &QAction::setEnabled);
        connect(m_undo, &QUndoStack::canUndoChanged, undo, &QAction::setEnabled);
        
        connect(m_undo, &QUndoStack::redoTextChanged, [redo](const QString& text){
            redo -> setText(tr("Redo %1").arg(text));
        });
        connect(m_undo, &QUndoStack::undoTextChanged, [undo](const QString& text){
            undo -> setText(tr("Undo %1").arg(text));
        });
        
        if(editor){
            setCentralWidget(editor);
            UndoBase*   ub  = dynamic_cast<UndoBase*>(editor);
            if(ub)
                ub -> setUndoCallback(this);
        }

        m_undo -> setClean();
    }

    UndoMainWindow::~UndoMainWindow()
    {
    }


    bool                UndoMainWindow::canRedo() const
    {
        return m_undo -> canRedo();
    }

    bool                UndoMainWindow::canUndo() const
    {
        return m_undo -> canUndo();
    }

    void    UndoMainWindow::clearUndo()
    {
        m_undo -> clear();
    }

    void    UndoMainWindow::connectNotify(const QMetaMethod&mm)
    {
        MainWindow::connectNotify(mm);
            
            //  Given that we don't actually need to connect the signals to the 
            //  unto stack until the client explicitly connected to our signals, 
            //  we defer this until here... just one way, don't bother with
            //  the disconnect.
        
        if(mm == QMetaMethod::fromSignal(&UndoMainWindow::cleanChanged) && !(m_connected & CC)){
            connect(m_undo, &QUndoStack::cleanChanged, this, &UndoMainWindow::cleanChanged);
            m_connected |= CC;
        }
    }

        
    bool                UndoMainWindow::isClean() const
    {
        return m_undo -> isClean();
    }

    void                UndoMainWindow::pushUndo(QUndoCommand* cmd) 
    {
        m_undo -> push(cmd);
    }

    QString             UndoMainWindow::redoText() const
    {
        return m_undo -> redoText();
    }

    void                UndoMainWindow::setClean()
    {
        m_undo -> setClean();
    }

    QString             UndoMainWindow::undoText() const
    {
        return m_undo -> undoText();
    }

}
