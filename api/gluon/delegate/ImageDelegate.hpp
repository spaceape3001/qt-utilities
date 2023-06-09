////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/delegate/Delegate.hpp>

class QImage;

namespace yq::gluon {

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
