#pragma once

#include "DataFilter.hpp"
#include "Vector.hpp"

#include <QDate>
#include <QDateTime>
#include <QRegularExpression>
#include <QTime>
#include <initializer_list>

namespace data_filters {
    
    class IsFalse : public DataFilter {
    public:
        bool    accept(const QVariant&) const override;
        IsFalse(){}
    private:
        virtual ~IsFalse(){}
    };

    class IsTrue : public DataFilter {
    public:
        bool    accept(const QVariant&) const override;
        IsTrue(){}
    private:
        virtual ~IsTrue(){}
    };
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    class DataLogicFilter : public DataFilter {
    public:
    
        //  the combiners will try left first, otherwise, right
        virtual Ptr     leftAnd(const Ptr rhs) const;
        virtual Ptr     leftAnd(const DataLogicFilter*) const;
        virtual Ptr     leftOr(const Ptr rhs) const;
        virtual Ptr     leftOr(const DataLogicFilter*) const;
        virtual Ptr     rightAnd(const Ptr lhs) const;
        virtual Ptr     rightOr(const Ptr lhs) const;
        virtual Ptr     invert() const;
    };
    
    class False : public DataLogicFilter {
    public:
        bool    accept(const QVariant&) const override;
        False(){}

        //virtual Ptr     combineAnd(const Ptr) const;
        //virtual Ptr     combineOr(const Ptr) const;
        //virtual Ptr     invert() const;

    private:
        virtual ~False(){}
    };

    class True : public DataLogicFilter {
    public:
        bool    accept(const QVariant&) const override;
        True(){}

        //virtual Ptr     combineAnd(const Ptr) const;
        //virtual Ptr     combineOr(const Ptr) const;
        //virtual Ptr     invert() const;

    private:
        virtual ~True(){}
    };
    
    class And : public DataLogicFilter {
    public:
        bool    accept(const QVariant&) const override;
        And(const std::initializer_list<Ptr>&);
        And(const Vector<Ptr>&);

        //virtual Ptr     combineAnd(const Ptr) const;
        //virtual Ptr     invert() const;

    private:
        virtual ~And();
        Vector<Ptr> m_filters;
    };
    
    class Nand : public DataLogicFilter {
    public:
        bool    accept(const QVariant&) const override;
        Nand(const std::initializer_list<Ptr>&);
        Nand(const Vector<Ptr>&);

        //virtual Ptr     combineAnd(const Ptr) const;
        //virtual Ptr     combineOr(const Ptr) const;
        //virtual Ptr     invert() const;

    private:
        virtual ~Nand();
        Vector<Ptr> m_filters;
    };

    class Nor : public DataLogicFilter {
    public:
        bool    accept(const QVariant&) const override;
        Nor(const std::initializer_list<Ptr>&);
        Nor(const Vector<Ptr>&);
    private:
        virtual ~Nor();
        Vector<Ptr> m_filters;
    };
    
    class Not : public DataLogicFilter {
    public:
        bool    accept(const QVariant&) const override;
        Not(Ptr a);
    private:
        virtual ~Not(){}
        Ptr m_a;
    };

    class Or : public DataLogicFilter {
    public:
        bool    accept(const QVariant&) const override;
        Or(const std::initializer_list<Ptr>&);
        Or(const Vector<Ptr>&);
    private:
        virtual ~Or();
        Vector<Ptr> m_filters;
    };
    
    class Xnor : public DataLogicFilter {
    public:
        bool    accept(const QVariant&) const override;
        Xnor(Ptr a, Ptr b);
    private:
        virtual ~Xnor(){}
        Ptr m_a, m_b;
    };

