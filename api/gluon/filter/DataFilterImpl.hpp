////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "DataFilterMeta.hpp"

namespace data_filters {
    
    class AbstractDataFilterMeta : public DataFilterMeta {
    public:
      
        
    protected:
        AbstractDataFilterMeta(const QString&, int);
        
        void    verb(const QString&);
        void    cmd(const QString&);
        void    symbol(const QString&);
        void    arg(const QString&, int);
        void    description(const QString&);
    };
    
    template <typename Filter, typename T>
    class TypedDataFilterMeta : public AbstractDataFilterMeta {
    protected:
    
        TypedDataFilterMeta(const QString& className) : 
            AbstractDataFilterMeta(className, qMetaTypeId<T>())
        {
        }
    
        void    doInit();
      
        using AbstractDataFilterMeta::arg;
        void    arg(const QString& name)
        {
            AbstractDataFilterMeta::arg(name, qMetaTypeId<T>());
        }
    };
    
    template <typename Filter, typename T>
    class ConcreteNoArgDataFilter : public TypedDataFilterMeta<Filter, T> {
    private:
    
        ConcreteNoArgDataFilter(const QString& className) : 
            TypedDataFilterMeta<Filter, T>(className) {}
    
        DataFilter* createImpl(const Vector<QVariant>& ) const 
        {
            return new Filter;
        }
        
        void initialize()
        {
            TypedDataFilterMeta<Filter, T>::doInit();
        }
        
        static ConcreteNoArgDataFilter<Filter, T>*  s_reg;
    };
    
    template <typename Filter, typename T>
    class ConcreteSimpleArgDataFilter : public TypedDataFilterMeta<Filter, T> {
    private:
        ConcreteSimpleArgDataFilter(const QString& className) : 
            TypedDataFilterMeta<Filter, T>(className) {}

        DataFilter* createImpl(const Vector<QVariant>&vals ) const 
        {
            return new Filter(vals[0].value<T>());
        }
        void initialize()
        {
            TypedDataFilterMeta<Filter, T>::doInit();
            if(DataFilterMeta::args().size() < 1){
                TypedDataFilterMeta<Filter, T>::arg("value");
            }
        }
        static ConcreteSimpleArgDataFilter*  s_reg;
    };

    template <typename Filter, typename T, typename U>
    class ConcreteComplexArgDataFilter : public TypedDataFilterMeta<Filter, T> {
    private:
        ConcreteComplexArgDataFilter(const QString& className) : 
            TypedDataFilterMeta<Filter, T>(className) {}

        DataFilter* createImpl(const Vector<QVariant>&vals ) const 
        {
            return new Filter(vals[0].value<U>());
        }
        void initialize()
        {
            TypedDataFilterMeta<Filter, T>::doInit();
            if(DataFilterMeta::args().size() < 1){
                AbstractDataFilterMeta::arg("value", qMetaTypeId<U>());
            }
        }
        static ConcreteComplexArgDataFilter*  s_reg;
    };


    template <typename Filter, typename T>
    class ConcreteTwoArgDataFilter : public TypedDataFilterMeta<Filter, T> {
    private:
        ConcreteTwoArgDataFilter(const QString& className) : 
            TypedDataFilterMeta<Filter, T>(className) {}

        DataFilter* createImpl(const Vector<QVariant>&vals ) const 
        {
            return new Filter(vals[0].value<T>(), vals[1].value<T>());
        }
        void initialize()
        {
            TypedDataFilterMeta<Filter, T>::doInit();
            while(DataFilterMeta::args().size() < 2){
                TypedDataFilterMeta<Filter, T>::arg("value");
            }
        }
        static ConcreteTwoArgDataFilter*  s_reg;
    };
    
    #define DATA_FILTER(name, type, ...)    \
        template <> void TypedDataFilterMeta<name, type>::doInit() { __VA_ARGS__ }  \
        template <> ConcreteNoArgDataFilter<name, type>* \
            ConcreteNoArgDataFilter<name, type>::s_reg = \
                new ConcreteNoArgDataFilter<name, type>(#name);

    #define DATA_FILTER1(name, type, ...) \
        template <> void TypedDataFilterMeta<name, type>::doInit() { __VA_ARGS__ }  \
        template <> ConcreteSimpleArgDataFilter<name, type>* \
            ConcreteSimpleArgDataFilter<name, type>::s_reg = \
                new ConcreteSimpleArgDataFilter<name, type>(#name);

    #define DATA_FILTER1C(name, type, arg,  ...) \
        template <> void TypedDataFilterMeta<name, type>::doInit() { __VA_ARGS__ }  \
        template <> ConcreteComplexArgDataFilter<name, type, arg>* \
            ConcreteComplexArgDataFilter<name, type, arg>::s_reg = \
                new ConcreteComplexArgDataFilter<name, type, arg>(#name);

    #define DATA_FILTER2(name, type, ...) \
        template <> void TypedDataFilterMeta<name, type>::doInit() { __VA_ARGS__ }  \
        template <> ConcreteTwoArgDataFilter<name, type>* \
            ConcreteTwoArgDataFilter<name, type>::s_reg = \
                new ConcreteTwoArgDataFilter<name, type>(#name);
    
}
