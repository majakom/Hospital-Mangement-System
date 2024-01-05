#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "person_class.hpp"

#include "json.hpp"
using json = nlohmann::json;

class Admin: public Person {
    public:
        Admin();
        ~Admin();
        void StartingMenuAdmin();
        void RegisterAdmin();
        void SaveObjectToJson();
        void RegisterPersonChoice();
        void LogInAdmin();
};

