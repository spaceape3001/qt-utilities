////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QToolBar>
#include <yq/gluon/keywords.hpp>

class QToolButton;

namespace yq::gluon {
    class GraphicsToolMeta;
    class GraphicsTool;
    class UInt64SignalMapper;

    class GraphicsToolBar : public QToolBar {
        Q_OBJECT
    public:
        GraphicsToolBar(QWidget*parent=nullptr);
        ~GraphicsToolBar();
        
        void    add(tool_k, const GraphicsToolMeta&);
        void    add(tool_k, std::string_view);
        void    add(separator_k);
        
        template <typename>
        void    add(tool_k);
        
    public slots:
        void    setActive(uint64_t);
        
    signals:
        void    clicked(uint64_t);
        
    private:
        std::map<uint64_t, QToolButton*>    m_buttons;
        UInt64SignalMapper*                 m_mapper    = nullptr;
    };
}
