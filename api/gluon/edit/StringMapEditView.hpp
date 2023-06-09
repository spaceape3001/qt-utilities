////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/edit/StringMapEdit.hpp>
#include <QTableView>

namespace yq::gluon {


    class StringMapEdit::View : public QTableView {
        Q_OBJECT
    public:
        View(Model*);
        ~View();
        
        std::vector<int>	selectedRows() const;
    };
}
