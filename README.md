# Multithreaded Data Logger in C (Windows Threads)

## 📌 Project Overview
This project implements a multithreaded data logging system in C using the Windows API.  
It simulates an RTOS-style architecture with producer-consumer design, shared buffer management, and synchronized thread communication.

---

## 🚀 Features

- Multithreading using Windows API (`CreateThread`)
- Producer–Consumer architecture
- Shared buffer with synchronization (`CRITICAL_SECTION`)
- Real-time data generation and logging
- File-based data storage (`data.txt`)
- System monitoring thread

---

## 🏗️ System Architecture

Sensor Thread → produces data  
Logger Thread → consumes & writes to file  
Monitor Thread → displays system status  

All threads communicate using a shared buffer protected by a mutex.

---

## 📁 Project Structure

c-multithreaded-data-logger
│
├── main.c
├── logger.h
├── README.md   ✅ (newly added)


---

## ⚙️ Technologies Used
- C Programming
- Windows API
- Multithreading
- Synchronization using Critical Section
- File Handling

---

## ▶️ How to Run

### Compile
gcc main.c -o logger.exe
### Run

---

## 🧠 Concepts Demonstrated
- Multithreading in C
- Producer–Consumer problem
- Inter-thread communication
- Mutex/Lock synchronization
- RTOS-style task architecture

---

## 📌 Future Improvements
- Circular buffer implementation
- Priority-based logging
- File rotation mechanism
- GUI-based monitoring dashboard

---

## 👨‍💻 Author
**Manoj Kumar N**  
GitHub: https://github.com/jo-codes-dev
