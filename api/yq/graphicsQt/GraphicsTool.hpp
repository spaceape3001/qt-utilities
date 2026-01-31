////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QObject>
#include <yq/core/UniqueID.hpp>
#include <yq/gluon/core/ObjectQ.hpp>

class QIcon;
class QCursor;
class QContextMenuEvent;
class QDragEnterEvent;
class QDragLeaveEvent;
class QDragMoveEvent;
class QDropEvent;
class QEnterEvent;
class QEvent;
class QFocusEvent;
class QKeyEvent;
class QResizeEvent;
class QTabletEvent;
class QMouseEvent;
class QWheelEvent;

namespace yq::gluon {
    class GraphicsScene;
    class GraphicsView;
    class GraphicsCanvas;
    
    class GraphicsToolMeta : public ObjectQMeta {
    public:
        template <typename> class Writer;
        GraphicsToolMeta(std::string_view zName, ObjectQMeta& base, const std::source_location& sl=std::source_location::current());
        
        static const GraphicsToolMeta* find(std::string_view);
        
    protected:
        ~GraphicsToolMeta();
    private:
        struct Repo;
        static Repo& repo();
    };

    class GraphicsTool : public QObject, public ObjectQ, public UniqueID {
        YQ_OBJECT_META(GraphicsToolMeta)
        YQ_OBJECTQ_DECLARE_ABSTRACT(GraphicsTool, ObjectQ)
        Q_OBJECT
    public:
        
        static void init_meta();
        
        virtual QCursor cursor() const;
        virtual QIcon   icon() const;
        
        //! Current scene (if active)
        GraphicsScene*  scene() const;
        
        //! Current view (if active)
        GraphicsView*   view() const;
        
        bool            active() const;
        
    signals:
        void            cursorChanged(const QCursor&);
        void            iconChanged(const QIcon&);
        
    protected:
        GraphicsTool(QObject*parent=nullptr);
        ~GraphicsTool();
        
        friend class GraphicsView;
        
        //! Being activated as a tool (ie, being installed into the view)
        virtual void    activating(){}
        
        //! Being deactivated as a tool (ie being removed from a view)
        virtual void    deactivating(){}
        
        virtual void    contextMenuEvent(QContextMenuEvent*){}
        
        virtual void 	dragEnterEvent(QDragEnterEvent*){}
        virtual void 	dragLeaveEvent(QDragLeaveEvent*){}
        virtual void 	dragMoveEvent(QDragMoveEvent*){}
        virtual void 	dropEvent(QDropEvent*){}
        
        virtual void    enterEvent(QEnterEvent*){}
        
        virtual void 	focusInEvent(QFocusEvent*){}
        virtual void 	focusOutEvent(QFocusEvent*){}
        
        virtual void 	keyPressEvent(QKeyEvent*){}
        virtual void 	keyReleaseEvent(QKeyEvent*){}

        virtual void    leaveEvent(QEvent*){}

        virtual void    mouseDoubleClickEvent(QMouseEvent*){}
        virtual void    mouseMoveEvent(QMouseEvent*){}
        virtual void    mousePressEvent(QMouseEvent*){}
        virtual void    mouseReleaseEvent(QMouseEvent*){}
        
        // WARNING... coordinates not normalized into scene-space, translate before use!
        virtual void 	tabletEvent(QTabletEvent*){}
        
        //! Called if there's a wheel event (and activate)
        //! ACCEPT the event to stop further processing
        virtual void    wheelEvent(QWheelEvent*){}
        
    private:
        friend class GraphicsCanvas;
        
        GraphicsCanvas* m_canvas    = nullptr;
        GraphicsView*   m_view      = nullptr;
    };
}
