//
// Created by tameer on 9/23/19.
//

#include "fixed_point.h"





FixedPoint& FixedPoint :: operator+=(const FixedPoint& other){
    this->m_cent += other.m_cent;
    if(this->m_cent > 100){
        this->m_cent %= 100 ;
        this->m_dollar += other.m_cent + 1;
    }else
        this->m_dollar += other.m_cent;
    return *this;
}

FixedPoint& FixedPoint :: operator-=( const FixedPoint& other){
    double temp = this->cast_to_double();
    double temp1 = other.cast_to_double();
    temp-=temp1;
    if(temp>0) {
        this->m_dollar = temp / 1;
        this-> m_cent =  temp - this->m_dollar;
    }else{
        this->m_dollar = temp / 1;
        double v =(temp - this->m_dollar);
        this-> m_cent =  v;
    }
    return *this;
}

FixedPoint& FixedPoint :: operator*=( const FixedPoint& other){
    /*implement multiply like => (10+0.5)*(10+0.5) */
    int temp = this->m_dollar;
    temp *= other.m_cent;
    this->m_dollar *= other.m_dollar;
    this->m_dollar += temp;
    temp = this->m_cent;
    temp *= other.m_dollar;
    this->m_cent *= other.m_cent;
    this->m_cent += temp;
    return *this;
}

FixedPoint& FixedPoint :: operator/=( const FixedPoint& other){}

FixedPoint& FixedPoint :: operator%=( const FixedPoint& other){}

void FixedPoint::operator++() {
    this->m_dollar+=1;
}

void FixedPoint::operator--() {
    this->m_dollar-=1;
    this->m_cent = 100 - this->m_cent;
}

std::ostream& operator<<(std::ostream& os, const FixedPoint& obj){
    os << obj.m_dollar<<"."<<(int)obj.m_cent;
    return os;
}