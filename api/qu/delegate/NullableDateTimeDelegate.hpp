////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/delegate/Delegate.hpp>

namespace qu {

    class NullableDateTimeDelegate : public Delegate {
        Q_OBJECT
    public:

        using DataType  = QDateTime;
        
        NullableDateTimeDelegate(QObject* parent=nullptr);
        virtual ~NullableDateTimeDelegate();
        
        virtual QVariant    render(const QVariant&) const override;
        virtual yq::Compare compare(const QVariant&, const QVariant&) const override; 
        virtual QWidget*    createEditor(QWidget* parent=nullptr) const override;
        virtual bool        setEditorData(QWidget*, const QVariant&) const override;
        virtual QVariant    getEditorData(const QWidget*) const override;
        virtual void        connectEditedSignal(QWidget*, QObject*, const char*) const override;
    };

}
