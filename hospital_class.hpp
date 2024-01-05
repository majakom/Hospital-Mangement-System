/* A header file for Hospital class */
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

class Hospital{
    private:
        std::vector<int> indexDoctors;
        std::vector<int> indexBeds;
        std::vector<int> indexPatients;
        std::vector<std::string> address;   
        std::string name; 
        int id;
    public:
        Hospital();
        ~Hospital();
        void AddHospital();
        void SetName();
        void SetAddress();
        void UpdateData();
        void SetId(int id);
        void ShowAllHospitals();
        void AddAllPatients();
        void AddAllDoctors();
};