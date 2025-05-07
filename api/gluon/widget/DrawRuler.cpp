////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <gluon/widget/DrawRuler.hpp>
#include <gluon/model/GridTickModel.hpp>

#include <cstring>
#include <cmath>

#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QDebug>

#include <yq/container/Map.hpp>
#include <gluon/logging.hpp>

namespace yq::gluon {

    DrawRuler::DrawRuler(QWidget *parent) : DrawRuler(Qt::Vertical, parent)
    {
    }

    DrawRuler::DrawRuler(Qt::Orientation o,QWidget* parent) : QWidget(parent), m_orientation(o)
    {
        m_model         = nullptr;
        m_bkgndColor	= QColor("lightgrey");
        m_zoom          = 1.0;
        m_center        = 0;
        m_mouse         = 0;
        m_width         = kDefWidth;
        m_tick          = kDefTick;
        m_label         = kDefLabel;
        m_press         = false;
        
        setOrientation(o);
        setCursor(Qt::OpenHandCursor);
    }


    DrawRuler::~DrawRuler()
    {

    }

    void    DrawRuler::leaveEvent(QEvent* event)
    {
        m_press	= false;
        setCursor(Qt::OpenHandCursor);
        QWidget::leaveEvent(event);
    }

    QSize   DrawRuler::minimumSizeHint() const
    {
        return QSize(m_width, m_width);
    }

    void    DrawRuler::mouseMoveEvent(QMouseEvent* event)
    {
        int     mouse       = (horz()?event->position().x():event->position().y());
        if(m_press){
            int         delta       = mouse - m_mouse;
            int64_t dc  = (int64_t) ( delta / m_zoom + 0.5 );
            /* TODO vet this */
            if(m_zoom >= 0.0)
                m_center       -= dc;
            else
                m_center       += dc;
        }
        m_mouse     = mouse;
        update();
        event -> accept();
    }

    void    DrawRuler::mousePressEvent(QMouseEvent* event)
    {
        if(!m_press){
            m_press	= true;
            setCursor(Qt::ClosedHandCursor);
            if(horz())
                m_mouse	= event -> position().x();
            else
                m_mouse = event -> position().y();
        }
        event -> accept();
    }

    void    DrawRuler::mouseReleaseEvent(QMouseEvent* event)
    {
        if(!m_press){
            m_press     = false;
            setCursor(Qt::OpenHandCursor);
        }
        event -> accept();
    }

    void    DrawRuler::paintEvent(QPaintEvent* event)
    {
        QRect       r   = event -> rect();
        QPainter    p(this);

        if(!m_model){
            p.fillRect(r, m_bkgndColor);
        } else {
            int a = (horz()?r.left():r.top());
            int b = (horz()?r.right():r.bottom());
            int c = (horz()?width():height()) >> 1;
            
            int64_t     d;
            int64_t     e;
            uint64_t    f;
            
            double          z   = fabs(m_zoom);

            if(m_zoom < 0.0){
                d   = (int64_t) ((b - c) / m_zoom - 0.5) + m_center;
                e   = (int64_t) ((a - c) / m_zoom + 0.5) + m_center;
                f   = (uint64_t)(m_tick /  z );
            } else {
                d   = (int64_t) ((a - c) / m_zoom - 0.5) + m_center;
                e   = (int64_t) ((b - c) / z + 0.5) + m_center;
                f   = (uint64_t)(m_tick /  z );
            }    
            int     x1  = 0;
            int     y1  = 0;
            int     x2  = m_width;
            int     y2  = m_width;
            
            int     &mm = horz()?y1:x1;
            int     &s1 = horz()?x1:y1;
            int     &s2 = horz()?x2:y2;
            QFontMetrics   font    	= p.fontMetrics();
            int 	dh   			= font.height();
            
            std::vector<int64_t>      stops   = m_model -> stops(d, e, f);
            p.fillRect(r, m_bkgndColor);
            
            Map<uint64_t,QPen> pens;
            //QMap<uint64_t,bool> major;
            
            p.setPen(QPen(QColor("black")));
            for(int64_t s :  stops){
                uint64_t      pi  = m_model->pitch(s);
                if(!pens.has(pi))
                    pens[pi]    = QPen(m_model->color(s));
                bool    major = ((int) (pi * z)) >= m_label;
                s1 = s2     = ((int)(s * m_zoom - m_center + 0.5)) + c;
                mm      = major?kDefMajor:kDefMinor;
    //            p.setPen(pens[pi]);
                p.drawLine(x1,y1,x2,y2);
                if(major){
                    QString label       = m_model -> label(s);
                    if(horz()){
                        p.drawText(x1-font.horizontalAdvance(label)/2, dh, label);
                    } else {
                        int     jx  = label.length();
                        int     j;
                        int     n   = y1 - (dh*jx)/2+dh;
                        for(j=0;j<jx;++j)
                            p.drawText(1,n+j*dh, QString(label[j]));
                    }
                }
            }
        }
        
        p.setPen(QColor("black"));
        if(horz()){
            p.drawLine(0, m_width-1, width(), m_width-1);
            p.drawLine(m_mouse, 0, m_mouse, m_width);
        } else {
            p.drawLine(m_width-1,0,m_width-1,height());
            p.drawLine(0,m_mouse, m_width, m_mouse);
        }
        
        event -> accept();
    }
    
    void    DrawRuler::resizeEvent(QResizeEvent* event)
    {
        QWidget::resizeEvent(event);
        update();
    }

    void                DrawRuler::setBackground(const QColor& clr)
    {
        m_bkgndColor        = clr;
        update();
    }

    void                DrawRuler::setCenter(int64_t c)
    {
        m_center        = c;
        update();
        emit center(c);
    }

    void                DrawRuler::setLabelThreshold(int n)
    {
        m_label     = n;
        update();
    }

    void                DrawRuler::setModel(Ref<const GridTickModel> model)
    {
        if(m_model == model)
            return;
        if(m_model)
            disconnect(m_model);
        m_model     = model;
        connect(m_model, &GridTickModel::modelChanged, [this]() { this->update(); });
        update();
    }

    void                DrawRuler::setMouse(int n)
    {
        m_mouse     = n;
        update();
        emit mouse(n);
    }

    void                DrawRuler::setOrientation(Qt::Orientation o)
    {
        m_orientation   = o;
        if(horz())
            setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
        else
            setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
        update();
    }

    void                DrawRuler::setTickThreshold(int n)
    {
        m_tick      = n;
        update();
    }

    void                DrawRuler::setZoom(double f)
    {
        m_zoom      = f;
        update();
    }

    QSize   DrawRuler::sizeHint() const
    {
        if(horz())
            return QSize(500, m_width);
        else
            return QSize(m_width, 500);
    }

    void    DrawRuler::wheelEvent(QWheelEvent* event)
    {
        int64_t     delta       = (int64_t) ((event->angleDelta().y() *  m_tick * kDefWheel) / m_zoom + 0.5);
            /* TODO vet this */
        if(m_zoom >= 0.0)
            m_center -= delta;
        else
            m_center += delta;
        
        event -> accept();
        update();
    }


}

#include "moc_DrawRuler.cpp"
