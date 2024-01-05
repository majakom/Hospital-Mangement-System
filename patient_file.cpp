#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <string>
#include "person_class.hpp"
#include "patient_class.hpp"
#include "doctor_class.hpp"
#include "beds_class.hpp"
#include "hospital_class.hpp"

Hospital hospital1;
Doctor doctor1;
Beds beds2;

#include "json.hpp"
using json = nlohmann::json;


Patient::Patient(){}
Patient::~Patient(){}

void ClearPatientTerminal();

void ClearPatientTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    return;
}

void Patient::LogInPatient() {
    int found = 0, object;
    std::string login, password;
    std::ifstream file("PatientData.json");
    nlohmann::json oldPatientData;
    if (file.is_open()) {
        oldPatientData = json::parse(file);
        file.close();
    }
    while (!found) {
        std::cout << "Enter your login:" << std::endl;
        std::cin >> login;
        std::cout << "Enter your password:" << std::endl;
        std::cin >> password;
        for (int i = 0; i < oldPatientData.size(); i++) {
            if (oldPatientData[i]["login"] == login &&
                oldPatientData[i]["password"] == password) {
                std::cout<<"found"<<std::endl;
                found = 1;
                object = i;
                break;
            }
        }
    }
    this->SetId(oldPatientData[object]["id"].get<int>());
    this->SetJustName(oldPatientData[object]["name"].get<std::string>());
    this->SetJustSurname(oldPatientData[object]["surname"].get<std::string>());
    this->SetJustLogin(oldPatientData[object]["login"].get<std::string>());
    this->SetJustPassword(oldPatientData[object]["password"].get<std::string>());
    this->SetJustAddress(oldPatientData[object]["address"].get<std::vector<std::string>>());
    this->SetJustEmail(oldPatientData[object]["email"].get<std::string>());
    this->SetJustPhoneNumber(oldPatientData[object]["phoneNumber"].get<int>());
    this->indexBeds = oldPatientData[object]["indexBeds"].get<std::vector<int>>();
    return;
}

void Patient::RegisterPatient() {
    int choice;
    while(true) {
        ClearPatientTerminal();
        std::cout<<"(0) Enter name"<<std::endl;
        std::cout<<"(1) Enter surname"<<std::endl;
        std::cout<<"(2) Enter phone number"<<std::endl;
        std::cout<<"(3) Enter email"<<std::endl;
        std::cout<<"(4) Enter address"<<std::endl;
        std::cout<<"(5) Enter login"<<std::endl;
        std::cout<<"(6) Enter password"<<std::endl;
        std::cout<<"(7) Confirm and continue"<<std::endl;
        std::cin>>choice;
        switch(choice) {
            case 0:
                this->SetName();
                break;
            case 1:
                this->SetSurname();
                break;
            case 2:
                this->SetPhoneNumber();
                break;
            case 3:
                this->SetEMail();
                break;
            case 4:
                this->SetAddress();
                break;
            case 5:
                this->SetLogin();
                break;
            case 6:
                this->SetPassword();
                break;
            case 7:
                this->SaveObjectToJson();          
                return;
        }
    }
    return;
}

void Patient::SaveObjectToJson(){
    std::ifstream file("PatientData.json");
    nlohmann::json oldPatientData;
    if (file.is_open()) {
        file >> oldPatientData;
        file.close();
    }
    std::ofstream outFile("PatientData.json");
    nlohmann::json PatientData;
    int id = oldPatientData.size();
    this->SetId(id);
    PatientData["id"] = id;
    PatientData["name"] = this->GetName();
    PatientData["surname"] = this->GetSurname();
    PatientData["email"] = this->GetEmail();
    PatientData["login"] = this->GetLogin();
    PatientData["password"] = this->GetPassword();
    PatientData["address"] = this->GetAddress();
    PatientData["phoneNumber"] = this->GetPhoneNumber();
    PatientData["indexBeds"] = this->indexBeds;
    oldPatientData.push_back(PatientData);
    outFile<<oldPatientData<<std::endl;
    file.close();
    outFile.close();
    return;
}

void Patient::StartingMenuPatient() {
    int choice;
    while(true) {
        ClearPatientTerminal();
        std::cout<<"(0) Show all hospitals"<<std::endl;
        std::cout<<"(1) Show all doctors"<<std::endl;
        std::cout<<"(2) Add rating for a doctor"<<std::endl;
        std::cout<<"(3) Book a bed"<<std::endl;
        std::cout<<"(4) Show my data"<<std::endl;
        std::cout<<"(5) Exit"<<std::endl;
        std::cin>>choice;
        switch(choice) {
            case 0:
                hospital1.ShowAllHospitals();
                break;
            case 1:
                this->ManageDoctor();
                break;
            case 2:
                doctor1.AddRating();
                break;
            case 3:
                this->BookBeds();
                break;
            case 4:
                this->ShowMyData();
                break;
            case 5:
                exit(0);
        }
    }
    return;
}

void Patient::BookBeds() {
    std::ifstream file("PatientData.json");
    nlohmann::json oldPatientData;
    if (file.is_open()) {
        file >> oldPatientData;
        file.close();
    }
    beds2.ShowAllAvailableBeds();
    this->indexBeds.push_back(beds2.GetId());
    for(int i = 0; i < oldPatientData.size(); i++) {
        if(oldPatientData[i]["id"] == this->GetId()){
            oldPatientData[i]["indexBeds"] = this->indexBeds;
        }
    }
    std::ofstream outFile("PatientData.json");
    outFile << oldPatientData;
    return;
}


void Patient::ShowMyData() {
    int ret;
    std::vector<std::string> addressTaken;
    while(true) {
        ClearPatientTerminal();
        std::cout<<this->GetName()<<" "<<this->GetSurname()<<std::endl;
        std::cout<<"-----------"<<std::endl;
        std::cout<<"Phone number: "<<this->GetPhoneNumber()<<std::endl;
        std::cout<<"Email: "<<this->GetEmail()<<std::endl;
        for(int i = 0; i < this->GetAddress().size(); i++){
            std::cout<<this->GetAddress()[i]<<" ";
        }
        std::cout<<"--------------------"<<std::endl;
        std::cout<<"All my beds: "<<std::endl;
        beds2.ShowAllMyBeds(this->indexBeds);
        std::cout<<"--------------------"<<std::endl;
        std::cout<<"Enter (-1) to return"<<std::endl;
        std::cin>>ret;
        if( ret == -1 ) {
            return;
        }  
    }
    
}


void Patient::ManageDoctor() {
    int choice;
    while(true) {
        ClearPatientTerminal();
        std::cout<<"(0) Sort doctors by rating"<<std::endl;
        std::cout<<"(1) Show all doctors"<<std::endl;
        std::cout<<"(2) Return"<<std::endl;
        std::cin>>choice;
        switch(choice){
            case 0:
                doctor1.SortDoctorsByRating();
                break;
            case 1:
                doctor1.ShowAllDoctors();
                break;
            case 2:
                return;
        }
    }

}


