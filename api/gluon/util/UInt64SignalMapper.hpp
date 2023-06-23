////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QObject>
#include <map>

namespace yq::gluon {
    class UInt64SignalMapper : public QObject {
        Q_OBJECT
    public:
        UInt64SignalMapper(QObject* parent=nullptr);
        virtual ~UInt64SignalMapper ();

        void        setMapping(QObject*, uint64_t);
        void        removeMappings(QObject*);

    signals:
        void        mapped(uint64_t);

    private slots:
        void        map();
        void        remove();

    private:
        std::map<QObject*,uint64_t>    m_mapping;    

        UInt64SignalMapper(const UInt64SignalMapper&) = delete;
        UInt64SignalMapper(UInt64SignalMapper&&) = delete;
        UInt64SignalMapper& operator=(const UInt64SignalMapper&) = delete;
        UInt64SignalMapper& operator=(UInt64SignalMapper&&) = delete;
    };
}
