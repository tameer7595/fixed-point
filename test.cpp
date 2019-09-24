//
// Created by tameer on 9/23/19.
//

#include "test.h"
#include "fixed_point.h"
using std::cout;
void Test ::test_fixed_point(){
    Price<int>temp(30,14,4);

    Price<int> temp1(23,15 , 4);
    cout<<"sum of : "<< temp << " + " << temp1 << " is :";
    temp = temp + temp1;
    cout << temp << std::endl;

    if(temp == temp1)
        cout << temp<<" and " << temp1<<" are equals"<<std ::endl;
    else
        cout << temp<<" and " << temp1<<" are not  equals"<<std ::endl;

    cout<<temp1<<" - "<<temp <<" is : ";
    Price<int> temp2 = temp1;
    temp2-=temp;
    cout<<temp2<<std::endl;

    cout<<temp1<<" + "<<temp <<" is : ";
    temp2 = temp1;
    temp2+=temp;
    cout<<temp2<<std::endl;



    Price< short > mySalary(120,35,3);
    cout <<"mySalary : "<< mySalary<<std::endl;
    Price< long > myOverdraft(99999,99,3);
    cout<<"myOverdraft : "<< myOverdraft << std::endl;
    Price<long> usaSelfDebt(145800000000000);
    cout<< "usaSelfDebt : "<< usaSelfDebt << std::endl;
    /*myOverdraft = mySalary;*/
    myOverdraft = usaSelfDebt;

}
