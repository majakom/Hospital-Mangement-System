[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/b7QIWzDa)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=12364245&assignment_repo_type=AssignmentRepo)
<header>

# Hospital Management System in C++

C++ programm with Hospital Management system. Stores data about hospitals, patients, doctors and admins. Alllows to search for specific data, add new hospital workers and patients and manage overally hospital system.
</header>

In order to manage json files nlohmann single header json.hpp was used in this project.

Graph in draw.io:
https://drive.google.com/file/d/1MEsaaC1L8H6FSwX4dJdFiZKQJtHgNiFW/view?usp=sharing 

Project due to 30.01.2024.

## Functions Supported:

- Add new admins
- Add new doctors
- Add new patients
- Add new hospitals
- Add new beds
- Save Hosptal data in json files
- Save Patients data in json files
- Save Doctors data in json files
- Print Hospital data
- Print Patients data
- Print Doctors data
- Save Beds data in json files
- Sort by available beds
- Sort doctors by rating
- Book a bed

## Approach:
1. Create header files for classes Hospital and Beds for the Hospital and beds management dataset.
2. Create header file for class Person with all people in database regardless of their function.
3. Create header files for subclasses in class Person: Doctor, Admin and Patient.
4. Initialize variables that store Hospital and Beds dataset and Person data.
5. Initialize functions and methods used for all classes to manage hospital system.
6. Implement system for storing and restoring data from classes and subclasses.
7. Create Objects for hospitals and Patient classes that access the Hospital dataset and Patient data.
8. Use vectors to store currently used data form json files
9. Implement the given functionality.

## Most of the relevant functions in the program:
- Beds::ShowAllAvailableBeds() and Beds::AddBed(int hospitalIndex) : They will print all the available beds and allow patient to book them.
- Beds::ShowAllMyBeds(std::vector<int> indexBeds) : It shows all beds booked by a patient.
- Doctor::RegisterDoctor() : It will allow to register a doctor in the system.
- Doctor::StartingMenuDoctor() : It displays a starting menu for a doctor in a terminal.
- Doctor::ShowMyData() : It allows to display data of the doctor.
- Doctor::LogInDoctor() : It allows a doctor to log in the system.
- Doctor::ShowAllDoctors() : It shows data of all doctors in the system.
- Doctor::SortDoctorsByRating() : It sorts and displays all doctors by their ratings.
- Doctor::ShowAllMyPatients() : It allows a doctor to see all his patients and their data.
- Doctor::AddRating() : It allows patients to add ratings of the doctors.
- Hospital::AddHospital() : It allows admin to register a new hospital in the system.
- Hospital::SetAddress() : It allows admin to set specific address of the hospital.
- Hospital::ShowAllHospitals() : It displays data of all hospitals in database.
- Hospital::UpdateData() : It updates data about a hospital in a json file.
- Hospital::AddAllPAtients() and Hospital::AddAllDoctors : It allows to add specific doctors who work in a hospital and patients who are registered in the hospital.
- Patient::ShowMyData() : It shows data of a current user - patient.
- Patient::ManageDoctor() : It allows patient to chose in which order to display doctors.
- Patient::LogInPatient() : It allows patient to log in the system.
- Patient::RegisterPatients() : It allows admin or a patient themselves to register in the system.
- Patient::SaveObjectToJson() : It allows patients data to be saved into a json file.
- Patient::StartingMenuPatient() : Displays a starting menu for a patient
- Patient::BookBeds() : It allows patient to book a bed.
- Admin::StartingMenuAdmin() : It displays a starting menu for an admin.
- Admin::RegisterAdmin() : It allows to register an admin in the system.
- Admin::SaveObjectToJson() : It saves amdins data into a json file.
- Admn::RegisterPersonChoice() : It helps admin to manage creating new accounts for admins, patients and doctors.
- Admin::LogInAdmin() : It allows admin to log in the system.


