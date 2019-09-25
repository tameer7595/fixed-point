//
// Created by tameer on 9/23/19.
//

#ifndef FIXED_POINT_FIXED_POINT_H
#define FIXED_POINT_FIXED_POINT_H

#include <iostream>
#include <fstream>
#include<math.h>
#include <stdio.h>
#include <iomanip>
#include <limits.h>
#include <limits>

unsigned int power_ten(unsigned int size);
std::string numberToWords(unsigned long int n);
std::string convert2digit(unsigned  long int n, std::string suffix);


template<class T>
class FixedPoint;

template<class T>
std::ostream &operator<<(std::ostream &os, const FixedPoint<T> &obj);

template<class T>
class FixedPoint {
public:

    explicit FixedPoint() {};

    explicit FixedPoint(T dollar, unsigned int cent = 0, int size = 2);

    double cast_to_double() const;/*todo : must be explicit operator double()const*/
    operator double () const;
    FixedPoint<T> &operator=(T dollar);

    FixedPoint<T> &operator=(const FixedPoint<T> &other);

    FixedPoint<T> &operator+=(const FixedPoint<T> &);

    FixedPoint<T> &operator-=(const FixedPoint<T> &);

    FixedPoint<T> &operator*=(const FixedPoint<T> &);

    FixedPoint<T> &operator/=(const FixedPoint<T> &);

    FixedPoint<T> &operator%=(const FixedPoint<T> &);

    bool operator==(const FixedPoint &);

    bool operator!=(const FixedPoint &);

    bool operator<(const FixedPoint &);

    bool operator<=(const FixedPoint &);

    bool operator>(const FixedPoint &);

    bool operator>=(const FixedPoint &);

    void operator++();

    void operator--();


    friend std::ostream &operator<<<>(std::ostream &os, const FixedPoint &obj);

    T get_dollar() const;

    void set_dollar(T dollar);

    unsigned int get_cent() const;

    int get_size() const;

    void set_cent(unsigned int cent);




private:
    /*todo:change name*/
    T m_dollar;
    unsigned int m_cent;
    int m_size;


};


template<class T>
inline FixedPoint<T> operator+(const FixedPoint<T> &t1, const FixedPoint<T> &t2) {
    if(std::numeric_limits<T>::max() - t1.get_dollar() < t2.get_dollar()){
        throw std::overflow_error("out of range");
    }
    FixedPoint<T> temp;
    unsigned int size = power_ten(t1.get_size());
    temp.set_cent((t2.get_cent() + t1.get_cent()));
    if (temp.get_cent() > size*10) {
        temp.set_cent(temp.get_cent() % size);
        temp.set_dollar(t2.get_dollar() + t1.get_dollar() + 1);
    } else
        temp.set_dollar(t2.get_dollar() + t1.get_dollar());
    return temp;
}

template<class T>
inline FixedPoint<T> operator-(const FixedPoint<T> &t1, const FixedPoint<T> &t2) {
    if(t1.get_dollar() < t2.get_dollar())
        throw std::out_of_range("operator - : can not be less than 0");
    else{
        if(t1.get_dollar() == t2.get_dollar() && t1.get_cent() < t2.get_cent())
            throw std::out_of_range("operator - : can not be less than 0");
    }
    FixedPoint<T> tem;
    T temp = t1.get_dollar()*power_ten(t1.get_size()) + t1.get_cent();
    T temp1 = t2.get_dollar()*power_ten(t2.get_size()) + t2.get_cent();
    temp-=temp1;
    tem.set_dollar(temp/power_ten(t2.get_size()));
    tem.set_cent((unsigned int)temp%power_ten(t2.get_size()));

    return tem;
}

template<class T>
FixedPoint<T> operator*(const FixedPoint<T> &t1, const FixedPoint<T> &t2) {
    if(t1.get_dollar() > 0)
    if(std::numeric_limits<T>::max() / t1.get_dollar() < t2.get_dollar()){
        throw std::overflow_error("out of range");
    }
    FixedPoint<T> temporary;
   long dd = t1.get_dollar() * t2.get_dollar();
   long dc = t1.get_dollar() * t2.get_cent();
   long cd = t1.get_cent() * t2.get_dollar();
   long cc = t1.get_cent() * t2.get_cent();
   temporary.set_dollar(dd + (cd + dc)/power_ten(t1.get_size()));
   temporary.set_cent((unsigned int)((cd + dc)%power_ten(t1.get_size()) + cc%power_ten(t1.get_size()*2)/power_ten(t1.get_size())));
   return temporary;

}

template<class T>
FixedPoint<T> operator/(const FixedPoint<T> &t1, const FixedPoint<T> &t2) {
    FixedPoint<T> temporary;
    T temp = t1.get_dollar()*(T)power_ten(t1.get_size()) + t1.get_cent();
    T temp1 = t2.get_dollar()*(T)power_ten(t2.get_size()) + t2.get_cent();
    temp/=temp1;
    temporary.set_dollar(temp);
    temporary.set_cent(0);
    return temporary;
}

