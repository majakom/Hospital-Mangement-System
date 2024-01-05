#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <string>
#include <algorithm>
#include "beds_class.hpp"

#include "json.hpp"
using json = nlohmann::json;

Beds::Beds(){}
Beds::~Beds(){}

void ClearBedsTerminal();

void ClearBedsTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    return;
}

void Beds::ShowAllMyBeds(std::vector<int> indexBeds) {
    std::string name;
    std::ifstream file("BedsData.json");
    nlohmann::json BedsData;
    file >> BedsData;
    std::ifstream newFile("HospitalData.json");
    nlohmann::json HospitalData;
    newFile >> HospitalData;
    ClearBedsTerminal();
    for(int i = 0; i < BedsData.size(); i++) {
        for (int j = 0; j < HospitalData.size(); j++) {
            if (HospitalData[j]["id"] == BedsData[i]["hospitalIndex"]) {
                name = HospitalData[j]["name"];
            }
        }
        for(int j = 0; j < indexBeds.size(); j++) {
            if(BedsData[i]["id"].get<int>() == indexBeds[j]){
                std::cout<<BedsData[i]["id"].get<int>()<<" - You booked in: "<<name<<std::endl;
            }

        }
    }
    return;
}

void Beds::ShowAllAvailableBeds() {
    int choice;
    std::string name;
    std::ifstream file("BedsData.json");
    nlohmann::json BedsData;
    file >> BedsData;
    std::ifstream newFile("HospitalData.json");
    nlohmann::json HospitalData;
    newFile >> HospitalData;
    ClearBedsTerminal();
    for(int i = 0; i < BedsData.size(); i++) {
        for (int j = 0; j < HospitalData.size(); j++) {
            if (HospitalData[j]["id"] == BedsData[i]["hospitalIndex"]) {
                name = HospitalData[j]["name"];
            }
        }
        if(!BedsData[i]["available"].get<int>()){
            std::cout<<BedsData[i]["id"].get<int>()<<" - You can book in: "<<name<<std::endl;
        }
    }
    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"Enter index of the bed you want to book: "<<std::endl;
    std::cin>>choice;
    this->SetId(BedsData[choice]["id"].get<int>());
    BedsData[choice]["available"] = 1;
    std::ofstream outFile("BedsData.json");
    outFile << BedsData;
    return;
}


void Beds::SetId(int id){
    this->id = id;
    return;
}
int Beds::GetId() {
    return this->id;
}
int Beds::AddBed(int hospitalIndex) {
    this->isAvailable = 0;
    std::ifstream file("BedsData.json");
    nlohmann::json oldBedsData;
    if (file.is_open()) {
        file >> oldBedsData;
        file.close();
    }
    std::ofstream outFile("BedsData.json");
    nlohmann::json BedsData;
    int id = oldBedsData.size();
    this->SetId(id);
    this->hospitalIndex = hospitalIndex;
    BedsData["id"] = id;
    BedsData["available"] = this->isAvailable;
    BedsData["hospitalIndex"] = hospitalIndex;
    oldBedsData.push_back(BedsData);
    outFile<<oldBedsData<<std::endl;
    file.close();
    outFile.close();
    return this->id;   
}