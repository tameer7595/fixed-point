//
// Created by tameer on 9/23/19.
//

#ifndef FIXED_POINT_FIXED_POINT_H
#define FIXED_POINT_FIXED_POINT_H

#include <iostream>
class FixedPoint {
public:
    FixedPoint(int dollar = 0, char cent = 0);

    double cast_to_double() const;

    FixedPoint &operator=(int dollar);

    FixedPoint &operator=(const FixedPoint& other);

    FixedPoint &operator+=(const FixedPoint &);

    FixedPoint &operator-=(const FixedPoint &);

    FixedPoint &operator*=(const FixedPoint &);

    FixedPoint &operator/=(const FixedPoint &);

    FixedPoint &operator%=(const FixedPoint &);

    bool operator==(const FixedPoint &);

    bool operator!=(const FixedPoint &);

    bool operator<(const FixedPoint &);

    bool operator<=(const FixedPoint &);

    bool operator>(const FixedPoint &);

    bool operator>=(const FixedPoint &);

    void operator++();

    void operator--();

    friend std::ostream& operator<<(std::ostream& os, const FixedPoint& obj);

    int get_dollar() const;
    void set_dollar(int dollar);
    char get_cent() const;
    void set_cent(char cent);

private:
    int m_dollar;
    unsigned char m_cent;
};


inline FixedPoint operator+(const FixedPoint & t1, const FixedPoint & t2){
    FixedPoint temp;
    temp.set_cent(t2.get_cent()+t1.get_cent());
    if(temp.get_cent() > 100){
        temp.set_cent(temp.get_cent()%100);
        temp.set_dollar(t2.get_cent() + t1.get_cent() + 1);
    }else
        temp.set_dollar(t2.get_dollar()+t1.get_dollar());
    return temp;
}

FixedPoint &operator-(const FixedPoint &, const FixedPoint &);

FixedPoint &operator*(const FixedPoint &, const FixedPoint &);

FixedPoint &operator/(const FixedPoint &, const FixedPoint &);

FixedPoint &operator%(const FixedPoint &, const FixedPoint &);

inline FixedPoint::FixedPoint(int dollar, char cent) : m_dollar(dollar), m_cent(cent) {}


inline int FixedPoint :: get_dollar() const{
    return m_dollar;
}

inline char FixedPoint :: get_cent() const{
    return m_cent;
}
inline void FixedPoint ::set_dollar(int dollar) {this->m_dollar = dollar;}

inline void FixedPoint ::set_cent(char cent) {this->m_cent = cent;}

inline FixedPoint& FixedPoint :: operator=(const FixedPoint& other){
    this->set_cent(other.get_cent());
    this->set_dollar(other.get_dollar());
    return *this;
}


inline FixedPoint &FixedPoint::operator=(int dollar) {
    this->m_dollar += dollar;
    return *this;
}

inline bool FixedPoint::operator==(const FixedPoint &other) {
    if (this->m_dollar == other.m_dollar)
        if (this->m_cent == other.m_cent)
            return true;
    return false;

}

inline bool FixedPoint::operator!=(const FixedPoint &other) {
    return !(*this == other);
}

inline bool FixedPoint::operator<(const FixedPoint &other) {
    if (this->m_dollar < other.m_dollar)
        return true;
    else {
        if (this->m_dollar == other.m_dollar)
            if (this->m_cent < other.m_cent)
                return true;
        return false;
    }

}

inline bool FixedPoint::operator<=(const FixedPoint &other) {
    return !(*this > other);
}

inline bool FixedPoint::operator>(const FixedPoint &other) {
    if (this->m_dollar > other.m_dollar)
        return true;
    else {
        if (this->m_dollar == other.m_dollar)
            if (this->m_cent > other.m_cent)
                return true;
        return false;
    }

}

inline bool FixedPoint::operator>=(const FixedPoint &other) {
    return !(*this < other);
}

inline double FixedPoint :: cast_to_double() const{
    return  static_cast<double>(this->m_dollar) + static_cast<double>(this->m_cent*0.01);
}

#endif //FIXED_POINT_FIXED_POINT_H
