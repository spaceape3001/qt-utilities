////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <tbb/spin_rw_mutex.h>

#include "ColorComboBoxDelegate.ipp"
#include "ColorDelegate.ipp"
#include "Delegate.ipp"
#include "DirBoxDelegate.ipp"
#include "EnumComboBoxDelegate.ipp"
#include "FileBoxDelegate.ipp"
#include "IconBarDelegate.ipp"
#include "ImageDelegate.ipp"
#include "IntegerDelegate.ipp"
#include "NullableDateDelegate.ipp"
#include "NullableDateTimeDelegate.ipp"
#include "StringComboDelegate.ipp"
#include "StringDelegate.ipp"
#include "UIntegerDelegate.ipp"

#include "moc_ColorComboBoxDelegate.cpp"
#include "moc_ColorDelegate.cpp"
#include "moc_Delegate.cpp"
#include "moc_DirBoxDelegate.cpp"
#include "moc_EnumComboBoxDelegate.cpp"
#include "moc_FileBoxDelegate.cpp"
#include "moc_IconBarDelegate.cpp"
#include "moc_ImageDelegate.cpp"
#include "moc_IntegerDelegate.cpp"
#include "moc_NullableDateDelegate.cpp"
#include "moc_NullableDateTimeDelegate.cpp"
#include "moc_StringComboDelegate.cpp"
#include "moc_StringDelegate.cpp"
#include "moc_UIntegerDelegate.cpp"

#include <meta/Init.hpp>
#include "DelegateInfoWriter.hpp"


YQ_OBJECT_IMPLEMENT(yq::gluon::ColorComboBoxDelegate)
YQ_OBJECT_IMPLEMENT(yq::gluon::ColorDelegate)
YQ_OBJECT_IMPLEMENT(yq::gluon::Delegate)
YQ_OBJECT_IMPLEMENT(yq::gluon::DirBoxDelegate)
YQ_OBJECT_IMPLEMENT(yq::gluon::FileBoxDelegate)
YQ_OBJECT_IMPLEMENT(yq::gluon::GenericEnumComboBoxDelegate)
YQ_OBJECT_IMPLEMENT(yq::gluon::IconBarDelegate)
YQ_OBJECT_IMPLEMENT(yq::gluon::ImageDelegate)
YQ_OBJECT_IMPLEMENT(yq::gluon::IntegerDelegate)
YQ_OBJECT_IMPLEMENT(yq::gluon::NullableDateDelegate)
YQ_OBJECT_IMPLEMENT(yq::gluon::NullableDateTimeDelegate)
YQ_OBJECT_IMPLEMENT(yq::gluon::StringComboDelegate)
YQ_OBJECT_IMPLEMENT(yq::gluon::StringDelegate)
YQ_OBJECT_IMPLEMENT(yq::gluon::UIntegerDelegate)

namespace {
    void    reg_all()
    {
        using namespace yq;
        using namespace yq::gluon;
        
        writer<ColorComboBoxDelegate>().declare_type<QColor>();
        writer<ColorDelegate>();
        writer<DirBoxDelegate>();
        writer<FileBoxDelegate>();
        writer<GenericEnumComboBoxDelegate>();
        writer<IconBarDelegate>();
        writer<ImageDelegate>().declare_type<QImage>();
        writer<IntegerDelegate>().declare_type<int>();
        writer<NullableDateDelegate>().declare_type<QDate>();
        writer<NullableDateTimeDelegate>().declare_type<QDateTime>();
        writer<StringComboDelegate>();
        writer<StringDelegate>().declare_type<QString>();
        writer<UIntegerDelegate>().declare_type<unsigned int>();
    }
    YQ_INVOKE(reg_all();)
}


