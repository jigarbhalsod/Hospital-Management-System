#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <fstream>
using namespace std;

// ============================
// Helper function for separators
// ============================
void separator() {
    cout << "\n========================================\n\n";
}

// ============================
// Input Validators
// ============================
string inputPhoneNumber() {
    string phone;
    cout << "📞 Enter a 10-digit phone number: ";
    cin >> phone;
    while (phone.length() != 10 || !all_of(phone.begin(), phone.end(), ::isdigit)) {
        cout << "❌ Invalid! Enter exactly 10 digits: ";
        cin >> phone;
    }
    return phone;
}

int inputDoctorID() {
    int id;
    cout << "🩺 Enter Doctor ID (0-9999): ";
    cin >> id;
    while (id < 0 || id > 9999) {
        cout << "❌ Invalid! Enter number between 0-9999: ";
        cin >> id;
    }
    return id;
}

int inputPatientID() {
    int id;
    cout << "🧑‍⚕️ Enter Patient ID (0-99999): ";
    cin >> id;
    while (id < 0 || id > 99999) {
        cout << "❌ Invalid! Enter number between 0-99999: ";
        cin >> id;
    }
    return id;
}

// ============================
// Base Person Class
// ============================
class Person {
protected:
    int id;
    string name;
    string phone;

public:
    Person(int p_id = 0, string p_name = "", string p_phone = "")
        : id(p_id), name(p_name), phone(p_phone) {}

    virtual void showPersonDetails() const {
        cout << "🆔 ID: " << id << "\n👤 Name: " << name << "\n📞 Contact: " << phone << endl;
    }

    int getId() const { return id; }
    virtual string toString() const = 0;
};

// ============================
// Doctor Class
// ============================
class Doctor : public Person {
private:
    string specialization;
    deque<string> appointments;

public:
    Doctor(int doc_id = 0, string doc_name = "", string doc_phone = "", string spec = "")
        : Person(doc_id, doc_name, doc_phone), specialization(spec) {}

    void addAppointment(const string& appointmentID) {
        appointments.push_back(appointmentID);
    }

    void getAppointmentsForDay() const {
        cout << "📅 Appointments for Dr. " << name << ":\n";
        for (const auto& appt : appointments) cout << "   - " << appt << endl;
    }

    void showDoctorDetails() const {
        cout << "--- 🩺 Doctor Details ---\n";
        showPersonDetails();
        cout << "💼 Specialization: " << specialization << endl;
    }

    string toString() const override {
        return to_string(id) + "," + name + "," + phone + "," + specialization;
    }

    const deque<string>& getAllAppointments() const { return appointments; }
};

// ============================
// Patient Class
// ============================
class Patient : public Person {
private:
    string illness;

public:
    Patient(int pat_id = 0, string pat_name = "", string pat_phone = "", string disease = "")
        : Person(pat_id, pat_name, pat_phone), illness(disease) {}

    void showPatientDetails() const {
        cout << "--- 🧑‍⚕️ Patient Details ---\n";
        showPersonDetails();
        cout << "⚕️ Illness: " << illness << endl;
    }

    string toString() const override {
        return to_string(id) + "," + name + "," + phone + "," + illness;
    }
};

// ============================
// Appointment Class
// ============================
class Appointment {
public:
    string appointmentID;
    int doctorID;
    int patientID;
    string date;

    Appointment(const Doctor& doctor, const Patient& patient, const string& appointmentDate)
        : doctorID(doctor.getId()), patientID(patient.getId()), date(appointmentDate) {
        appointmentID = generateAppointmentID();
    }

    string generateAppointmentID() const {
        return to_string(doctorID).insert(0, 4 - to_string(doctorID).length(), '0') +
               to_string(patientID).insert(0, 5 - to_string(patientID).length(), '0') + date;
    }

