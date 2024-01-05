/* A cpp file containing declarations
of methods for subclass Patient    */

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


void ClearPatientTerminal() {                                           //function to clear terminal for linux and windows
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    return;
}
                                                                        //method for a patient to log into the hospital system
void Patient::LogIn() {
    int found = 0, object;
    std::string login, password;                                        //opening "PatientData.json" and loading its data into a vector
    std::ifstream file("PatientData.json");                     
    nlohmann::json oldPatientData;
    if (file.is_open()) {
        oldPatientData = json::parse(file);
        file.close();
    }
    while (!found) {                                                    //asking user to enter the login and password
        ClearPatientTerminal();
        std::cout << "Enter your login:" << std::endl;
        std::cin >> login;
        std::cout << "Enter your password:" << std::endl;
        std::cin >> password;
        for (int i = 0; i < oldPatientData.size(); i++) {               //chcecking if the use user is in the system untill they give correct data (password and login)
            if (oldPatientData[i]["login"] == login &&
                oldPatientData[i]["password"] == password) {
                std::cout<<"found"<<std::endl;
                found = 1;
                object = i;
                break;
            }
        }
    }
    this->SetId(oldPatientData[object]["id"].get<int>());                                           //provided that user is in the system object of subclass Patient is being initilized
    this->SetJustName(oldPatientData[object]["name"].get<std::string>());                           //with data of the user stored in json
    this->SetJustSurname(oldPatientData[object]["surname"].get<std::string>());
    this->SetJustLogin(oldPatientData[object]["login"].get<std::string>());
    this->SetJustPassword(oldPatientData[object]["password"].get<std::string>());
    this->SetJustAddress(oldPatientData[object]["address"].get<std::vector<std::string>>());
    this->SetJustEmail(oldPatientData[object]["email"].get<std::string>());
    this->SetJustPhoneNumber(oldPatientData[object]["phoneNumber"].get<int>());
    this->indexBeds = oldPatientData[object]["indexBeds"].get<std::vector<int>>();
    return;
}

void Patient::RegisterPatient() {                                                                   //method for registering new patients in the system
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
                this->SetName();                                                                    //Asking for name in a Person class setter
                break;
            case 1:
                this->SetSurname();                                                                  //Asking for surname in a Person class setter
                break;
            case 2:
                this->SetPhoneNumber();                                                              //Asking for phone number in a Person class setter
                break;
            case 3:
                this->SetEMail();                                                                    //Asking for e-mail in a Person class setter
                break;
            case 4:
                this->SetAddress();                                                                  //Asking for address in a Person class setter
                break;
            case 5:
                this->SetLogin();                                                                    //Asking for login in a Person class setter
                break;
            case 6:
                this->SetPassword();                                                                 //Asking for password in a Person class setter
                break;
            case 7:
                this->SaveObjectToJson();                                                            //Direction to a method which saves entire object to json
                return;
        }
    }
    return;
}

void Patient::SaveObjectToJson(){
    std::ifstream file("PatientData.json");                                                           //Reading json file and downloading its contents about all patients
    nlohmann::json oldPatientData;
    if (file.is_open()) {
        file >> oldPatientData;
        file.close();
    }
    std::ofstream outFile("PatientData.json");                                                        //opening json to be able to save new object
    nlohmann::json PatientData;
    int id = oldPatientData.size();
    this->SetId(id);                                                                                   //seting id of the Patient object
    PatientData["id"] = id;                                                                            //setting other information about Patients via class Person and its setters
    PatientData["name"] = this->GetName();
    PatientData["surname"] = this->GetSurname();
    PatientData["email"] = this->GetEmail();
    PatientData["login"] = this->GetLogin();
    PatientData["password"] = this->GetPassword();
    PatientData["address"] = this->GetAddress();
    PatientData["phoneNumber"] = this->GetPhoneNumber();
    PatientData["indexBeds"] = this->indexBeds;                                                         //setting vector with beds indexes for subclass Patient
    oldPatientData.push_back(PatientData);                                                              //merging data of other patients with currently created one to upload it into the json
    outFile<<oldPatientData<<std::endl;
    file.close();
    outFile.close();
    return;
}

