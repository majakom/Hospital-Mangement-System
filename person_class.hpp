/* A header file for class Person*/
#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

class Person{
    private:
        int id;
        int phoneNumber;
        std::string email;
        std::string name;
        std::string surname;
        std::string login;
        std::string password;
        std::vector<std::string> address;
    public:
        Person();
        ~Person();
        void SetId(int id);                                     //setters:
        void SetLogin();
        void SetName();
        void SetSurname();
        void SetPhoneNumber();
        void SetEMail();
        void SetAddress();
        void SetPassword();
        void SetJustName(std::string name);
        void SetJustSurname(std::string surname);
        void SetJustAddress(std::vector<std::string> address);
        void SetJustEmail(std::string email);
        void SetJustPhoneNumber(int phoneNumber);
        void SetJustLogin(std::string login);
        void SetJustPassword(std::string password);
        std::string GetName();                                  //getters:
        std::string GetSurname();
        std::string GetLogin();
        std::string GetPassword();
        std::vector<std::string> GetAddress();
        std::string GetEmail();
        int GetId();
        int GetPhoneNumber();
        virtual void LogIn() {};        //virtual void method to be overrided by method from subclasses

};