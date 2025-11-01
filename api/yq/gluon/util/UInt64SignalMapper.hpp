////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QObject>
#include <map>

namespace yq::gluon {
    /*! \brief Signal Mapper that maps using an UNSIGNED uint64 integer
    */
    class UInt64SignalMapper : public QObject {
        Q_OBJECT
    public:
        //! Constructor
        UInt64SignalMapper(QObject* parent=nullptr);
        
        //! Destructor
        virtual ~UInt64SignalMapper ();

        //! Sets the object's mapping
        void        setMapping(QObject*, uint64_t);
        
        //! Removes the object from the map
        void        removeMappings(QObject*);

    signals:
        //! Emitted when a mapped signal is triggered
        void        mapped(uint64_t);

    public slots:
        //! Used by the objects to connect their signals to this one
        void        map();

    private slots:
        void        remove();

    private:
        std::map<QObject*,uint64_t>    m_mapping;    

        UInt64SignalMapper(const UInt64SignalMapper&) = delete;
        UInt64SignalMapper(UInt64SignalMapper&&) = delete;
        UInt64SignalMapper& operator=(const UInt64SignalMapper&) = delete;
        UInt64SignalMapper& operator=(UInt64SignalMapper&&) = delete;
    };
}
