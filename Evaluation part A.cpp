#include <iostream>
#include <string>
using namespace std;

// Task 1: Book Request Node
struct BookRequestNode
{
    int studentID;
    string studentName;
    int bookID;
    string bookTitle;
    int priority;
    BookRequestNode* next;
};

// Task 2: Priority Queue Class
class PriorityQueue
{
private:
    BookRequestNode* front;
    BookRequestNode* rear;
    int count;

    // Helper function for deep copying
    void CopyFrom(const PriorityQueue& other)
    {
        BookRequestNode* current = other.front;

        while (current != NULL)
        {
            BookRequestNode* node = new BookRequestNode;

            node->studentID = current->studentID;
            node->studentName = current->studentName;
            node->bookID = current->bookID;
            node->bookTitle = current->bookTitle;
            node->priority = current->priority;
            node->next = NULL;

            if (front == NULL)
            {
                front = rear = node;
            }
            else
            {
                rear->next = node;
                rear = node;
            }

            count++;
            current = current->next;
        }
    }

public:
    // Constructor
    PriorityQueue()
    {
        front = NULL;
        rear = NULL;
        count = 0;
    }

    // Copy Constructor: Deep Copy
    PriorityQueue(const PriorityQueue& other)
    {
        front = NULL;
        rear = NULL;
        count = 0;

        CopyFrom(other);
    }

    // Assignment Operator: Deep Copy
    PriorityQueue& operator=(const PriorityQueue& other)
    {
        if (this != &other)
        {
            // Delete existing nodes
            while (front != NULL)
            {
                BookRequestNode* temp = front;
                front = front->next;
                delete temp;
            }

            rear = NULL;
            count = 0;

            // Copy nodes from the other queue
            CopyFrom(other);
        }

        return *this;
    }

    // Add a request according to priority
    void Add(BookRequestNode* request)
    {
        if (request == NULL)
            return;

        request->next = NULL;

        // Case 1: Queue is empty
        if (front == NULL)
        {
            front = rear = request;
        }
        // Case 2: New request has higher priority
        else if (request->priority < front->priority)
        {
            request->next = front;
            front = request;
        }
        // Case 3: Insert in the middle or at the end
        else
        {
            BookRequestNode* current = front;

            while (current->next != NULL &&
                   current->next->priority <= request->priority)
            {
                current = current->next;
            }

            request->next = current->next;
            current->next = request;

            if (request->next == NULL)
            {
                rear = request;
            }
        }

        count++;
    }

    // Remove the highest-priority request
    BookRequestNode* Remove()
    {
        if (front == NULL)
        {
            return NULL;
        }

        BookRequestNode* temp = front;
        front = front->next;

        if (front == NULL)
        {
            rear = NULL;
        }

        temp->next = NULL;
        count--;

        return temp;
    }

    // Check whether the queue is empty
    bool IsEmpty()
    {
        return front == NULL;
    }

    // Check whether the queue is not empty
    bool IsNotEmpty()
    {
        return front != NULL;
    }

    // Return the number of requests
    int GetCount()
    {
        return count;
    }

    // Display all requests
    void PrintQueue()
    {
        if (IsEmpty())
        {
            cout << "\nNo book requests are waiting.\n";
            return;
        }

        BookRequestNode* current = front;

        cout << "\n--- Library Book Request Queue ---\n";

        while (current != NULL)
        {
            cout << "Student ID: " << current->studentID << endl;
            cout << "Student Name: "
                 << current->studentName << endl;
            cout << "Book ID: " << current->bookID << endl;
            cout << "Book Title: " << current->bookTitle << endl;
            cout << "Priority: " << current->priority << endl;
            cout << "---------------------------------\n";

            current = current->next;
        }
    }

    // Destructor: Release all remaining nodes
    ~PriorityQueue()
    {
        while (front != NULL)
        {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = NULL;
        count = 0;
    }
};

// Task 3: Create a new book request
BookRequestNode* CreateRequest(
    int studentID,
    string studentName,
    int bookID,
    string bookTitle,
    int priority)
{
    if (priority < 1 || priority > 3)
    {
        cout << "Invalid priority. Use 1, 2, or 3.\n";
        return NULL;
    }

    BookRequestNode* request = new BookRequestNode;

    request->studentID = studentID;
    request->studentName = studentName;
    request->bookID = bookID;
    request->bookTitle = bookTitle;
    request->priority = priority;
    request->next = NULL;

    return request;
}

// Task 4: Menu-Driven Main Function
int main()
{
    PriorityQueue q;
    int choice;

    do
    {
        cout << "\n===== Library Book Request System =====\n";
        cout << "1. Add Book Request\n";
        cout << "2. Process Highest-Priority Request\n";
        cout << "3. Display All Requests\n";
        cout << "4. Check Queue Status\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                int studentID;
                int bookID;
                int priority;
                string studentName;
                string bookTitle;

                cout << "Enter student ID: ";
                cin >> studentID;

                cout << "Enter student name: ";
                getline(cin >> ws, studentName);

                cout << "Enter book ID: ";
                cin >> bookID;

                cout << "Enter book title: ";
                getline(cin >> ws, bookTitle);

                cout << "Enter priority:\n";
                cout << "1 = Urgent Exam Request\n";
                cout << "2 = Assignment/Project\n";
                cout << "3 = Normal Reading\n";
                cout << "Priority: ";

                cin >> priority;

                if (priority < 1 || priority > 3)
                {
                    cout << "Invalid priority. Request not added.\n";
                    break;
                }

                BookRequestNode* request =
                    CreateRequest(studentID, studentName,
                                  bookID, bookTitle, priority);

                q.Add(request);

                cout << "Book request added successfully.\n";
                break;
            }

            case 2:
            {
                BookRequestNode* processed = q.Remove();

                if (processed == NULL)
                {
                    cout << "No requests to process.\n";
                }
                else
                {
                    cout << "\nProcessing highest-priority request:\n";
                    cout << "Student: "
                         << processed->studentName << endl;
                    cout << "Book: "
                         << processed->bookTitle << endl;
                    cout << "Priority: "
                         << processed->priority << endl;

                    delete processed;
                }

                break;
            }

            case 3:
                q.PrintQueue();
                break;

            case 4:
                cout << "\nTotal waiting requests: "
                     << q.GetCount() << endl;

                if (q.IsEmpty())
                {
                    cout << "Queue status: Empty\n";
                }
                else
                {
                    cout << "Queue status: Not Empty\n";
                }

                break;

            case 5:
                cout << "Exiting Library Book Request System.\n";
                break;

            default:
                cout << "Invalid choice. Enter a number from 1 to 5.\n";
        }

    } while (choice != 5);

    return 0;
}