    string toString() const {
        return "AppID: " + appointmentID + " DocID: " + to_string(doctorID) + " PatID: " + to_string(patientID) + " Date: " + date;
    }
};

// ============================
// Billing Class
// ============================
class Billing {
private:
    Doctor doctor;
    Patient patient;
    double totalAmount;
    string paymentStatus;

public:
    Billing(const Doctor& doc, const Patient& pat, double amount, const string& status)
        : doctor(doc), patient(pat), totalAmount(amount), paymentStatus(status) {}

    void showBillingDetails() const {
        cout << "--- 💰 Billing Info ---\n";
        cout << "Doctor ID: " << doctor.getId() << ", Patient ID: " << patient.getId() << endl;
        cout << "Amount: $" << fixed << setprecision(2) << totalAmount << ", Status: " << paymentStatus << endl;
    }

    void updateAmount(double newAmount) { totalAmount = newAmount; }
    void updatePaymentStatus(const string& newStatus) { paymentStatus = newStatus; }
};

// ============================
// Inventory Classes
// ============================
class InventoryItem {
protected:
    int itemID;
    string name;
    int quantity;
    double price;

public:
    InventoryItem(int id = 0, string itemName = "", int qty = 0, double cost = 0.0)
        : itemID(id), name(itemName), quantity(qty), price(cost) {}

    virtual void showItemDetails() const {
        cout << "ID: " << itemID << ", Name: " << name << ", Qty: " << quantity << ", Price: $" << price << endl;
    }

    int getItemID() const { return itemID; }

    virtual void addStock(int qty) {
        quantity += qty;
        cout << "✅ " << qty << " units added. Total: " << quantity << endl;
    }

    virtual void useStock(int qty) {
        if (quantity >= qty) {
            quantity -= qty;
            cout << "✔️ " << qty << " units used. Remaining: " << quantity << endl;
        } else {
            cout << "❌ Insufficient stock! Available: " << quantity << endl;
        }
    }

    virtual ~InventoryItem() {}
};

class Medicine : public InventoryItem {
private:
    string expiryDate;

public:
    Medicine(int id, string medName, int qty, double cost, string expDate)
        : InventoryItem(id, medName, qty, cost), expiryDate(expDate) {}

    void showItemDetails() const override {
        InventoryItem::showItemDetails();
        cout << "🗓️ Expiry Date: " << expiryDate << endl;
    }
};

class Equipment : public InventoryItem {
private:
    string maintenanceDate;

public:
    Equipment(int id, string equipName, int qty, double cost, string maintDate)
        : InventoryItem(id, equipName, qty, cost), maintenanceDate(maintDate) {}

    void showItemDetails() const override {
        InventoryItem::showItemDetails();
        cout << "🛠️ Next Maintenance: " << maintenanceDate << endl;
    }
};

// ============================
// Main Menu & Program
// ============================
int main() {
    cout << "🌟 Welcome to the Humanized Hospital System 🌟\n";

    const int MAX_DOCTORS = 10;
    const int MAX_PATIENTS = 10;
    Doctor doctors[MAX_DOCTORS];
    Patient patients[MAX_PATIENTS];
    int doctorCount = 0, patientCount = 0;

    vector<InventoryItem*> inventory;

    int mainChoice;
    do {
        separator();
        cout << "--- Main Menu ---\n";
        cout << "1. Hospital Management System\n";
        cout << "2. Inventory Management\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1: {
                separator();
                cout << "🏥 Hospital Management System\n";
                cout << "Feature-rich and human-friendly interface coming here...\n";
                break;
            }
            case 2: {
                separator();
                cout << "📦 Inventory Management\n";
                cout << "Feature-rich inventory UI coming here...\n";
                break;
            }
            case 3:
                cout << "👋 Exiting system. Take care!\n";
                break;
            default:
                cout << "❌ Invalid choice, try again.\n";
        }
    } while (mainChoice != 3);

    for (auto item : inventory) delete item;
    return 0;
}
