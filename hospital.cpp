#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <fstream>
using namespace std;

#include <string>
#include <vector>

struct PersonalInfo {
    std::string name;
    int age;
    std::string gender;
    std::string contactNumber;
    std::string address;
};

struct DoctorInfo {
    std::string doctorID;
    PersonalInfo personalInfo;
    std::string specialization;
    int yearsOfExperience;
    std::string contactNumber;
};

struct Appointment {
    std::string appointmentID;
    std::string patientID;
    std::string doctorID;
    std::string date;
    std::string time;
};

struct RoomInfo {
    int roomNumber;
    std::string roomType;    // e.g., "ICU", "General", "Private"
    bool isAvailable;
    double roomRate;         // Rate per day
};

struct MedicalHistory {
    std::string patientID;
    std::vector<std::string> diagnoses;
    std::vector<std::string> treatments;
    std::vector<std::string> medications;
};

struct BillingInfo {
    std::string billID;
    std::string patientID;
    double consultationFee;
    double treatmentCost;
    double roomCharges;
    double discount;
    double insuranceCoverage;
    bool isPaid;
};

struct Medication {
    std::string medicationID;
    std::string name;
    std::string dosage;        // e.g., "500mg"
    int stockQuantity;
    double pricePerUnit;
};

struct NurseInfo {
    std::string nurseID;
    PersonalInfo personalInfo;
    std::string shift;        // e.g., "Day", "Night"
    std::string contactNumber;
};

struct InsuranceDetails {
    std::string insuranceID;
    std::string patientID;
    std::string provider;
    double coveragePercentage;
    std::string policyNumber;
};

struct InventoryItem {
    std::string itemID;
    std::string name;
    int quantity;
    std::string category;     // e.g., "Medical Supply", "Equipment"
    double pricePerUnit;
};


// Base Person class
class Person {
protected:
    int id;
    string name;
    string phone;

public:
    Person(int p_id = 0, string p_name = "", string p_phone = "")
        : id(p_id), name(p_name), phone(p_phone) {}

    void showPersonDetails() const {
        cout << "ID: " << id << ", Name: " << name << ", Contact: " << phone << endl;
    }

    int getId() const { return id; } 
    virtual string toString() const = 0;
};

cout<<"I am Nishant The hero of this film"

// Doctor class inheriting from Person
class Doctor : public Person {
protected:
    string specialization;
    deque<string> appointments; 

public:
    Doctor(int doc_id = 0, string doc_name = "", string doc_phone = "", string spec = "")
        : Person(doc_id, doc_name, doc_phone), specialization(spec) {}

    // Function to add an appointment
    void addAppointment(const string& appointmentID) {
        appointments.push_back(appointmentID); // Add appointments dynamically
    }

    // Function to display appointments for the day
    void getAppointmentsForDay() const {
        cout << "Appointments for Dr. " << name << ":\n";
        for (const auto& appt : appointments) {
            cout << appt << endl;
        }
    }

    void showDoctorDetails() const {
        showPersonDetails();
        cout << "Specialization: " << specialization << endl;
    }
   string toString() const override {
        return to_string(id) + "," + name + "," + phone + "," + specialization;
    }
    const deque<string>& getAllAppointments() const { return appointments; }
};

// Patient class inheriting from Person
class Patient : public Person {
protected:
    string illness;

public:
    Patient(int pat_id = 0, string pat_name = "", string pat_phone = "", string disease = "")
        : Person(pat_id, pat_name, pat_phone), illness(disease) {}

    void showPatientDetails() const {
        showPersonDetails();
        cout << "Illness: " << illness << endl;
    }
     string toString() const override {
        return to_string(id) + "," + name + "," + phone + "," + illness;
    }
};

// Appointment class
class Appointment {
public:
    string appointmentID;
    int doctorID;
    int patientID;
    string date;

    // Constructor to initialize appointment details and generate appointment ID
    Appointment(const Doctor& doctor, const Patient& patient, const string& appointmentDate)
        : doctorID(doctor.getId()), patientID(patient.getId()), date(appointmentDate) {
        appointmentID = generateAppointmentID(); // Generate the appointment ID
    }

