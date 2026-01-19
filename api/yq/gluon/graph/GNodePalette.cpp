////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/core/uicon.hpp>
#include <yq/gluon/core/ustring.hpp>
#include <yq/graph/GNodeTemplate.hpp>
#include <yq/text/match.hpp>

#include "GNodePalette.hpp"
#include "GNodeNewMimeData.hpp"

namespace yq::gluon {
    struct GNodePalette::Item : public PaletteWidget::Item {
        Item(const GNodeTemplateCPtr& v) : PaletteWidget::Item(qString(v->label)), m_node(v) 
        {
            static QIcon    s_regular  = qIcon("yq/icon/rectangle.svg");
            setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);
            setIcon(s_regular);
            
            // icons, colors...?
        }
        
        const GNodeTemplateCPtr  m_node;
    };

    GNodePalette::GNodePalette(QWidget*parent) : PaletteWidget(parent)
    {
        setDragEnabled(true);
        setWindowTitle(tr("Palette"));
    }
    
    GNodePalette::GNodePalette(const std::vector<GNodeTemplateCPtr>& nodes, QWidget*parent) : GNodePalette(parent)
    {
        addNodes(nodes);
    }
    
    GNodePalette::~GNodePalette()
    {
    }

    void GNodePalette::addNodes(const std::vector<GNodeTemplateCPtr>& nodes)
    {
        std::vector<GNodeTemplateCPtr> copy;
        for(auto& n : nodes){
            if(!n)
                continue;
            copy.push_back(n);
        }
        std::stable_sort(copy.begin(), copy.end(), [](const GNodeTemplateCPtr& a, const GNodeTemplateCPtr& b) -> bool{
            return is_less_igCase(a->label, b->label);
        });
        for(auto& xn : copy){
            category(qString(xn->category)).addItem(new Item(xn));
        }
    }

    QMimeData*  GNodePalette::mimeData(const PaletteWidget::Item* it) const
    {
        if(const Item*i = dynamic_cast<const Item*>(it))
            return new GNodeNewMimeData(i->m_node);
        return nullptr;
    }
}

#include "moc_GNodePalette.cpp"
