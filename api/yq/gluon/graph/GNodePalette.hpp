////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/widget/PaletteWidget.hpp>
#include <yq/typedef/g_node_template.hpp>

namespace yq::gluon {
    class GNodePalette : public PaletteWidget {
        Q_OBJECT
    public:
        GNodePalette(QWidget*parent=nullptr);
        GNodePalette(const std::vector<GNodeTemplateCPtr>& nodes, QWidget*parent=nullptr);
        ~GNodePalette();
        
        void addNodes(const std::vector<GNodeTemplateCPtr>&);

        struct Item;
        
    protected:
        virtual QMimeData*  mimeData(const PaletteWidget::Item*) const override;
    };
}
