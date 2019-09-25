//
// Created by tameer on 9/23/19.
//

#include "test.h"
#include "fixed_point.h"
using std::cout;
void Test ::test_fixed_point(){
    FixedPoint<long>temp(0,50,2);

    FixedPoint<long> temp1(0,19 , 2);
   /* cout<<"sum of : "<< temp << " + " << temp1 << " is :";
    temp = temp + temp1;
    cout << temp << std::endl;*/

    if(temp == temp1)
        cout << temp<<" and " << temp1<<" are equals"<<std ::endl;
    else
        cout << temp<<" and " << temp1<<" are not  equals"<<std ::endl;

    cout<<temp<<" - "<<temp1 <<" is : ";
    FixedPoint<long> temp2 = temp;
    temp2-=temp1;
    cout<<temp2<<std::endl;
    cout << numberToWords((unsigned long int)temp2.get_dollar())<<numberToWords((unsigned long int)temp2.get_cent()) << std::endl;

    cout<<temp1<<" *= "<<temp <<" is : ";
    temp2 = temp1;
    temp2*=temp;
    cout<<temp2<<std::endl;
    cout << numberToWords((unsigned long int)temp2.get_dollar())<<numberToWords((unsigned long int)temp2.get_cent()) <<std::endl;

    cout<<temp<<" /= "<<temp1 <<" is : ";
    temp2 = temp;
    temp2/=temp1;
    cout<<temp2<<std::endl;
    cout << numberToWords((unsigned long int)temp2.get_dollar())<<numberToWords((unsigned long int)temp2.get_cent()) <<std::endl;

    cout<<temp<<" %= "<<temp1 <<" is : ";
    temp2 = temp;
    temp2%=temp1;
    cout<<temp2<<std::endl;
    cout << numberToWords((unsigned long int)temp2.get_dollar())<<numberToWords((unsigned long int)temp2.get_cent()) <<std::endl;

    FixedPoint< short > mySalary(120,35,3);
    cout <<"mySalary : "<< mySalary<<std::endl;
    FixedPoint< long > myOverdraft(99999,99,3);
    cout<<"myOverdraft : "<< myOverdraft << std::endl;
    cout << numberToWords((unsigned long int)myOverdraft.get_dollar())<<std::endl;

    FixedPoint<long> usaSelfDebt(145800000000000);
    myOverdraft += usaSelfDebt;
    cout<< "usaSelfDebt : "<< usaSelfDebt << std::endl;
    cout<<"myOverdraft : "<< myOverdraft << std::endl;
    /*myOverdraft = mySalary;*/
    myOverdraft = usaSelfDebt;

}