void Patient::StartingMenuPatient() {                                                                   //Starting Menu for Patient
    int choice;
    while(true) {
        ClearPatientTerminal();                                                                         //displays actions that users of subclass Patient can make
        std::cout<<"(0) Show all hospitals"<<std::endl;
        std::cout<<"(1) Show all doctors"<<std::endl;
        std::cout<<"(2) Add rating for a doctor"<<std::endl;
        std::cout<<"(3) Book a bed"<<std::endl;
        std::cout<<"(4) Show my data"<<std::endl;
        std::cout<<"(5) Exit"<<std::endl;
        std::cin>>choice;
        switch(choice) {
            case 0:
                hospital1.ShowAllHospitals();                                                           //calls a method from class Hospital to show all hospitals in json database
                break;
            case 1:
                this->ManageDoctor();                                                                   //calls a method to manage options available for subclass Doctor
                break;
            case 2:
                doctor1.AddRating();                                                                    //calls a method for Doctor subclass to choose Doctor for the vector and add new rating for it
                break;
            case 3:
                this->BookBeds();                                                                       //calls a method in subclass Patient which allows to book a bed for a current user
                break;
            case 4:
                this->ShowMyData();                                                                     //calls a method from subclass Patient which displays data of a current user (Patient)
                break;
            case 5:
                exit(0);
        }
    }
    return;
}

void Patient::BookBeds() {                                                                              //method which allows currently logged in Patient to book a bed in a hospital
    std::ifstream file("PatientData.json");                                                             //loading data from PatientData.json to replace it later with altered data containing
    nlohmann::json oldPatientData;                                                                      //indexes of beds in a vector that where booked by the user
    if (file.is_open()) {
        file >> oldPatientData;
        file.close();
    }
    beds2.ShowAllAvailableBeds();                                                                       //calling a method from Beds class to show all available beds and enable to choose a bed
    this->indexBeds.push_back(beds2.GetId());                                                           //index to book
    for(int i = 0; i < oldPatientData.size(); i++) {
        if(oldPatientData[i]["id"] == this->GetId()){                                                   //looking in vector for a current user by their id
            oldPatientData[i]["indexBeds"] = this->indexBeds;                                           //overwriting old vector with data of booked beds with new updated vector 
        }
    }
    std::ofstream outFile("PatientData.json");
    outFile << oldPatientData;                                                                          //uploading altered data of a Patient
    return;
}


void Patient::ShowMyData() {                                                                            //method in subclass Patient used for uploading data
    int ret;
    std::vector<std::string> addressTaken;
    while(true) {
        ClearPatientTerminal();
        std::cout<<this->GetName()<<" "<<this->GetSurname()<<std::endl;                                 //method uses getters from class Person to access data about the Patient
        std::cout<<"-----------"<<std::endl;
        std::cout<<"Phone number: "<<this->GetPhoneNumber()<<std::endl;
        std::cout<<"Email: "<<this->GetEmail()<<std::endl;
        for(int i = 0; i < this->GetAddress().size(); i++){
            std::cout<<this->GetAddress()[i]<<" ";
        }
        std::cout<<"--------------------"<<std::endl;
        std::cout<<"All my beds: "<<std::endl;
        beds2.ShowAllMyBeds(this->indexBeds);                                                           //method calls a method from class Beds to show data about beds booked by this Patient
        std::cout<<"--------------------"<<std::endl;
        std::cout<<"Enter (-1) to return"<<std::endl;
        std::cin>>ret;
        if( ret == -1 ) {
            return;
        }  
    }
    
}


void Patient::ManageDoctor() {                                                                          //method from subclass Patient allows user to choose how to display data about Doctor objects
    int choice;
    while(true) {
        ClearPatientTerminal();
        std::cout<<"(0) Sort doctors by rating"<<std::endl;
        std::cout<<"(1) Show all doctors"<<std::endl;
        std::cout<<"(2) Return"<<std::endl;
        std::cin>>choice;
        switch(choice){
            case 0:
                doctor1.SortDoctorsByRating();                                                          //calls a method from subclass Doctor to display doctors data by their average ratings
                break;
            case 1:
                doctor1.ShowAllDoctors();                                                               //calls a method from subclass Doctor to display doctors data according to their positioning in json
                break;
            case 2:
                return;
        }
    }

}


