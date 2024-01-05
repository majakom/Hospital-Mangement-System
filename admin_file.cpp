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
#include "admin_class.hpp"
#include "hospital_class.hpp"

#include "json.hpp"
using json = nlohmann::json;



Admin::Admin(){}
Admin::~Admin(){}

void ClearAdminTerminal();

void ClearAdminTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    return;
}

void Admin::LogInAdmin() {
    int found = 0, object;
    std::string login, password;
    std::ifstream file("AdminData.json");
    nlohmann::json oldAdminData;
    if (file.is_open()) {
        oldAdminData = json::parse(file);
        file.close();
    }
    while (!found) {
        ClearAdminTerminal();
        std::cout << "Enter your login:" << std::endl;
        std::cin >> login;
        std::cout << "Enter your password:" << std::endl;
        std::cin >> password;
        for (int i = 0; i < oldAdminData.size(); i++) {
            if (oldAdminData[i]["login"] == login &&
                oldAdminData[i]["password"] == password) {
                found = 1;
                object = i;
                break;
            }
        }
    }
    this->SetId(oldAdminData[object]["id"].get<int>());
    this->SetJustName(oldAdminData[object]["name"].get<std::string>());
    this->SetJustSurname(oldAdminData[object]["surname"].get<std::string>());
    this->SetJustLogin(oldAdminData[object]["login"].get<std::string>());
    this->SetJustPassword(oldAdminData[object]["password"].get<std::string>());
    return;
}

void Admin::RegisterPersonChoice() {
    Doctor doc;
    Patient pat;
    Admin adm;
    int choice;
    while(true) {
        ClearAdminTerminal();
        std::cout<<"Add a person:"<<std::endl;
        std::cout<<"(0) Doctor"<<std::endl;
        std::cout<<"(1) Admin"<<std::endl;
        std::cout<<"(2) Patient"<<std::endl;
        std::cout<<"(3) Return"<<std::endl;
        std::cin>>choice;
        switch(choice) {
            case 0:
                doc.RegisterDoctor();
                break;
            case 1:
                adm.RegisterAdmin();
                break;
            case 2:
                pat.RegisterPatient();
                break;
            case 3:
                return;
        }
    }
}

void Admin::StartingMenuAdmin() {
    Hospital hosp, hosp1;
    int choice;
    while(true) {
        ClearAdminTerminal();
        std::cout<<"(0) Add a hospital"<<std::endl;
        std::cout<<"(1) Add a person"<<std::endl;
        std::cout<<"(2) Exit"<<std::endl;
        std::cin>>choice;
        switch(choice) {
            case 0:
                hosp.AddHospital();
                break;
            case 1:
                this->RegisterPersonChoice();
                break;
            case 2:
                exit(0);
        }
    }
}



void Admin::RegisterAdmin(){
    int choice;
    while(true) {
        ClearAdminTerminal();
        std::cout<<"(0) Enter name"<<std::endl;
        std::cout<<"(1) Enter surname"<<std::endl;
        std::cout<<"(2) Enter login"<<std::endl;
        std::cout<<"(3) Enter password"<<std::endl;
        std::cout<<"(4) Confirm and continue"<<std::endl;
        std::cin>>choice;
        switch(choice) {
            case 0:
                this->SetName();
                std::cout<<this->GetName();
                break;
            case 1:
                this->SetSurname();
                std::cout<<this->GetSurname();
                break;
            case 2:
                this->SetLogin();
                std::cout<<this->GetLogin();
                break;
            case 3:
                this->SetPassword();
                std::cout<<this->GetPassword();
                break;
            case 4:
                this->SaveObjectToJson();          
                return;
        }
    }
    return;
}

void Admin::SaveObjectToJson() {
    std::ifstream file("AdminData.json");
    nlohmann::json oldAdminData;
    if (file.is_open()) {
        file >> oldAdminData;
        file.close();
    }
    std::ofstream outFile("AdminData.json");
    nlohmann::json AdminData;
    int id = oldAdminData.size();
    std::cout<<id;
    this->SetId(id);
    AdminData["id"] = id;
    AdminData["login"] = this->GetLogin();
    AdminData["name"] = this->GetName();
    AdminData["password"] = this->GetPassword();
    AdminData["surname"] = this->GetSurname();
    oldAdminData.push_back(AdminData);
    outFile<<oldAdminData<<std::endl;
    file.close();
    outFile.close();
    return;
}