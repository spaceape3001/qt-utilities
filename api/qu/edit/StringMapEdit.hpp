////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/preamble.hpp>
#include <qu/undo/UndoBase.hpp>
#include <QWidget>

namespace qu {

    /*! \brief Edit for a string-string map
    */
    class StringMapEdit : public QWidget, public UndoBase {
        Q_OBJECT
    public:

        using Validator  = std::function<bool(const QString&)>;
        
        StringMapEdit(QWidget* parent=nullptr);
        ~StringMapEdit();
        
        StringMap	get() const;
        void		set(const StringMap&);
        
        class View;
        class Model;
        
        Model*		    model() { return m_model; }
        const Model* 	model() const { return m_model; }
        View*			view() { return m_view; }
        const View* 	view() const { return m_view; }

    private slots:
    //	void		addRow();
        void		delRow();
    private:
        Model*	m_model;
        View*	m_view;
        
        struct Item;

        enum {
            ColKey	= 0,
            ColValue,
            MAX_COLS
        };
    };
}
