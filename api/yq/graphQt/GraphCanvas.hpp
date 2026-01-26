////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Ref.hpp>
#include <yq/graphicsQt/GraphicsCanvas.hpp>
#include <yq/net/Url.hpp>
#include <yq/typedef/g_document.hpp>
#include <yq/typedef/g_meta_graph.hpp>
#include <filesystem>

namespace yq::gluon {
    class GraphScene;
    class GraphView;

    class GraphCanvas : public GraphicsCanvas {
        Q_OBJECT
    public:
    
        GraphCanvas(QWidget*parent=nullptr);
        ~GraphCanvas();
        
        GraphScene*             scene() { return m_scene; }
        const GraphScene*       scene() const { return m_scene; }
        
        GraphView*              view() { return m_view; }
        const GraphView*        view() const { return m_view; }
        
        std::filesystem::path   dirpath() const;
        QString                 dirname() const;
        
        std::filesystem::path   filepath() const;
        QString                 filename() const;
        
        GDocumentPtr            get() const;
        void                    set(const GDocument&);
        
        const Url& url() const { return m_url; }
        

    public slots:
        void        updateTitle();
        void        clear();
        
    private:
        const unsigned          m_number;
        Url                     m_url;
        GraphScene*             m_scene     = nullptr;
        GraphView*              m_view      = nullptr;
    };

}
