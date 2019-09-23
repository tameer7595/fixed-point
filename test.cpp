//
// Created by tameer on 9/23/19.
//

#include "test.h"
#include "fixed_point.h"
using std::cout;
void Test ::test_fixed_point(){
    FixedPoint temp(30,14);

    FixedPoint temp1(23,15);
    cout<<"sum of : "<< temp << " + " << temp1 << " is :";
    temp = temp + temp1;
    cout << temp << std::endl;

    if(temp == temp1)
        cout << temp<<" and " << temp1<<" are equals"<<std ::endl;
    else
        cout << temp<<" and " << temp1<<" are not  equals"<<std ::endl;

    cout<<temp1<<" - "<<temp <<"is"<<std::endl;
    temp1 -= temp;
    cout<<temp;
}
