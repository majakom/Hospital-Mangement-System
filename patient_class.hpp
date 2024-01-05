/* Header file for subclass Patient*/
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "person_class.hpp"                 //including header file of class Person
#include "doctor_class.hpp"                 //including header file of subclass Doctor

class Patient: public Person {
    private:
        int yourId;
        std::vector<int> indexBeds;
    public:
        Patient();
        ~Patient();
        void ShowMyData();
        void StartingMenuPatient();
        void ManageDoctor();
        void RegisterPatient();
        void SaveObjectToJson();
        void LogIn() override;              //overriding method from class Person
        void BookBeds();
};