template<class T>
FixedPoint<T> operator%(const FixedPoint<T> &t1, const FixedPoint<T> &t2) {
    FixedPoint<T> temporary;

    T temp = t1.get_dollar()*(T)power_ten(t1.get_size()) + t1.get_cent();
    T temp1 = t2.get_dollar()*(T)power_ten(t2.get_size()) + t2.get_cent();
    temp%=temp1;
    temporary.set_dollar(temp/(T)power_ten(t1.get_size()));
    temporary.set_cent((unsigned int)(temp%(T)power_ten(t1.get_size())));
    return temporary;

}

template<class T>
inline FixedPoint<T>::FixedPoint(T dollar, unsigned int cent, int size) : m_dollar(dollar), m_cent(cent), m_size(size) {

}

template<class T>
inline T FixedPoint<T>::get_dollar() const {
    return m_dollar;
}

template<class T>
inline unsigned int FixedPoint<T>::get_cent() const {
    return m_cent;
}

template<class T>
inline void FixedPoint<T>::set_dollar(T dollar) { this->m_dollar = dollar; }

template<class T>
inline void FixedPoint<T>::set_cent(unsigned int cent) { this->m_cent = cent; }

template<class T>
inline FixedPoint<T> &FixedPoint<T>::operator=(const FixedPoint<T> &other) {
    this->set_cent(other.get_cent());
    this->set_dollar(other.get_dollar());
    return *this;
}

template<class T>
inline FixedPoint<T> &FixedPoint<T>::operator=(T dollar) {
    this->m_dollar += dollar;
    return *this;
}

template<class T>
inline bool FixedPoint<T>::operator==(const FixedPoint<T> &other) {
    if (this->m_dollar == other.m_dollar)
        if (this->m_cent == other.m_cent)
            return true;
    return false;

}

template<class T>
inline bool FixedPoint<T>::operator!=(const FixedPoint<T> &other) {
    return !(*this == other);
}

template<class T>
inline bool FixedPoint<T>::operator<(const FixedPoint<T> &other) {
    if (this->m_dollar < other.m_dollar)
        return true;
    else {
        if (this->m_dollar == other.m_dollar)
            if (this->m_cent < other.m_cent)
                return true;
        return false;
    }

}

template<class T>
inline bool FixedPoint<T>::operator<=(const FixedPoint<T> &other) {
    return !(*this > other);
}

template<class T>
inline bool FixedPoint<T>::operator>(const FixedPoint<T> &other) {
    if (this->m_dollar > other.m_dollar)
        return true;
    else {
        if (this->m_dollar == other.m_dollar)
            if (this->m_cent > other.m_cent)
                return true;
        return false;
    }

}

template<class T>
inline bool FixedPoint<T>::operator>=(const FixedPoint<T> &other) {
    return !(*this < other);
}

template<class T>
inline FixedPoint<T> :: operator double ()const {
    double x = (double)(1.0/power_ten(get_size()));
    return static_cast<double>(this->m_dollar)+static_cast<double>((this->m_cent)*x);
}

template<class T>
FixedPoint<T> &FixedPoint<T>::operator+=(const FixedPoint<T> &other) {
    *this = *this + other;
    return *this;
}

template<class T>
FixedPoint<T> &FixedPoint<T>::operator-=(const FixedPoint<T> &other) {
    *this = *this - other;
    return *this;
}

/*todo: uncompleted*/
template<class T>
FixedPoint<T> &FixedPoint<T>::operator*=(const FixedPoint<T> &other) {

    *this = *this * other;
    return *this;

}

template<class T>
FixedPoint<T> &FixedPoint<T>::operator/=(const FixedPoint<T> &other) {
    *this = *this / other;
    return *this;
}

template<class T>
FixedPoint<T> &FixedPoint<T>::operator%=(const FixedPoint<T> &other) {
    *this = *this % other;
    return *this;
}

template<class T>
void FixedPoint<T>::operator++() {
    this->m_dollar += 1; /* todo : use traits to prevent overflow*/
}

template<class T>
void FixedPoint<T>::operator--() {
    this->m_dollar -= 1;
    this->m_cent = power_ten(m_size) - this->m_cent;
}

template<class T>
inline std::ostream &operator<<(std::ostream &os, const FixedPoint<T> &obj) {
    os << obj.m_dollar << "." << std::setfill('0') << std::setw(obj.get_size()) << (int) obj.m_cent;
    return os;
}


template<class T>
inline int FixedPoint<T>::get_size() const {
    return m_size;
}

#endif //FIXED_POINT_FIXED_POINT_H
