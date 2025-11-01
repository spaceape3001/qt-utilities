////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Dock.hpp"
#include "DockMetaWriter.hpp"
#include <QCloseEvent>

namespace yq::gluon {
    struct Dock::Repo {
        MetaLookup<DockMeta>    docks;
    };

    const std::vector<const DockMeta*>& DockMeta::all()
    {
        return Dock::repo().docks.all;
    }

    DockMeta::DockMeta(std::string_view zName, ObjectMeta& pMeta, const std::source_location& sl) : 
        ObjectMeta(zName, pMeta, sl)
    {
        Dock::repo().docks << this;
    }

    Object*     DockMeta::create() const 
    {
        return create(nullptr);
    }

    ///////////////////////////////////////////////////////////////////////////

    void Dock::init_meta()
    {
        auto w = writer<Dock>();
        w.description("Dock");
        w.abstract();
    }

    Dock::Repo& Dock::repo()
    {
        static Repo s_repo;
        return s_repo;
    }

    Dock::Dock(QWidget*parent) : QDockWidget(parent)
    {
    }
    
    Dock::~Dock()
    {
    }

    void    Dock::_update()
    {
        if(m_action)
            m_action -> setChecked(isVisible());
    }

    void        Dock::closeEvent(QCloseEvent*evt)
    {
        hide();
        _update();
        evt -> ignore();
    }

    void        Dock::hideEvent(QHideEvent*evt) 
    {
        QDockWidget::hideEvent(evt);
        _update();
    }

    void        Dock::showEvent(QShowEvent*evt) 
    {
        QDockWidget::showEvent(evt);
        _update();
    }

    void Dock::startup()
    {
        const DockMeta& di = metaInfo();
        const ActionInfo& ai  = di.action_info();
        m_action    = createAction(ai, this);
        m_action->setVisible(ai.checked);
        setVisible(ai.checked);
        setAllowedAreas(di.allowed_areas());
        if(windowTitle().isEmpty())
            setWindowTitle(ai.label);
        connect(m_action, &QAction::triggered, this, &Dock::triggered);
    }

    void        Dock::triggered(bool f)
    {
        setVisible(f);
        _update();
    }
}

YQ_OBJECT_IMPLEMENT(yq::gluon::Dock)

#include "moc_Dock.cpp"
