// COMSC-210 | Lab 22 | Sarthak Pani
// adapted from the instructor doubly linked list demo

#include <iostream>
using namespace std;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList();
    void push_back(int value);
    void push_front(int value);
    void insert_after(int value, int position);
    void delete_pos(int position);
    void pop_front();
    void pop_back();
    void delete_val(int value);
    void print();
    void print_reverse();
    ~DoublyLinkedList();
};

void show_list(DoublyLinkedList& list, const char* label, const char* expected);

int main() {
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    list.push_back(50);
    show_list(list, "Starting list", "10 20 30 40 50");

    // remove nodes from both ends
    list.pop_front();
    show_list(list, "pop_front(): head", "20 30 40 50");
    list.pop_back();
    show_list(list, "pop_back(): tail", "20 30 40");

    // delete by value at the middle and both ends
    list.delete_val(30);
    show_list(list, "delete_val(30): middle", "20 40");
    list.delete_val(20);
    show_list(list, "delete_val(20): head", "40");
    list.delete_val(40);
    show_list(list, "delete_val(40): only node", "List is empty");

    // reuse the empty list before normal scope cleanup
    list.push_front(60);
    list.push_back(70);
    show_list(list, "Reuse after deletions", "60 70");

    // delete middle, head, and tail by zero-based position
    list.push_back(80);
    list.push_back(90);
    list.push_back(100);
    show_list(list, "Starting list for position deletion", "60 70 80 90 100");
    list.delete_pos(2);
    show_list(list, "delete_pos(2): middle", "60 70 90 100");
    list.delete_pos(0);
    show_list(list, "delete_pos(0): head", "70 90 100");
    list.delete_pos(2);
    show_list(list, "delete_pos(2): tail", "70 90");

    // invalid positions leave the list unchanged
    list.delete_pos(-1);
    show_list(list, "delete_pos(-1): invalid", "70 90");
    list.delete_pos(2);
    show_list(list, "delete_pos(2): out of range", "70 90");

    return 0;
}

void show_list(DoublyLinkedList& list, const char* label, const char* expected) {
    cout << "\n" << label << endl;
    cout << "Expected forward: " << expected << endl;
    cout << "Forward: ";
    list.print();
    cout << "Backward: ";
    list.print_reverse();
}

DoublyLinkedList::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
}

void DoublyLinkedList::push_back(int value) {
    Node* newNode = new Node(value);
    if (!tail)
        head = tail = newNode;
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void DoublyLinkedList::push_front(int value) {
    Node* newNode = new Node(value);
    if (!head)
        head = tail = newNode;
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void DoublyLinkedList::insert_after(int value, int position) {
    if (position < 0) {
        cout << "Position must be >= 0." << endl;
        return;
    }

    Node* newNode = new Node(value);
    if (!head) {
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

void DoublyLinkedList::delete_pos(int position) {
    if (position < 0) {
        cout << "Position must be >= 0." << endl;
        return;
    }

    Node* temp = head;
    for (int i = 0; i < position && temp; ++i)
        temp = temp->next;

    if (!temp) {
        cout << "Position exceeds list size. Node not deleted.\n";
        return;
    }

    if (temp == head) {
        pop_front();
    } else if (temp == tail) {
        pop_back();
    } else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }
}

void DoublyLinkedList::pop_front() {
    if (!head) return;

    Node* temp = head;
    head = head->next;
    if (head)
        head->prev = nullptr;
    else
        tail = nullptr;
    delete temp;
}

void DoublyLinkedList::pop_back() {
    if (!tail) return;

    Node* temp = tail;
    tail = tail->prev;
    if (tail)
        tail->next = nullptr;
    else
        head = nullptr;
    delete temp;
}

void DoublyLinkedList::delete_val(int value) {
    if (!head) return;

    Node* temp = head;
    while (temp && temp->data != value)
        temp = temp->next;

    if (!temp) return;

    if (temp->prev) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;
    }

    if (temp->next) {
        temp->next->prev = temp->prev;
    } else {
        tail = temp->prev;
    }

    delete temp;
}

void DoublyLinkedList::print() {
    Node* current = head;
    if (!current) {
        cout << "List is empty" << endl;
        return;
    }
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void DoublyLinkedList::print_reverse() {
    Node* current = tail;
    if (!current) {
        cout << "List is empty" << endl;
        return;
    }
    while (current) {
        cout << current->data << " ";
        current = current->prev;
    }
    cout << endl;
}

DoublyLinkedList::~DoublyLinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}
