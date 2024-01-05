#include <iostream>
#include <fstream>
#include "hospital_class.hpp"
#include "beds_class.hpp"
#include "json.hpp"
#include "person_class.hpp"
#include "patient_class.hpp"
#include "doctor_class.hpp"
#include "admin_class.hpp"
using json = nlohmann::json;

Hospital::Hospital(){}
Hospital::~Hospital(){}

Beds beds1;
Patient patient4;
Doctor doctor4;

void ClearHospitalTerminal();

void ClearHospitalTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    return;
}

void Hospital::AddHospital(){
    this->indexBeds.clear();
    this->indexDoctors.clear();
    this->indexPatients.clear();
    this->address.clear();
    std::ifstream file("HospitalData.json");
    nlohmann::json oldHospitalData;
    if (file.is_open()) {
        file >> oldHospitalData;
        file.close();
    }
    int id = oldHospitalData.size();
    std::cout<<"2"<<std::endl;
    this->SetId(id);
    int choice;
    while(true){
        ClearHospitalTerminal();
        std::cout<<"(0) Add name of the hospital"<<std::endl;
        std::cout<<"(1) Add address of the hospital"<<std::endl;
        std::cout<<"(2) Add all doctors"<<std::endl;
        std::cout<<"(3) Add all patients"<<std::endl;
        std::cout<<"(4) Add all beds"<<std::endl;
        std::cout<<"(5) Confirm and return"<<std::endl;
        std::cin>>choice;
        switch(choice){
            case 0:
                this->SetName();
                break;
            case 1:
                this->SetAddress();
                break;
            case 2:
                this->AddAllDoctors();
                break;
            case 3:
                this->AddAllPatients();
                break;
            case 4:
                id = beds1.AddBed(this->id);
                this->indexBeds.push_back(id);
                break;
            case 5:
                this->UpdateData();
                return;
        }
    }
}

void Hospital::SetName(){
    std::cout<<"Enter the name of the hospital: "<<std::endl;
    std::cin>>this->name;
}

void Hospital::SetAddress() {
    int choice;
    std::string country, city, street, number;
    std::vector<std::string> setAddress (4);
    while(true){
        ClearHospitalTerminal();
        std::cout<<"(0) Country"<<std::endl;
        std::cout<<"(1) City/town/village"<<std::endl;
        std::cout<<"(2) Street"<<std::endl;
        std::cout<<"(3) Buildings number"<<std::endl;
        std::cout<<"(4) Confirm and continue"<<std::endl;
        std::cin>>choice;
        switch (choice)
        {
            case 0:
                std::cin>>country;
                setAddress[0] = country;
                break;
            case 1:
                std::cin>>city;
                setAddress[1] = city;
                break;
            case 2:
                std::cin>>street;
                setAddress[2] = street;
                break;
            case 3:
                std::cin>>number;
                setAddress[3] = number;
                break;
            case 4:
                this->address = setAddress;
                return;
        }
    }
}

void Hospital::SetId(int id){
    this->id = id;
    return;
}

void Hospital::UpdateData(){
    std::ifstream file("HospitalData.json");
    nlohmann::json oldHospitalData;
    if (file.is_open()) {
        file >> oldHospitalData;
        file.close();
    }
    std::ofstream outFile("HospitalData.json");
    nlohmann::json HospitalData;
    int id = oldHospitalData.size();
    this->SetId(id);
    HospitalData["id"] = this->id;
    HospitalData["name"] = this->name;
    HospitalData["address"] = this->address;
    HospitalData["indexBeds"] = this->indexBeds;
    HospitalData["indexPatients"] = this->indexPatients;
    HospitalData["indexDoctors"] = this->indexDoctors;
    oldHospitalData.push_back(HospitalData);
    outFile<<oldHospitalData<<std::endl;
    file.close();
    outFile.close();
    return;                
}

void Hospital::ShowAllHospitals() {
    int choice, ret;
    std::ifstream file("HospitalData.json");
    nlohmann::json HospitalData;
    file >> HospitalData;
    while(true){
        ClearHospitalTerminal();
        for(int i = 0; i<HospitalData.size(); i++) {
            std::cout<<HospitalData[i]["id"].get<int>()<<" - "<<HospitalData[i]["name"].get<std::string>()<<std::endl;
        }
        std::cout<<"-----------------------"<<std::endl;
        std::cout<<"Enter the id of hospital to check details"<<std::endl;
        std::cin>>choice;
        ClearHospitalTerminal();
        std::cout<<HospitalData[choice]["id"].get<int>()<<" - "<<HospitalData[choice]["name"].get<std::string>()<<std::endl;
        for(int i = 0; i<HospitalData[choice]["address"].size(); i++){
            std::cout<<HospitalData[choice]["address"][i].get<std::string>()<<" ";
        }
        std::cout<<std::endl;
        std::cout<<"Enter (-1) to return"<<std::endl;
        std::cin>>ret;
        if( ret == -1) {
            return;
        }
    }
}

void Hospital::AddAllPatients() {
    int choice;
    std::ifstream file("PatientData.json");
    nlohmann::json PatientData;
    file >> PatientData;
    while(true) {
        ClearHospitalTerminal();
        for(int i = 0; i<PatientData.size(); i++) {
            std::cout<<PatientData[i]["id"].get<int>()<<" - "<<PatientData[i]["name"].get<std::string>()<<" "<<PatientData[i]["surname"].get<std::string>();
        }
        std::cout<<"-----------------------"<<std::endl;
        std::cout<<"Enter the id of the patient to add to the list or (-1) return to save: "<<std::endl;
        std::cin>>choice;
        if(choice == -1) {
            return;
        } else {
            this->indexPatients.push_back(PatientData[choice]["id"].get<int>());
        }

    }

    return;
}

void Hospital::AddAllDoctors() {
    int choice;
    float averageRating;
    std::ifstream file("DoctorData.json");
    nlohmann::json DoctorData;
    file >> DoctorData;
    while(true) {
        ClearHospitalTerminal();
        for(int i = 0; i<DoctorData.size(); i++) {
            std::cout<<DoctorData[i]["id"].get<int>()<<" - "<<DoctorData[i]["name"].get<std::string>()<<" "<<DoctorData[i]["surname"].get<std::string>()<<" "<<DoctorData[i]["specialization"].get<std::string>()<<std::endl;
        }
        std::cout<<"-----------------------"<<std::endl;
        std::cout<<"Enter the id of doctor to add to the list or (-1) return to save: "<<std::endl;
        std::cin>>choice;
        if(choice == -1) {
            return;
        } else {
            this->indexDoctors.push_back(DoctorData[choice]["id"].get<int>());
        }

    }
}