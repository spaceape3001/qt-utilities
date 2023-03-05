////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#include <qu/edit/ColorChip.hpp>
#include <QColorDialog>

#include <QPainter>
#include <QPaintEvent>

namespace qu {

    ColorChip::ColorChip(QWidget* parent) : 
        QWidget(parent), m_chooser(true), m_readOnly(false)
    {
        connect(this, &ColorChip::clicked, [this](){
            if(m_chooser)
                executeChooser();
        });
    }

    ColorChip::~ColorChip()
    {
    }

    void ColorChip::enterEvent(QEvent* event) 
    {
        m_pressed = false;
        QWidget::enterEvent(event);
    }

    void    ColorChip::executeChooser(QWidget*parent)
    {
        if(!m_readOnly){
            QColorDialog::ColorDialogOptions    options = {};
            if(m_alpha)
                options |= QColorDialog::ShowAlphaChannel;
            QColor  newColor    = QColorDialog::getColor(m_color, parent?parent:this, 
                tr("Select Color"), options);
            if(newColor.isValid() && (newColor != m_color))
                setColor(newColor);
        }
    }

    void ColorChip::leaveEvent(QEvent *event) 
    {
        m_pressed = false;
        QWidget::leaveEvent(event);
    }

    void    ColorChip::mouseDoubleClickEvent ( QMouseEvent * event )
    {
        emit doubleClicked();
        event->accept();
    }

    void ColorChip:: mousePressEvent ( QMouseEvent * event ) 
    {
        m_pressed = true;
        event->accept();
    }
    
    void ColorChip:: mouseReleaseEvent ( QMouseEvent * event ) 
    {
        if(m_pressed){
            event->accept();
            m_pressed = false;
            emit clicked();
        }
    }

    void    ColorChip::paintEvent ( QPaintEvent * event )
    {
        QPainter painter(this);
        painter.fillRect(geometry(), m_color);
        event->accept();
    }

    void    ColorChip:: setAlphaEnable(bool f)
    {
        m_alpha     = f;
    }


    void    ColorChip:: setChooserEnable(bool f)
    {
        m_chooser   = f;
    }


    void    ColorChip:: setColor(const QColor& c)
    {
        execSet(m_color, c, this, &ColorChip::updateNotify);
    }

    void    ColorChip::setReadOnly(bool f)
    {
        m_readOnly      = f;
    }


    void    ColorChip::updateNotify(const QColor& c)
    {
        update();
        emit colorChanged(c);
    }
}
