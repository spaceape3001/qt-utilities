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
        
        bool    dragEnabled() const { return m_dragEnabled; }
        
    public slots:
        void    setDragEnabled(bool);

    private slots:
        void    itemPressed(QListWidgetItem*);

    signals:
        
    protected:
        virtual Item*       createItem(const QString&);
        virtual QMimeData*  mimeData(const Item*) const { return nullptr; }
    private:
        std::map<QString, Pane*, IgCaseQ>   m_panes;
        QListView::ViewMode                 m_viewMode      = QListView::ListMode;
        bool                                m_dragEnabled   = false;
    };

    class PaletteWidget::Item : public QListWidgetItem {
    public:
    
        Item(const QString&);
        virtual ~Item();
    
    };

    class PaletteWidget::Pane : public QListWidget {
        Q_OBJECT
    public:
    
        Pane(PaletteWidget*, QWidget*parent=nullptr);
        ~Pane();
    
        Item*   addItem(const QString&);
        Item*   addItem(Item*);
        
    protected:
    
    private:
        void 	addItems(const QStringList &) = delete;

        friend class PaletteWidget;
        PaletteWidget*  const   m_widget;
        int                     m_index = 0;
    };

}

