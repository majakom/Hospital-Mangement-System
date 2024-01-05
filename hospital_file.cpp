/* A cpp file with declarations of method for a class Hospital */
#include <iostream>
#include <fstream>
#include "hospital_class.hpp"       //including hospital class header
#include "beds_class.hpp"           //including beds class header
#include "json.hpp"                 //including json single header to manage json files
#include "person_class.hpp"         //including person class header
#include "patient_class.hpp"        //including patient subclass header
#include "doctor_class.hpp"         //including doctor subclass header
#include "admin_class.hpp"          //including admin subclass header
using json = nlohmann::json;

Hospital::Hospital(){}
Hospital::~Hospital(){}

Beds beds1;
Patient patient4;
Doctor doctor4;

void ClearHospitalTerminal();       //declartion of function used to clear terminal for windows or linux

void ClearHospitalTerminal() {      //function used to clear terminal for windows or linux
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    return;
}

void Hospital::AddHospital(){           //Method for adding new hospitals into the database system
    this->indexBeds.clear();            //clearing old data of a hospital
    this->indexDoctors.clear();
    this->indexPatients.clear();
    this->address.clear();
    std::ifstream file("HospitalData.json");            //opening json file and reading its contents
    nlohmann::json oldHospitalData;
    if (file.is_open()) {
        file >> oldHospitalData;
        file.close();
    }
    int id = oldHospitalData.size();    
    this->SetId(id);                                    //setting id of a newly created hospital
    int choice;
    while(true){
        ClearHospitalTerminal();                                        //giving choice as to which data should be entered first
        std::cout<<"(0) Add name of the hospital"<<std::endl;
        std::cout<<"(1) Add address of the hospital"<<std::endl;
        std::cout<<"(2) Add all doctors"<<std::endl;
        std::cout<<"(3) Add all patients"<<std::endl;
        std::cout<<"(4) Add all beds"<<std::endl;
        std::cout<<"(5) Confirm and return"<<std::endl;
        std::cin>>choice;
        switch(choice){
            case 0:                                                     //following lines include calling setters
                this->SetName();
                break;
            case 1:
                this->SetAddress();
                break;
            case 2:                                                     //Enables to chose which doctors wotk in a certain hospital
                this->AddAllDoctors();
                break;
            case 3:                                                     //Enables to chose which patients are being treated in a certain hospital
                this->AddAllPatients(); 
                break;
            case 4:
                id = beds1.AddBed(this->id);                            //calls a method from class Beds which takes in id of a newly created hospital and gets id of a newly created bed in the hospital
                this->indexBeds.push_back(id);                          //updates vector with indexes of all Beds that are in a hospital
                break;
            case 5:
                this->UpdateData();                                     //calls a method which saves all data about new hospital
                return;
        }
    }
}

void Hospital::SetName(){                                               //user-friendly setter of a hospital name
    std::cout<<"Enter the name of the hospital: "<<std::endl;
    std::cin>>this->name;
}

void Hospital::SetAddress() {                                           //method which sets vector address from class Hospital
    int choice;
    std::string country, city, street, number;
    std::vector<std::string> setAddress (4);
    while(true){                                                        //enables choice
        ClearHospitalTerminal();
        std::cout<<"(0) Country"<<std::endl;
        std::cout<<"(1) City/town/village"<<std::endl;
        std::cout<<"(2) Street"<<std::endl;
        std::cout<<"(3) Buildings number"<<std::endl;
        std::cout<<"(4) Confirm and continue"<<std::endl;
        std::cin>>choice;
        switch (choice)                                                 //following code allows user to set relevant information about hospital address
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
            case 4:                                                       //allows user to set private vector address to what was entered and gathered in a temporary storing data vector
                this->address = setAddress;
                return;
        }
    }
}

void Hospital::SetId(int id){                                           //setter of hospital id
    this->id = id;
    return;
}

