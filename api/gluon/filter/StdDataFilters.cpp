#include "StdDataFilters.hpp"
#include "DataFilterImpl.hpp"
#include "Utilities.hpp"

namespace data_filters {
    

    bool    IsFalse::accept(const QVariant&v) const
    {
        return v.toBool();
    }
    
    DATA_FILTER(IsFalse, bool,
        description("Checks for a boolean that is false.");
        symbol("!");
        cmd("false");
        verb("False");
    )

    bool    IsTrue::accept(const QVariant&v) const
    {
        return !v.toBool();
    }
    
    DATA_FILTER(IsTrue, bool,
        description("Checks for a boolean that is true.");
        symbol("!!");
        cmd("true");
        verb("True");
    )

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    DataFilter::Ptr     DataLogicFilter::leftAnd(const Ptr rhs) const
    {
        return new And({Ptr(this), Ptr(rhs)});
    }
    
    DataFilter::Ptr     DataLogicFilter::leftAnd(const DataLogicFilter*rhs) const
    {
        return new And({Ptr(this), Ptr(rhs)});
    }
    
    DataFilter::Ptr     DataLogicFilter::leftOr(const Ptr rhs) const
    {
        return new Or({Ptr(this), Ptr(rhs)});
    }
    
    DataFilter::Ptr     DataLogicFilter::leftOr(const DataLogicFilter*rhs) const
    {
        return new Or({Ptr(this), Ptr(rhs)});
    }
    
    DataFilter::Ptr     DataLogicFilter::rightAnd(const Ptr lhs) const
    {
        return new And({lhs, Ptr(this)});
    }
    
    DataFilter::Ptr     DataLogicFilter::rightOr(const Ptr lhs) const
    {
        return new Or({lhs, Ptr(this)});
    }
    
    DataFilter::Ptr     DataLogicFilter::invert() const
    {
        return new Not(this);
    }

    bool False::accept(const QVariant&) const
    {
        return false;
    }
    
    bool True::accept(const QVariant&) const
    {
        return true;
    }
    
    And::And(const std::initializer_list<Ptr>&them) : 
        m_filters(them.begin(), them.end())
    {
        assert(m_filters.size() >= 2);
        for(auto filterPtr : them){
            assert(filterPtr.valid());
        }
    }
    
    And::And(const Vector<Ptr>&them) : m_filters(them)
    {
        assert(m_filters.size() >= 2);
        for(auto filterPtr : them){
            assert(filterPtr.valid());
        }
    }

    And::~And()
    {
    }

    bool And::accept(const QVariant&v) const
    {
        for(auto & f : m_filters)
            if(!f->accept(v))
                return false;
        return true;
    }

    Nand::Nand(const std::initializer_list<Ptr>&them) : 
        m_filters(them.begin(), them.end())
    {
        assert(m_filters.size() >= 2);
        for(auto filterPtr : them){
            assert(filterPtr.valid());
        }
    }
    
    Nand::Nand(const Vector<Ptr>&them) : m_filters(them)
    {
        assert(m_filters.size() >= 2);
        for(auto filterPtr : them){
            assert(filterPtr.valid());
        }
    }

    Nand::~Nand()
    {
    }

    bool Nand::accept(const QVariant&v) const
    {
        for(auto& f : m_filters)
            if(!f->accept(v))
                return true;
        return false;
    }

    Nor::Nor(const std::initializer_list<Ptr>&them) : 
        m_filters(them.begin(), them.end())
    {
        assert(m_filters.size() >= 2);
        for(auto filterPtr : them){
            assert(filterPtr.valid());
        }
    }
    
    Nor::Nor(const Vector<Ptr>&them) : m_filters(them)
    {
        assert(m_filters.size() >= 2);
        for(auto filterPtr : them){
            assert(filterPtr.valid());
        }
    }

    Nor::~Nor()
    {
    }

    bool Nor::accept(const QVariant&v) const
    {
        for(auto &f  : m_filters)
            if(f->accept(v))
                return false;
        return true;
    }

    Not::Not(Ptr a) : m_a(a)
    {
        assert(a.valid());
    }

    bool Not::accept(const QVariant&v) const
    {
        return !m_a->accept(v);
    }

