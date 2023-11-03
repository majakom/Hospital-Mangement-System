#include <iostream>
#include <string>
#include <windows.h>
#include <typeinfo>
#include <cmath>
#include <vector>
#define MAX 500

void ClearTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    return;
}
class Person{
    private:
        std::string name;
        std::string surname;
        std::string email;
        std::string login;
        std::string password;
        int phone_number;
    public:
        void setName(std::string name) {
            this->name = name;
        }
        void setSurname(std::string surname) {
            this->surname = surname;
        }
        void setEmail(std::string email) {
            this->email = email;
        }
        void setPhoneNumber(int phone_number) {
            this->phone_number = phone_number;
        }
        void setLogin(std::string login) {
            this->login = login;
        }
        void setPassword(std::string password) {
            this->password = password;
        }

        std::string getName() {
            return this->name;
        }
        std::string getSurname() {
            return this->surname;
        }
        std::string getEmail() {
            return this->email;
        }
        std::string getPassword(){
            return this->password;
        }
        std::string getLogin() {
            return this->login;
        }
        int getPhoneNumber() {
            return this->phone_number;
        }
        void RegisterPerson() {
            int choice;
            int phoneNumber = -1;
            std::string login, password, name, surname, email;
            while(password.empty() || login.empty()){
                ClearTerminal();
                if (!login.empty()){
                    std::cout<<this->getLogin()<<std::endl;
                }
                std::cout<<"============"<<std::endl;
                std::cout<<"Registration"<<std::endl;
                std::cout<<"(0) Enter login"<<std::endl;
                std::cout<<"(1) Enter password"<<std::endl;
                std::cout<<"(2) Exit"<<std::endl;
                std::cin>>choice;
                ClearTerminal();
                switch(choice) {
                    case 0:
                        if (!login.empty()){
                            std::cout<<this->getLogin()<<std::endl;
                        }
                        std::cout<<"Enter login: ";
                        std::cin>>login;
                        this->setLogin(login);
                        break;
                    case 1:
                        std::cout<<this->getPassword()<<std::endl;
                        std::cout<<"Enter password: ";
                        std::cin>>password;
                        this->setPassword(password);
                        break;
                    case 2:
                        exit(0);
                }
                if (!login.empty() && !password.empty()) {
                    ClearTerminal();
                    std::cout<<"Login: "<<this->getLogin()<<std::endl;
                    std::cout<<"Password: "<<this->getPassword()<<std::endl;
                    std::cout<<"=========="<<std::endl;
                    std::cout<<"Continue?"<<std::endl;
                    std::cout<<"(0) Yes"<<std::endl;
                    std::cout<<"(1) No - enter data again"<<std::endl;
                    std::cout<<"(2) Exit"<<std::endl;
                    std::cin>>choice;
                    switch (choice) {
                        case 0:
                            break;
                        case 1:
                            password.clear();
                            login.clear();
                            this->setPassword(password);
                            this->setLogin(login);
                            break;
                        case 2:
                            exit(0);
                    }
                }    
            }
            while(name.empty() || surname.empty() || email.empty() || phoneNumber == -1){
                ClearTerminal();
                std::cout<<"Login: "<<this->getLogin()<<std::endl;
                if(!this->getName().empty()) {
                    std::cout<<"Name: "<<this->getName()<<std::endl;
                } if(!this->getSurname().empty()) {
                    std::cout<<"Surname: "<<this->getSurname()<<std::endl;
                } if (!this->getEmail().empty()) {
                    std::cout<<"Email: "<<this->getEmail()<<std::endl;
                } if (this->getPhoneNumber() != -1 && int(log10(phoneNumber) + 1) == 9) {
                    std::cout<<"Phone number: "<<this->getPhoneNumber()<<std::endl;
                }
                std::cout<<"============================"<<std::endl;
                std::cout<<"Registration - personal data"<<std::endl;
                std::cout<<"(0) Enter name"<<std::endl;
                std::cout<<"(1) Enter surname"<<std::endl;
                std::cout<<"(2) Enter email"<<std::endl;
                std::cout<<"(3) Enter phone number"<<std::endl;
                std::cout<<"(4) Exit"<<std::endl;
                std::cin>>choice;
                ClearTerminal();
                switch (choice) {
                    case 0:
                        if (!name.empty()){
                            std::cout<<this->getName()<<std::endl;
                        }
                        std::cout<<"Enter name: ";
                        std::cin>>name;
                        this->setName(name);
                        break;
                    case 1:
                        if (!surname.empty()){
                            std::cout<<this->getSurname()<<std::endl;
                        }
                        std::cout<<"Enter surname: ";
                        std::cin>>surname;
                        this->setSurname(surname);
                        break;
                    case 2:
                        if (!email.empty()){
                            std::cout<<this->getEmail()<<std::endl;
                        }
                        std::cout<<"Enter e-mail: ";
                        std::cin>>email;
                        this->setEmail(email);
                        break;
                    case 3:
                        if (phoneNumber != -1 && int(log10(phoneNumber) + 1) == 9){
                            std::cout<<this->getPhoneNumber()<<std::endl;
                        }
                        std::cout<<"Enter phone number: ";
                        std::cin>>phoneNumber;
                        while(typeid(phoneNumber) != typeid(int) || int(log10(phoneNumber) + 1) != 9){
                            ClearTerminal();
                            std::cout<<"Try again, enter phone number: ";
                            std::cin>>phoneNumber;
                        }
                        if(typeid(phoneNumber) == typeid(int)) {
                            this->setPhoneNumber(phoneNumber);
                        }
                        break;
                    case 4:
                        exit(0);
                }
                if (!name.empty() && !surname.empty() && !email.empty() && phoneNumber != -1) {
                    ClearTerminal();
                    std::cout<<"Name: "<<this->getName()<<std::endl;
                    std::cout<<"Surname: "<<this->getSurname()<<std::endl;
                    std::cout<<"Email: "<<this->getEmail()<<std::endl;
                    std::cout<<"Phone number: "<<this->getPhoneNumber()<<std::endl;
                    std::cout<<"========="<<std::endl;
                    std::cout<<"Continue?"<<std::endl;
                    std::cout<<"(0) Yes"<<std::endl;
                    std::cout<<"(1) No - enter data again"<<std::endl;
                    std::cout<<"(2) Exit"<<std::endl;
                    std::cin>>choice;
                    switch (choice) {
                        case 0:
                            break;
                        case 1:
                            email.clear();
                            phoneNumber = -1;
                            name.clear();
                            surname.clear();
                            this->setEmail(email);
                            this->setPhoneNumber(phoneNumber);
                            this->setName(name);
                            this->setSurname(surname);
                            break;
                        case 2:
                            exit(0);
                    }
                }    


            }
            return;
        }
        void ChangePersonalData(){
            
        }

