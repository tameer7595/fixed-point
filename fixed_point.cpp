//
// Created by tameer on 9/23/19.
//

#include "fixed_point.h"

unsigned int power_ten(unsigned int size){
    unsigned  int ten = 10;
    unsigned int res = 1;
    while(size){
        res*=ten;
        size--;
    }
    return res;
}