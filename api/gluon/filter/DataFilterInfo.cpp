#include "DataFilterImpl.hpp"
#include "DataFilter.hpp"
#include "Map.hpp"

namespace {
    struct Repo {
        Vector<const DataFilterInfo*>           all;
        Map<QString,const DataFilterInfo*,IgCase>      byName;
        Map<int,Vector<const DataFilterInfo*>>  byType;
    };
    
    
    Repo& repo()
    {
        static Repo *s_repo = new Repo;
        return *s_repo;
    }
}

DataFilterInfo::DataFilterInfo(const QString&name, int dataType) : 
    m_name(name), m_dataType(dataType)
{
    m_command = m_verb = m_symbol = name;
    
    Repo&   _r  = repo();
    _r.all << this;
    _r.byName[name] = this;
    _r.byType[dataType] << this;
}

DataFilter::Ptr  DataFilterInfo::create(const Vector<QVariant>& args) const
{
    if(args.size() < m_args.size())
        return DataFilter::Ptr();
    for(size_t n=0;n<m_args.size(); ++n){
        if(!args[n].canConvert(m_args[n].dataType))
            return DataFilter::Ptr();
    }
    return createImpl(args);
}


Vector<const DataFilterInfo*>&   DataFilterInfo::all()
{
    return repo().all;
}

Vector<const DataFilterInfo*>    DataFilterInfo::lookupForType(int i)
{
    return repo().byType.get(i);
}

const DataFilterInfo*            DataFilterInfo::lookup(const QString&k)
{
    return repo().byName.get(k);
}


namespace data_filters {
    AbstractDataFilterInfo::AbstractDataFilterInfo(const QString&n, int t) :
        DataFilterInfo(n, t)
    {
    }
    
    void    AbstractDataFilterInfo::verb(const QString&v)
    {
        m_verb      = v;
    }
    
    void    AbstractDataFilterInfo::cmd(const QString&v)
    {
        m_command       = v;
    }
    
    void    AbstractDataFilterInfo::symbol(const QString&v)
    {
        m_symbol    = v;
    }
    
    void    AbstractDataFilterInfo::description(const QString&v)
    {
        m_description   = v;
    }

    void    AbstractDataFilterInfo::arg(const QString&n, int t)
    {
        Arg arg;
        arg.name    = n;
        arg.dataType    = t;
        m_args << arg;
    }
    
}

