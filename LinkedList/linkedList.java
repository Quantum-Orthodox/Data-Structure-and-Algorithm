class Node {
    int data;
    Node next;

    Node(int data) {
        this.data = data;
        this.next = null;
    }
}

class LinkedList {
    Node head;

    LinkedList() {
        this.head = null;
    }

    void insertAtHead(int data) {
        Node newNode = new Node(data);
        newNode.next = head;
        head = newNode;
    }

    void insertAtEnd(int data) {
        Node newNode = new Node(data);
        newNode.next = null;

        if (head == null) {
            head = newNode;
        } else {
            Node current = head;
            while (current.next != null) {
                current = current.next;
            }
            current.next = newNode;
        }
    }

    void deleteNode(int data) {
        if (head == null) {
            return;
        }

        if (head.data == data) {
            head = head.next;
            return;
        }

        Node current = head;
        while (current.next != null && current.next.data != data) {
            current = current.next;
        }

        if (current.next == null) {
            return;
        }

        current.next = current.next.next;
    }

    void printList() {
        Node current = head;
        StringBuilder output = new StringBuilder("Linked List: ");
        while (current != null) {
            output.append(current.data).append(" ");
            current = current.next;
        }
        System.out.println(output.toString());
    }
}

public class Main {
    public static void main(String[] args) {
        LinkedList list = new LinkedList();

        list.insertAtHead(10);
        list.insertAtEnd(20);
        list.insertAtEnd(30);
        list.insertAtHead(40);
        list.deleteNode(30);
        list.deleteNode(40);
        list.insertAtHead(5);
        list.printList();
    }
}
