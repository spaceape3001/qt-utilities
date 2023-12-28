#pragma once
#include <QVariant>
#include "Vector.hpp"
#include "DelayInit.hpp"
#include "DataFilter.hpp"

class DataFilter;

namespace data_filters {
    class AbstractDataFilterInfo;
}



class DataFilterInfo : public DelayInit {
public:

    static Vector<const DataFilterInfo*>&   all();
    static Vector<const DataFilterInfo*>    lookupForType(int);
    static const DataFilterInfo*            lookup(const QString&);
    
    struct Arg {
        QString name;
        int     dataType;
    };
    
    DataFilter::Ptr     create(const Vector<QVariant>& args=Vector<QVariant>()) const;

    const Vector<Arg>&  args() const { return m_args; }
    bool                needsArg() const { return !m_args.empty(); }
    int                 dataType() const { return m_dataType; }
    QString             description() const { return m_description; }
    
    //! Full name
    QString             name() const { return m_name; }
    
    //! A verb (for a qcombobox)
    QString             verb() const { return m_verb; }
    
    //! For parsing a URL query
    QString             cmd() const { return m_command; }
    QString             symbol() const { return m_symbol; }

protected:

    DataFilterInfo(const QString&, int);
    
    virtual const DataFilter* createImpl(const Vector<QVariant>& args) const = 0;

private:
    friend class data_filters::AbstractDataFilterInfo;

    Vector<Arg> m_args;
    QString     m_description;
    QString     m_name;
    QString     m_command;
    QString     m_verb;
    QString     m_symbol;
    int         m_dataType;
};

