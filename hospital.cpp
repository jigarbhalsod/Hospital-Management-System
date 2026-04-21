#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

// ================= UTIL =================
string pad(int num, int width) {
    string s = to_string(num);
    return string(width - s.length(), '0') + s;
}

// ================= INPUT =================
string inputPhone() {
    string p;
    cin >> p;
    while (p.length() != 10 || !all_of(p.begin(), p.end(), ::isdigit)) {
        cout << "Invalid phone. Enter 10 digits: ";
        cin >> p;
    }
    return p;
}

// ================= BASE =================
class Person {
protected:
    int id;
    string name, phone;

public:
    Person(int i, string n, string p) : id(i), name(n), phone(p) {}
    int getId() const { return id; }

    virtual void show() const {
        cout << "ID: " << id << " | Name: " << name << " | Phone: " << phone << endl;
    }
};

// ================= DOCTOR =================
class Doctor : public Person {
    string spec;
    deque<string> appointments;

public:
    Doctor(int i, string n, string p, string s)
        : Person(i, n, p), spec(s) {}

    void addAppointment(string id) {
        appointments.push_back(id);
    }

    void show() const override {
        Person::show();
        cout << "Specialization: " << spec << endl;
    }
};

// ================= PATIENT =================
class Patient : public Person {
    string illness;

public:
    Patient(int i, string n, string p, string ill)
        : Person(i, n, p), illness(ill) {}

    void show() const override {
        Person::show();
        cout << "Illness: " << illness << endl;
    }
};

// ================= APPOINTMENT =================
class Appointment {
public:
    string id;
    int docID, patID, date;

    Appointment(int d, int p, int dt) {
        docID = d;
        patID = p;
        date = dt;
        id = pad(d,4) + pad(p,5) + to_string(dt);
    }

    void show() {
        cout << "AppID: " << id
             << " | Doc: " << docID
             << " | Pat: " << patID
             << " | Date: " << date << endl;
    }
};

// ================= SEARCH =================
Doctor* findDoctor(vector<Doctor>& v, int id) {
    for (auto& d : v)
        if (d.getId() == id) return &d;
    return nullptr;
}

Patient* findPatient(vector<Patient>& v, int id) {
    for (auto& p : v)
        if (p.getId() == id) return &p;
    return nullptr;
}

// ================= MAIN =================
int main() {
    vector<Doctor> doctors;
    vector<Patient> patients;
    vector<Appointment> appointments;

    int choice;

    do {
        cout << "\n1.Add Doctor\n2.Add Patient\n3.Book Appointment\n4.View All\n5.Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            int id; string name, phone, spec;
            cout << "Enter ID Name Phone Spec:\n";
            cin >> id >> name;
            phone = inputPhone();
            cin >> spec;

            if (findDoctor(doctors, id)) {
                cout << "Doctor ID exists!\n";
                continue;
            }

            doctors.emplace_back(id, name, phone, spec);
        }

        else if (choice == 2) {
            int id; string name, phone, ill;
            cout << "Enter ID Name Phone Illness:\n";
            cin >> id >> name;
            phone = inputPhone();
            cin >> ill;

            if (findPatient(patients, id)) {
                cout << "Patient ID exists!\n";
                continue;
            }

            patients.emplace_back(id, name, phone, ill);
        }

        else if (choice == 3) {
            int d, p, date;
            cout << "Enter DoctorID PatientID Date(YYYYMMDD): ";
            cin >> d >> p >> date;

            Doctor* doc = findDoctor(doctors, d);
            Patient* pat = findPatient(patients, p);

            if (!doc || !pat) {
                cout << "Invalid Doctor/Patient ID\n";
                continue;
            }

            Appointment a(d, p, date);
            appointments.push_back(a);
            doc->addAppointment(a.id);

            cout << "Appointment Booked!\n";
        }

        else if (choice == 4) {
            cout << "\n--- Doctors ---\n";
            for (auto& d : doctors) d.show();

            cout << "\n--- Patients ---\n";
            for (auto& p : patients) p.show();

            cout << "\n--- Appointments ---\n";
            for (auto& a : appointments) a.show();
        }

    } while (choice != 5);

    return 0;
}
