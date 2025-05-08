////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QScrollBar>

namespace yq::gluon {
    class ScrollBar : public QScrollBar {
        Q_OBJECT
    public:
        ScrollBar(QWidget *parent = nullptr);
        ScrollBar(Qt::Orientation orientation, QWidget *parent = nullptr);        
        ~ScrollBar();
        
        QSize sizeHint() const override;
    };
}
