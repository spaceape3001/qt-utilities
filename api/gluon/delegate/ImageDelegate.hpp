////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/delegate/Delegate.hpp>

class QImage;

namespace yq::gluon {

    /*! \brief Image Delegate
    
        Use this when you expect the data to be an image
    */
    class ImageDelegate : public Delegate {
        Q_OBJECT
        YQ_OBJECT_DECLARE(ImageDelegate, Delegate)
    public:
        using DataType = QImage;
        
        //! Constructor
        ImageDelegate(QObject* parent=nullptr);
        
        //! Destructor
        virtual ~ImageDelegate();
        
        //! Paints the cell
        virtual bool        paint(QPainter*, const QStyleOptionViewItem& option, const QVariant&) const override;
        
        //! Size hint for the cell
        virtual QSize       sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    };

}
