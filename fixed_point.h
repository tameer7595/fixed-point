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
std::string numberToWords(unsigned long int n);
std::string convert2digit(int n, std::string suffix);


template<class T>
class Price;

template<class T>
std::ostream &operator<<(std::ostream &os, const Price<T> &obj);

template<class T>
class Price {
public:
    explicit Price() {};

    explicit Price(T dollar, unsigned int cent = 0, int size = 2);

    double cast_to_double() const;/*todo : must be explicit operator double()const*/

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


    friend std::ostream &operator<<<>(std::ostream &os, const Price &obj);

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
inline Price<T> operator+(const Price<T> &t1, const Price<T> &t2) {
    Price<T> temp;
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
inline Price<T> operator-(const Price<T> &t1, const Price<T> &t2) {
    Price<T> tem;
    T temp = t1.get_dollar()*power_ten(t1.get_size()) + t1.get_cent();
    T temp1 = t2.get_dollar()*power_ten(t2.get_size()) + t2.get_cent();
    temp1-=temp;
    tem.set_dollar(temp1/power_ten(t2.get_size()));
    tem.set_cent(temp1%power_ten(t2.get_size()));

    return tem;
}

template<class T>
Price<T> operator*(const Price<T> &t1, const Price<T> &t2) {
    Price<T> temporary;

    T temp = t1.get_dollar()*power_ten(t1.get_size()) + t1.get_cent();
    T temp1 = t2.get_dollar()*power_ten(t2.get_size()) + t2.get_cent();
    temp1*=temp;

    temporary.set_dollar(temp1/power_ten(t1.get_size()*2));
    temporary.set_cent(temp1%power_ten(t1.get_size()*2));
    temporary.set_cent(temporary.get_cent()/power_ten(t1.get_size()));
    return temporary;

}

template<class T>
Price<T> operator/(const Price<T> &t1, const Price<T> &t2) {
    Price<T> temporary;

    T temp = t1.get_dollar()*power_ten(t1.get_size()) + t1.get_cent();
    T temp1 = t2.get_dollar()*power_ten(t2.get_size()) + t2.get_cent();
    temp/=temp1;
    temporary.set_dollar(temp);
    temporary.set_cent(0);
    return temporary;
}

template<class T>
Price<T> operator%(const Price<T> &obj, const Price<T> &other) {
    Price<T> temporary;
    double temp = obj.cast_to_double();
    double temp1 = other.cast_to_double();
    if (temp < temp1) {
        return obj;
    }
    while (temp > temp1) {
        temp -= temp1;
    }
    temporary.set_dollar((int) temp);
    temporary.set_cent((int) ((temp - temporary.get_dollar()) * power_ten(obj.get_size())));
    return temporary;

}/*todo:refactoring*/

template<class T>
inline Price<T>::Price(T dollar, unsigned int cent, int size) : m_dollar(dollar), m_cent(cent), m_size(size) {

}

template<class T>
inline T Price<T>::get_dollar() const {
    return m_dollar;
}

template<class T>
inline unsigned int Price<T>::get_cent() const {
    return m_cent;
}

template<class T>
inline void Price<T>::set_dollar(T dollar) { this->m_dollar = dollar; }

template<class T>
inline void Price<T>::set_cent(unsigned int cent) { this->m_cent = cent; }

template<class T>
inline Price<T> &Price<T>::operator=(const Price<T> &other) {
    this->set_cent(other.get_cent());
    this->set_dollar(other.get_dollar());
    return *this;
}

template<class T>
inline Price<T> &Price<T>::operator=(T dollar) {
    this->m_dollar += dollar;
    return *this;
}

template<class T>
inline bool Price<T>::operator==(const Price<T> &other) {
    if (this->m_dollar == other.m_dollar)
        if (this->m_cent == other.m_cent)
            return true;
    return false;

}

template<class T>
inline bool Price<T>::operator!=(const Price<T> &other) {
    return !(*this == other);
}

template<class T>
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

template<class T>
inline bool Price<T>::operator<=(const Price<T> &other) {
    return !(*this > other);
}

template<class T>
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

template<class T>
inline bool Price<T>::operator>=(const Price<T> &other) {
    return !(*this < other);
}

template<class T>
inline double Price<T>::cast_to_double() const {
    double x = (double)(1.0/power_ten(get_size()));
    return static_cast<double>(this->m_dollar)+static_cast<double>((this->m_cent)*x);
}

template<class T>
Price<T> &Price<T>::operator+=(const Price<T> &other) {
    *this = *this + other;
    return *this;
}

template<class T>
Price<T> &Price<T>::operator-=(const Price<T> &other) {
    *this = *this - other;
    return *this;
}

/*todo: uncompleted*/
template<class T>
Price<T> &Price<T>::operator*=(const Price<T> &other) {

    *this = *this * other;
    return *this;

}

template<class T>
Price<T> &Price<T>::operator/=(const Price<T> &other) {
    *this = *this / other;
    return *this;
}

template<class T>
Price<T> &Price<T>::operator%=(const Price<T> &other) {
    *this = *this % other;
    return *this;
}

template<class T>
void Price<T>::operator++() {
    this->m_dollar += 1; /* todo : use traits to prevent overflow*/
}

template<class T>
void Price<T>::operator--() {
    this->m_dollar -= 1;
    this->m_cent = power_ten(m_size) - this->m_cent;
}

template<class T>
inline std::ostream &operator<<(std::ostream &os, const Price<T> &obj) {
    os << obj.m_dollar << "." << std::setfill('0') << std::setw(obj.get_size()) << (int) obj.m_cent;
    return os;
}


template<class T>
inline int Price<T>::get_size() const {
    return m_size;
}

#endif //FIXED_POINT_FIXED_POINT_H
