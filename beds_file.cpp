/* A cpp file with declarations of methods in Beds class */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <string>
#include <algorithm>
#include "beds_class.hpp"               //including header with Beds class

#include "json.hpp"                     //including single header for managing json files
using json = nlohmann::json;

Beds::Beds(){}
Beds::~Beds(){}

void ClearBedsTerminal();               //declaration of function which clears terminal for windows and linux

void ClearBedsTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    return;
}

void Beds::ShowAllMyBeds(std::vector<int> indexBeds) {                      //method which shows all Beds booked by a certain patient
    std::string name;
    std::ifstream file("BedsData.json");                                    //opens json BedsData.json an loads its content
    nlohmann::json BedsData;
    file >> BedsData;
    std::ifstream newFile("HospitalData.json");                             //opens json HospitalData.json and loads its contents
    nlohmann::json HospitalData;
    newFile >> HospitalData;
    ClearBedsTerminal();
    for(int i = 0; i < BedsData.size(); i++) {                              //for each Bed loaded from json a hospital name where it is being kept is found
        for (int j = 0; j < HospitalData.size(); j++) {
            if (HospitalData[j]["id"] == BedsData[i]["hospitalIndex"]) {
                name = HospitalData[j]["name"];
            }
        }
        for(int j = 0; j < indexBeds.size(); j++) {                                                 //checks if bed has the same id as beds from patients vector, where all booked beds ids are stored
            if(BedsData[i]["id"].get<int>() == indexBeds[j]){
                std::cout<<BedsData[i]["id"].get<int>()<<" - You booked in: "<<name<<std::endl;     //displays booked beds and names of hospitals they are booked in
            }

        }
    }
    return;
}

void Beds::ShowAllAvailableBeds() {                                                         //method shows all available to book beds in the systems
    int choice;
    std::string name;
    std::ifstream file("BedsData.json");                                                    //loads data about all beds from json file
    nlohmann::json BedsData;
    file >> BedsData;
    std::ifstream newFile("HospitalData.json");                                             //loads data about all hospitals from a json file
    nlohmann::json HospitalData;
    newFile >> HospitalData;
    ClearBedsTerminal();
    for(int i = 0; i < BedsData.size(); i++) {                                              //gets names of all hospitals that are having available for booking beds
        for (int j = 0; j < HospitalData.size(); j++) {
            if (HospitalData[j]["id"] == BedsData[i]["hospitalIndex"]) {
                name = HospitalData[j]["name"];
            }
        }
        if(!BedsData[i]["available"].get<int>()){                                                   //if bed is not booked it is being displayed with its id and the name of the hospital they are in
            std::cout<<BedsData[i]["id"].get<int>()<<" - You can book in: "<<name<<std::endl;
        }
    }
    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"Enter index of the bed you want to book: "<<std::endl;                              //user can choose which bed to book by giving its index
    std::cin>>choice;
    this->SetId(BedsData[choice]["id"].get<int>());
    BedsData[choice]["available"] = 1;                                                              //changing availabiltiy of the chosen bed
    std::ofstream outFile("BedsData.json");                                                         //updating data about beds in json file
    outFile << BedsData;
    return;
}


void Beds::SetId(int id){           //Id setter for a bed
    this->id = id;
    return;
}
int Beds::GetId() {                 //Id getter for a bed
    return this->id;
}
int Beds::AddBed(int hospitalIndex) {                               //Method used to create new beds while adding new hospital to the database
    this->isAvailable = 0;
    std::ifstream file("BedsData.json");                            //reading and loading json file with beds data
    nlohmann::json oldBedsData;
    if (file.is_open()) {
        file >> oldBedsData;
        file.close();
    }
    std::ofstream outFile("BedsData.json");                         //opening BedsData.json to writing mode
    nlohmann::json BedsData;
    int id = oldBedsData.size();
    this->SetId(id);                                                //setting id of a newly added bed based on the length of contents of json BedsData
    this->hospitalIndex = hospitalIndex;
    BedsData["id"] = id;                                            //creating new json object by adding data about beds: hospitalIndex - where the bed is; its availability to book and its id
    BedsData["available"] = this->isAvailable;
    BedsData["hospitalIndex"] = hospitalIndex;
    oldBedsData.push_back(BedsData);                                //merging new data bed with old data about previously created beds
    outFile<<oldBedsData<<std::endl;
    file.close();
    outFile.close();
    return this->id;                                                //returning the id of the bed (while adding hospital it is used to update all indexes of Beds in a certain hospital)
}