    // Method to generate the appointment ID using string concatenation
    string generateAppointmentID() const {
        return to_string(doctorID).insert(0, 4 - to_string(doctorID).length(), '0') + // Pad doctor ID with zeros
               to_string(patientID).insert(0, 5 - to_string(patientID).length(), '0') + // Pad patient ID with zeros
               date; // Using DDMM format without year
    }
    string toString() const {
        return "AppID: " + appointmentID + " DocID: " + to_string(doctorID) + " PatID: " + to_string(patientID) + " Date: " + date;
    }
    // Static function to extract doctor ID from appointment ID
     static Appointment fromString(const string& data) {
        size_t pos = 0, prev_pos = 0;
        vector<string> tokens;

        while ((pos = data.find(',', prev_pos)) != string::npos) {
            tokens.push_back(data.substr(prev_pos, pos - prev_pos));
            prev_pos = pos + 1;
        }
        tokens.push_back(data.substr(prev_pos));

        return Appointment(Doctor(stoi(tokens[1]), "", "", ""), 
                           Patient(stoi(tokens[2]), "", "", ""), tokens[3]);
    }
};

// Billing class inheriting from both Doctor and Patient
class Billing {
private:
    Doctor doctor; 
    Patient patient;
    double totalAmount;
    string paymentStatus;

public:
    Billing(const Doctor& doc, const Patient& pat, double amount, const string& status)
        : doctor(doc), patient(pat), totalAmount(amount), paymentStatus(status) {}

    // Function to display billing details
    void showBillingDetails() const {
        cout << "billing Info:" << endl;
        cout << "Doctor ID: " << doctor.getId() << ", Patient ID: " << patient.getId() << endl;
        cout << "Amount: $" << totalAmount << ", Payment Status: " << paymentStatus << endl;
    }

    void updateAmount(double newAmount) {
        totalAmount = newAmount;
    }

    void updatePaymentStatus(const string& newStatus) {
        paymentStatus = newStatus;
    }
};

// Base InventoryItem class
class InventoryItem {
protected:
    int itemID;
    string name;
    int quantity;
    double price;

public:
    InventoryItem(int id = 0, string itemName = "", int qty = 0, double cost = 0.0)
        : itemID(id), name(itemName), quantity(qty), price(cost) {}

    // Show basic details of the item
    virtual void showItemDetails() const {
        cout << "ID: " << itemID << ", Name: " << name
             << ", Quantity: " << quantity << ", Price: $" << price << endl;
    }

    // Getter for itemID to allow searching by ID
    int getItemID() const { return itemID; }

    // Virtual functions for stock updates (can be overridden if needed)
    virtual void addStock(int qty) {
        quantity += qty;
        cout << qty << " units added to " << name << ". Total stock: " << quantity << endl;
    }

    virtual void useStock(int qty) {
        if (quantity >= qty) {
            quantity -= qty;
            cout << qty << " units used from " << name << ". Remaining stock: " << quantity << endl;
        } else {
            cout << "Insufficient stock to use " << qty << " units.\n";
        }
    }

    virtual ~InventoryItem() {} // Virtual destructor for cleanup
};

// Derived Medicine class
class Medicine : public InventoryItem {
private:
    string expiryDate; // Specific to medicine

public:
    Medicine(int id, string medName, int qty, double cost, string expDate)
        : InventoryItem(id, medName, qty, cost), expiryDate(expDate) {}

    void showItemDetails() const override {
        InventoryItem::showItemDetails();
        cout << "Expiry Date: " << expiryDate << endl;
    }
};

// Derived Equipment class
class Equipment : public InventoryItem {
private:
    string maintenanceDate; // Specific to equipment

public:
    Equipment(int id, string equipName, int qty, double cost, string maintDate)
        : InventoryItem(id, equipName, qty, cost), maintenanceDate(maintDate) {}

    void showItemDetails() const override {
        InventoryItem::showItemDetails();
        cout << "Next Maintenance Date: " << maintenanceDate << endl;
    }
};

void saveAppointment(const string& appointmentID) {
    ofstream file("appointments.txt", ios::app);  
    if (!file) {
        cerr << "Error opening appointments.txt for writing!" << endl;
        return;
    }
    file << appointmentID << endl;
    file.close();
}