        virtual void StartingMenu(){};

};
class Admin: public Person{};
class Guest: public Person{
    public:
        void StartingMenu() {
            int choice;
            ClearTerminal();
            std::cout<<"(0) Register as a patient"<<std::endl;
            std::cout<<"(1) Register as a doctor"<<std::endl;
            std::cout<<"(2) Register as an admin"<<std::endl;
            std::cout<<"(3) Show all hospitals"<<std::endl;
            std::cout<<"(4) Exit"<<std::endl;
            std::cin>>choice;
            ClearTerminal();
            switch (choice) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                    exit(0);
            }
        }


};
class Patient: public Person{
    private:
        int day;
        int month;
        int year;
        int dateOfBirth[3] = {day, month, year};
    public:

};
class Doctor: public Person{};
class Beds{};
class Hospital{
    private:
        std::string name;
        std::string email;
        std::string country;
        std::string city;
        std::string street;
        std::string house_number;
        std::string location[4] = {country, city, street, house_number};

        float rating;
        float average_rating;
        int number_of_beds;
        int phone_number;

        Beds array_beds[MAX];
        Doctor array_doctors[MAX];
        Patient array_patients[MAX];
    public:
        void setName(std::string name) {
            this->name = name;
        }
        void setEmail(std::string email) {
            this->email = email;
        }
        void setPhoneNumber(int phone_number) {
            this->phone_number = phone_number;
        }
        void setCountry(std::string country) {
            this->country = country;
        }
        void setCity(std::string city) {
            this->city = city;
        }
        void setStreet(std::string street) {
            this->street = street;
        }
        void setHouseNumber(std::string house_number) {
            this->house_number = house_number;
        }
        void setArrayBeds(Beds array_beds) {
            this->array_beds[MAX] = array_beds;
        }
        void setArrayDoctors(Doctor array_doctors) {
            this->array_doctors[MAX] = array_doctors;
        }
        void setArrayPatients(Patient array_patients) {
            this->array_patients[MAX] = array_patients;
        }

