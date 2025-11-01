////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/edit/StringMapEdit.hpp>
#include <QTableView>

namespace yq::gluon {

    //! View for the string map edit
    class StringMapEdit::View : public QTableView {
        Q_OBJECT
    public:
        //! Constructor 
        View(Model*);
        
        //! Destructor
        ~View();
        
        //! Returns the currently selected rows
        std::vector<int>	selectedRows() const;
    };
}
