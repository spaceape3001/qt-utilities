////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QWidget>
#include <optional>
#include <gluon/undo/UndoBase.hpp>

class QToolButton;

namespace yq::gluon {

    class LineEdit;
    
    /*! \brief Widget to edit directory 
    
        This is a widget to edit a directory path.  A "..." box is 
        added that'll allow for browsing.
    */
    
    class DirBox : public QWidget, public UndoBase {
        Q_OBJECT
    public:
    
        //! Constructor
        DirBox(QWidget*parent=nullptr);
        
        //! Destructor
        virtual ~DirBox();
        
        //! Sets the directory
        void                        set(const std::optional<QString>&);
        
        //! Gets the directory
        std::optional<QString>      get() const;

        //! Sets the directory path to start
        void    setDirPath(const QString&);
        
        //! Gets the directory path
        QString dirPath() const;
        
        //! Sets the title
        void    setTitle(const QString&);
        
        //  eventually, get UNDO working....
    public slots:
        //! Clears the current directory
        void        clear();
        
        //! Sets the read only flag
        void        setReadOnly(bool);
    signals:
    
        //! Signal for when the directory path is changed
        void        dirPathChanged(const QString&);    
    private slots:
        void        browse();
    private:
        QString         m_title;
        LineEdit*       m_edit;
        QToolButton*    m_button;
    };

}
