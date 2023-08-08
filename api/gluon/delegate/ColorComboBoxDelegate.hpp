////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/delegate/Delegate.hpp>

namespace yq::gluon {

    /*! \brief Delegate for QItemModel that uses the ColorComboBox
    */
    class  ColorComboBoxDelegate : public Delegate {
        Q_OBJECT
        YQ_OBJECT_DECLARE(ColorComboBoxDelegate, Delegate)
    public:

        using DataType = QColor;

        //! Creates the editor
        virtual QWidget*    createEditor(QWidget* parent=nullptr) const;

        //! Sets the editor data
        virtual bool        setEditorData(QWidget*, const QVariant&) const;

        //! Gets the editor data
        virtual QVariant    getEditorData(const QWidget*) const;

        //! Paints the cell
        virtual bool        paint(QPainter*, const QStyleOptionViewItem& option, const QVariant&) const;

        //! Connect the "edited" signal
        virtual void        connectEditedSignal(QWidget*, QObject*, const char*) const;

        //! Constructor
        ColorComboBoxDelegate(QObject* parent=nullptr);
        
        //! Destructor
        virtual ~ColorComboBoxDelegate();
    };
}
