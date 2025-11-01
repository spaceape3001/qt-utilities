////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/undo/UndoBase.hpp>
#include <QWidget>
#include <optional>

class QToolButton;

namespace yq::gluon {
    class LineEdit;

    /*! \brief File Edit
    
        This is a file edit that's shown as a line-edit with 
        a "..." button for browsing.  This allows for direct
        entry (or copy & paste) when known, or for usage of
        the standard file open dialog box.
    */
    class FileBox : public QWidget, public UndoBase {
        Q_OBJECT
    public:
    
        //! Constructor
        FileBox(QWidget*parent=nullptr);
        
        //! Destructor
        virtual ~FileBox();
        
        //! Sets the file
        void    setFile(const QString&);
        
        //! Gets the file
        QString file() const;
        
        //! Option in that it'll be blank if not valid
        void                        set(const std::optional<QString>&);
        
        //! Gets the data as "optional" false if empty
        std::optional<QString>      get() const;
        
        //! Sets the file filters (ie *.txt)
        void    setFilter(const QString&);
        
        //! Sets the title for the file dialog
        void    setTitle(const QString&);
        
        //  eventually, get UNDO working....
    public slots:
    
        //! Clears the field
        void        clear();
        
        //! Sets read-only flag
        void        setReadOnly(bool);
        
    signals:
        //! Emitted whenever the file changes
        void        fileChanged(const QString&);    
    private slots:
        void        browse();
    private:
        QString         m_title;
        QString         m_filter;
        LineEdit*       m_edit;
        QToolButton*    m_button;
    };

}
