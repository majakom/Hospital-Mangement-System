#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "person_class.hpp"
#include "doctor_class.hpp"

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
        void LogInPatient();
        void BookBeds();
};