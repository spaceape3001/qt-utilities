////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QString>

namespace yq::gluon {

    /*! \brief FileName
    
        This is a filename object, that breaks it down into parts.
    */
    class FileName {
    public:

        //! Default constructor (empty)
        FileName();
        
        //! Creates filename from string
        FileName(const QString&);
        
        //! Copy Constructor
        FileName(const FileName&);
        
        //! Move Constructor
        FileName(FileName&&);
        
        //! Destructor
        ~FileName();
        
        //! Copy operator
        FileName&           operator=(const FileName&);
        
        //! Move operator
        FileName&           operator=(FileName&&);
        
        //! Assignment (from string)
        FileName&           operator=(const QString&);
        
        //! Full filename
        const QString&      full() const { return m_full; }
        
        //! Name of the file
        const QString&      name() const { return m_name; }
        
        //! Path bit
        const QString&      path() const { return m_path; }
        
        //! TRUE if the filename is empty
        bool                isEmpty() const { return m_full.isEmpty(); }
        
        //! Clears the filename
        void                clear();
        
    private:
        void    _set(const QString&);
        QString m_full, m_name, m_path;
    };
}
