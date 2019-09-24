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
unsigned int power_ten(unsigned int size);
template<class T>
class Price;
template <class T>
std::ostream &operator<<(std::ostream &os, const Price<T> &obj);

template <class T >
class Price {
public:

    explicit  Price(){};
    explicit Price(T dollar, unsigned int cent = 0, int size = 2);

    double cast_to_double() const;

    Price<T> &operator=(T dollar);

    Price<T> &operator=(const Price<T> &other);

    Price<T> &operator+=(const Price<T> &);

    Price<T> &operator-=(const Price<T> &);

    Price<T> &operator*=(const Price<T> &);

    Price<T> &operator/=(const Price<T> &);

    Price<T> &operator%=(const Price<T> &);

    bool operator==(const Price &);

    bool operator!=(const Price &);

    bool operator<(const Price &);

    bool operator<=(const Price &);

    bool operator>(const Price &);

    bool operator>=(const Price &);

    void operator++();

    void operator--();


    friend std::ostream &operator<< <>(std::ostream &os, const Price &obj);

    T get_dollar() const;

    void set_dollar(T dollar);

    unsigned int get_cent() const;

    int get_size() const;

    void set_cent(unsigned int  cent);


private:
    T m_dollar;
    unsigned int m_cent;
    int m_size;


};



template <class T>
inline Price<T> operator+(const Price<T> &t1, const Price<T> &t2) {
    Price<T> temp;
    unsigned int size = power_ten(t1.get_size());
    temp.set_cent((unsigned int)(t2.get_cent() + t1.get_cent()));
    if (temp.get_cent() > size ) {
        temp.set_cent(temp.get_cent() % size);
        temp.set_dollar(t2.get_cent() + t1.get_cent() + 1);
    } else
        temp.set_dollar(t2.get_dollar() + t1.get_dollar());
    return temp;
}

template <class T>
inline Price<T> operator-(const Price<T> &t1, const Price<T> &t2) {
    Price<T> tem;
    double temp = t1.cast_to_double();
    double temp1 = t2.cast_to_double();
    temp -= temp1;
    if (temp > 0) {
        tem.set_dollar(int(temp / 1.0));
        tem.set_cent(int(temp - tem.get_dollar()));
    } else {
        tem.set_dollar(int(temp / 1.0));
        double v = (temp - tem.get_dollar()) * power_ten(t1.get_size());
        tem.set_cent(int(v * -1));
    }
    return tem;
}

template <class T>
Price<T> &operator*(const Price<T> &, const Price<T> &);/*todo:uncompleted*/

template <class T>
Price<T> &operator/(const Price<T> &, const Price<T> &);/*todo:uncompleted*/

template <class T>
Price<T> &operator%(const Price<T> &, const Price<T> &);/*todo:uncompleted*/

template <class T>
inline  Price<T>::Price(T dollar, unsigned int cent , int size) : m_dollar(dollar), m_cent(cent) , m_size(size) {

}

template <class T>
inline T Price<T>::get_dollar() const {
    return m_dollar;
}

template <class T>
inline unsigned int Price<T>::get_cent() const {
    return m_cent;
}

template <class T>
inline void Price<T>::set_dollar(T dollar) { this->m_dollar = dollar; }

template <class T>
inline void Price<T>::set_cent(unsigned int cent) { this->m_cent = cent; }

template <class T>
inline Price<T> &Price<T>::operator=(const Price<T> &other) {
    this->set_cent(other.get_cent());
    this->set_dollar(other.get_dollar());
    return *this;
}

template <class T>
inline Price<T> &Price<T>::operator=(T dollar) {
    this->m_dollar += dollar;
    return *this;
}

template <class T>
inline bool Price<T>::operator==(const Price<T> &other) {
    if (this->m_dollar == other.m_dollar)
        if (this->m_cent == other.m_cent)
            return true;
    return false;

}

template <class T>
inline bool Price<T>::operator!=(const Price<T> &other) {
    return !(*this == other);
}

template <class T>
inline bool Price<T>::operator<(const Price<T> &other) {
    if (this->m_dollar < other.m_dollar)
        return true;
    else {
        if (this->m_dollar == other.m_dollar)
            if (this->m_cent < other.m_cent)
                return true;
        return false;
    }

}

template <class T>
inline bool Price<T>::operator<=(const Price<T> &other) {
    return !(*this > other);
}

template <class T>
inline bool Price<T>::operator>(const Price<T> &other) {
    if (this->m_dollar > other.m_dollar)
        return true;
    else {
        if (this->m_dollar == other.m_dollar)
            if (this->m_cent > other.m_cent)
                return true;
        return false;
    }

}

template <class T>
inline bool Price<T>::operator>=(const Price<T> &other) {
    return !(*this < other);
}
template <class T>
inline double Price<T>::cast_to_double() const {
    return static_cast<double>(this->m_dollar) + static_cast<double>(this->m_cent * 0.01);
}
template <class T>
Price<T>& Price<T> :: operator+=(const Price<T>& other){
    *this = *this+other;
    return *this;
}

template <class T>
Price<T>& Price<T> :: operator-=( const Price<T>& other){
    *this = *this - other;
    return *this;
}

/*todo: uncompleted*/
template <class T>
Price<T>& Price<T> :: operator*=( const Price<T>& other){
    /*implement multiply like => (10+0.5)*(10+0.5) */
    double temp = this->m_dollar;
    temp *= (other.m_cent*0.01)*100;
    this->m_dollar *= other.m_dollar;
    this->m_dollar += temp;
    temp = this->m_cent*0.01;
    temp *= other.m_dollar;
    this->m_cent *= other.m_cent*0.01;
    this->m_cent += temp;
    return *this;
}

template <class T>
Price<T>& Price<T> :: operator/=( const Price<T>& other){
    double temp = this->cast_to_double();
    double temp1 = other.cast_to_double();

}

template <class T>
Price<T>& Price<T> :: operator%=( const Price<T>& other){}

template <class T>
void Price<T>::operator++() {
    this->m_dollar+=1;
}

template <class T>
void Price<T>::operator--() {
    this->m_dollar-=1;
    this->m_cent = power_ten(m_size) - this->m_cent;
}

template <class T>
inline std::ostream&  operator<<(std::ostream& os, const Price<T>& obj){
    os << obj.m_dollar<<"."<<std::setfill('0')<<std::setw(obj.get_size())<<(int)obj.m_cent;
    return os;
}


template <class T>
inline int Price<T> ::get_size() const {
    return m_size;
}
#endif //FIXED_POINT_FIXED_POINT_H
