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
#include <yq/core/Ref.hpp>
#include <gluon/preamble.hpp>

namespace yq::gluon {

    class GridTickModel;

    /*! \brief Ruler for ticking off pixels
    */
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
        
        //! Background color
        QColor          	background() const 	{ return m_bkgndColor; }
        
        //! Zoom factor
        double				zoom() const   		{ return m_zoom; }
        
        //! Mouse position (either x or y depending on orientation)
        int					mouse() const 		{ return m_mouse; }
        
        //! Ruler orientation
        Qt::Orientation     orientation() const { return m_orientation; }
        /*! minimum number of pixels for ruler to consider a tick */
        int                 tickThreshold() const  { return m_tick; }
        /*! minimum number of pixels for ruler to consider a label */
        int                 labelThreshold() const { return m_label; }

        //! Sets the tick model
        void                setModel(Ref<const GridTickModel>);
        
        //! Sets the background
        void                setBackground(const QColor&);
        
        //! Sets the orientation
        void                setOrientation(Qt::Orientation);
        
        //! Sets the tick threshhold
        void                setTickThreshold(int);
        
        //! Sets the label threshhold
        void                setLabelThreshold(int);
        
    public slots:
    
        //! Sets the mouse position (ie, moves the marker)
        void                setMouse(int);
        
        //! Sets the center tick
        void                setCenter(int64_t);
        
        //! Sets the zoom
        void                setZoom(double);

    signals:
    
        //! Mouse changed
        void                mouse(int);
        
        //! Center changed
        void                center(int64_t);

    protected:
        //! Size hint
        QSize               sizeHint() const;
        
        //! Paint event
        virtual void        paintEvent(QPaintEvent*) override;
        
        //! Resize event
        virtual void        resizeEvent(QResizeEvent*) override;
        
        //! Mouse pressed
        virtual void        mousePressEvent(QMouseEvent*) override;
        
        //! Mouse released
        virtual void        mouseReleaseEvent(QMouseEvent*) override;
        
        //! Mouse moved
        virtual void        mouseMoveEvent(QMouseEvent*) override;
        
        //! Mouse wheel spun
        virtual void        wheelEvent(QWheelEvent*) override;
        
        //! Left the widget
        virtual void        leaveEvent(QEvent*) override;

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