        std::string getName() {
            return this->name;
        }
        std::string getEmail() {
            return this->email;
        }
        std::string getCountry() {
            return this->location[0];
        }
        std::string getCity() {
            return this->location[1];
        }
        std::string getStreet() {
            return this->location[2];
        }
        std::string getHouseNumber() {
            return this->location[3];
        }
        int getNumberOfBeds() {
            return this->number_of_beds;
        }
        int getRating() {
            return this->rating;
        }
        int getAverageRating() {
            return this->average_rating;
        }
        Doctor getAllDoctors() {
            return this->array_doctors[MAX];
        }
        Patient getAllPatients() {
            return this->array_patients[MAX];
        }
        Beds getAllBeds() {
            return this->array_beds[MAX];
        }  
        
        std::string AddLocation() {
            int choice;
            while(!this->country.empty() && !this->city.empty() && !this->street.empty() && !this->house_number.empty()) {
                ClearTerminal();
                std::cout<<"Add location:"<<std::endl;
                std::cout<<"(0) Enter country"<<std::endl;
                std::cout<<"(1) Enter city/town"<<std::endl;
                std::cout<<"(2) Enter street name"<<std::endl;
                std::cout<<"(3) Enter house number"<<std::endl;
                std::cout<<"(4) Exit"<<std::endl;
                std::cin>>choice;
                ClearTerminal();
                switch (choice) {
                    case 0:
                        if(!this->country.empty()){
                            std::cout<<"Country: "<<this->country;
                        }
                        std::cout<<"Enter country"<<std::endl;
                        std::cin>>this->country;
                        break;
                    case 1:
                        if(!this->city.empty()){
                            std::cout<<"City/town: "<<this->city;
                        }
                        std::cout<<"Enter city/town"<<std::endl;
                        std::cin>>this->city;
                        break;
                    case 2:
                        if(!this->street.empty()){
                            std::cout<<"Street: "<<this->street;
                        }
                        std::cout<<"Enter street name"<<std::endl;
                        std::cin>>this->street;
                        break;
                    case 3:
                        if(!this->house_number.empty()){
                            std::cout<<"House number: "<<this->house_number;
                        }
                        std::cout<<"Enter house number"<<std::endl;
                        std::cin>>this->house_number;
                        break;
                    case 4:
                        exit(0);
                }
                if(this->country.empty() && this->city.empty() && this->street.empty() && this->house_number.empty()){
                    ClearTerminal();
                    std::cout<<"Country: "<<this->getCountry()<<std::endl;
                    std::cout<<"City: "<<this->getCity()<<std::endl;
                    std::cout<<"Street: "<<this->getStreet()<<std::endl;
                    std::cout<<"House number: "<<this->getHouseNumber()<<std::endl;
                    std::cout<<"=========="<<std::endl;
                    std::cout<<"Continue?"<<std::endl;
                    std::cout<<"(0) Yes"<<std::endl;
                    std::cout<<"(1) No - enter data again"<<std::endl;
                    std::cout<<"(2) Exit"<<std::endl;
                    std::cin>>choice;
                    switch (choice) {
                        case 0:
                            return this->location[4];
                        case 1:
                            this->country.clear();
                            this->city.clear();
                            this->street.clear();
                            this->house_number.clear();
                            break;
                        case 2:
                            exit(0);
                    }
                }
            }
        }
        void AddHospital() {
            int choice;
            ClearTerminal();
            std::cout<<"Add a new hospital"<<std::endl;
            std::cout<<"(0) Enter a name"<<std::endl;
            std::cout<<"(1) Enter an e-mail"<<std::endl;
            std::cout<<"(2) Enter a phone number"<<std::endl;
            std::cout<<"(3) Enter location"<<std::endl;
            std::cout<<"(4) Add a list of doctors"<<std::endl;
            std::cout<<"(5) Add a list of patients"<<std::endl;
            std::cout<<"(6) Add a list of beds"<<std::endl;
            std::cout<<"(7) Exit"<<std::endl;
            std::cin>>choice;
            ClearTerminal();
            switch (choice) {
                case 0:
                    std::cout<<"Enter a name: ";
                    std::cin>>this->name;
                    break;
                case 1:
                    std::cout<<"Enter an e-mail: ";
                    std::cin>>this->email;
                case 2:
                    if(phone_number == -1) {
                        std::cout<<phone_number;
                    }
                    std::cout<<"Enter a phone number: ";
                    std::cin>>this->phone_number;
                case 3:
                    if(!this->location[0].empty() && !this->location[1].empty() && !this->location[2].empty() && !this->location[3].empty()) {
                        std::cout<<this->location[0]<<std::endl;
                        std::cout<<this->location[1]<<std::endl;
                        std::cout<<this->location[2]<<std::endl;
                        std::cout<<this->location[3]<<std::endl;
                        std::cout<<"Do you want to change location?"<<std::endl;
                        std::cout<<"(0) Yes"<<std::endl;
                        std::cout<<"(1) No"<<std::endl;
                        std::cout<<"(2) Exit"<<std::endl;
                        std::cin>>choice;
                        switch (choice) {
                            case 0:
                                this->location[0].clear();
                                this->location[1].clear();
                                this->location[2].clear();
                                this->location[3].clear();
                                AddLocation();
                                break;
                            case 1:
                                break;
                            case 2:
                                exit(0);
                        }
                    }
                case 4:
                case 5:
                case 6:
                case 7:
                    exit(0);
            }
        }         
};


