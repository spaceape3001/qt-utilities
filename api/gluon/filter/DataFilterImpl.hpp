#pragma once

#include "DataFilterInfo.hpp"

namespace data_filters {
    
    class AbstractDataFilterInfo : public DataFilterInfo {
    public:
      
        
    protected:
        AbstractDataFilterInfo(const QString&, int);
        
        void    verb(const QString&);
        void    cmd(const QString&);
        void    symbol(const QString&);
        void    arg(const QString&, int);
        void    description(const QString&);
    };
    
    template <typename Filter, typename T>
    class TypedDataFilterInfo : public AbstractDataFilterInfo {
    protected:
    
        TypedDataFilterInfo(const QString& className) : 
            AbstractDataFilterInfo(className, qMetaTypeId<T>())
        {
        }
    
        void    doInit();
      
        using AbstractDataFilterInfo::arg;
        void    arg(const QString& name)
        {
            AbstractDataFilterInfo::arg(name, qMetaTypeId<T>());
        }
    };
    
    template <typename Filter, typename T>
    class ConcreteNoArgDataFilter : public TypedDataFilterInfo<Filter, T> {
    private:
    
        ConcreteNoArgDataFilter(const QString& className) : 
            TypedDataFilterInfo<Filter, T>(className) {}
    
        DataFilter* createImpl(const Vector<QVariant>& ) const 
        {
            return new Filter;
        }
        
        void initialize()
        {
            TypedDataFilterInfo<Filter, T>::doInit();
        }
        
        static ConcreteNoArgDataFilter<Filter, T>*  s_reg;
    };
    
    template <typename Filter, typename T>
    class ConcreteSimpleArgDataFilter : public TypedDataFilterInfo<Filter, T> {
    private:
        ConcreteSimpleArgDataFilter(const QString& className) : 
            TypedDataFilterInfo<Filter, T>(className) {}

        DataFilter* createImpl(const Vector<QVariant>&vals ) const 
        {
            return new Filter(vals[0].value<T>());
        }
        void initialize()
        {
            TypedDataFilterInfo<Filter, T>::doInit();
            if(DataFilterInfo::args().size() < 1){
                TypedDataFilterInfo<Filter, T>::arg("value");
            }
        }
        static ConcreteSimpleArgDataFilter*  s_reg;
    };

    template <typename Filter, typename T, typename U>
    class ConcreteComplexArgDataFilter : public TypedDataFilterInfo<Filter, T> {
    private:
        ConcreteComplexArgDataFilter(const QString& className) : 
            TypedDataFilterInfo<Filter, T>(className) {}

        DataFilter* createImpl(const Vector<QVariant>&vals ) const 
        {
            return new Filter(vals[0].value<U>());
        }
        void initialize()
        {
            TypedDataFilterInfo<Filter, T>::doInit();
            if(DataFilterInfo::args().size() < 1){
                AbstractDataFilterInfo::arg("value", qMetaTypeId<U>());
            }
        }
        static ConcreteComplexArgDataFilter*  s_reg;
    };


    template <typename Filter, typename T>
    class ConcreteTwoArgDataFilter : public TypedDataFilterInfo<Filter, T> {
    private:
        ConcreteTwoArgDataFilter(const QString& className) : 
            TypedDataFilterInfo<Filter, T>(className) {}

        DataFilter* createImpl(const Vector<QVariant>&vals ) const 
        {
            return new Filter(vals[0].value<T>(), vals[1].value<T>());
        }
        void initialize()
        {
            TypedDataFilterInfo<Filter, T>::doInit();
            while(DataFilterInfo::args().size() < 2){
                TypedDataFilterInfo<Filter, T>::arg("value");
            }
        }
        static ConcreteTwoArgDataFilter*  s_reg;
    };
    
    #define DATA_FILTER(name, type, ...)    \
        template <> void TypedDataFilterInfo<name, type>::doInit() { __VA_ARGS__ }  \
        template <> ConcreteNoArgDataFilter<name, type>* \
            ConcreteNoArgDataFilter<name, type>::s_reg = \
                new ConcreteNoArgDataFilter<name, type>(#name);

    #define DATA_FILTER1(name, type, ...) \
        template <> void TypedDataFilterInfo<name, type>::doInit() { __VA_ARGS__ }  \
        template <> ConcreteSimpleArgDataFilter<name, type>* \
            ConcreteSimpleArgDataFilter<name, type>::s_reg = \
                new ConcreteSimpleArgDataFilter<name, type>(#name);

    #define DATA_FILTER1C(name, type, arg,  ...) \
        template <> void TypedDataFilterInfo<name, type>::doInit() { __VA_ARGS__ }  \
        template <> ConcreteComplexArgDataFilter<name, type, arg>* \
            ConcreteComplexArgDataFilter<name, type, arg>::s_reg = \
                new ConcreteComplexArgDataFilter<name, type, arg>(#name);

    #define DATA_FILTER2(name, type, ...) \
        template <> void TypedDataFilterInfo<name, type>::doInit() { __VA_ARGS__ }  \
        template <> ConcreteTwoArgDataFilter<name, type>* \
            ConcreteTwoArgDataFilter<name, type>::s_reg = \
                new ConcreteTwoArgDataFilter<name, type>(#name);
    
}
