/* A cpp file of a doctor subclass*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <string>
#include "person_class.hpp"         //including header of a Person class
#include "doctor_class.hpp"         //including header of a Doctor class
#include "hospital_class.hpp"       //including header of a Hospital class

#include "json.hpp"                 //including single header for json management
using json = nlohmann::json;

Hospital hospital2;

Doctor::Doctor(){}
Doctor::~Doctor(){}

void ClearDoctorTerminal();         //declaration of function to clear terminal in windows and linux

void ClearDoctorTerminal() {        //function to clear terminal in windows and linux
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    return;
}


void Doctor::SetJob() {                                 //user-friendly setter for job specialization of a Doctor
    std::cout<<"Enter your job: "<<std::endl;
    std::cin>>this->jobName;
}

std::string Doctor::GetJob() {                          //getter for job specialization
    return this->jobName;
}

float Doctor::GetRating(std::vector<float> rating) {    //method which calculates average rating of a Doctor - it takes in a vector with all ratings
    float sum, averageRating;
    for(int i = 0; i<rating.size(); i++) {              //adding up all rating from a vector
        sum+=rating[i];
    }  
    averageRating = sum/(rating.size());                //calculating an average value
    if (averageRating<= 0.1) {                          //avoiding extremly small ratings from showing up as decimals
        averageRating = 0.0;
    }
    return averageRating;                               //returns average rating
}

void Doctor::RegisterDoctor() {                        //method which allows to register a doctor
    int choice;
    std::vector<float> rating;
    while(true) {
        ClearDoctorTerminal();
        std::cout<<"(0) Enter name"<<std::endl;         //choice of which data should be enetered first
        std::cout<<"(1) Enter surname"<<std::endl;
        std::cout<<"(2) Enter phone number"<<std::endl;
        std::cout<<"(3) Enter email"<<std::endl;
        std::cout<<"(4) Enter specialization"<<std::endl;
        std::cout<<"(5) Enter address"<<std::endl;
        std::cout<<"(6) Enter login"<<std::endl;
        std::cout<<"(7) Enter password"<<std::endl;
        std::cout<<"(8) Confirm and continue"<<std::endl;
        std::cin>>choice;
        switch(choice) {                                //in the following lines multiple setters used from parent class Person to set data of new Doctor object
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
                this->SetJob();                         //apart from unique setters which are strictly used for subclass Doctor and are in fact its methods
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
                this->SaveObjectToJson(rating);          //calls a method which saves new Doctor object to json while setting its rating vector as an empty vector - ratings are added by patients
                return;
        }
    }
    return;
}

void Doctor::SaveObjectToJson(std::vector<float> rating){       //method for saving Doctor objects to json file DoctorData.json
    std::ifstream file("DoctorData.json");                      //opening, reading json and downloading its contents
    nlohmann::json oldDoctorData;
    if (file.is_open()) {
        file >> oldDoctorData;
        file.close();
    }
    std::ofstream outFile("DoctorData.json");                   //opening the same json in writing mode
    nlohmann::json DoctorData;
    int id = oldDoctorData.size();
    this->SetId(id);                                            //setting id of new object which is determined by the length of json contents
    DoctorData["id"] = id;                                      //saving all information abut Doctor object as a json object
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
    oldDoctorData.push_back(DoctorData);                        //merging old data with the rest of already registered doctors with the new one
    outFile<<oldDoctorData<<std::endl;                          //uploading data into json file
    file.close();
    outFile.close();
    return;
}

void Doctor::StartingMenuDoctor() {                             //This method enables doctors to choose an action
    int choice;
    while(true) {
        ClearDoctorTerminal();
        std::cout<<"(0) Show all hospitals"<<std::endl;         //displaying all actions for a doctor
        std::cout<<"(1) Show all your patients"<<std::endl;
        std::cout<<"(2) Show your data"<<std::endl;
        std::cout<<"(3) Exit"<<std::endl;
        std::cin>>choice;
        switch(choice) {
            case 0:
                hospital2.ShowAllHospitals();                   //calling a method from Hospital class which downloads hospital data from json and displays it onscreen
                break;
            case 1:
                this->ShowAllMyPatients();                      //calls a method which displays all patient of the logged on doctor
                break;
            case 2:
                this->ShowMyData();                             //shows data of the doctor currently logged on
                break;
            case 3:
                exit(0);
        }
    }
    return;
}

void Doctor::ShowMyData() {                                     //method shows all data about the doctor who is currently using the programm
    int ret;
    float averageRating;
    std::vector<std::string> addressTaken;
    averageRating = this->GetRating(this->rating);              //calls a method which calculates average rating of the doctor from all his ratings saved in the vector
    while(true) {
        ClearDoctorTerminal();
        std::cout<<this->GetJob()<<std::endl;                               //method uses multiple getters to display data stored in class Person and subclass Doctor
        std::cout<<this->GetName()<<" "<<this->GetSurname()<<std::endl;
        std::cout<<"-----------"<<std::endl;
        std::cout<<this->GetPhoneNumber()<<std::endl;
        std::cout<<this->GetEmail()<<std::endl;
        for(int i = 0; i < this->GetAddress().size(); i++){
            std::cout<<this->GetAddress()[i]<<" ";
        }
        std::cout<<"-----------"<<std::endl;
        std::cout<<"Your rating: "<<averageRating<<std::endl;
        std::cout<<"Enter (-1) to return: "<<std::endl;                     //waits for input to return
        std::cin>>ret;
        if(ret == -1){
            return;  
        }
    }  
}


void Doctor::LogIn(){                                                       //overrided method from subclass Doctor which allows a Doctor to log in
    int found = 0, object;
    std::string login, password;
    std::ifstream file("DoctorData.json");                                  //loading data about all doctors from DoctorData.json
    nlohmann::json oldDoctorData;
    if (file.is_open()) {
        oldDoctorData = json::parse(file);
        file.close();
    }   
    while (!found) {                                                        //checking if inputted login and password are the same as in any object downloaded form json
        std::cout << "Enter your login:" << std::endl;
        std::cin >> login;
        std::cout << "Enter your password:" << std::endl;
        std::cin >> password;
        for (int i = 0; i < oldDoctorData.size(); i++) {
            if (oldDoctorData[i]["login"] == login &&
                oldDoctorData[i]["password"] == password) {                 //if so loop is broken
                found = 1;
                object = i;
                break;
            }
        }
    }
    this->SetId(oldDoctorData[object]["id"].get<int>());                                        //Data of a doctor with login and password typed in before is being set with the use of setters
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

void Doctor::ShowAllDoctors() {                                                             //shows all doctors from the database
    int choice, ret;
    float averageRating;
    std::ifstream file("DoctorData.json");                                                  //loading all json objects form DoctorData.json
    nlohmann::json DoctorData;
    file >> DoctorData;
    while(true) {
        ClearDoctorTerminal();                                                              //displaying short information about each doctor
        for(int i = 0; i<DoctorData.size(); i++) {
            std::cout<<DoctorData[i]["id"].get<int>()<<" - "<<DoctorData[i]["name"].get<std::string>()<<" "<<DoctorData[i]["surname"].get<std::string>()<<" "<<DoctorData[i]["specialization"].get<std::string>()<<std::endl;
        }
        std::cout<<"-----------------------"<<std::endl;
        std::cout<<"Enter the id of doctor to check details"<<std::endl;                    //asks for id of a doctor whose details should be later displayed
        std::cin>>choice;
        ClearDoctorTerminal();
        averageRating = this->GetRating(DoctorData[choice]["rating"].get<std::vector<float>>());        //caluclating chosen doctors rating and displaying details
        std::cout<<DoctorData[choice]["id"].get<int>()<<" - "<<DoctorData[choice]["name"].get<std::string>()<<" "<<DoctorData[choice]["surname"].get<std::string>()<<" "<<DoctorData[choice]["specialization"].get<std::string>()<<std::endl;
        std::cout<<"Rating: "<<averageRating<<std::endl;
        std::cout<<"Contact: "<<std::endl;
        std::cout<<DoctorData[choice]["phoneNumber"].get<int>()<<std::endl;     
        std::cout<<DoctorData[choice]["email"].get<std::string>()<<std::endl;
        for(int i = 0; i<DoctorData[choice]["address"].size(); i++){
            std::cout<<DoctorData[choice]["address"][i].get<std::string>()<<" ";
        }
        std::cout<<"Enter (-1) to return: "<<std::endl;                                     //waiting for input to return
        std::cin>>ret;
        if (ret == -1) {
            return;
        }
    }
    
}
bool CompareDoctorsByRating(const nlohmann::json& doctor1, const nlohmann::json& doctor2) {     //function which helps calculating which average rating is higher
    Doctor d1, d2; 
    float rating1 = d1.GetRating(doctor1["rating"].get<std::vector<float>>());                  //calculating average rating of one doctor
    float rating2 = d2.GetRating(doctor2["rating"].get<std::vector<float>>());                  //calculating average rating of the second doctor
    return rating1 > rating2;                                                                   //return true or false depending of correction of the statement
}
void Doctor::SortDoctorsByRating() {                                                            //method to display sorted by rating doctors
    float averageRating;
    int ret;
    std::ifstream file("DoctorData.json");                                                      //downloading data of all doctors
    nlohmann::json DoctorData;
    file >> DoctorData;

    std::sort(DoctorData.begin(), DoctorData.end(), CompareDoctorsByRating);                    //sorting them by rating with the use of bool function
    
    while(true) {
        ClearDoctorTerminal();
        for (int i = 0; i < DoctorData.size(); i++) {                                                                       //displayind data of the sorted by average ratings doctors
            float averageRating = this->GetRating(DoctorData[i]["rating"].get<std::vector<float>>());
            std::cout << i << " - Rating: " << averageRating << " - "
                    << DoctorData[i]["name"].get<std::string>() << " " << DoctorData[i]["surname"].get<std::string>()
                    << " " << DoctorData[i]["specialization"].get<std::string>() << std::endl;
        }
        std::cout<<"Enter (-1) to return: "<<std::endl;                                             //waiting for input to return
        std::cin>>ret;
        if (ret == -1) {
            return;
        }
    }
}

void Doctor::ShowAllMyPatients(){                                                                   //showing all patients of a doctor currently using programm
    int choice, ret;
    float averageRating;
    std::ifstream file("PatientData.json");                                                         //loading data of Patients from PatientsData.json
    nlohmann::json PatientData;
    file >> PatientData;
    while(true){
        ClearDoctorTerminal();
        for(int i = 0; i<PatientData.size(); i++) {                                                 //firstly showing just short innformation about each Patient
            std::cout<<PatientData[i]["id"].get<int>()<<" - "<<PatientData[i]["name"].get<std::string>()<<" "<<PatientData[i]["surname"].get<std::string>()<<std::endl;
        }
        std::cout<<"-----------------------"<<std::endl;
        std::cout<<"Enter the id of the patient to check details"<<std::endl;                       //asking for id of a Patient to show details about them
        std::cin>>choice;
        ClearDoctorTerminal();
        std::cout<<PatientData[choice]["id"].get<int>()<<" - "<<PatientData[choice]["name"].get<std::string>()<<" "<<PatientData[choice]["surname"].get<std::string>()<<std::endl;
        std::cout<<"Contact: "<<std::endl;
        std::cout<<PatientData[choice]["phoneNumber"].get<int>()<<std::endl;
        std::cout<<PatientData[choice]["email"].get<std::string>()<<std::endl;
        for(int i = 0; i<PatientData[choice]["address"].size(); i++){                               
            std::cout<<PatientData[choice]["address"][i].get<std::string>()<<" ";
        }
        std::cout<<"Enter (-1) to return: "<<std::endl;                                             //waiting for input to return from method
        std::cin>>ret;
        if (ret == -1) {
            return;
        }
    }
}

void Doctor::AddRating() {                                                                          //method which allows Patient to add a single rating for a doctor
    int choice, ret;
    float averageRating, rating, sum;
    std::vector<float> allRatings;
    std::ifstream file("DoctorData.json");                                                          //loading data from json file DoctorData.json
    nlohmann::json DoctorData;
    file >> DoctorData;
    ClearDoctorTerminal();
    for(int i = 0; i<DoctorData.size(); i++) {                                                     //showing all doctors with their ratings caluclated by another method
        averageRating = GetRating(DoctorData[i]["rating"]);
        std::cout<<DoctorData[i]["id"].get<int>()<<" - Rating: "<<averageRating<<" "<<DoctorData[i]["name"].get<std::string>()<<" "<<DoctorData[i]["surname"].get<std::string>()<<" "<<DoctorData[i]["specialization"].get<std::string>()<<std::endl;
    }
    std::cout<<"-----------------------"<<std::endl;
    std::cout<<"Enter the id of doctor to enter rating: "<<std::endl;                              //method asks to input id of the doctor to be rated by patient
    std::cin>>choice;
    std::cout<<"Enter your rating: "<<std::endl;                                                    //method asks for rating to be added by patient to a certain doctor
    std::cin>>rating;
    allRatings = DoctorData[choice]["rating"].get<std::vector<float>>();                            //ratings of that doctor are being downloaded from a their corresponding json object
    allRatings.push_back(rating);                                                                   //new rating is being added to the rest of ratings of that doctor in a vector
    for(int i = 0; i < allRatings.size() ; i++) {                                                   //new average rating is being calculated
        sum += allRatings[i];
    }
    std::cout<<"New data: "<<std::endl;
    averageRating = sum/allRatings.size();
    ClearDoctorTerminal();
    DoctorData[choice]["rating"] = allRatings;                                                       //new data about doctors is updated to a json file
    std::ofstream outFile("DoctorData.json");                                       
    outFile << DoctorData;
    while(true) {                                                                                    //data about rated by patient doctor is displayed including new average rating
        std::cout<<DoctorData[choice]["id"].get<int>()<<" - Rating: "<<averageRating<<" "<<DoctorData[choice]["name"].get<std::string>()<<" "<<DoctorData[choice]["surname"].get<std::string>()<<" "<<DoctorData[choice]["specialization"].get<std::string>()<<std::endl;
        std::cout<<"Enter (-1) to return: "<<std::endl;
        std::cin>>ret;
        if(ret == -1){                                                                               //waiting for input to return
            return;  
        }
    }
}