    class Xor : public DataLogicFilter {
    public:
        bool    accept(const QVariant&) const override;
        Xor(Ptr a, Ptr b);
    private:
        virtual ~Xor(){}
        Ptr m_a, m_b;
    };

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    class DateEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DateEqual(const QDate&v) : m_value(v) {}
    private:
        virtual ~DateEqual(){}
        QDate       m_value;
    };
    
    class DateGreater : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DateGreater(const QDate&v) : m_value(v) {}
    private:
        virtual ~DateGreater(){}
        QDate       m_value;
    };
    
    class DateGreaterOrEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DateGreaterOrEqual(const QDate&v) : m_value(v) {}
    private:
        virtual ~DateGreaterOrEqual(){}
        QDate       m_value;
    };

    class DateLesser : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DateLesser(const QDate&v) : m_value(v) {}
    private:
        virtual ~DateLesser(){}
        QDate       m_value;
    };
    
    class DateLesserOrEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DateLesserOrEqual(const QDate&v) : m_value(v) {}
    private:
        virtual ~DateLesserOrEqual(){}
        QDate       m_value;
    };

    class DateNotEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DateNotEqual(const QDate&v) : m_value(v) {}
    private:
        virtual ~DateNotEqual(){}
        QDate       m_value;
    };
    
    class DateNull : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DateNull() {}
    private:
        virtual ~DateNull(){}
    };

    class DateValid : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DateValid() {}
    private:
        virtual ~DateValid(){}
    };

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    class DateTimeEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DateTimeEqual(const QDateTime&v) : m_value(v) {}
    private:
        virtual ~DateTimeEqual(){}
        QDateTime       m_value;
    };
    
    class DateTimeGreater : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DateTimeGreater(const QDateTime&v) : m_value(v){}
    private:
        virtual ~DateTimeGreater(){}
        QDateTime       m_value;
    };

    class DateTimeGreaterOrEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DateTimeGreaterOrEqual(const QDateTime&v) : m_value(v) {}
    private:
        virtual ~DateTimeGreaterOrEqual(){}
        QDateTime       m_value;
    };

    
    class DateTimeLesser : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DateTimeLesser(const QDateTime&v) : m_value(v) {}
    private:
        virtual ~DateTimeLesser(){}
        QDateTime       m_value;
    };
    
    class DateTimeLesserOrEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DateTimeLesserOrEqual(const QDateTime&v) : m_value(v) {}
    private:
        virtual ~DateTimeLesserOrEqual(){}
        QDateTime       m_value;
    };

    class DateTimeNotEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DateTimeNotEqual(const QDateTime&v) : m_value(v) {}
    private:
        virtual ~DateTimeNotEqual(){}
        QDateTime       m_value;
    };

    class DateTimeNull : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DateTimeNull() {}
    private:
        virtual ~DateTimeNull(){}
    };

    class DateTimeValid : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DateTimeValid() {}
    private:
        virtual ~DateTimeValid(){}
    };
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    class DoubleEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DoubleEqual(double v) : m_value(v) {}
    private:
        virtual ~DoubleEqual(){}
        double      m_value;
    };
    
    class DoubleEqualWithin : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DoubleEqualWithin(double v,double ep) : 
            m_value(v), m_epsilon(ep){}
    private:
        virtual ~DoubleEqualWithin(){}
        double      m_value, m_epsilon;
    };

    class DoubleGreater : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DoubleGreater(double v) : m_value(v) {}
    private:
        virtual ~DoubleGreater(){}
        double      m_value;
    };
    
    class DoubleGreaterOrEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DoubleGreaterOrEqual(double v) : m_value(v) {}
    private:
        virtual ~DoubleGreaterOrEqual(){}
        double      m_value;
    };
    
    class DoubleLesser : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DoubleLesser(double v) : m_value(v) {}
    private:
        virtual ~DoubleLesser(){}
        double      m_value;
    };
    
    class DoubleLesserOrEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DoubleLesserOrEqual(double v) : m_value(v) {}
    private:
        virtual ~DoubleLesserOrEqual(){}
        double      m_value;
    };

    class DoubleNotEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DoubleNotEqual(double v) : m_value(v) {}
    private:
        virtual ~DoubleNotEqual(){}
        double      m_value;
    };
    
    class DoubleNotEqualWithin : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        DoubleNotEqualWithin(double v,double ep) :
            m_value(v), m_epsilon(ep) {}
            
    private:
        virtual ~DoubleNotEqualWithin(){}
        double      m_value, m_epsilon;
    };
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    class IntegerEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        IntegerEqual(int v) : m_value(v) {}
    private:
        virtual ~IntegerEqual(){}
        int      m_value;
    };
    
    class IntegerGreater : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        IntegerGreater(int v) : m_value(v) {}
    private:
        virtual ~IntegerGreater(){}
        int      m_value;
    };

    class IntegerGreaterOrEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        IntegerGreaterOrEqual(int v) : m_value(v) {}
    private:
        virtual ~IntegerGreaterOrEqual(){}
        int      m_value;
    };
    
    class IntegerLesser : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        IntegerLesser(int v) : m_value(v) {}
    private:
        virtual ~IntegerLesser(){}
        int      m_value;
    };

    class IntegerLesserOrEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        IntegerLesserOrEqual(int v) : m_value(v) {}
    private:
        virtual ~IntegerLesserOrEqual(){}
        int      m_value;
    };
    
    class IntegerNotEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        IntegerNotEqual(int v) : m_value(v) {}
    private:
        virtual ~IntegerNotEqual(){}
        int      m_value;
    };
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    class StringContains : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        StringContains(const QString&v) : m_value(v) {}
    private:
        virtual ~StringContains(){}
        QString      m_value;
    };
    
    class StringEmpty : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        StringEmpty(){}
    private:
        virtual ~StringEmpty(){}
    };
    
    class StringEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        StringEqual(const QString&v) : m_value(v) {}
    private:
        virtual ~StringEqual(){}
        QString      m_value;
    };
    
    class StringGreater : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        StringGreater(const QString&v) : m_value(v.toLower()) {}
    private:
        virtual ~StringGreater(){}
        QString      m_value;
    };
    
    class StringGreaterEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        StringGreaterEqual(const QString&v) : m_value(v.toLower()) {}
    private:
        virtual ~StringGreaterEqual(){}
        QString      m_value;
    };
    
    class StringLesser : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        StringLesser(const QString&v) : m_value(v.toLower()) {}
    private:
        virtual ~StringLesser(){}
        QString      m_value;
    };

    class StringLesserEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        StringLesserEqual(const QString&v) : m_value(v.toLower()) {}
    private:
        virtual ~StringLesserEqual(){}
        QString      m_value;
    };
    
    class StringNotContains : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        StringNotContains(const QString&v) : m_value(v) {}
    private:
        virtual ~StringNotContains(){}
        QString      m_value;
    };
    
    class StringNotEmpty : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        StringNotEmpty(){}
    private:
        virtual ~StringNotEmpty(){}
    };

    class StringNotEqual  : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        StringNotEqual(const QString&v) : m_value(v) {}
    private:
        virtual ~StringNotEqual(){}
        QString      m_value;
    };
    
    class StringRegex : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        StringRegex(const QString& pat) :
            m_regex(pat, 
                QRegularExpression::CaseInsensitiveOption | 
                QRegularExpression::UseUnicodePropertiesOption |
                QRegularExpression::OptimizeOnFirstUsageOption
            ) {}
    protected:
        virtual ~StringRegex(){}
    private:
        QRegularExpression  m_regex;
    };

    class StringStarts : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        StringStarts(const QString&v) : m_value(v) {}
    private:
        virtual ~StringStarts(){}
        QString      m_value;
    };

    class StringWildcard : public StringRegex {
    public:
        StringWildcard(const QString& pat);
    private:
        virtual ~StringWildcard(){}
    };
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    class StringListContains : public DataFilter {
    public:
        StringListContains(const QString& pat) : m_value(pat) {}
        bool accept(const QVariant&) const override;
    private:
        virtual ~StringListContains(){}
        QString      m_value;
    };
    
    class StringListEmpty : public DataFilter {
    public:
        StringListEmpty(){}
        bool accept(const QVariant&) const override;
    private:
        virtual ~StringListEmpty(){}
    };
    
    class StringListNotContains : public DataFilter {
    public:
        StringListNotContains(const QString& pat) : m_value(pat) {}
        bool accept(const QVariant&) const override;
    private:
        virtual ~StringListNotContains(){}
        QString      m_value;
    };

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    class TimeEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        TimeEqual(const QTime&v) : m_value(v) {}
    private:
        virtual ~TimeEqual(){}
        QTime      m_value;
    };
    
    class TimeGreater : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        TimeGreater(const QTime&v) : m_value(v) {}
    private:
        virtual ~TimeGreater(){}
        QTime      m_value;
    };
    
    class TimeGreaterOrEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        TimeGreaterOrEqual(const QTime&v) : m_value(v) {}
    private:
        virtual ~TimeGreaterOrEqual(){}
        QTime      m_value;
    };
    
    class TimeLesser : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        TimeLesser(const QTime&v) : m_value(v) {}
    private:
        virtual ~TimeLesser(){}
        QTime      m_value;
    };
    
    class TimeLesserOrEqual  : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        TimeLesserOrEqual(const QTime&v) : m_value(v) {}
    private:
        virtual ~TimeLesserOrEqual(){}
        QTime      m_value;
    };
    
    class TimeNotEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        TimeNotEqual(const QTime&v) : m_value(v) {}
    private:
        virtual ~TimeNotEqual() {}
        QTime      m_value;
    };

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    class UnsignedIntegerEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        UnsignedIntegerEqual(unsigned int v) : m_value(v) {}
    private:
        virtual ~UnsignedIntegerEqual(){}
        unsigned int      m_value;
    };
    
    class UnsignedIntegerGreater : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        UnsignedIntegerGreater(unsigned int v) : m_value(v) {}
    private:
        virtual ~UnsignedIntegerGreater(){}
        unsigned int      m_value;
    };

    class UnsignedIntegerGreaterOrEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        UnsignedIntegerGreaterOrEqual(unsigned int v) : m_value(v) {}
    private:
        virtual ~UnsignedIntegerGreaterOrEqual(){}
        unsigned int      m_value;
    };
    
    class UnsignedIntegerLesser : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        UnsignedIntegerLesser(unsigned int v) : m_value(v) {}
    private:
        virtual ~UnsignedIntegerLesser(){}
        unsigned int      m_value;
    };

    class UnsignedIntegerLesserOrEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        UnsignedIntegerLesserOrEqual(unsigned int v) : m_value(v) {}
    private:
        virtual ~UnsignedIntegerLesserOrEqual(){}
        unsigned int      m_value;
    };
    
    class UnsignedIntegerNotEqual : public DataFilter {
    public:
        bool accept(const QVariant&) const override;
        UnsignedIntegerNotEqual(unsigned int v) : m_value(v) {}
    private:
        virtual ~UnsignedIntegerNotEqual(){}
        unsigned int      m_value;
    };
}
