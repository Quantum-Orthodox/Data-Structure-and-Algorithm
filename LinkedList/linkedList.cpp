#include <iostream>
using namespace std;

class Node {
    public:
        int data;
        Node *next;

        Node(int data) {
            this->data = data;
            this->next = nullptr;
        }
};


class LinkedList {
    public:
        Node *head;

        LinkedList() {
            this->head = nullptr;
        };

        void insertAtHead(int data) {
            Node* new_node = new Node(data);
            new_node->next = this->head;
            this->head = new_node;
        };

        void insertAtEnd(int data) {
            Node* new_node = new Node(data);
            new_node->next = nullptr;

            if(head == nullptr) {
                head = new_node;
            } else {
                Node* current = head;
                while(current->next != nullptr) {
                    current = current->next;
                }
                current->next = new_node;
            }
        };


        void deleteNode(int data) {
            if(head == nullptr) {
                return;
            };

            if(head->data == data) {
                Node* temp = head;
                head = head->next;
                delete temp;
                return;
            }

            Node* current = head;
            while(current->next != nullptr && current->next->data != data) {
                current = current->next;
            }

            if(current->next == nullptr) {
                return;
            }

            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        };


        void printList() {
            Node* current = head;
            cout << "Linked List:";
            while(current != nullptr) {
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        }
};


int main() {
    LinkedList list;

    list.insertAtHead(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtHead(40);
    list.deleteNode(30);
    list.deleteNode(40);
    list.insertAtHead(5);
    list.printList();
}