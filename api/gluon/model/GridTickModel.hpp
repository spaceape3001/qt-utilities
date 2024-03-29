////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QObject>
#include <QColor>
#include <vector>
#include <gluon/core/RefQ.hpp>

namespace yq::gluon {

    /*!	\brief Single dimension grid and tick model 

        The grid/tick model runs on an underlying integer grid 
        (not floating point--that was too much trouble).   This is for 
        "grid units" to which there is no finer division.  However, 
        it is expected that tick/zoom factors will be massaged
        to produce a desired ranging/zooming effect.  (Ie.  "100%" isn't 
        100% for this grid, but maybe 1% so that way, a zoom in will 
        produce reasonable gridding down to some reaonsable resolution.)
    */
    class GridTickModel : public QObject, public RefQ {
        Q_OBJECT
    public:
        GridTickModel(QObject* parent=nullptr);
        virtual ~GridTickModel();
        
        /*! TRUE if this index is a grid stop */
        virtual bool				    hasStop(int64_t) const = 0;
        
        //! List of stops between points
        virtual std::vector<int64_t>    stops  (int64_t from, int64_t to, uint64_t minPitch) const = 0;
        
        //! Pitch (in units) of specified point... 
        virtual uint64_t		        pitch  (int64_t) const = 0;
        
        //! Label at specified point
        virtual QString				    label  (int64_t) const = 0;
        
        //! Color at specified point
        virtual QColor				    color  (int64_t) const = 0;
        
        //! Tick to unit ratio
        virtual double                  tickToUnitPitchRatio() const = 0;

    signals:
        void        modelChanged();
    };
}
