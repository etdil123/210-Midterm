// Ethan Dilk | Midterm 1 | COMSC 210
#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// Initializing a class that will serve as the blueprint for initializing a DoublyLinkedList object
class DoublyLinkedList {
// private members of the class 
private:
    // Creating a struct called Node that will be the blueprint for each individual node in the doubly linked list 
    // Overall - struct stores data, pointer to next node, and pointer to previous node; essentially "linking" a list of Node structs together
    struct Node {
        // storing an integer of data 
        int data;
        // Pointer to a node that is one element previous to the current node
        Node* prev;
        // Pointer to a ndoe that is one element in-front of the current node 
        Node* next;

        // A parameter constructor for the Node struct
        // if the user fills in values upon creation of Node struct - the values will populate in data, prev, or next 
        // if p and n are left empty the values will be nullptr
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };
    // creating private class members
    // pointers to a node that will serve as the head (beginning) & tail (ending) of the doubly linked list
    Node* head;
    Node* tail;

public:
    // Default constructor - when a DoublyLinkList object is created head and tail will point to nullptr
    DoublyLinkedList() { head = nullptr; tail = nullptr; }
    
    // insert_after function: return nothing but takes two integer values
    // Purpose: insert a node after the position the user enters with a value the user enters in the node
    void insert_after(int value, int position) {
        // validation that position is not negative 
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }
        // Dynamically allocating a new instance of Node struct 
        Node* newNode = new Node(value);
        // If head is not true - there are no elements in DLL 
        if (!head) {
            // assign head and tail to newNode to serve as only element in DLL
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}