// ============================================================
//  FILE     : 06_practice_queue_array.cpp
//  TOPIC    : Queue — Using Array
//  TITLE    : Queue — Linear Queue, Student Queue, Circular Queue
//  TYPE     : Practice
//  CONCEPTS : Queue FIFO, enqueue, dequeue, peek, circular indexing
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// ============================================================
//  PART 1 — Basic Integer Queue (Array)
// ============================================================

class Queue {
public:
    int* arr;
    int  front;
    int  rear;
    int  capacity;

    Queue(int size) {
        capacity = size;
        arr      = new int[capacity];
        front    = rear = -1;
    }

    bool is_empty() { return front == -1; }
    bool is_full()  { return rear == capacity - 1; }

    // Enqueue — add at rear
    void enqueue(int val) {
        if (is_full()) { cout << "Queue is full.\n"; return; }
        if (is_empty()) front = rear = 0;
        else            rear++;
        arr[rear] = val;
    }

    // Dequeue — remove from front
    void dequeue() {
        if (is_empty()) { cout << "Queue is empty.\n"; return; }
        cout << arr[front] << " dequeued.\n";
        if (front == rear) front = rear = -1;
        else               front++;
    }

    int peek_front() {
        if (is_empty()) { cout << "Queue is empty.\n"; return -1; }
        return arr[front];
    }

    int peek_rear() {
        if (is_empty()) { cout << "Queue is empty.\n"; return -1; }
        return arr[rear];
    }

    void print() {
        if (is_empty()) { cout << "Queue is empty.\n"; return; }
        cout << "Queue: ";
        for (int i = front; i <= rear; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

// ============================================================
//  PART 2 — Student Queue (Array)
// ============================================================

struct Student {
    int   id;
    string name;
    float cgpa;
};

class StudentQueue {
public:
    Student* arr;
    int      front, rear, capacity;

    StudentQueue(int size) {
        capacity = size;
        arr      = new Student[capacity];
        front    = rear = -1;
    }

    bool is_empty() { return front == -1; }
    bool is_full()  { return rear == capacity - 1; }

    void enqueue(Student s) {
        if (is_full()) { cout << "Queue is full.\n"; return; }
        if (is_empty()) front = rear = 0;
        else            rear++;
        arr[rear] = s;
        cout << s.name << " joined the queue.\n";
    }

    void dequeue() {
        if (is_empty()) { cout << "Queue is empty.\n"; return; }
        cout << arr[front].name << " (ID: " << arr[front].id
             << ", CGPA: " << arr[front].cgpa << ") processed.\n";
        if (front == rear) front = rear = -1;
        else               front++;
    }

    void print() {
        if (is_empty()) { cout << "Queue is empty.\n"; return; }
        cout << "Current Queue:\n";
        for (int i = front; i <= rear; i++)
            cout << "  ID: " << arr[i].id << " | Name: " << arr[i].name
                 << " | CGPA: " << arr[i].cgpa << endl;
    }
};

// ============================================================
//  PART 3 — Circular Queue (Array)
// ============================================================

class CircularQueue {
public:
    int* arr;
    int  front, rear, capacity;

    CircularQueue(int size) {
        capacity = size;
        arr      = new int[capacity];
        front    = rear = -1;
    }

    bool is_empty() { return front == -1; }
    bool is_full()  { return (rear + 1) % capacity == front; }

    void enqueue(int val) {
        if (is_full()) { cout << "Circular queue is full.\n"; return; }
        if (is_empty()) front = rear = 0;
        else            rear = (rear + 1) % capacity;
        arr[rear] = val;
    }

    void dequeue() {
        if (is_empty()) { cout << "Queue is empty.\n"; return; }
        cout << arr[front] << " dequeued.\n";
        if (front == rear) front = rear = -1;
        else               front = (front + 1) % capacity;
    }

    void print() {
        if (is_empty()) { cout << "Queue is empty.\n"; return; }
        cout << "Circular Queue: ";
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear) break;
            i = (i + 1) % capacity;
        }
        cout << endl;
    }
};

// ----- Main — Demo of all three -----
int main() {
    // --- Basic Queue ---
    cout << "=== Basic Integer Queue ===\n";
    Queue q(10);
    q.enqueue(100);
    q.enqueue(200);
    q.enqueue(300);
    q.print();
    q.dequeue();
    q.print();
    cout << "Front: " << q.peek_front() << " | Rear: " << q.peek_rear() << endl;

    // --- Student Queue ---
    cout << "\n=== Student Queue ===\n";
    StudentQueue sq(5);
    sq.enqueue({101, "Mustafa",       3.5f});
    sq.enqueue({103, "Mustafa Javed", 3.7f});
    sq.enqueue({105, "Mustafa Sheikh",3.85f});
    sq.print();
    sq.dequeue();
    sq.print();

    // --- Circular Queue ---
    cout << "\n=== Circular Queue ===\n";
    CircularQueue cq(5);
    cq.enqueue(10);
    cq.enqueue(20);
    cq.enqueue(30);
    cq.print();
    cq.dequeue();
    cq.enqueue(40);
    cq.print();

    return 0;
}
