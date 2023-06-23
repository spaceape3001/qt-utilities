////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QObject>
#include <map>

namespace yq::gluon {
    class Int64SignalMapper : public QObject {
        Q_OBJECT
    public:
        Int64SignalMapper(QObject* parent=nullptr);
        virtual ~Int64SignalMapper ();

        void        setMapping(QObject*, int64_t);
        void        removeMappings(QObject*);

    signals:
        void        mapped(int64_t);

    private slots:
        void        map();
        void        remove();

    private:
        std::map<QObject*,int64_t>    m_mapping;    

        Int64SignalMapper(const Int64SignalMapper&) = delete;
        Int64SignalMapper(Int64SignalMapper&&) = delete;
        Int64SignalMapper& operator=(const Int64SignalMapper&) = delete;
        Int64SignalMapper& operator=(Int64SignalMapper&&) = delete;
    };
}
