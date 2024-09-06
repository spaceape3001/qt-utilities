////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/basic/BasicApp.hpp>
#include <QApplication>

namespace yq::gluon {

    /*! \brief Application class for the library
    
        This application class binds the Qt with the toolbox
    */
    class Application : public QApplication, public BasicApp {
        Q_OBJECT
    public:
    
        //! Current instance (may be NULL)
        static Application*     app();
    
        //! Constructor
        Application(int&, char**);
        
        //! Destructor
        ~Application();
        
    private:
        static Application* s_app;
    };
}

