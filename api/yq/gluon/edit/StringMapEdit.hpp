////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/preamble.hpp>
#include <yq/gluon/undo/UndoBase.hpp>
#include <QWidget>

namespace yq::gluon {

    /*! \brief Edit for a string-string map
    */
    class StringMapEdit : public QWidget, public UndoBase {
        Q_OBJECT
    public:

        //! Validator function
        using Validator  = std::function<bool(const QString&)>;
        
        //! Constructor
        StringMapEdit(QWidget* parent=nullptr);
        
        //! Destructor
        ~StringMapEdit();
        
        //! Get the map
        QStringMap	get() const;
        
        //! Set the map
        void		set(const QStringMap&);
        
        class View;
        class Model;
        
        //! Get the model for this edit
        Model*		    model() { return m_model; }

        //! Get the model for this edit
        const Model* 	model() const { return m_model; }

        //! Get the view for this edit
        View*			view() { return m_view; }

        //! Get the view for this edit
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
