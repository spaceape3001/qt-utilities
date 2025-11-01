////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QWidget>
#include <QColor>
#include <yq/gluon/undo/UndoBase.hpp>

namespace yq::gluon {

    /*! \brief Color chip
    
        A chip of color, double click to change colors.
    */
    class ColorChip : public QWidget, public UndoBase {
        Q_OBJECT
    public:
    
        //! Constructor 
        ColorChip(QWidget* parent=nullptr);
        
        //! Destructor
        ~ColorChip();

        //! Set to enable the color chooser (ie, double click)
        void        setChooserEnable(bool);
        
        //! True if the chooser is enabled
        bool        chooserEnable() const { return m_chooser; }
        
        //! Set to enable an alpha channel
        void        setAlphaEnable(bool);
        
        //! True if the alpha channel is eanbled
        bool        alphaEnable() const { return m_alpha; }
        
        //  only valid when edit policy is Chooser
        //! TRUE to disable editing (only editable with chooser enabled)
        bool        readOnly() const { return m_readOnly; }
        
        //! Current color
        QColor      color() const { return m_color; }
    public slots:
    
        //! Sets the current color
        void        setColor(const QColor&);
        
        //! Sets the read-only policy
        void        setReadOnly(bool);
        
        //! Executes the chooser
        void        executeChooser(QWidget*parent=nullptr);
        
    signals:
    
        //! Emitted when clicked
        void        clicked();
        
        //! Emitted when double clicked
        void        doubleClicked();
        
        //! Color changed notification
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
