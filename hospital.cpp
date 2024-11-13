#include <iostream>
#include <string>
#include<fstream>
using namespace std;

class Person {
protected:
    int id;
    string name;
    string phone;

public:
    Person(int p_id, string p_name, string p_phone) {
        id = p_id;
        name = p_name;
        phone = p_phone;
    }

    void showPersonDetails() {
        cout << "ID: " << id << ", Name: " << name << ", Contact: " << phone << endl;
    }
};

class Doctor : public Person {
protected:
    string specialization;

public:
    Doctor(int doc_id, string doc_name, string doc_phone, string spec)
        : Person(doc_id, doc_name, doc_phone) {
        specialization = spec;
    }

    void showDoctorDetails() {
        showPersonDetails();
        cout << "Specialization: " << specialization << endl;
    }
};

class Patient : public Person {
protected:
    string illness;

public:
    Patient(int pat_id, string pat_name, string pat_phone, string disease)
        : Person(pat_id, pat_name, pat_phone) {
        illness = disease;
    }

    void showPatientDetails() {
        showPersonDetails();
        cout << "Illness: " << illness << endl;
    }
};

class Billing : public Doctor, public Patient {
private:
    double totalAmount;
    string paymentStatus;

public:
    Billing(int doc_id, string doc_name, string doc_phone, string spec, 
            int pat_id, string pat_name, string pat_phone, string disease, 
            double amount, string status)
        : Doctor(doc_id, doc_name, doc_phone, spec), 
          Patient(pat_id, pat_name, pat_phone, disease) {
        totalAmount = amount;
        paymentStatus = status;
    }

    void showBillingDetails() {
        cout << "Billing Info:" << endl;
        cout << "Doctor ID: " << Doctor::id << ", Patient ID: " << Patient::id << endl;
        cout << "Amount: $" << totalAmount << ", Payment Status: " << paymentStatus << endl;
    }

    void updateAmount(double newAmount) {
        totalAmount = newAmount;
    }

    void updatePaymentStatus(string newStatus) {
        paymentStatus = newStatus;
    }
};

int main() {
    Doctor doc(101, "Dr. Smith", "1234567890", "Cardiology");
    Patient pat(201, "John Doe", "0987654321", "Heart Disease");
    Billing bill(101, "Dr. Smith", "1234567890", "Cardiology", 
                 201, "John Doe", "0987654321", "Heart Disease", 
                 1500.00, "Unpaid");

    cout << "Doctor Details:" << endl;
    doc.showDoctorDetails();
    cout << endl;

    cout << "Patient Details:" << endl;
    pat.showPatientDetails();
    cout << endl;

    cout << "Billing Details:" << endl;
    bill.showBillingDetails();
    cout << endl;

    bill.updateAmount(2000.00);
    bill.updatePaymentStatus("Paid");

    cout << "Updated Billing Details:" << endl;
    bill.showBillingDetails();

    return 0;
}
