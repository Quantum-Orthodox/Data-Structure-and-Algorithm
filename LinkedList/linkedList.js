class Node {
  constructor(data) {
    this.data = data;
    this.next = null;
  }
}

class LinkedList {
  constructor() {
    this.head = null;
  }

  insertAtHead(data) {
    const newNode = new Node(data);
    newNode.next = this.head;
    this.head = newNode;
  }

  insertAtEnd(data) {
    const newNode = new Node(data);
    newNode.next = null;

    if (this.head === null) {
      this.head = newNode;
    } else {
      let current = this.head;
      while (current.next !== null) {
        current = current.next;
      }
      current.next = newNode;
    }
  }

  deleteNode(data) {
    if (this.head === null) {
      return;
    }

    if (this.head.data === data) {
      const temp = this.head;
      this.head = this.head.next;
      // In JavaScript, garbage collection handles memory deallocation
      return;
    }

    let current = this.head;
    while (current.next !== null && current.next.data !== data) {
      current = current.next;
    }

    if (current.next === null) {
      return;
    }

    const temp = current.next;
    current.next = current.next.next;
    // In JavaScript, garbage collection handles memory deallocation
  }

  printList() {
    let current = this.head;
    let output = "Linked List: ";
    while (current !== null) {
      output += current.data + " ";
      current = current.next;
    }
    console.log(output);
  }
}

// Usage example
const list = new LinkedList();

list.insertAtHead(10);
list.insertAtEnd(20);
list.insertAtEnd(30);
list.insertAtHead(40);
list.deleteNode(30);
list.deleteNode(40);
list.insertAtHead(5);
list.printList();
