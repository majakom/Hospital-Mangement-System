#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <string>
#include "person_class.hpp"
#include "doctor_class.hpp"
#include "hospital_class.hpp"

#include "json.hpp"
using json = nlohmann::json;

Hospital hospital2;

Doctor::Doctor(){}
Doctor::~Doctor(){}

void ClearDoctorTerminal();

void ClearDoctorTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    return;
}


void Doctor::SetJob() {
    std::cout<<"Enter your job: "<<std::endl;
    std::cin>>this->jobName;
}

std::string Doctor::GetJob() {
    return this->jobName;
}

float Doctor::GetRating(std::vector<float> rating) {
    float sum, averageRating;
    for(int i = 0; i<rating.size(); i++) {
        sum+=rating[i];
    }
    averageRating = sum/(rating.size());
    if (averageRating<= 0.1) {
        averageRating = 0.0;
    }
    return averageRating;
}

void Doctor::RegisterDoctor() {
    int choice;
    std::vector<float> rating;
    while(true) {
        ClearDoctorTerminal();
        std::cout<<"(0) Enter name"<<std::endl;
        std::cout<<"(1) Enter surname"<<std::endl;
        std::cout<<"(2) Enter phone number"<<std::endl;
        std::cout<<"(3) Enter email"<<std::endl;
        std::cout<<"(4) Enter specialization"<<std::endl;
        std::cout<<"(5) Enter address"<<std::endl;
        std::cout<<"(6) Enter login"<<std::endl;
        std::cout<<"(7) Enter password"<<std::endl;
        std::cout<<"(8) Confirm and continue"<<std::endl;
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
                this->SetJob();
                break;
            case 5:
                this->SetAddress();
                break;
            case 6:
                this->SetLogin();
                break;
            case 7:
                this->SetPassword();
                break;
            case 8:
                this->SaveObjectToJson(rating);          
                return;
        }
    }
    return;
}

void Doctor::SaveObjectToJson(std::vector<float> rating){
    std::ifstream file("DoctorData.json");
    nlohmann::json oldDoctorData;
    if (file.is_open()) {
        file >> oldDoctorData;
        file.close();
    }
    std::ofstream outFile("DoctorData.json");
    nlohmann::json DoctorData;
    int id = oldDoctorData.size();
    std::cout<<id;
    this->SetId(id);
    DoctorData["id"] = id;
    DoctorData["name"] = this->GetName();
    DoctorData["surname"] = this->GetSurname();
    DoctorData["email"] = this->GetEmail();
    DoctorData["login"] = this->GetLogin();
    DoctorData["password"] = this->GetPassword();
    DoctorData["specialization"] = this->GetJob();
    DoctorData["address"] = this->GetAddress();
    DoctorData["phoneNumber"] = this->GetPhoneNumber();
    DoctorData["patientsIndex"] = this->indexPatient;
    DoctorData["rating"] = rating;
    oldDoctorData.push_back(DoctorData);
    outFile<<oldDoctorData<<std::endl;
    file.close();
    outFile.close();
    return;
}

void Doctor::StartingMenuDoctor() {
    int choice;
    while(true) {
        ClearDoctorTerminal();
        std::cout<<"(0) Show all hospitals"<<std::endl;
        std::cout<<"(1) Show all your patients"<<std::endl;
        std::cout<<"(2) Show your data"<<std::endl;
        std::cout<<"(3) Exit"<<std::endl;
        std::cin>>choice;
        switch(choice) {
            case 0:
                hospital2.ShowAllHospitals();
                break;
            case 1:
                this->ShowAllMyPatients();
                break;
            case 2:
                this->ShowMyData();
                break;
            case 3:
                exit(0);
        }
    }
    return;
}

void Doctor::ShowMyData() {
    int ret;
    float averageRating;
    std::vector<std::string> addressTaken;
    averageRating = this->GetRating(this->rating);
    while(true) {
        ClearDoctorTerminal();
        std::cout<<this->GetJob()<<std::endl;
        std::cout<<this->GetName()<<" "<<this->GetSurname()<<std::endl;
        std::cout<<"-----------"<<std::endl;
        std::cout<<this->GetPhoneNumber()<<std::endl;
        std::cout<<this->GetEmail()<<std::endl;
        for(int i = 0; i < this->GetAddress().size(); i++){
            std::cout<<this->GetAddress()[i]<<" ";
        }
        std::cout<<"-----------"<<std::endl;
        std::cout<<"Your rating: "<<averageRating<<std::endl;
        std::cout<<"Enter (-1) to return: "<<std::endl;
        std::cin>>ret;
        if(ret == -1){
            return;  
        }
    }  
}


