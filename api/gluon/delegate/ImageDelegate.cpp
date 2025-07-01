////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <gluon/delegate/ImageDelegate.hpp>
#include <gluon/delegate/DelegateInfoWriter.hpp>
#include <QPainter>

namespace yq::gluon {
    ImageDelegate::ImageDelegate(QObject* parent) : Delegate(parent)
    {
    }

    ImageDelegate::~ImageDelegate()
    {
    }

    bool        ImageDelegate::paint(QPainter*painter, const QStyleOptionViewItem& option, const QVariant&value) const
    {
        //QVariant        value   = index.data();
        if(value.canConvert<QImage>()){
            QImage      image   = 
                value.value<QImage>()
                    .scaled(option.rect.size(), Qt::KeepAspectRatio);
            QSize       isize   = image.size();
            QPoint      pt;
            
            pt.setX((option.rect.width()-isize.width())/2+option.rect.left());
            pt.setY((option.rect.height()-isize.height())/2+option.rect.top());
            QRect       fit(pt, isize);
            painter->drawImage(fit, image);
            return true;
        } else {
            return false;
        }
    }

    QSize       ImageDelegate::sizeHint(const QStyleOptionViewItem &option,
                            const QModelIndex &index) const
    {
        QVariant        value   = index.data();
        if(value.canConvert<QImage>()){
            QImage      image   = value.value<QImage>();
            return image.size();
        } else {
            return Delegate::sizeHint(option, index);
        }
    }

    void ImageDelegate::init_meta()
    {
        auto w = writer<ImageDelegate>();
        w.description("Image delegate");
        w.declare_type<QImage>();
    }
}

YQ_OBJECT_IMPLEMENT(yq::gluon::ImageDelegate)
#include "moc_ImageDelegate.cpp"
