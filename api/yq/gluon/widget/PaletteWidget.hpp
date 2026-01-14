////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QListWidget>
#include <QListWidgetItem>
#include <QToolBox>
#include <yq/gluon/core/IgCaseQ.hpp>

namespace yq::gluon {
    class PaletteWidget : public QToolBox {
        Q_OBJECT
    public:
        PaletteWidget(QWidget*parent=nullptr);
        ~PaletteWidget();
        
        struct Item;
        struct Pane;
        
        Pane&   category(const QString&, const QIcon& ico={});

    signals:
        
    private:
        std::map<QString, Pane*, IgCaseQ>   m_panes;
    };

    class PaletteWidget::Item : public QListWidgetItem {
    public:
    
        Item(const QString&);
        virtual ~Item();
    
    };

    class PaletteWidget::Pane : public QListWidget {
        Q_OBJECT
    public:
    
        Pane(QWidget*parent=nullptr);
        ~Pane();
    
        Item&   addItem(const QString&);
        
    private:
        void 	addItems(const QStringList &) = delete;

        friend class PaletteWidget;
        int         m_index = 0;
    };

}

