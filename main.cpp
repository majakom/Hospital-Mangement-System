/* Main cpp file for managing hospital system which includes:

 - class Hospital - to manage hospital data;
 - class Beds - to manage Beds data;
 - class Person - to manage mostly data about its subclasses:
    - subclass Patient - to manage patients;
    - subclass Doctor - to manage doctors;
    - subclass Admin - to manage adding new objects of class Person, Hospital and Beds
    
 Entire program uses single header json.hpp from Nlohmann library to manage json files:
 - HospitalData.json
 - BedsData.json
 - PatientData.json
 - DoctorData.json
 - AdminData.json
 Json files store data about every class and subclass */

#include<iostream>
#include<string>
#include<fstream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "hospital_class.hpp"           //including header for class Hospital
#include "person_class.hpp"             //including header for class Person
#include "beds_class.hpp"               //including header for class Beds
#include "doctor_class.hpp"             //including header for subclass Doctor
#include "patient_class.hpp"            //including header for subclass Patient
#include "admin_class.hpp"              //including header for subclass Admin

#include "json.hpp"                     //single header for json files
using json = nlohmann::json;

Hospital hospital;
Person person;
Beds beds;
Doctor doctor;
Patient patient;
Admin admin;


void ClearTerminal();               //declarations of functions used in main.cpp
void LogIn();
void SignIn();

int main(){                         //Displays a starting menu for hospital system management 
    int choice, id;
    while(true){
        ClearTerminal();
        std::cout<<"Welcome to hospital system"<<std::endl;     
        std::cout<<"(0) Log In"<<std::endl;
        std::cout<<"(1) Create an account"<<std::endl;  
        std::cout<<"(2) Exit"<<std::endl;
        std::cin>>choice;
        switch(choice) {
            case 0:
                LogIn();                                        //Calls a function to enable logging in if user is already in the database
                break;
            case 1:
                SignIn();                                       //Calls a function to enable signing in if user is not in the database
                break;
            case 2:
                exit(0);                                        //exits the programm
        }
    }
    return 0;
}

void LogIn() {                                                  //function for logging in if user is in the database
    int choice;
    while(true) {
        ClearTerminal();                                        //function enables to choose as who to log in
        std::cout<<"Log in as: "<<std::endl;
        std::cout<<"(0) Doctor"<<std::endl;
        std::cout<<"(1) Patient"<<std::endl;
        std::cout<<"(2) Admin"<<std::endl;
        std::cin>>choice;
        ClearTerminal();
        switch(choice) {
            case 0:
                doctor.LogIn();                                 //calls an overrided method from subclass Doctor which allows to verify if enetered login and password are in the database of Doctors
                ClearTerminal();                
                doctor.StartingMenuDoctor();                    //if logging in was successfull, Starting Menu for a Doctor is activated from a subclass Doctor
                break;
            case 1:
                patient.LogIn();                                //calls an overrided method from subclass Patient which allows to verify if enetered login and password are in the database of Patients
                ClearTerminal();
                patient.StartingMenuPatient();                  //if logging in was successfull, Starting Menu for a Patient is activated from a subclass Patient
                break;
            case 2:
                admin.LogIn();                                  //calls an overrided method from subclass Admin which allows to verify if enetered login and password are in the database of Admins
                ClearTerminal();
                admin.StartingMenuAdmin();                      //if logging in was successfull, Starting Menu for an Admin is activated from a subclass Admin
                break;
        }
    }
}

void SignIn(){                                                  //function helps with registering new Person in the database
    int choice;
    while(true) {
        ClearTerminal();
        std::cout<<"Register as: "<<std::endl;                  //Enables choice who to register
        std::cout<<"(0) Doctor"<<std::endl;
        std::cout<<"(1) Patient"<<std::endl;
        std::cout<<"(2) Admin"<<std::endl;
        std::cout<<"(3) Exit"<<std::endl;
        std::cin>>choice;
        ClearTerminal();
        switch(choice){
            case 0:
                doctor.RegisterDoctor();                        //calls a method from subclass Doctor to register Doctor
                break;
            case 1:
                patient.RegisterPatient();                      //calls a method from subclass Patient to register Patient
                break;
            case 2:
                admin.RegisterAdmin();                          //calls a method from subclass Admin to register Admin
                break;
            case 3:
                return;                                         //goes back to int main()
        }
    }
}



void ClearTerminal() {                                          //function to clear terminal for windows or linux
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    return;
}
