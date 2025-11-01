////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DataFilterImpl.hpp"
#include "DataFilter.hpp"
#include "Map.hpp"

namespace {
    struct Repo {
        Vector<const DataFilterMeta*>           all;
        Map<QString,const DataFilterMeta*,IgCase>      byName;
        Map<int,Vector<const DataFilterMeta*>>  byType;
    };
    
    
    Repo& repo()
    {
        static Repo *s_repo = new Repo;
        return *s_repo;
    }
}

DataFilterMeta::DataFilterMeta(const QString&name, int dataType) : 
    m_name(name), m_dataType(dataType)
{
    m_command = m_verb = m_symbol = name;
    
    Repo&   _r  = repo();
    _r.all << this;
    _r.byName[name] = this;
    _r.byType[dataType] << this;
}

DataFilter::Ptr  DataFilterMeta::create(const Vector<QVariant>& args) const
{
    if(args.size() < m_args.size())
        return DataFilter::Ptr();
    for(size_t n=0;n<m_args.size(); ++n){
        if(!args[n].canConvert(m_args[n].dataType))
            return DataFilter::Ptr();
    }
    return createImpl(args);
}


Vector<const DataFilterMeta*>&   DataFilterMeta::all()
{
    return repo().all;
}

Vector<const DataFilterMeta*>    DataFilterMeta::lookupForType(int i)
{
    return repo().byType.get(i);
}

const DataFilterMeta*            DataFilterMeta::lookup(const QString&k)
{
    return repo().byName.get(k);
}


namespace data_filters {
    AbstractDataFilterMeta::AbstractDataFilterMeta(const QString&n, int t) :
        DataFilterMeta(n, t)
    {
    }
    
    void    AbstractDataFilterMeta::verb(const QString&v)
    {
        m_verb      = v;
    }
    
    void    AbstractDataFilterMeta::cmd(const QString&v)
    {
        m_command       = v;
    }
    
    void    AbstractDataFilterMeta::symbol(const QString&v)
    {
        m_symbol    = v;
    }
    
    void    AbstractDataFilterMeta::description(const QString&v)
    {
        m_description   = v;
    }

    void    AbstractDataFilterMeta::arg(const QString&n, int t)
    {
        Arg arg;
        arg.name    = n;
        arg.dataType    = t;
        m_args << arg;
    }
    
}

