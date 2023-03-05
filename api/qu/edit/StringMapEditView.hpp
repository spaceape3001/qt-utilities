////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/edit/StringMapEdit.hpp>
#include <QTableView>

namespace qu {


    class StringMapEdit::View : public QTableView {
        Q_OBJECT
    public:
        View(Model*);
        ~View();
        
        std::vector<int>	selectedRows() const;
    };
}
