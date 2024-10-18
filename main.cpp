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

        // creating pointer to a Node called temp and assigning the head to it
        // temp will be pointer to traverse the DLL
        Node* temp = head;
        // Iterating through each position 
        for (int i = 0; i < position && temp; ++i)
            // moving the DLL forward by setting temp equal to the next pointer in the DLL
            temp = temp->next;

        // If temp is null - the iteration went too far and the user entered a position outside scope of DLL
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            // Delete dynamically allocated node and return
            delete newNode;
            return;
        }
        // At this point temp has iterated through the DLL to the point of insertion

        // INSERTION: because temp has next and prev pointer of the node before we want newNode to be inserted after temp and before temp->next
        // Assigning the next node of newNode to be temp next node
        newNode->next = temp->next;
        // Assigning the previous node of newNode to be the temp previous node
        newNode->prev = temp;
        // If there is non-null pointer at the node following temp
        if (temp->next)
            // Set the pointer of the next node's previous node to our newNode
            // This will link newNode and the next node in the DLL
            temp->next->prev = newNode;
        // else it is the end and in that case set tail to the newNode
        else
            tail = newNode;
        // temp is pointing to the node before where we want to insert - set the node before next pointer to newNode
        // this adds newNode after the temp node which is pointing one element before where newNode now resides
        temp->next = newNode;
    }
    // Function delete_val: Returns nothing and takes in a value that we will be searching for
    // function traverses DLL - if it finds the user-inputted value it deletes the node - else it just returns doing nothing
    void delete_val(int value) {
        // if there are no elements (head is null) return 
        if (!head) return;
        // get temp pointer
        Node* temp = head;
        // traverse the DLL while not having the value or not null
        while (temp && temp->data != value)
            temp = temp->next;
        // if temp is null - value wasn't found
        if (!temp) return; 
        // Value IS FOUND
        // set the previous element before temp equal to what temp is pointing to next
        if (temp->prev)
            temp->prev->next = temp->next;
        // else the element is the first
        else
        // set head pointing to the next after temp - removing first element
            head = temp->next; 
        // set element after's prev equal to what is before temp
        // this removes the next elements prev pointer removing the node to be deleted
        if (temp->next)
            temp->next->prev = temp->prev;
        // else it is the last element and the tail is set to what is before temp
        else
            tail = temp->prev; 
        // delete dynamically allocated memory avoid leakage
        delete temp;
    }

    // Function delete_pos: Similar to delete_val - but instead of value we want position that we will delete from user
    // returns nothing
    void delete_pos(int pos) {
        // Head is null there is nothing to delete
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        // If the position is the front - use a separate pop_front function 
        if (pos == 1) {
            pop_front();
            return;
        }
        // set temp to head - temp is used to traverse DLL
        Node* temp = head;
        // Go through each element in DLL 
        for (int i = 1; i < pos; i++){
            // If temp is null - we went too far
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            // else continue to iterate using the temp next pointer
            else
                temp = temp->next;
        }
        // if at the end temp is null - we went too far out of scope
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
        // if temp is the last element - use pop_back() function to delete element
        if (!temp->next) {
            pop_back();
            return;
        }
        // new pointer to previous element
        Node* tempPrev = temp->prev;
        // use both temps to skip the element at temp
        tempPrev->next = temp->next;
        // set element in front of temp to what's before temp 
        temp->next->prev = tempPrev;
        delete temp;
    }
    // push_back returns nothing
    // used to add element to end of DLL
    void push_back(int v) {
        // newNode to store user inputted data
        Node* newNode = new Node(v);
        // If there is no tail - no elements in list - set head and tail to newNode adding it in
        if (!tail)
            head = tail = newNode;
        else {
            // set the tail's next pointer to newNode - adding it after the last element
            tail->next = newNode;
            // set newNode's previous pointer to the tail - connecting the last element to the one before
            newNode->prev = tail;
            // tail is now newNode 
            tail = newNode;
        }
    }
    // push_front returns nothing and adds the user inputted value node to the beginning of DLL
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