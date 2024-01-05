/* A header file for Admin subclass */
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "person_class.hpp"             //including header file with a parent class Person

#include "json.hpp"                     //including single header for managing json files
using json = nlohmann::json;

class Admin: public Person {
    public:
        Admin();
        ~Admin();
        void StartingMenuAdmin();
        void RegisterAdmin();
        void SaveObjectToJson();
        void RegisterPersonChoice();
        void LogIn() override;          //overriding a method from parent class Person
};

