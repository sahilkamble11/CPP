# include <iostream>
# include <string>  
# include "../include/employee.h"
#include"../include/SalesEmployee.h"

int main() {
   
    //string name1="Sahil";
    //string name2="";
    // Employee emp1(101, name1, 75000.0);
    // Employee emp2(102, name2, 85000.0);

    // emp1.displayInfo();
    // emp2.displayInfo();

    salesEmployee semp(1,"Sahil",80000,50000,3000);
    semp.displayInfo();

    return 0;
}   