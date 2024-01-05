/* A header file for a Beds class */
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Beds {
    private:
        int id;
        int isAvailable;
        int hospitalIndex;
    public:
        Beds();
        ~Beds();
        void SetId(int id);
        void ShowAllAvailableBeds();
        void ShowAllMyBeds(std::vector<int> indexBeds);
        int GetId();
        int AddBed(int hospitalIndex);
};

