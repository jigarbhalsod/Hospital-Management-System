# 🏥 Hospital Management System

A **console-based Hospital Management System in C++** designed to manage doctors, patients, appointments, billing, and inventory with structured logic and validation.

---

## 🚀 Project Purpose

Built for **IT Workshop Lab Evaluation** to demonstrate:

* Object-Oriented Design (OOP)
* Data handling & validation
* System-level thinking (not just features)

---

## 👥 Team

* Ayush
* Anupam
* Jigar
* Nishant

---

## ⚙️ Features

### 👩‍⚕️ Doctor Management

* Add doctors with ID, specialization, contact
* Prevent duplicate IDs

### 🧑‍⚕️ Patient Management

* Store patient records with illness
* Input validation for phone & ID

### 📅 Appointment System

* Connect Doctor ↔ Patient
* Unique Appointment ID generation

```
Format: [DoctorID(4)] + [PatientID(5)] + [Date]
Example: 00010001020240101
```

### 💰 Billing

* Track payments
* Update amount + status

### 📦 Inventory System

* Medicines (expiry tracking)
* Equipment (maintenance tracking)
* Stock add/remove with validation

---

## 🧠 System Design

```
Doctor ─────┐
            ├── Appointment ─── Patient
Inventory ──┘
```

---

## 🛠️ Tech Stack

* **Language:** C++
* **Concepts:** OOP, STL (vector, deque)
* **Interface:** Console-based CLI
* **Storage:** File handling (persistent data)

---

## ▶️ How to Run

```bash
g++ main.cpp -o hospital
./hospital
```

---

## 🧪 Sample Flow

```
1 → Add Doctor
2 → Add Patient
3 → Book Appointment
4 → View Data
```

---

## ⚠️ Constraints & Validations

| Input         | Rule              |
| ------------- | ----------------- |
| Phone         | Exactly 10 digits |
| Doctor ID     | 0–9999            |
| Patient ID    | 0–99999           |
| Duplicate IDs | Rejected          |

---

## ❌ Current Limitations

* No GUI (CLI only)
* No database (file-based)
* No authentication
* Linear search (not optimized)

---

## 🔥 Future Improvements

* GUI (Qt / Flutter)
* Database (MySQL/PostgreSQL)
* Fast lookup (hashing/indexing)
* Role-based access (Admin/Staff)
* Analytics dashboard

---

## 💡 What This Project Shows

* You can design **connected systems**, not isolated classes
* You understand **data flow + validation**
* You can move from **logic → working program**

---

## 🧭 Reality Check

If this project stays here, it’s **basic**.

To make it resume-worthy:

* Add file persistence properly
* Add delete/update operations
* Optimize search (maps)
* Show real test cases

---

## 📌 License

For academic and learning purposes.