void loadDoctors(Doctor doctors[], int& doctorCount) {
    ifstream file("doctors.txt");
    if (!file) {
        cout << "Unable to open doctors file.\n";
        return;
    }

    int id;
    string name, phone, specialization;
    while (file >> id) {
        file.ignore(); 
        getline(file, name, ',');
        getline(file, phone, ',');
        getline(file, specialization);
        doctors[doctorCount++] = Doctor(id, name, phone, specialization);
    }
    file.close();
}

// Function to save doctors to a file
void saveDoctors(const Doctor& doctor) {
    ofstream file("doctors.txt", ios::app); 
    if (!file) {
        cerr << "Error opening doctors.txt for writing!" << endl;
        return;
    }
    file << doctor.toString() << endl;
    file.close();
}
// Function to load patients from a file
void loadPatients(Patient patients[], int& patientCount) {
    ifstream file("patients.txt");
    if (!file) {
        cout << "Unable to open patients file.\n";
        return;
    }

    int id;
    string name, phone, illness;
    while (file >> id) {
        file.ignore(); 
        getline(file, name, ',');
        getline(file, phone, ',');
        getline(file, illness);
        patients[patientCount++] = Patient(id, name, phone, illness);
    }
    file.close();
}


// Function to save patients to a file
void savePatients(const Patient& patient) {
    ofstream file("patients.txt", ios::app);
    if (!file) {
        cerr << "Error opening patients.txt for writing!" << endl;
        return;
    }
    file << patient.toString() << endl;
    file.close();
}

void saveAppointment(const Appointment& appointment) {
    ofstream file("appointments.txt", ios::app);
    if (!file) {
        cerr << "Error opening appointments.txt for writing!" << endl;
        return;
    }
    
    file << appointment.toString() << endl;
    file.close();
}

// Load appointments from file
void loadAppointments(vector<Appointment>& appointments) {
    ifstream file("appointments.txt");
    if (!file) {
        cout << "No appointments found.\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        appointments.push_back(Appointment::fromString(line));
    }
    file.close();
}

