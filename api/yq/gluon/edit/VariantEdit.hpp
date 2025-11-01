////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <QWidget>
#include "UndoBase.hpp"

class DateWidget;
class DateTimeWidget;
class DataTypeCombo;
class LineEdit;
class ColorCombo;
class CheckBox;

class VariantEdit : public QWidget, public UndoBase {
    Q_OBJECT
public:
    VariantEdit(QWidget* parent=nullptr);
    ~VariantEdit();
    
    QVariant        value() const;
    
public slots:
    void            setQtType(int);
    void            setValue(const QVariant&);
    void            showTypeSelector(bool);
    
private:
    DataTypeCombo*  m_type;
    int             m_qt;
    LineEdit*       m_string;
    DateWidget*     m_dateWidget;
    DateTimeWidget* m_dateTimeWidget;
    ColorCombo*     m_color;
    CheckBox*       m_boolean;
};
