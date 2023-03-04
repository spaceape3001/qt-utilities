////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <qu/undo/UndoBase.hpp>
#include <atomic>
//  ACTION CLASS

namespace qu {

    UndoAction::UndoAction (QUndoCommand* cmd) : m_action(cmd)
    {
    }

    UndoAction::UndoAction (UndoAction&& mv) : m_action(nullptr)
    {
        std::swap(m_action, mv.m_action);
    }

    UndoAction::~UndoAction()
    {
        if(m_action){
            m_action->redo();
            m_action   = nullptr;
        }
    }

    UndoAction& UndoAction::operator=(UndoAction&&mv)
    {
        if(this != &mv){
            if(m_action){
                m_action->redo();
                m_action   = nullptr;
            }
            std::swap(m_action, mv.m_action);
        }
        return *this;
    }

    QUndoCommand*       UndoAction::release()
    {
        QUndoCommand*   cmd = nullptr;
        std::swap(cmd, m_action);
        return cmd;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    int      UndoBase::makeUndoId()
    {
        static std::atomic<int>     sId(0);
        return ++sId;
    }

    void            UndoBase::setUndoCallback(UndoCallback* newCallback)
    {
        m_callback  = newCallback;
        if(m_recursive){
            // TODO
        }
    }

    void            UndoBase::execute(QUndoCommand*cmd)
    {
        if(m_callback){
            m_callback -> pushUndo(cmd);
        } else {
            cmd -> redo();
            delete cmd;
        }
    }

}
