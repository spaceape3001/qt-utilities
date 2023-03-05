////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/model/GridTickModel.hpp>
#include <qu/preamble.hpp>
#include <basic/Map.hpp>

namespace qu {
    /*! \brief Standard "grid" tick model
    
        This uses "tick-stops" to denote a virtual grid of stops.
    */
    class StandardGridTickModel : public GridTickModel {
        Q_OBJECT
    public:
        
        StandardGridTickModel(QObject* parent=nullptr);
        ~StandardGridTickModel();
        
        /*! TRUE if this index is a grid stop */
        virtual bool			        hasStop(int64_t) const override;
        virtual std::vector<int64_t>	stops  (int64_t from, int64_t to, uint64_t minPitch) const override;
        virtual uint64_t		        pitch  (int64_t) const override;
        virtual QString			        label  (int64_t) const override;
        virtual QColor			        color  (int64_t) const override;
        
        void	                        clearAllTicks();
        void	                        setTickToUnitPitchRatio(uint64_t);
        virtual double                  tickToUnitPitchRatio() const { return m_tickToUnitPitch; }
        void	                        setPositiveFormat(const QString&);
        void	                        setNegativeFormat(const QString&);
        
        void	                        addTick(uint64_t, const QColor&color=QColor("black"));
        
        uint64_t				        tickToUnitPitch() const { return m_tickToUnitPitch; }
        QString					        positiveFormat() const { return m_posFormat; }
        QString					        negativeFormat() const { return m_negFormat; }

    //signals:
    //	virtual void        modelChanged();
        
    private:
        Map<uint64_t, QColor>       m_ticks;
        QString					    m_posFormat;
        QString					    m_negFormat;
        uint64_t					m_tickToUnitPitch = 0;
    };

}
