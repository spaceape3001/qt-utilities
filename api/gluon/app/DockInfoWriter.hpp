////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/app/Dock.hpp>
#include <yq/meta/ObjectMetaWriter.hpp>

namespace yq::gluon {
    template <typename C>
    class DockInfo::Writer : public ObjectMeta::Writer<C> {
    public:
        Writer(DockInfo* dInfo) : ObjectMeta::Writer<C>(dInfo), m_meta(dInfo)
        {
        }
        
        Writer(DockInfo& dInfo) : Writer(&dInfo)
        {
        }

        Writer& allow(Qt::DockWidgetAreas dwa)
        {
            if(m_meta)
                m_meta -> m_allowedAreas   = dwa;
            return *this;
        }

        Writer& area(Qt::DockWidgetArea dwa)
        {
            if(m_meta)
                m_meta -> m_startArea   = dwa;
            return *this;
        }
        
        Writer& auto_start()
        {
            if(m_meta)
                m_meta -> m_action.checked  = true;
            return *this;
        }

        Writer& icon(const QIcon& ico)
        {
            if(m_meta)
                m_meta -> m_action.icon    = ico;
            return *this;
        }
        
        Writer& label(const QString& s)
        {
            if(m_meta)
                m_meta -> m_action.label    = s;
            return *this;
        }
        
        Writer& shortcut(const QKeySequence& ks)
        {
            if(m_meta)
                m_meta -> m_action.shortcut = ks;
            return *this;
        }
        
        Writer& tooltip(const QString& s)
        {
            if(m_meta)
                m_meta -> m_action.toolTip = s;
            return *this;
        }

    private:
        DockInfo*    m_meta;
    };

    template <typename Obj> 
    class DockFixer : public ObjectFixer<Obj> {
    public:
        DockFixer(std::string_view szName, typename Obj::MyBase::MyInfo& myBase, std::source_location sl=std::source_location::current()) : 
            ObjectFixer<Obj>(szName, myBase, sl) 
        {
        }
        
        using ObjectFixer<Obj>::create; // only here to suppress warning

        Dock*       create(QWidget*parent) const override
        {
            if constexpr (std::is_constructible_v<Obj, QWidget*> && !std::is_abstract_v<Obj>) {
                if(ObjectMeta::is_abstract())
                    return nullptr;
                Dock*   ret = new Obj(parent);
                ret->startup();
                return ret;
            } else
                return nullptr;
        }
        
    };
}

