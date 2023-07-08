////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graph/GraphBase.hpp>

namespace yq::gluon {
    class GraphPin : public GraphBase {
        Q_OBJECT
    public:
        GraphPin(QObject*parent=nullptr);
        GraphPin(const g::Pin&, QObject*parent=nullptr);
        ~GraphPin();
    
        bool    operator==(const GraphPin&) const;
    
        g::Pin  get() const;
        void    saveTo(g::Pin&) const;

        g::Flow         flow() const { return m_flow; }
        unsigned        countMin() const { return m_count.min; }
        unsigned        countMax() const { return m_count.max; }
        unsigned        countDef() const { return m_count.def; }
        
        bool            isMulti() const { return options()[g::Option::MULTI]; }
        
        Q_PROPERTY(unsigned countMin READ countMin WRITE setCountMin )
        Q_PROPERTY(unsigned countMax READ countMax WRITE setCountMax )
        Q_PROPERTY(unsigned countDef READ countDef WRITE setCountDef )
        
    public slots:
    
        void    setFlow(g::Flow);
        void    setCountMin(unsigned);
        void    setCountMax(unsigned);
        void    setCountDef(unsigned);
        void    setMultiFlag(bool);

    
    signals:

        void    flowChanged(g::Flow);
        void    countMinChanged(unsigned);
        void    countMaxChanged(unsigned);
        void    countDefChanged(unsigned);
        
    private:
        g::Flow                 m_flow;
        MinMaxDef<unsigned>     m_count = {};
    
    };
}
