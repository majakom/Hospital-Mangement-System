/*A cpp file to manage declarations of methods from subclass Admin*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <string>
#include "person_class.hpp"             //including header for class Person
#include "patient_class.hpp"            //including header for subclass Patient
#include "doctor_class.hpp"             //including header for subclass Doctor
#include "beds_class.hpp"               //including header for class Beds
#include "admin_class.hpp"              //including header for subclass Admin
#include "hospital_class.hpp"           //including header for class Hospital

#include "json.hpp"                     //single header for json files
using json = nlohmann::json;



Admin::Admin(){}
Admin::~Admin(){}

void ClearAdminTerminal();              //declaration of function to clear terminal for windows or linux

void ClearAdminTerminal() {             //function to clear terminal for windows or linux
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    return;
}

void Admin::LogIn() {                                       //overrided method from class Person which allows Admin to log in
    int found = 0, object;
    std::string login, password;
    std::ifstream file("AdminData.json");                   //opens AdminData.json file to download data about all admins in the system
    nlohmann::json oldAdminData;
    if (file.is_open()) {
        oldAdminData = json::parse(file);
        file.close();
    }
    while (!found) {
        ClearAdminTerminal();                               //chcecks password and login inputted untill an object from json is found with exactly the same login and password
        std::cout << "Enter your login:" << std::endl;
        std::cin >> login;
        std::cout << "Enter your password:" << std::endl;
        std::cin >> password;
        for (int i = 0; i < oldAdminData.size(); i++) {
            if (oldAdminData[i]["login"] == login &&       //checks if login and password are the same as an object form json
                oldAdminData[i]["password"] == password) {
                found = 1;
                object = i;
                break;
            }
        }
    }
    this->SetId(oldAdminData[object]["id"].get<int>());                                         //if a correct object from json file is found an details about this Admin are set by setters
    this->SetJustName(oldAdminData[object]["name"].get<std::string>());
    this->SetJustSurname(oldAdminData[object]["surname"].get<std::string>());
    this->SetJustLogin(oldAdminData[object]["login"].get<std::string>());
    this->SetJustPassword(oldAdminData[object]["password"].get<std::string>());
    return;
}

void Admin::RegisterPersonChoice() {                                                            //method used to enable admin to register anybody into the system
    Doctor doc;
    Patient pat;
    Admin adm;
    int choice;
    while(true) {
        ClearAdminTerminal();
        std::cout<<"Add a person:"<<std::endl;                                                  //enables choice who to register
        std::cout<<"(0) Doctor"<<std::endl;
        std::cout<<"(1) Admin"<<std::endl;
        std::cout<<"(2) Patient"<<std::endl;
        std::cout<<"(3) Return"<<std::endl;
        std::cin>>choice;
        switch(choice) {
            case 0:
                doc.RegisterDoctor();                                                          //calls a method from subclass Doctor which allows to register a new Doctor
                break;
            case 1:
                adm.RegisterAdmin();                                                            //calls a method from subclass Admin which allows to register a new Admin
                break;
            case 2:
                pat.RegisterPatient();                                                          //calss a method from subclass Patient which allows to register a new Patient
                break;  
            case 3:
                return;
        }
    }
}

void Admin::StartingMenuAdmin() {                                                           //method which allows choice of actions to be made by admin
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
                hosp.AddHospital();                                                         //calls a method from class Hospital which enables to add to the system a new hospital
                break;
            case 1:
                this->RegisterPersonChoice();                                               //calls a method from subclass Admin which enables choice of who to register
                break;
            case 2:
                exit(0);
        }
    }
}



void Admin::RegisterAdmin(){                                                                 //method from subclass Admin which enables to register a new admin in the system
    int choice;
    while(true) {
        ClearAdminTerminal();
        std::cout<<"(0) Enter name"<<std::endl;                                              //enables choice of which data should be saved about admin first
        std::cout<<"(1) Enter surname"<<std::endl;
        std::cout<<"(2) Enter login"<<std::endl;
        std::cout<<"(3) Enter password"<<std::endl;
        std::cout<<"(4) Confirm and continue"<<std::endl;
        std::cin>>choice;
        switch(choice) {
            case 0:
                this->SetName();                                                            //setter for a name from parent class Person
                break;
            case 1:
                this->SetSurname();                                                         //setter for a surname from parent class Person
                break;
            case 2:
                this->SetLogin();                                                           //setter for a login from parent class Person
                break;
            case 3:
                this->SetPassword();                                                        //setter for a password from parent class Person
                break;
            case 4:
                this->SaveObjectToJson();                                                   //saves new admin data to a json file AdminData.json
                return;
        }
    }
    return;
}

void Admin::SaveObjectToJson() {                                                            //saves new admin data to a json file AdminData.json
    std::ifstream file("AdminData.json");
    nlohmann::json oldAdminData;                                                            //opens and downloads all data from a json
    if (file.is_open()) {
        file >> oldAdminData;
        file.close();
    }
    std::ofstream outFile("AdminData.json");
    nlohmann::json AdminData;
    int id = oldAdminData.size();
    this->SetId(id);                                                                        //sets id for a newly created object from  subclass admin
    AdminData["id"] = id;
    AdminData["login"] = this->GetLogin();                                                  //saves all data of an admin as a json object
    AdminData["name"] = this->GetName();
    AdminData["password"] = this->GetPassword();
    AdminData["surname"] = this->GetSurname();
    oldAdminData.push_back(AdminData);                                                      //merges old admins with new one and uploads into a json file
    outFile<<oldAdminData<<std::endl;
    file.close();
    outFile.close();
    return;
}