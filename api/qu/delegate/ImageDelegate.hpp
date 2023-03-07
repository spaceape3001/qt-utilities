////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/delegate/Delegate.hpp>

class QImage;

namespace qu {

    class ImageDelegate : public Delegate {
        Q_OBJECT
    public:
        using DataType = QImage;
        ImageDelegate(QObject* parent=nullptr);
        virtual ~ImageDelegate();
        
        virtual bool        paint(QPainter*, const QStyleOptionViewItem& option, const QVariant&) const override;
        virtual QSize       sizeHint(const QStyleOptionViewItem &option,
                                const QModelIndex &index) const override;
    };

}
