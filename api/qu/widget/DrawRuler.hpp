////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QWidget>
#include <QColor>
//#include <QList>
//#include <QSize>
#include <QtGlobal>
#include <basic/Ref.hpp>
#include <qu/preamble.hpp>

namespace qu {

    class GridTickModel;

    class DrawRuler : public QWidget {
        Q_OBJECT
    //    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor )
    //    Q_PROPERTY(int mouse READ mouse WRITE setMouse )

    public:    
                            DrawRuler(QWidget* parent=0);
                            DrawRuler(Qt::Orientation,QWidget* parent=0);
                           ~DrawRuler();
        
        /*! \brief	Specifies the CENTER position of the ruler */
        int64_t			    center() const 		{ return m_center; }
        QColor          	background() const 	{ return m_bkgndColor; }
        double				zoom() const   		{ return m_zoom; }
        int					mouse() const 		{ return m_mouse; }
        Qt::Orientation     orientation() const { return m_orientation; }
        /*! minimum number of pixels for ruler to consider a tick */
        int                 tickThreshold() const  { return m_tick; }
        /*! minimum number of pixels for ruler to consider a label */
        int                 labelThreshold() const { return m_label; }

        void                setModel(Ref<const GridTickModel>);
        void                setBackground(const QColor&);
        void                setOrientation(Qt::Orientation);
        void                setTickThreshold(int);
        void                setLabelThreshold(int);
        
    public slots:
        void                setMouse(int);
        void                setCenter(int64_t);
        void                setZoom(double);

    signals:
        void                mouse(int);
        void                center(int64_t);

    protected:
        QSize               sizeHint() const;
        virtual void        paintEvent(QPaintEvent*);
        virtual void        resizeEvent(QResizeEvent*);
        virtual void        mousePressEvent(QMouseEvent*);
        virtual void        mouseReleaseEvent(QMouseEvent*);
        virtual void        mouseMoveEvent(QMouseEvent*);
        virtual void        wheelEvent(QWheelEvent*);
        virtual void        leaveEvent(QEvent*);

    private:
        Ref<const GridTickModel>    m_model;
        QColor                  m_bkgndColor;
        double                  m_zoom;
        int64_t                 m_center;
        int                     m_mouse;
        int                     m_tick;
        int                     m_label;
        int                     m_width;
        Qt::Orientation         m_orientation;
        bool                    m_press;

        bool                horz() const { return m_orientation == Qt::Horizontal; }

        //  default settings
        static constexpr const int    kDefTick     = 7;
        static constexpr const int    kDefLabel    = 100;
        static constexpr const double kDefWheel    = 1.0; /* with respect to the m_tick value */
        static constexpr const int    kDefWidth    = 24;
        static constexpr const int    kDefMajor    = 12;
        static constexpr const int    kDefMinor    = 18;
    };

}