void Doctor::LogInDoctor(){
    int found = 0, object;
    std::string login, password;
    std::ifstream file("DoctorData.json");
    nlohmann::json oldDoctorData;
    if (file.is_open()) {
        oldDoctorData = json::parse(file);
        file.close();
    }
    while (!found) {
        std::cout << "Enter your login:" << std::endl;
        std::cin >> login;
        std::cout << "Enter your password:" << std::endl;
        std::cin >> password;
        for (int i = 0; i < oldDoctorData.size(); i++) {
            if (oldDoctorData[i]["login"] == login &&
                oldDoctorData[i]["password"] == password) {
                std::cout<<"found"<<std::endl;
                found = 1;
                object = i;
                break;
            }
        }
    }
    this->SetId(oldDoctorData[object]["id"].get<int>());
    this->SetJustName(oldDoctorData[object]["name"].get<std::string>());
    this->SetJustSurname(oldDoctorData[object]["surname"].get<std::string>());
    this->SetJustLogin(oldDoctorData[object]["login"].get<std::string>());
    this->SetJustPassword(oldDoctorData[object]["password"].get<std::string>());
    this->SetJustAddress(oldDoctorData[object]["address"].get<std::vector<std::string>>());
    this->SetJustEmail(oldDoctorData[object]["email"].get<std::string>());
    this->SetJustPhoneNumber(oldDoctorData[object]["phoneNumber"].get<int>());
    this->indexPatient = oldDoctorData[object]["patientsIndex"].get<std::vector<int>>();
    this->rating = oldDoctorData[object]["rating"].get<std::vector<float>>();
    this->jobName = oldDoctorData[object]["specialization"].get<std::string>();
    return;
}

void Doctor::ShowAllDoctors() {
    int choice, ret;
    float averageRating;
    std::ifstream file("DoctorData.json");
    nlohmann::json DoctorData;
    file >> DoctorData;
    while(true) {
        ClearDoctorTerminal();
        for(int i = 0; i<DoctorData.size(); i++) {
            std::cout<<DoctorData[i]["id"].get<int>()<<" - "<<DoctorData[i]["name"].get<std::string>()<<" "<<DoctorData[i]["surname"].get<std::string>()<<" "<<DoctorData[i]["specialization"].get<std::string>()<<std::endl;
        }
        std::cout<<"-----------------------"<<std::endl;
        std::cout<<"Enter the id of doctor to check details"<<std::endl;
        std::cin>>choice;
        ClearDoctorTerminal();
        averageRating = this->GetRating(DoctorData[choice]["rating"].get<std::vector<float>>());
        std::cout<<DoctorData[choice]["id"].get<int>()<<" - "<<DoctorData[choice]["name"].get<std::string>()<<" "<<DoctorData[choice]["surname"].get<std::string>()<<" "<<DoctorData[choice]["specialization"].get<std::string>()<<std::endl;
        std::cout<<"Rating: "<<averageRating<<std::endl;
        std::cout<<"Contact: "<<std::endl;
        std::cout<<DoctorData[choice]["phoneNumber"].get<int>()<<std::endl;
        std::cout<<DoctorData[choice]["email"].get<std::string>()<<std::endl;
        for(int i = 0; i<DoctorData[choice]["address"].size(); i++){
            std::cout<<DoctorData[choice]["address"][i].get<std::string>()<<" ";
        }
        std::cout<<"Enter (-1) to return: "<<std::endl;
        std::cin>>ret;
        if (ret == -1) {
            return;
        }
    }
    
}
bool CompareDoctorsByRating(const nlohmann::json& doctor1, const nlohmann::json& doctor2) {
    Doctor d1, d2; 
    float rating1 = d1.GetRating(doctor1["rating"].get<std::vector<float>>());
    float rating2 = d2.GetRating(doctor2["rating"].get<std::vector<float>>());
    return rating1 > rating2;
}
void Doctor::SortDoctorsByRating() {
    float averageRating;
    int ret;
    std::ifstream file("DoctorData.json");
    nlohmann::json DoctorData;
    file >> DoctorData;

    std::sort(DoctorData.begin(), DoctorData.end(), CompareDoctorsByRating);
    
    while(true) {
        ClearDoctorTerminal();
        for (int i = 0; i < DoctorData.size(); i++) {
            float averageRating = this->GetRating(DoctorData[i]["rating"].get<std::vector<float>>());
            std::cout << i << " - Rating: " << averageRating << " - "
                    << DoctorData[i]["name"].get<std::string>() << " " << DoctorData[i]["surname"].get<std::string>()
                    << " " << DoctorData[i]["specialization"].get<std::string>() << std::endl;
        }
        std::cout<<"Enter (-1) to return: "<<std::endl;
        std::cin>>ret;
        if (ret == -1) {
            return;
        }
    }
}