// Function to display the hospital management menu
void displayHospitalMenu() {
    cout << "\n--- Hospital Management System ---\n";
    cout << "1. Add Doctor\n";
    cout << "2. Add Patient\n";
    cout << "3. Schedule an Appointment\n";
    cout << "4. Display Doctor's Appointments\n";
    cout << "5. Generate Bill\n";
    cout << "6. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

// Function to display the inventory management menu
void displayInventoryMenu() {
    cout << "\n--- Hospital Inventory Management System ---\n";
    cout << "1. Add Medicine\n";
    cout << "2. Add Equipment\n";
    cout << "3. View Inventory\n";
    cout << "4. Update Stock (Add/Use)\n";
    cout << "5. Search Item by ID\n";
    cout << "6. Remove Item from Inventory\n";
    cout << "7. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

string inputPhoneNumber() {
    string phone;
    cout << "Enter a 10-digit phone number: ";
    cin >> phone;

    // While the input is not 10 digits or contains non-numeric characters, prompt again
    while (phone.length() != 10 || !all_of(phone.begin(), phone.end(), ::isdigit)) {
        cout << "Invalid phone number. Please enter exactly 10 digits: ";
        cin >> phone;
    }

    return phone;
}

int inputDoctorID() {
    int doctorID;
    cout << "Enter a doctor ID (up to 4 digits): ";
    cin >> doctorID;

    // Input validation: must be between 0 and 9999
    while (doctorID < 0 || doctorID > 9999) {
        cout << "Invalid doctor ID. Please enter a number between 0 and 9999: ";
        cin >> doctorID;
    }

    return doctorID;
}


int inputPatientID() {
    int patientID;
    cout << "Enter a patient ID (up to 5 digits): ";
    cin >> patientID;

    // Input validation: must be between 0 and 99999
    while (patientID < 0 || patientID > 99999) {
        cout << "Invalid patient ID. Please enter a number between 0 and 99999: ";
        cin >> patientID;
    }

    return patientID;
}

int main() {
    const int MAX_DOCTORS = 10;
    const int MAX_PATIENTS = 10;
    Doctor doctors[MAX_DOCTORS];
    Patient patients[MAX_PATIENTS];

    int doctorCount = 0;
    int patientCount = 0;
     loadDoctors(doctors, doctorCount);
     loadPatients(patients, patientCount);

    vector<InventoryItem*> inventory; // To store pointers to InventoryItem objects
    int choice;

    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Hospital Management System\n";
        cout << "2. Hospital Inventory Management System\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int hospitalChoice;
            do {
                displayHospitalMenu();
                cin >> hospitalChoice;

                switch (hospitalChoice) {
                // Case 1: Add Doctor
               case 1:
               if (doctorCount < MAX_DOCTORS) {
               int id;
               string name, phone, specialization;
               
               id=inputDoctorID();
               
               cout << "Enter Doctor Name: ";
               cin >> ws; // To clear any whitespace
               getline(cin, name);
               
			   phone = inputPhoneNumber();
               
			   cout << "Enter Specialization: ";
               getline(cin, specialization);
        
               Doctor newDoctor(id, name, phone, specialization);
              doctors[doctorCount++] = newDoctor;
              saveDoctors(newDoctor); // Save only the new doctor
             cout << "Doctor added successfully!\n";
             } else {
             cout << "Cannot add more doctors.\n";
             }
             break;

// Case 2: Add Patient
case 2:
    if (patientCount < MAX_PATIENTS) {
        int id;
        string name, phone, illness;
        id=inputPatientID();
        cout << "Enter Patient Name: ";
        cin >> ws; 
        getline(cin, name);
        phone = inputPhoneNumber();
        cout << "Enter Illness: ";
        getline(cin, illness);
        
        Patient newPatient(id, name, phone, illness);
        patients[patientCount++] = newPatient;
        savePatients(newPatient); 
        cout << "Patient has been added successfully!\n";
    } else {
        cout << "Cannot add more patients.\n";
    }
    break;

                
                case 3: { // Schedule an Appointment
               
                    int docID, patID;
                    string date;
                    docID=inputDoctorID();
                    patID=inputPatientID();
                    cout << "Enter Appointment Date (DDMM format): ";
                    cin >> date;

                    
                    bool docFound = false, patFound = false;
                    for (int i = 0; i < doctorCount; i++) {
                        if (doctors[i].getId() == docID) {
                            docFound = true;
                            break;
                        }
                    }
                    for (int i = 0; i < patientCount; i++) {
                        if (patients[i].getId() == patID) {
                            patFound = true;
                            break;
                        }
                    }
                    if (docFound && patFound) {
                        Appointment appt(doctors[0], patients[0], date); 
                        doctors[0].addAppointment(appt.appointmentID);
                        saveAppointment(appt);
                         
                        cout << "Appointment has been scheduled successfully. ID: " << appt.appointmentID << endl;
                    } else {
                        cout << "Doctor or Patient not found.\n";
                    }
                    break;
                }
                case 4: { // Display Doctor's Appointments
                    int docID;
                    cout << "Enter Doctor ID: ";
                    cin >> docID;

                    bool docFound = false;
                    for (int i = 0; i < doctorCount; i++) {
                        if (doctors[i].getId() == docID) {
                            doctors[i].getAppointmentsForDay();
                            docFound = true;
                            break;
                        }
                    }
                    if (!docFound) {
                        cout << "Doctor is not found.\n";
                    }
                    break;
                }
                case 5: { // Generate Bill
                    int docID, patID;
                    double billAmount;
                    string paymentStatus;
                    cout << "Enter Doctor ID: ";
                    cin >> docID;
                    cout << "Enter Patient ID: ";
                    cin >> patID;
                    cout << "Enter Bill Amount: ";
                    cin >> billAmount;
                    cout << "Enter Payment Status (Paid/Unpaid): ";
                    cin >> paymentStatus;

                    bool docFound = false, patFound = false;
                    for (int i = 0; i < doctorCount; i++) {
                        if (doctors[i].getId() == docID) {
                            docFound = true;
                            break;
                        }
                    }
                    for (int i = 0; i < patientCount; i++) {
                        if (patients[i].getId() == patID) {
                            patFound = true;
                            break;
                        }
                    }
                    if (docFound && patFound) {
                        Billing bill(doctors[0], patients[0], billAmount, paymentStatus); // Using first doctor and patient for demo
                        bill.showBillingDetails();
                    } else {
                        cout << "Doctor or Patient not found.\n";
                    }
                    break;
                }
                case 6: // Back to Main Menu
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    cout << "Invalid choice, please try again.\n";
                }
            } while (hospitalChoice != 6);
            break;
        }
        case 2: {
            int inventoryChoice;
            do {
                displayInventoryMenu();
                cin >> inventoryChoice;

                switch (inventoryChoice) {
                case 1: { // Add Medicine
                    int itemID;
                    string name, expiryDate;
                    int quantity;
                    double price;
                    cout << "Enter Medicine ID: ";
                    cin >> itemID;
                    cout << "Enter Medicine Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Medicine Quantity: ";
                    cin >> quantity;
                    cout << "Enter Medicine Price: ";
                    cin >> price;
                    cout << "Enter Expiry Date: ";
                    cin.ignore();
                    getline(cin, expiryDate);
                    inventory.push_back(new Medicine(itemID, name, quantity, price, expiryDate));
                    cout << "Medicine added to inventory.\n";
                    break;
                }
                case 2: { // Add Equipment
                    int itemID;
                    string name, maintenanceDate;
                    int quantity;
                    double price;
                    cout << "Enter Equipment ID: ";
                    cin >> itemID;
                    cout << "Enter Equipment Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Equipment Quantity: ";
                    cin >> quantity;
                    cout << "Enter Equipment Price: ";
                    cin >> price;
                    cout << "Enter Maintenance Date: ";
                    cin.ignore();
                    getline(cin, maintenanceDate);
                    inventory.push_back(new Equipment(itemID, name, quantity, price, maintenanceDate));
                    cout << "Equipment added to inventory.\n";
                    break;
                }
                case 3: { // View Inventory
                    cout << "\n--- Inventory Items ---\n";
                    for (const auto& item : inventory) {
                        item->showItemDetails();
                    }
                    break;
                }
                case 4: { // Update Stock
                    int itemID, qty;
                    string action;
                    cout << "Enter Item ID: ";
                    cin >> itemID;
                    cout << "Enter Action (add/use): ";
                    cin >> action;
                    cout << "Enter Quantity: ";
                    cin >> qty;

                    auto it = find_if(inventory.begin(), inventory.end(), [itemID](InventoryItem* item) {
                        return item->getItemID() == itemID;
                    });

                    if (it != inventory.end()) {
                        if (action == "add") {
                            (*it)->addStock(qty);
                        } else if (action == "use") {
                            (*it)->useStock(qty);
                        } else {
                            cout << "Invalid action. Please use 'add' or 'use'.\n";
                        }
                    } else {
                        cout << "Item not found in inventory.\n";
                    }
                    break;
                }
                case 5: { // Search Item by ID
                    int itemID;
                    cout << "Enter Item ID to search: ";
                    cin >> itemID;

                    auto it = find_if(inventory.begin(), inventory.end(), [itemID](InventoryItem* item) {
                        return item->getItemID() == itemID;
                    });

                    if (it != inventory.end()) {
                        (*it)->showItemDetails();
                    } else {
                        cout << "Item not found.\n";
                    }
                    break;
                }
                case 6: { // Remove Item from Inventory
                    int itemID;
                    cout << "Enter Item ID to remove: ";
                    cin >> itemID;

                    auto it = remove_if(inventory.begin(), inventory.end(), [itemID](InventoryItem* item) {
                        return item->getItemID() == itemID;
                    });

                    if (it != inventory.end()) {
                        delete *it; // Free the memory for the item
                        inventory.erase(it, inventory.end());
                        cout << "Item removed from inventory.\n";
                    } else {
                        cout << "Item not found in inventory.\n";
                    }
                    break;
                }
                case 7: // Back to Main Menu
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    cout << "Invalid choice, please try again.\n";
                }
            } while (inventoryChoice != 7);
            break;
        }
        case 3: // Exit
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 3);

    // Cleanup: Free memory allocated for inventory items
    for (auto item : inventory) {
        delete item;
    }
    return 0;
}

//Comment 1 added
//Comment 2 added