void Hospital::UpdateData(){                                            //method used to save new objects of class Hospital into a json file
    std::ifstream file("HospitalData.json");                            //reading and loading contents of json file
    nlohmann::json oldHospitalData;
    if (file.is_open()) {
        file >> oldHospitalData;
        file.close();
    }
    std::ofstream outFile("HospitalData.json");
    nlohmann::json HospitalData;
    int id = oldHospitalData.size();                                    //calculating id of newly created hospital object
    this->SetId(id);                                                    //setting the id of the hospital object
    HospitalData["id"] = this->id;                                      //creating object for a json file corresponding to the one created in the programm
    HospitalData["name"] = this->name;
    HospitalData["address"] = this->address;
    HospitalData["indexBeds"] = this->indexBeds;
    HospitalData["indexPatients"] = this->indexPatients;
    HospitalData["indexDoctors"] = this->indexDoctors;
    oldHospitalData.push_back(HospitalData);                            //merging data of previously created hospitals with the new one
    outFile<<oldHospitalData<<std::endl;                                //uploading data to the json file HospitalData.json
    file.close();       
    outFile.close();
    return;                
}

void Hospital::ShowAllHospitals() {                                     //method for showing all hospital in the databse
    int choice, ret;
    std::ifstream file("HospitalData.json");                            //reading and loading data about all hospitals form json
    nlohmann::json HospitalData;
    file >> HospitalData;
    while(true){
        ClearHospitalTerminal();                                                                                                //displaying short information about each hospital
        for(int i = 0; i<HospitalData.size(); i++) {
            std::cout<<HospitalData[i]["id"].get<int>()<<" - "<<HospitalData[i]["name"].get<std::string>()<<std::endl;
        }
        std::cout<<"-----------------------"<<std::endl;
        std::cout<<"Enter the id of hospital to check details"<<std::endl;                                                      //asking for id of a ceratain hospital to see its details
        std::cin>>choice;
        ClearHospitalTerminal();
        std::cout<<HospitalData[choice]["id"].get<int>()<<" - "<<HospitalData[choice]["name"].get<std::string>()<<std::endl;    //showing details
        for(int i = 0; i<HospitalData[choice]["address"].size(); i++){
            std::cout<<HospitalData[choice]["address"][i].get<std::string>()<<" ";
        }
        std::cout<<std::endl;
        std::cout<<"Enter (-1) to return"<<std::endl;                                                                           //waiting for input to return from method
        std::cin>>ret;  
        if( ret == -1) {
            return;
        }
    }
}

void Hospital::AddAllPatients() {                               //method used while creating new hospital in the system for chosing all patients registered in the hospital
    int choice;
    std::ifstream file("PatientData.json");                     //opening json file with all data about patients
    nlohmann::json PatientData;
    file >> PatientData;
    while(true) {
        ClearHospitalTerminal();                                //displaying short information about all patients
        for(int i = 0; i<PatientData.size(); i++) {
            std::cout<<PatientData[i]["id"].get<int>()<<" - "<<PatientData[i]["name"].get<std::string>()<<" "<<PatientData[i]["surname"].get<std::string>();
        }
        std::cout<<"-----------------------"<<std::endl;
        std::cout<<"Enter the id of the patient to add to the list or (-1) return to save: "<<std::endl;        //Method asks for id of a patient to save as one registered in the new hospital
        std::cin>>choice;
        if(choice == -1) {                                                                                      //loop repeats until user decides all patients that were meant to be registered are
            return;                                                                                             //loop break on command and returns
        } else {
            this->indexPatients.push_back(PatientData[choice]["id"].get<int>());                                //if loop is not broken it saves in a vector ids of newly added to hospital patients
        }

    }

    return;
}

void Hospital::AddAllDoctors() {                                                        //method analogical to Hospital::AddAllPatients() except it adds doctors to newly created hospital
    int choice;
    float averageRating;    
    std::ifstream file("DoctorData.json");                                              //opening DoctorData.json and loading its contents
    nlohmann::json DoctorData;
    file >> DoctorData;
    while(true) {
        ClearHospitalTerminal();                                                        //showing shortly data about doctors
        for(int i = 0; i<DoctorData.size(); i++) {
            std::cout<<DoctorData[i]["id"].get<int>()<<" - "<<DoctorData[i]["name"].get<std::string>()<<" "<<DoctorData[i]["surname"].get<std::string>()<<" "<<DoctorData[i]["specialization"].get<std::string>()<<std::endl;
        }
        std::cout<<"-----------------------"<<std::endl;
        std::cout<<"Enter the id of doctor to add to the list or (-1) return to save: "<<std::endl;
        std::cin>>choice;                                                               //user choses which doctor to add into the hospital vector with their ids
        if(choice == -1) {
            return;
        } else {
            this->indexDoctors.push_back(DoctorData[choice]["id"].get<int>());          //loop continues to save all chosen ids of doctors untill its broken by the certain input 
        }

    }
}