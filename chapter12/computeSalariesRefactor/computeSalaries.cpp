#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <functional>
#include "computeSalaries.h"

using namespace std;

int main(){
    string id;
    string employee_id;
    string first_name;
    string last_name;
    string seniority_level;
    string position;
    string years_worked_continuously;
    string special_bonus_level;

    ifstream employeesFile("./Employees.csv");
    while (getline(employeesFile, id, ',')) {
        getline(employeesFile, employee_id, ',') ;
        getline(employeesFile, first_name, ',') ;
        getline(employeesFile, last_name, ',') ;
        getline(employeesFile, seniority_level, ',') ;
        getline(employeesFile, position, ',') ;
        getline(employeesFile, years_worked_continuously, ',') ;
        getline(employeesFile, special_bonus_level);
        if(id == "id") continue;

        auto bonusFactor = bind(specialBonusFactor, [&](){ return bonusLevel(special_bonus_level); } );
        auto roundedSalary = computeSalary(
                bind(baseSalaryForPosition, position), 
                bind(factorForSeniority, seniority_level),
                bind(factorForContinuity, years_worked_continuously),
                bonusFactor
            );

        cout  << seniority_level << position << " " << first_name << " " << last_name << " (" << years_worked_continuously << "yrs)" <<  ", " << employee_id << ", has salary (bonus level  " << special_bonus_level << ") " << roundedSalary << endl;
    }
}
