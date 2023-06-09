////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <atomic>
#include <gluon/preamble.hpp>
#include <basic/Ref.hpp>

namespace yq::gluon {

    /*! \brief Basic Reference Counted class
    */
    class RefQ {
    public:
    
        //! Tests for uniqueness
        bool	unique() const 
        {
            return m_count <= 1;
        }

        //! Current ref count
        //! \note For debug info only, subject to change
        size_t	count() const 
        {
            return m_count;
        }
        
        /*! \brief Cause a memory leak
        
            This VIOLATES the pairity, ensuring that proper functions will never
            release the memory.  (Are you sure this is what you want to do?)
        */
        void    leak() { incRef(); }

    protected:

        RefQ();
        RefQ(const RefQ& copy);
        virtual ~RefQ(){}
        
        RefQ& operator=(const RefQ&) = delete;
        
        template <typename T>  friend class yq::Ref;

            //! TREAD LIGHTLY!  Increments the reference count (can lead to orphaned memory)
        void	incRef() const;
            //! TREAD LIGHTLY!  Decrements the reference count (can lead to dangling pointers)
        void	decRef() const;

    private:
        mutable std::atomic<size_t>  m_count;
    };
}

