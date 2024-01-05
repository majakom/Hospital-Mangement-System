#include<iostream>
#include<string>
#include<fstream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "hospital_class.hpp"
#include "person_class.hpp"
#include "beds_class.hpp"
#include "doctor_class.hpp"
#include "patient_class.hpp"
#include "admin_class.hpp"

#include "json.hpp"
using json = nlohmann::json;

Hospital hospital;
Person person;
Beds beds;
Doctor doctor;
Patient patient;
Admin admin;


void ClearTerminal();
void LogIn();
void SignIn();

int main(){
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
                LogIn();
                break;
            case 1:
                SignIn();
                break;
            case 2:
                exit(0);
        }
    }
    return 0;
}

void LogIn() {
    int choice;
    while(true) {
        ClearTerminal();
        std::cout<<"Log in as: "<<std::endl;
        std::cout<<"(0) Doctor"<<std::endl;
        std::cout<<"(1) Patient"<<std::endl;
        std::cout<<"(2) Admin"<<std::endl;
        std::cin>>choice;
        ClearTerminal();
        switch(choice) {
            case 0:
                doctor.LogInDoctor();
                ClearTerminal();
                doctor.StartingMenuDoctor();
                break;
            case 1:
                patient.LogInPatient();
                ClearTerminal();
                patient.StartingMenuPatient();
                break;
            case 2:
                admin.LogInAdmin();
                ClearTerminal();
                admin.StartingMenuAdmin();
                break;
        }
    }
}

void SignIn(){
    int choice;
    while(true) {
        ClearTerminal();
        std::cout<<"Register as: "<<std::endl;
        std::cout<<"(0) Doctor"<<std::endl;
        std::cout<<"(1) Patient"<<std::endl;
        std::cout<<"(2) Admin"<<std::endl;
        std::cout<<"(3) Exit"<<std::endl;
        std::cin>>choice;
        ClearTerminal();
        switch(choice){
            case 0:
                doctor.RegisterDoctor();
                break;
            case 1:
                patient.RegisterPatient();
                break;
            case 2:
                admin.RegisterAdmin();
                break;
            case 3:
                return;
        }
    }
}



void ClearTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    return;
}
