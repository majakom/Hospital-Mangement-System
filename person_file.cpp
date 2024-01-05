#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <string>
#include "person_class.hpp"

Person::Person(){}
Person::~Person(){}

void Person::SetId(int id) {
    this->id = id;
    return;
}
void Person::SetLogin(){
    std::cout<<"Enter your login: "<<std::endl;
    std::cin>>this->login;
    return;
}
void Person::SetName() {
    std::cout<<"Enter name: "<<std::endl;
    std::cin>>this->name;
    return;
}
void Person::SetSurname() {
    std::cout<<"Enter surname: "<<std::endl;
    std::cin>>this->surname;
    return;
}
void Person::SetPhoneNumber() {
    std::cout<<"Enter phone number: "<<std::endl;
    std::cin>>this->phoneNumber;
    return;
}
void Person::SetEMail() {
    std::string email;
    std::cout<<"Enter an email:"<<std::endl;
    std::cin>>email;
    this->email = email;
    return;

}
void Person::SetAddress() {
    int choice;
    std::string country, city, street, number;
    std::vector<std::string> setAddress (4);
    while(true){
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
void Person::SetPassword() {
    std::cout<<"Enter password: "<<std::endl;
    std::cin>>this->password;
}
int Person::GetPhoneNumber() {
    return this->phoneNumber;
}
std::string Person::GetLogin() {
    return this->login;
}
std::string Person::GetEmail(){
    return this->email;
}
std::string Person::GetName() {
    return this->name;
}
std::string Person::GetSurname() {
    return this->surname;
}
std::vector<std::string> Person::GetAddress() {
    return this->address;
}
std::string Person::GetPassword() {
    return this->password;
}
int Person::GetId(){
    return this->id;
}

void Person::SetJustName(std::string name) {
    this->name = name;
    return;
}

void Person::SetJustSurname(std::string surname){
    this->surname = surname;
    return;
}
void Person::SetJustAddress(std::vector<std::string> address){
    this->address = address;
    return;
}
void Person::SetJustEmail(std::string email){
    this->email = email;
    return;
}
void Person::SetJustPhoneNumber(int phoneNumber){
    this->phoneNumber = phoneNumber;
    return;
}
void Person::SetJustLogin(std::string login){
    this->login = login;
    return;
}
void Person::SetJustPassword(std::string password){
    this->password = password;
    return;
}