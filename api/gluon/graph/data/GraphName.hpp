////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graph/preamble.hpp>

namespace yq::gluon {
    class GraphName : public QObject {
        Q_OBJECT
    public:
        GraphName(QObject* parent=nullptr);
        GraphName(const g::TND&, QObject* parent=nullptr);
        ~GraphName();
        
        g::TND      get() const;
        void        saveTo(g::TND&) const;
        
        const QString&  name() const { return m_name; }
        const QString&  type() const { return m_type; }
        const QString&  description() const { return m_description; }
        const QString&  notes() const { return m_notes; }
        
        bool            isInfo() const { return m_options[g::Option::INFO]; }
        Flag<g::Option> options() const { return m_options; }
        
        Q_PROPERTY(QString name READ name WRITE setName)
        Q_PROPERTY(QString type READ type WRITE setType)
        Q_PROPERTY(QString description READ description WRITE setDescription)
        Q_PROPERTY(QString notes READ notes WRITE setNotes)
        Q_PROPERTY(bool info READ isInfo WRITE setInfoFlag)
        
        void            setOptions(Flag<g::Option>);
        
        bool            operator==(const GraphName&) const;
        
    public slots:
        void            setName(const QString&);
        void            setType(const QString&);
        void            setDescription(const QString&);
        void            setNotes(const QString&);
        void            setInfoFlag(bool);
        
    signals:
    
        void            nameChanged(const QString&);
        void            typeChanged(const QString&);
        void            descriptionChanged(const QString&);
        void            notesChanged(const QString&);
        void            infoFlagChanged(bool);
        void            pinsFlagChanged(bool);
        void            multiFlagChanged(bool);
    
    protected:
    
        void            setOption(g::Option, bool);
    
    private:
        QString         m_type;
        QString         m_name;
        QString         m_description;
        QString         m_notes;
        Flag<g::Option> m_options = {};
    
    };
}