void Doctor::ShowAllMyPatients(){
    int choice, ret;
    float averageRating;
    std::ifstream file("PatientData.json");
    nlohmann::json PatientData;
    file >> PatientData;
    while(true){
        ClearDoctorTerminal();
        for(int i = 0; i<PatientData.size(); i++) {
            std::cout<<PatientData[i]["id"].get<int>()<<" - "<<PatientData[i]["name"].get<std::string>()<<" "<<PatientData[i]["surname"].get<std::string>()<<std::endl;
        }
        std::cout<<"-----------------------"<<std::endl;
        std::cout<<"Enter the id of the patient to check details"<<std::endl;
        std::cin>>choice;
        ClearDoctorTerminal();
        std::cout<<PatientData[choice]["id"].get<int>()<<" - "<<PatientData[choice]["name"].get<std::string>()<<" "<<PatientData[choice]["surname"].get<std::string>()<<std::endl;
        std::cout<<"Contact: "<<std::endl;
        std::cout<<PatientData[choice]["phoneNumber"].get<int>()<<std::endl;
        std::cout<<PatientData[choice]["email"].get<std::string>()<<std::endl;
        for(int i = 0; i<PatientData[choice]["address"].size(); i++){
            std::cout<<PatientData[choice]["address"][i].get<std::string>()<<" ";
        }
        std::cout<<"Enter (-1) to return: "<<std::endl;
        std::cin>>ret;
        if (ret == -1) {
            return;
        }
    }
}

void Doctor::AddRating() {
    int choice, ret;
    float averageRating, rating, sum;
    std::vector<float> allRatings;
    std::ifstream file("DoctorData.json");
    nlohmann::json DoctorData;
    file >> DoctorData;
    ClearDoctorTerminal();
    for(int i = 0; i<DoctorData.size(); i++) {
        averageRating = GetRating(DoctorData[i]["rating"]);
        std::cout<<DoctorData[i]["id"].get<int>()<<" - Rating: "<<averageRating<<" "<<DoctorData[i]["name"].get<std::string>()<<" "<<DoctorData[i]["surname"].get<std::string>()<<" "<<DoctorData[i]["specialization"].get<std::string>()<<std::endl;
    }
    std::cout<<"-----------------------"<<std::endl;
    std::cout<<"Enter the id of doctor to enter rating: "<<std::endl;
    std::cin>>choice;
    std::cout<<"Enter your rating: "<<std::endl;
    std::cin>>rating;
    allRatings = DoctorData[choice]["rating"].get<std::vector<float>>();
    allRatings.push_back(rating);
    for(int i = 0; i < allRatings.size() ; i++) {
        sum += allRatings[i];
    }
    std::cout<<"New data: "<<std::endl;
    averageRating = sum/allRatings.size();
    ClearDoctorTerminal();
    DoctorData[choice]["rating"] = allRatings;
    std::ofstream outFile("DoctorData.json");
    outFile << DoctorData;
    while(true) {
        std::cout<<DoctorData[choice]["id"].get<int>()<<" - Rating: "<<averageRating<<" "<<DoctorData[choice]["name"].get<std::string>()<<" "<<DoctorData[choice]["surname"].get<std::string>()<<" "<<DoctorData[choice]["specialization"].get<std::string>()<<std::endl;
        std::cout<<"Enter (-1) to return: "<<std::endl;
        std::cin>>ret;
        if(ret == -1){
            return;  
        }
    }
}