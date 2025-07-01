////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QDockWidget>
#include <QIcon>
#include <QKeySequence>
#include <yq/core/Object.hpp>
#include <gluon/core/Action.hpp>

class QAction;

namespace yq::gluon {
    template <typename Obj> class DObjectFixer;
    class Dock;

    template <typename Obj> class DockFixer;

    class DockInfo : public ObjectMeta {
    public:
        template <typename C> class Writer;
        
        DockInfo(std::string_view, ObjectMeta&, const std::source_location& sl);
        
        const ActionInfo&   action_info() const { return m_action; }
        
        Object*         create() const override;
        virtual Dock*   create(QWidget*parent) const = 0;
        
        Qt::DockWidgetArea  start_area() const { return m_startArea; }
        Qt::DockWidgetAreas allowed_areas() const { return m_allowedAreas; }
    
        static const std::vector<const DockInfo*>& all();
    
    protected:

#if 0    
        enum class DFlag {
            HAS_ACTION  = (int) Flag::NEXT_DEFINED_FLAG
        };
        
        static constexpr Flag   FlagHasAction   = (Flag) DFlag::HAS_ACTION;
#endif        
    
        ActionInfo          m_action;
        Qt::DockWidgetArea  m_startArea       = Qt::LeftDockWidgetArea;
        Qt::DockWidgetAreas m_allowedAreas    = Qt::AllDockWidgetAreas;
    };

    /*! \brief Application scoped dock (one that hides in lieu of closing)
    */
    class Dock : public QDockWidget, public Object {
        Q_OBJECT
        YQ_OBJECT_INFO(DockInfo)
        YQ_OBJECT_FIXER(DockFixer)
        YQ_OBJECT_DECLARE(Dock, Object)
        template <typename C> friend class DockFixer;
    public:
    
        QAction*    action() const { return m_action; }
        
        static void init_meta();
    
    protected:
        Dock(QWidget*parent=nullptr);
        ~Dock();

        void        closeEvent(QCloseEvent*) override;
        void        showEvent(QShowEvent*) override;
        void        hideEvent(QHideEvent*) override;
        
        //! Used when starting up... (after the constructor but before the add)
        virtual void startup();
    
    private slots:
        void        triggered(bool);

    private:
        friend class DockInfo;
        struct Repo;
        static Repo& repo();

        void    _update();

        QAction*    m_action    = nullptr;
    };

}
