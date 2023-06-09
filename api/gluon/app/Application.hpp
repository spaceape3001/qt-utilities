////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/BasicApp.hpp>
#include <QApplication>

namespace yq::gluon {
    class Application : public QApplication, public BasicApp {
        Q_OBJECT
    public:
        static Application*     app();
    
        Application(int&, char**);
        ~Application();
        
    private:
        static Application* s_app;
    };
}

