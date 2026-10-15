#include <iostream>
#include <string>
using namespace std;

// Part 1: Node structure
struct PatientNode
{
    int patientID;
    string patientName;
    string reason;
    int priority;
    PatientNode* next;
};

// Part 2: Priority Queue class
class PriorityQueue
{
private:
    PatientNode* front;
    PatientNode* rear;
    int count;

public:
    // Constructor
    PriorityQueue()
    {
        front = NULL;
        rear = NULL;
        count = 0;
    }

    // Add patient according to priority
    void Add(PatientNode* patient)
    {
        if (patient == NULL)
            return;

        patient->next = NULL;

        // Case 1: Queue is empty
        if (front == NULL)
        {
            front = rear = patient;
        }
        // Case 2: New patient has higher priority
        else if (patient->priority < front->priority)
        {
            patient->next = front;
            front = patient;
        }
        // Case 3: Insert in middle or at rear
        else
        {
            PatientNode* current = front;

            while (current->next != NULL &&
                   current->next->priority <= patient->priority)
            {
                current = current->next;
            }

            patient->next = current->next;
            current->next = patient;

            if (patient->next == NULL)
            {
                rear = patient;
            }
        }

        count++;
    }

    // Remove the highest-priority patient
    PatientNode* Remove()
    {
        if (front == NULL)
        {
            return NULL;
        }

        PatientNode* temp = front;
        front = front->next;

        if (front == NULL)
        {
            rear = NULL;
        }

        temp->next = NULL;
        count--;

        return temp;
    }

    // Check whether queue is empty
    bool IsEmpty()
    {
        return front == NULL;
    }

    // Check whether queue is not empty
    bool IsNotEmpty()
    {
        return front != NULL;
    }

    // Return total waiting patients
    int GetCount()
    {
        return count;
    }

    // Display the queue
    void PrintQueue()
    {
        if (IsEmpty())
        {
            cout << "No patients are waiting.\n";
            return;
        }

        PatientNode* current = front;

        cout << "\n--- MedQueue: Front to Rear ---\n";

        while (current != NULL)
        {
            cout << "Patient ID: " << current->patientID << endl;
            cout << "Name: " << current->patientName << endl;
            cout << "Reason: " << current->reason << endl;
            cout << "Priority: " << current->priority << endl;
            cout << "------------------------------\n";

            current = current->next;
        }
    }

    // Destructor
    ~PriorityQueue()
    {
        while (front != NULL)
        {
            PatientNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = NULL;
        count = 0;
    }

private:
    // Prevent unsafe shallow copying
    PriorityQueue(const PriorityQueue&);
    PriorityQueue& operator=(const PriorityQueue&);
};

// Part 3: Create a patient node
PatientNode* CreatePatient(int id, string name,
                           string reason, int priority)
{
    if (priority < 1 || priority > 3)
    {
        cout << "Invalid priority. Use 1, 2, or 3.\n";
        return NULL;
    }

    PatientNode* patient = new PatientNode;

    patient->patientID = id;
    patient->patientName = name;
    patient->reason = reason;
    patient->priority = priority;
    patient->next = NULL;

    return patient;
}

// Part 4: Main function
int main()
{
    PriorityQueue q;

    // Add four sample patients
    q.Add(CreatePatient(101, "Ali",
                        "Routine appointment", 3));

    q.Add(CreatePatient(102, "Ahmed",
                        "Urgent request", 1));

    q.Add(CreatePatient(103, "Bilal",
                        "Important appointment", 2));

    q.Add(CreatePatient(104, "Hamza",
                        "Urgent request", 1));

    // Display queue
    q.PrintQueue();

    cout << "\nPatients waiting: " << q.GetCount() << endl;
    cout << "Is queue empty? "
         << (q.IsEmpty() ? "Yes" : "No") << endl;
    cout << "Is queue not empty? "
         << (q.IsNotEmpty() ? "Yes" : "No") << endl;

    // Process one patient
    PatientNode* processed = q.Remove();

    if (processed != NULL)
    {
        cout << "\nProcessed patient: "
             << processed->patientName << endl;

        delete processed;
    }

    // Display remaining queue
    q.PrintQueue();

    cout << "\nPatients waiting now: "
         << q.GetCount() << endl;

    return 0;
}