template <typename T> void LogIn(T person, T vectorPeople) {
    int choice;
    std::string newLogin, newPassword;
    while (!newLogin.empty() && !newPassword.empty()){
        std::cout<<"(0) Enter your login"<<std::endl;
        std::cout<<"(1) Enter your password"<<std::endl;
        std::cout<<"(2) Exit"<<std::endl;
        std::cin>>choice;
        switch (choice) {
            case 0:
                std::cout<<"Enter your login: ";
                std::cin>>newLogin;
            case 1:
                std::cout<<"Enter your password: ";
                std::cin>>newPassword;
        }

    }


}

void SignIn() {
    Patient newPatient;
    Doctor newDoctor;
    int choice;
    ClearTerminal();
    std::cout<<"(0) As a doctor"<<std::endl;
    std::cout<<"(1) As a patient"<<std::endl;
    std::cout<<"(2) Exit"<<std::endl;
    ClearTerminal();
    switch (choice) {
        case 0:
            newDoctor.RegisterPerson();
        case 1:
            newPatient.RegisterPerson(); 
        case 2:
            exit(0);
    }
}

int main() {
    int choice;

    Admin newAdmin;
    Guest newGuest;
    Patient newPatient;
    Doctor newDoctor;

    std::vector<Patient> AllPatients;
    std::vector<Doctor> AllDoctors;
    std::vector<Admin> AllAdmins;
    std::vector<Hospital> AllHospitals;

    while (true) {
        ClearTerminal();
        std::cout<<"Welcome"<<std::endl;
        std::cout<<"=========="<<std::endl;
        std::cout<<"Log in as:"<<std::endl;
        std::cout<<"(0) Guest"<<std::endl;
        std::cout<<"(1) Patient"<<std::endl;
        std::cout<<"(2) Doctor"<<std::endl;
        std::cout<<"(3) Admin"<<std::endl;
        std::cout<<"============"<<std::endl;
        std::cout<<"(4) Sign in"<<std::endl;
        std::cout<<"(5) Exit"<<std::endl;
        std::cin>>choice;
        ClearTerminal();
        switch (choice) {
            case 0:
                newGuest.StartingMenu();
            case 1:
                newPatient.RegisterPerson();
                AllPatients.push_back(newPatient);
                std::cout<<newPatient.getName()<<std::endl;
                break;
            case 2:
                newDoctor.RegisterPerson();
                AllDoctors.push_back(newDoctor);
                break;
            case 3:
                newAdmin.RegisterPerson();
                AllAdmins.push_back(newAdmin);
                break;
            case 4:
                SignIn();
                break;
            case 5:
                exit(0);
        }
    }
}

