////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/graph/Graph.hpp>
#include <gluon/graph/data/GraphName.hpp>
#include <QVariant>

namespace yq::gluon {
    class GraphProperty : public GraphName {
        Q_OBJECT
    public:
    
        GraphProperty(GraphBase*parent=nullptr);
        GraphProperty(const g::Property&, GraphBase*parent=nullptr);
        ~GraphProperty();

        bool    operator==(const GraphProperty&) const;
        
        g::Property get() const;
        void        saveTo(g::Property&) const;
        
        const QVariant& value() const { return m_value; }
        unsigned        countMin() const { return m_count.min; }
        unsigned        countMax() const { return m_count.max; }
        unsigned        countDef() const { return m_count.def; }
        
        bool            isMulti() const { return options()[g::Option::MULTI]; }
        
        Q_PROPERTY(QVariant value READ value WRITE setValue )
        Q_PROPERTY(unsigned countMin READ countMin WRITE setCountMin )
        Q_PROPERTY(unsigned countMax READ countMax WRITE setCountMax )
        Q_PROPERTY(unsigned countDef READ countDef WRITE setCountDef )
        
    public slots:
        void    setValue(const QVariant&);
        void    setCountMin(unsigned);
        void    setCountMax(unsigned);
        void    setCountDef(unsigned);
        void    setMultiFlag(bool);
    
    signals:
        void    valueChanged(const QVariant&);
        void    countMinChanged(unsigned);
        void    countMaxChanged(unsigned);
        void    countDefChanged(unsigned);
        
    private:
        QVariant            m_value;
        MinMaxDef<unsigned> m_count = {};
        
    };
}

