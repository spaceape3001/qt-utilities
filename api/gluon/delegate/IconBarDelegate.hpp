////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/delegate/Delegate.hpp>
#include <yq-toolbox/container/Vector.hpp>

namespace yq::gluon {

    /*! \brief Delegate to show buttons, allow the user to "click" on them

        Buttons can have two types, ones that alternate, ones that show/hide.  
        If an "off" icon is specifed, then the former behavior is chosen,
        whereas a single icon implies the later.
        
        The value is bitwise unsigned integer, thereby *restricting*
        to 32 icons, shouldn't be a real problem for most anticipated usages.
        
        It's bitwise, btw
    */
    class IconBarDelegate : public Delegate {
        Q_OBJECT
        YQ_OBJECT_DECLARE(IconBarDelegate, Delegate)
    public:
    
        //! Maximum number of panels
        static constexpr const unsigned int kMaxPanel      = 32;

        //! Constructor
        IconBarDelegate(QObject* parent=nullptr);
        
        //! Destructor
        ~IconBarDelegate();
        
        /*! Adds a panel.
        
            If off is specified, then it's assumed to be a togggle, and 
            the panel will always send a "clicked" notification.  If the off
            is omitted, then it's assumed to be a regular button, and
            clicked notifications will be restricted to "on-state" only.
        */
        uint8_t     addPanel(const QString& on, const QString& off=QString());
        
        //! Size hint of item
        QSize       sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const override;
        
        //! Count of panels
        uint8_t     count() const;
        
    protected:
    
        //! Editor event
        bool    editorEvent(QEvent*, QAbstractItemModel*, const QStyleOptionViewItem&, const QModelIndex&) override;
        
        //! Paint
        bool    paint(QPainter*, const QStyleOptionViewItem&, const QVariant&) const override;

    signals:
        //  User clicked on an icon.  
        void        clicked(const QModelIndex&, uint8_t, Qt::KeyboardModifiers);

    private:
        struct Panel;
        
        Vector<Panel>   m_panels;
        QSize           m_size;

    };
}
