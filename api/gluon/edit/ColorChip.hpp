////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QWidget>
#include <QColor>
#include <gluon/undo/UndoBase.hpp>

namespace yq::gluon {

    /*! \brief Color chip
    
        A chip of color, double click to change colors.
    */
    class ColorChip : public QWidget, public UndoBase {
        Q_OBJECT
    public:
        ColorChip(QWidget* parent=nullptr);
        ~ColorChip();

        void        setChooserEnable(bool);
        bool        chooserEnable() const { return m_chooser; }
        
        void        setAlphaEnable(bool);
        bool        alphaEnable() const { return m_alpha; }
        
        //  only valid when edit policy is Chooser
        bool        readOnly() const { return m_readOnly; }
        QColor      color() const { return m_color; }
    public slots:
        void        setColor(const QColor&);
        void        setReadOnly(bool);
        void        executeChooser(QWidget*parent=nullptr);
        
    signals:
        void        clicked();
        void        doubleClicked();
        void        colorChanged(const QColor&);

    private slots:
        void        updateNotify(const QColor&);

    protected:    
        
        virtual void enterEvent(QEnterEvent* event) override;
        virtual void leaveEvent(QEvent *event) override;
        virtual void mouseDoubleClickEvent ( QMouseEvent * event ) override;
        virtual void mousePressEvent ( QMouseEvent * event ) override;
        virtual void mouseReleaseEvent ( QMouseEvent * event ) override;
        virtual void paintEvent ( QPaintEvent * event ) override;

    private:
        QColor      m_color;
        bool        m_alpha;
        bool        m_chooser;
        bool        m_readOnly;
        bool        m_pressed       = false;
    };

}
