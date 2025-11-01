////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/preamble.hpp>
#include <yq/gluon/core/IgCaseQ.hpp>
#include <yq/gluon/undo/UndoBase.hpp>
#include <yq/container/Map.hpp>
#include <QWidget>

namespace yq::gluon {

    class CheckBox;
    class FlowLayout;

    /*! \brief Set of checkboxes, arranged horizontall, but wrapped
    */
    class StringSetCheck : public QWidget, public UndoBase {
        Q_OBJECT
    public:
        
        /*! \brief Constructor */
        StringSetCheck(QWidget* parent=nullptr);
        
        //! \brief Destructor
        ~StringSetCheck();
        
        //! Sets the items to be checkable
        void                setItems(const QStringSet&);
        
        //! Sets items that are checked
        void                setChecked(const QStringSet&);
        
        //! Sets items to tristate (ie defaulted and can't be toggled)
        void                setFixed(const QStringSet&);
        
        //! Gets items that are checked
        //! \param[in] fIncFixed TRUE to include fixed items in the results
        QStringSet          checked(bool fIncFixed=false) const;

    public slots:
        //! Unchecks all items
        void                clear();
        //! Sets the readonly attribute on all checkboxes
        void                setReadOnly(bool);
        
    signals:
        //! Emitted when a checkbox is changed
        void                changed();
        
    private:
        FlowLayout*                         m_layout;
        Map<QString,CheckBox*,IgCaseQ>      m_checks;
    };
}
