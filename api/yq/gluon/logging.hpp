////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef emit
    #fatal
#endif

#include <yq/gluon/core/Logging.hpp>
#include <yq/core/LogFilter.hpp>

#define gluonAlert                    yAlert("gluon")
#define gluonCritical                 yCritical("gluon")
#define gluonDebug                    yDebug("gluon")
#define gluonError                    yError("gluon")
#define gluonEmergency                yEmergency("gluon")
#define gluonFatal                    yFatal("gluon")
#define gluonInfo                     yInfo("gluon")
#define gluonNotice                   yNotice("gluon")
#define gluonWarning                  yWarning("gluon")

#define gluonFirstAlert(...)          yLogFirstAlert("gluon", __VA_ARGS__)
#define gluonFirstCritical(...)       yLogFirstCritical("gluon", __VA_ARGS__)
#define gluonFirstDebug(...)          yLogFirstDebug("gluon", __VA_ARGS__)
#define gluonFirstError(...)          yLogFirstError("gluon", __VA_ARGS__)
#define gluonFirstEmergency(...)      yLogFirstEmergency("gluon", __VA_ARGS__)
#define gluonFirstFatal(...)          yLogFirstFatal("gluon", __VA_ARGS__)
#define gluonFirstInfo(...)           yLogFirstInfo("gluon", __VA_ARGS__)
#define gluonFirstNotice(...)         yLogFirstNotice("gluon", __VA_ARGS__)
#define gluonFirstWarning(...)        yLogFirstWarning("gluon", __VA_ARGS__)

#define gluonOnceAlert                yLogOnceAlert("gluon")             
#define gluonOnceCritical             yLogOnceCritical("gluon")          
#define gluonOnceDebug                yLogOnceDebug("gluon")             
#define gluonOnceError                yLogOnceError("gluon")             
#define gluonOnceEmergency            yLogOnceEmergency("gluon")         
#define gluonOnceFatal                yLogOnceFatal("gluon")             
#define gluonOnceInfo                 yLogOnceInfo("gluon")              
#define gluonOnceNotice               yLogOnceNotice("gluon")            
#define gluonOnceWarning              yLogOnceWarning("gluon")           
