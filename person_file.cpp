/* A cpp file with declarations of methods,
 mostly setters and getters for class Person*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <string>
#include "person_class.hpp"                             //including header file with class Person

Person::Person(){}
Person::~Person(){}

void Person::SetId(int id) {                            //simple setter of id for class Person
    this->id = id;
    return;
}
void Person::SetLogin(){                                //user-friendly setter of login for class Person
    std::cout<<"Enter your login: "<<std::endl;
    std::cin>>this->login;
    return;
}
void Person::SetName() {                                //user-friendly setter of name for class Person
    std::cout<<"Enter name: "<<std::endl;
    std::cin>>this->name;
    return;
}
void Person::SetSurname() {                             //user-firendly setter of surname for class Person
    std::cout<<"Enter surname: "<<std::endl;
    std::cin>>this->surname;
    return;
}
void Person::SetPhoneNumber() {                         //user-friendly setter of phone number for class Person
    std::cout<<"Enter phone number: "<<std::endl;
    std::cin>>this->phoneNumber;
    return;
}
void Person::SetEMail() {                               //user-friendly setter of e-mail for class Person
    std::cout<<"Enter an email:"<<std::endl;
    std::cin>>this->email;
    return;

}
void Person::SetAddress() {                                     //method for class Person used to set address for a Person in a vector
    int choice;
    std::string country, city, street, number;
    std::vector<std::string> setAddress (4);
    while(true){
        std::cout<<"(0) Country"<<std::endl;                    //User can choose which part of address to save first
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
                this->address = setAddress;                     //after setting all relevant address data, private vector in class Person is overwrited with new data
                return;
        }
    }
}
void Person::SetPassword() {                                    //user-friendly setter for password for class Person
    std::cout<<"Enter password: "<<std::endl;
    std::cin>>this->password;
}
int Person::GetPhoneNumber() {                                  //getter for phone number in class Person
    return this->phoneNumber;
}
std::string Person::GetLogin() {                                //getter for login in class Person
    return this->login;
}
std::string Person::GetEmail(){                                 //getter for e-mail in class Person
    return this->email;
}
std::string Person::GetName() {                                 //getter for name in class Person
    return this->name;
}
std::string Person::GetSurname() {                              //getter for surname in class Person
    return this->surname;
}
std::vector<std::string> Person::GetAddress() {                 //getter for vector with address in class Person
    return this->address;
}
std::string Person::GetPassword() {                             //getter for password in class Person
    return this->password;
}
int Person::GetId(){                                            //getter for id in class Person
    return this->id;
}

void Person::SetJustName(std::string name) {                    //simple setter for name in class Person
    this->name = name;
    return;
}

void Person::SetJustSurname(std::string surname){               //simple setter for surname in class Person
    this->surname = surname;
    return;
}
void Person::SetJustAddress(std::vector<std::string> address){  //simple setter for vector with address in class Person
    this->address = address;
    return;
}
void Person::SetJustEmail(std::string email){                   //simple setter for email in class Person
    this->email = email;
    return;
}
void Person::SetJustPhoneNumber(int phoneNumber){               //simple setter for phone number in class Person
    this->phoneNumber = phoneNumber;
    return;
}
void Person::SetJustLogin(std::string login){                   // simple setter for login in class Person
    this->login = login;
    return;
}
void Person::SetJustPassword(std::string password){             //simple setter for password in class Person
    this->password = password;
    return;
}


