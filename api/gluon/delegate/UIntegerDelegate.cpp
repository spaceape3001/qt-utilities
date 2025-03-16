////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <gluon/delegate/UIntegerDelegate.hpp>
#include <gluon/delegate/DelegateInfoWriter.hpp>
#include <gluon/edit/SpinBox.hpp>

namespace yq::gluon {

    UIntegerDelegate::UIntegerDelegate(QObject* parent) : Delegate(parent)
    {
        m_minValue  = 0;
        m_maxValue  = 999;
        m_step      = 1;
        m_zeroNull  = true;
    }

    UIntegerDelegate::~UIntegerDelegate()
    {
    }


    yq::Compare UIntegerDelegate::compare(const QVariant&va, const QVariant&vb) const 
    {
        return yq::compare(va.toUInt(), vb.toUInt());
    }

    QWidget*    UIntegerDelegate::createEditor(QWidget* parent) const
    {
        SpinBox*       sb  = new SpinBox(parent);
        sb->setRange((int) std::min(m_minValue, m_maxValue), (int) std::max(m_minValue, m_maxValue));
        sb->setSingleStep(m_step);
        return sb;
    }

    bool        UIntegerDelegate::setEditorData(QWidget*editor, const QVariant&val) const
    {
        static_cast<SpinBox*>(editor)->setValue( (int) val.toUInt());
        return true;
    }

    QVariant    UIntegerDelegate::getEditorData(const QWidget*editor) const
    {
        return (unsigned int) static_cast<const SpinBox*>(editor)->value();
    }

    void        UIntegerDelegate::connectEditedSignal(QWidget*editor, QObject*other, const char*slot) const
    {
        connect(editor, SIGNAL(valueChanged(int)), other, slot);
    }

    void        UIntegerDelegate::setMaxValue(unsigned int v)
    {
        m_maxValue      = v;
    }

    void        UIntegerDelegate::setMinValue(unsigned int v)
    {
        m_minValue      = v;
    }

    void        UIntegerDelegate::setStep(unsigned int v)
    {
        m_step          = v;
    }

    void        UIntegerDelegate::setZeroNull(bool f) 
    {
        m_zeroNull      = f;
    }


    QVariant    UIntegerDelegate::render(const QVariant&v) const 
    {
        if(m_zeroNull && v.toInt() == 0)
            return QVariant();
        return v;
    }

    void UIntegerDelegate::init_info()
    {
        auto w = writer<UIntegerDelegate>();
        w.description("Unsigned integer delegate");
        w.declare_type<unsigned int>();
    }
}

YQ_OBJECT_IMPLEMENT(yq::gluon::UIntegerDelegate)
#include "moc_UIntegerDelegate.cpp"
