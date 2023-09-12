////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QObject>
#include <map>

namespace yq::gluon {

    /*! \brief Signal Mapper that maps using a SIGNED int64 integer
    */
    class Int64SignalMapper : public QObject {
        Q_OBJECT
    public:
    
        //! Constructor
        Int64SignalMapper(QObject* parent=nullptr);
        
        //! Destructor
        virtual ~Int64SignalMapper ();

        //! Sets the mapping for a qobject
        void        setMapping(QObject*, int64_t);
        
        //! Removes the mapping for the qobject
        void        removeMappings(QObject*);

    signals:
        //! Emitted when triggered
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
