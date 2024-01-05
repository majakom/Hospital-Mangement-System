#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "person_class.hpp"

class Doctor: public Person {
    private:
        std::string jobName;
        std::vector<int> indexPatient;
        std::vector<float> rating;
    public:
        Doctor();
        ~Doctor();
        void RegisterDoctor();
        void StartingMenuDoctor();
        void ShowMyData();
        void SetJob();
        std::string GetJob();
        void SaveObjectToJson(std::vector<float> rating);
        void LogInDoctor();
        void ShowAllDoctors();
        void SortDoctorsByRating();
        float GetRating(std::vector<float> rating);
        void ShowAllMyPatients();
        void AddRating();
};