    Or::Or(const std::initializer_list<Ptr>&them) : 
        m_filters(them.begin(), them.end())
    {
        assert(m_filters.size() >= 2);
        for(auto filterPtr : them){
            assert(filterPtr.valid());
        }
    }
    
    Or::Or(const Vector<Ptr>&them) : m_filters(them)
    {
        assert(m_filters.size() >= 2);
        for(auto filterPtr : them){
            assert(filterPtr.valid());
        }
    }
    
    Or::~Or()
    {
    }

    bool Or::accept(const QVariant&v) const
    {
        for(auto& f : m_filters)
            if(f->accept(v))
                return true;
        return false;
    }

    Xnor::Xnor(Ptr a, Ptr b) : m_a(a), m_b(b)
    {
        assert(a.valid() && b.valid());
    }

    bool Xnor::accept(const QVariant&v) const
    {
        return m_a->accept(v) == m_b->accept(v);
    }

    Xor::Xor(Ptr a, Ptr b) : m_a(a), m_b(b)
    {
        assert(a.valid() && b.valid());
    }

    bool Xor::accept(const QVariant&v) const
    {
        if(m_a->accept(v))
            return !m_b->accept(v);
        else
            return m_b->accept(v);
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    bool DateEqual::accept(const QVariant&v) const
    {
        return v.toDate() == m_value;
    }

    DATA_FILTER1(DateEqual, QDate,
        description("Checks for a date that is equal.");
        symbol("=");
        verb("Equal");
        cmd("equ");
    )

    bool DateGreater::accept(const QVariant&v) const
    {
        return v.toDate() > m_value;
    }

    DATA_FILTER1(DateGreater, QDate,
        description("Checks for a date that is greater.");
        symbol(">");
        verb("Greater");
        cmd("gt");
    )

    bool DateGreaterOrEqual::accept(const QVariant&v) const
    {
        return v.toDate() >= m_value;
    }

    DATA_FILTER1(DateGreaterOrEqual, QDate,
        description("Checks for a date that is greater or equal.");
        symbol(">="); // "\u2265"
        verb("Above");
        cmd("gq");
    )

    bool DateLesser::accept(const QVariant&v) const
    {
        return v.toDate() < m_value;
    }
    
    DATA_FILTER1(DateLesser, QDate,
        description("Checks for a date that is lesser.");
        symbol("<");
        verb("Lesser");
        cmd("lt");
    )

    bool DateLesserOrEqual::accept(const QVariant&v) const
    {
        return v.toDate() <= m_value;
    }

    DATA_FILTER1(DateLesserOrEqual, QDate,
        description("Checks for a date that is lesser or equal.");
        symbol("<=");
        verb("Below");
        cmd("lq");
    )

    bool DateNotEqual::accept(const QVariant&v) const
    {
        return v.toDate() != m_value;
    }

    DATA_FILTER1(DateNotEqual, QDate,
        description("Checks for a date that is greater or equal.");
        symbol("!=");
        verb("NotEqual");
        cmd("neq");
    )

    bool DateNull::accept(const QVariant&v) const
    {
        return v.toDate().isNull();
    }

    DATA_FILTER(DateNull, QDate,
        description("Checks for a date that is null.");
        symbol("!");
        verb("NotExist");
        cmd("nx");
    )
    
    bool DateValid::accept(const QVariant&v) const
    {
        return v.toDate().isValid();
    }

    DATA_FILTER(DateValid, QDate,
        description("Checks for a date that is valid.");
        symbol("?");
        verb("Exist");
        cmd("valid");
    )

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    bool DateTimeEqual::accept(const QVariant&v) const
    {
        return v.toDateTime() == m_value;
    }

    DATA_FILTER1(DateTimeEqual, QDateTime,
        description("Checks for a date time that is equal.");
        symbol("=");
        verb("Equal");
        cmd("equ");
    )
    
    bool DateTimeGreater::accept(const QVariant&v) const
    {
        return v.toDateTime() > m_value;
    }

    DATA_FILTER1(DateTimeGreater, QDateTime,
        description("Checks for a date time that is greater.");
        symbol(">");
        verb("Greater");
        cmd("gt");
    )

    bool DateTimeGreaterOrEqual::accept(const QVariant&v) const
    {
        return v.toDateTime() >= m_value;
    }

    DATA_FILTER1(DateTimeGreaterOrEqual, QDateTime,
        description("Checks for a date time that is greater or equal.");
        symbol(">=");
        verb("Above");
        cmd("gq");
    )

    bool DateTimeLesser::accept(const QVariant&v) const
    {
        return v.toDateTime() < m_value;
    }

    DATA_FILTER1(DateTimeLesser, QDateTime,
        description("Checks for a date time that is lesser.");
        symbol("<");
        verb("Lesser");
        cmd("lt");
    )
    
    bool DateTimeLesserOrEqual::accept(const QVariant&v) const
    {
        return v.toDateTime() <= m_value;
    }

    DATA_FILTER1(DateTimeLesserOrEqual, QDateTime,
        description("Checks for a date time that is lesser or equal.");
        symbol("<=");
        verb("Below");
        cmd("lq");
    )
    
    bool DateTimeNotEqual::accept(const QVariant&v) const
    {
        return v.toDateTime() != m_value;
    }

    DATA_FILTER1(DateTimeNotEqual, QDateTime,
        description("Checks for a date time that not  equal.");
        symbol("!=");
        verb("NotEqual");
        cmd("neq");
    )
    

    bool DateTimeNull::accept(const QVariant&v) const
    {
        return v.toDate().isNull();
    }

    DATA_FILTER(DateTimeNull, QDateTime,
        description("Checks for a date time that is null.");
        symbol("!");
        verb("NotExist");
        cmd("nx");
    )
    
    bool DateTimeValid::accept(const QVariant&v) const
    {
        return v.toDate().isValid();
    }

    DATA_FILTER(DateTimeValid, QDateTime,
        description("Checks for a date time that is valid.");
        symbol("?");
        verb("Exist");
        cmd("ex");
    )

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    bool DoubleEqual::accept(const QVariant&v) const
    {
        return v.toDouble() == m_value;
    }

    DATA_FILTER1(DoubleEqual, double,
        description("Checks for a number that is equal.");
        symbol("=");
        verb("Equal");
        cmd("equ");
    )
    
    bool DoubleEqualWithin::accept(const QVariant&v) const
    {
        return fabs(v.toDouble() - m_value) <= m_epsilon;
    }

    DATA_FILTER2(DoubleEqualWithin, double,
        description("Checks for a number that is equal (within tolerance).");
        symbol("?=");
        verb("Within");
        cmd("wq");
        arg("value");
        arg("epsilon");
    )
    
    bool DoubleGreater::accept(const QVariant&v) const
    {
        return v.toDouble() > m_value;
    }
    
    DATA_FILTER1(DoubleGreater, double,
        description("Checks for a number that is greater.");
        symbol(">");
        verb("Greater");
        cmd("gt");
    )

    bool DoubleGreaterOrEqual::accept(const QVariant&v) const
    {
        return v.toDouble() >= m_value;
    }
    
    DATA_FILTER1(DoubleGreaterOrEqual, double,
        description("Checks for a number that is greater or equal.");
        symbol(">=");
        verb("Above");
        cmd("gq");
    )


    bool DoubleLesser::accept(const QVariant&v) const
    {
        return v.toDouble() < m_value;
    }

    DATA_FILTER1(DoubleLesser, double,
        description("Checks for a number that is lesser.");
        symbol("<");
        verb("Lesser");
        cmd("lt");
    )

    bool DoubleLesserOrEqual::accept(const QVariant&v) const
    {
        return v.toDouble() <= m_value;
    }

    DATA_FILTER1(DoubleLesserOrEqual, double,
        description("Checks for a number that is lesser or equal.");
        symbol("<=");
        verb("Below");
        cmd("lq");
    )

    bool DoubleNotEqual::accept(const QVariant&v) const
    {
        return v.toDouble() != m_value;
    }
    
    DATA_FILTER1(DoubleNotEqual, double,
        description("Checks for a number that is not equal.");
        symbol("=");
        verb("NotEqual");
        cmd("neq");
    )

    bool DoubleNotEqualWithin::accept(const QVariant&v) const
    {
        return fabs(v.toDouble() - m_value) > m_epsilon;
    }
    
    DATA_FILTER2(DoubleNotEqualWithin, double,
        description("Checks for a number that is not equal (within tolerance).");
        symbol("!?=");
        verb("Within");
        cmd("nw");
        arg("value");
        arg("epsilon");
    )

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    bool IntegerEqual::accept(const QVariant&v) const
    {
        return v.toInt() == m_value;
    }

    DATA_FILTER1(IntegerEqual, int,
        description("Checks for an integer that is equal.");
        symbol("=");
        verb("Equal");
        cmd("equ");
    )
    
    bool IntegerGreater::accept(const QVariant&v) const
    {
        return v.toInt() > m_value;
    }

    DATA_FILTER1(IntegerGreater, int,
        description("Checks for an integer that is greater.");
        symbol(">");
        verb("Greater");
        cmd("gt");
    )

    bool IntegerGreaterOrEqual::accept(const QVariant&v) const
    {
        return v.toInt() >= m_value;
    }

    DATA_FILTER1(IntegerGreaterOrEqual, int,
        description("Checks for an integer that is greater or equal.");
        symbol(">=");
        verb("Above");
        cmd("gq");
    )

    
    bool IntegerLesser::accept(const QVariant&v) const
    {
        return v.toInt() < m_value;
    }

    DATA_FILTER1(IntegerLesser, int,
        description("Checks for an integer that is lesser.");
        symbol("<");
        verb("Lesser");
        cmd("lt");
    )

    bool IntegerLesserOrEqual::accept(const QVariant&v) const
    {
        return v.toInt() <= m_value;
    }

    DATA_FILTER1(IntegerLesserOrEqual, int,
        description("Checks for an integer that is lesser or equal.");
        symbol("<=");
        verb("Below");
        cmd("lq");
    )

    bool IntegerNotEqual::accept(const QVariant&v) const
    {
        return v.toInt() != m_value;
    }

    DATA_FILTER1(IntegerNotEqual, int,
        description("Checks for an integer that is not equal.");
        symbol("!=");
        verb("NotEqual");
        cmd("neq");
    )
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    bool StringContains::accept(const QVariant&v) const
    {
        return v.toString().contains(m_value, Qt::CaseInsensitive);
    }

    DATA_FILTER1(StringContains, QString,
        description("Checks for a string that contains value.");
        symbol("[]");
        verb("Contains");
        cmd("in");
    )

    bool StringEmpty::accept(const QVariant&v) const
    {
        return v.toString().isEmpty();
    }

    DATA_FILTER(StringEmpty, QString,
        description("Checks for a string that is empty.");
        verb("NotExist");
        cmd("nx");
        symbol("!");
    )

    bool StringEqual::accept(const QVariant&v) const
    {
        return v.toString().compare(m_value, Qt::CaseInsensitive) == 0;
    }
    
    DATA_FILTER1(StringEqual, QString,
        description("Checks for a string is the same.");
        symbol("=");
        verb("Equal");
        cmd("equ");
    )

    bool StringGreater::accept(const QVariant&v) const
    {
        return v.toString().toLower().localeAwareCompare(m_value) > 0;
    }

    DATA_FILTER1(StringGreater, QString,
        description("Checks for a string is greater.");
        symbol(">");
        verb("Greater");
        cmd("gt");
    )

    bool StringGreaterEqual::accept(const QVariant&v) const
    {
        return v.toString().toLower().localeAwareCompare(m_value) >= 0;
    }

    DATA_FILTER1(StringGreaterEqual, QString,
        description("Checks for a string is greater or equal.");
        symbol(">=");
        verb("Above");
        cmd("gq");
    )

    bool StringLesser::accept(const QVariant&v) const
    {
        return v.toString().toLower().localeAwareCompare(m_value) < 0;
    }

    DATA_FILTER1(StringLesser, QString,
        description("Checks for a string is lesser.");
        symbol("<");
        verb("Lesser");
        cmd("lt");
    )

    bool StringLesserEqual::accept(const QVariant&v) const
    {
        return v.toString().toLower().localeAwareCompare(m_value) <= 0;
    }

    DATA_FILTER1(StringLesserEqual, QString,
        description("Checks for a string is lesser or equal.");
        symbol("<=");
        verb("Below");
        cmd("lq");
    )

    bool StringNotContains::accept(const QVariant&v) const
    {
        return !v.toString().contains(m_value, Qt::CaseInsensitive);
    }

    DATA_FILTER1(StringNotContains, QString,
        description("Checks for a string that does not contains value.");
        symbol("![]");
        verb("NotContains");
        cmd("ni");
    )

    bool StringNotEmpty::accept(const QVariant&v) const
    {
        return !v.toString().isEmpty();
    }

    DATA_FILTER(StringNotEmpty, QString,
        description("Checks for a string that is not empty.");
        verb("Exist");
        cmd("ex");
        symbol("?");
    )

    bool StringNotEqual::accept(const QVariant&v) const
    {
        return v.toString().compare(m_value, Qt::CaseInsensitive)  != 0;
    }

    DATA_FILTER1(StringNotEqual, QString,
        description("Checks for a string is not the same.");
        symbol("!=");
        verb("NotEqual");
        cmd("neq");
    )
    
    bool StringRegex::accept(const QVariant&v) const
    {
        return m_regex.match(v.toString()).hasMatch();
    }

    DATA_FILTER1(StringRegex, QString,
        description("Checks for a string using regex.");
        symbol("[?]");
        verb("Regex");
        cmd("rg");
    )

    bool StringStarts::accept(const QVariant&v) const 
    {
        return v.toString().startsWith(m_value, Qt::CaseInsensitive);
    }
    DATA_FILTER1(StringStarts, QString,
        description("Checks for a string that starts with value.");
        symbol("?{}");
        verb("Starts");
        cmd("rs");
    )


    StringWildcard::StringWildcard(const QString& pat) :
        StringRegex(wildcardToRegex(pat)) 
    {
    }
    
    DATA_FILTER1(StringWildcard, QString,
        description("Checks for a string using wildcard.");
        symbol("{?}");
        verb("Wildcard");
        cmd("rw");
    )

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    bool StringListContains::accept(const QVariant&var) const
    {
        return var.value<QStringList>().contains(m_value, Qt::CaseInsensitive);
    }
    
    DATA_FILTER1C(StringContains, QStringList, QString,
        description("Checks for a string list that contains value.");
        symbol("[]");
        verb("Contains");
        cmd("in");
    )

    bool StringListEmpty::accept(const QVariant&var) const 
    {
        return var.value<QStringList>().isEmpty();
    }

    DATA_FILTER(StringListEmpty, QStringList,
        description("Checks for a string list that is empty.");
        verb("NotExist");
        cmd("nx");
        symbol("!");
    )
    
    bool StringListNotContains::accept(const QVariant&var) const
    {
        return !var.value<QStringList>().contains(m_value, Qt::CaseInsensitive);
    }
    
    DATA_FILTER1C(StringListNotContains, QStringList, QString,
        description("Checks for a string list that contains value.");
        symbol("![]");
        verb("NotContains");
        cmd("ni");
    )

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    bool TimeEqual::accept(const QVariant&v) const
    {
        return v.toTime() == m_value;
    }
    
    DATA_FILTER1(TimeEqual, QTime,
        description("Checks for a time that is equal.");
        symbol("=");
        verb("Equal");
        cmd("equ");
    )

    bool TimeGreater::accept(const QVariant&v) const
    {
        return v.toTime() > m_value;
    }

    DATA_FILTER1(TimeGreater, QTime,
        description("Checks for a time that is greater.");
        symbol(">");
        verb("Greater");
        cmd("gt");
    )

    bool TimeGreaterOrEqual::accept(const QVariant&v) const
    {
        return v.toTime() >= m_value;
    }
    
    DATA_FILTER1(TimeGreaterOrEqual, QTime,
        description("Checks for a time that is greater or equal.");
        symbol(">=");
        verb("Above");
        cmd("gq");
    )

    bool TimeLesser::accept(const QVariant&v) const
    {
        return v.toTime() < m_value;
    }

    DATA_FILTER1(TimeLesser, QTime,
        description("Checks for a time that is lesser.");
        symbol("<");
        verb("Lesser");
        cmd("lt");
    )

    bool TimeLesserOrEqual::accept(const QVariant&v) const
    {
        return v.toTime() <= m_value;
    }

    DATA_FILTER1(TimeLesserOrEqual, QTime,
        description("Checks for a time that is lesser or equal.");
        symbol("<=");
        verb("Below");
        cmd("lq");
    )


    bool TimeNotEqual::accept(const QVariant&v) const
    {
        return v.toTime() != m_value;
    }

    DATA_FILTER1(TimeNotEqual, QTime,
        description("Checks for a time that is not equal.");
        symbol("!=");
        verb("NotEqual");
        cmd("neq");
    )

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    bool UnsignedIntegerEqual::accept(const QVariant&v) const
    {
        return v.toUInt() == m_value;
    }

    DATA_FILTER1(UnsignedIntegerEqual, unsigned int,
        description("Checks for an unsigned integer that is equal.");
        symbol("=");
        verb("Equal");
        cmd("equ");
    )
    
    bool UnsignedIntegerGreater::accept(const QVariant&v) const
    {
        return v.toUInt() > m_value;
    }

    DATA_FILTER1(UnsignedIntegerGreater, unsigned int,
        description("Checks for an unsigned integer that is greater.");
        symbol(">");
        verb("Greater");
        cmd("gt");
    )

    bool UnsignedIntegerGreaterOrEqual::accept(const QVariant&v) const
    {
        return v.toUInt() >= m_value;
    }

    DATA_FILTER1(UnsignedIntegerGreaterOrEqual, unsigned int,
        description("Checks for an unsigned integer that is greater or equal.");
        symbol(">=");
        verb("Above");
        cmd("gq");
    )

    
    bool UnsignedIntegerLesser::accept(const QVariant&v) const
    {
        return v.toUInt() < m_value;
    }

    DATA_FILTER1(UnsignedIntegerLesser, unsigned int,
        description("Checks for an unsigned integer that is lesser.");
        symbol("<");
        verb("Lesser");
        cmd("lt");
    )

    bool UnsignedIntegerLesserOrEqual::accept(const QVariant&v) const
    {
        return v.toUInt() <= m_value;
    }

    DATA_FILTER1(UnsignedIntegerLesserOrEqual, unsigned int,
        description("Checks for an unsigned integer that is lesser or equal.");
        symbol("<=");
        verb("Below");
        cmd("lq");
    )

    bool UnsignedIntegerNotEqual::accept(const QVariant&v) const
    {
        return v.toUInt() != m_value;
    }

    DATA_FILTER1(UnsignedIntegerNotEqual, unsigned int,
        description("Checks for an unsigned integer that is not equal.");
        symbol("!=");
        verb("NotEqual");
        cmd("neq");
    )
}

using namespace data_filters;

namespace data {

