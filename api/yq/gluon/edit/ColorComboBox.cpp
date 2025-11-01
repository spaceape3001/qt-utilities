////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <gluon/edit/ColorComboBox.hpp>

namespace yq::gluon {
    ColorComboBox::ColorComboBox(QWidget* parent) : ComboBox(parent)
    {
        populate();
    }

    ColorComboBox::~ColorComboBox()
    {
    }

    QColor  ColorComboBox::color() const
    {
        return itemData(currentIndex(), Qt::DecorationRole).value<QColor>();
    }

    void    ColorComboBox::setColor(QColor clr)
    {
        setCurrentIndex(findData(clr, (int) Qt::DecorationRole));
    }
        

    void    ColorComboBox::populate()
    {
        insertItem(0, "(no color)");
        setItemData(0, QColor(), Qt::DecorationRole);
        QStringList     names   = QColor::colorNames();
        names.sort();
        for(int i=0;i<names.size();++i){
            insertItem(i+1, names[i]);
            setItemData(i+1, QColor(names[i]), Qt::DecorationRole);
        }
    }
}

#include "moc_ColorComboBox.cpp"
