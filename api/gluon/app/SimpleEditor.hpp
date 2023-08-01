////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "UndoMainWindow.hpp"
#include <gluon/core/FileName.hpp>
\
class QUndoStack;

namespace yq::gluon {

    /*! \brief Simple Editor
    
        This implements a simple main window as an edtor.
    */
    class SimpleEditor : public UndoMainWindow
    {
        Q_OBJECT
    public:

        //! Override to catch the "okay-to-close" 
        bool    okayToClose() override;
        
        //! Our filename, broken into bits
        const FileName&   file() const { return m_file; }

    public slots:
        //! New file
        void            cmdNew();
        
        //! Open file
        void            cmdOpen();
        
        //! Save the file
        void            cmdSave();
        
        //! Save the file to a new filename
        void            cmdSaveAs();
        
        //! Update the title bar
        virtual void    updateTitle();
        
    protected:
        //! Constructor, takes in an editor widget
        SimpleEditor(QWidget* editor);
        
        //! Destructor
        ~SimpleEditor();
        
        //! Our data type name
        virtual QString     ourData() const { return tr("Data"); }
        
        //! Our app name
        virtual QString     ourName() const { return tr("SimpleEditor"); }
        
        //! Our save type
        virtual QString     ourSaveType() const { return QString(); }
        
        
        //! New file (please override)
        virtual bool        newFile() { return false; }
        
        //! Open file (please override)
        virtual bool        openFile(const QString&) { return false; }
        
        //! Save file (please override)
        virtual bool        saveFile(const QString&) const { return false; }
        
        //  Override to alter open-file-dialog
        virtual QString     promptOpenFile();
        
        //  Override to alter save-file-dialog
        virtual QString     promptSaveFile();

    private:
        FileName  m_file;
    };

}