    const DataFilter::Ptr   operator && (const DataFilter::Ptr a, const DataFilter::Ptr b)
    {
        const DataLogicFilter*  fa  = dynamic_cast<const DataLogicFilter*>(a.ptr());
        const DataLogicFilter*  fb  = dynamic_cast<const DataLogicFilter*>(b.ptr());
        
        if(fa){
            if(fb)
                return fa->leftAnd(fb);
            else if(b.valid())
                return fa->leftAnd(b);
            else 
                return new False;
        } else if(a.valid()){
            if(fb)
                return fb->rightAnd(a);
            else if(b.valid())
                return new And({a, b});
            else
                return new False;
        } else
            return new False;
    }

    const DataFilter::Ptr   operator || (const DataFilter::Ptr a, const DataFilter::Ptr b)
    {
        const DataLogicFilter*  fa  = dynamic_cast<const DataLogicFilter*>(a.ptr());
        const DataLogicFilter*  fb  = dynamic_cast<const DataLogicFilter*>(b.ptr());
        
        if(fa){
            if(fb)
                return fa->leftOr(fb);
            else if(b.valid())
                return fa->leftOr(b);
            else
                return a;
        } else if(a.valid()){
            if(fb)
                return fb->rightOr(a);
            else if(b.valid())
                return new Or({a, b});
            else
                return a;
        } else if(b.valid()){
            return b;
        } else
            return new False;
    }

    const DataFilter::Ptr   operator ^  (const DataFilter::Ptr a, const DataFilter::Ptr b)
    {
        if(a.valid()){
            if(b.valid())
                return new Xor(a,b);
            else
                return a;
        } else {
            if(b.valid())
                return b;
            else
                return new False;
        }
    }

    const DataFilter::Ptr   operator !  (const DataFilter::Ptr a)
    {
        const DataLogicFilter*  fa  = dynamic_cast<const DataLogicFilter*>(a.ptr());
        if(fa)
            return fa->invert();
        if(a.valid())
            return new Not(a);
        return new True;
    }

}
