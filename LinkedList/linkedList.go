package main

import "fmt"

type Node struct {
    data int
    next *Node
}

type LinkedList struct {
    head *Node
}

func (list *LinkedList) insertAtHead(data int) {
    newNode := &Node{data: data, next: list.head}
    list.head = newNode
}

func (list *LinkedList) insertAtEnd(data int) {
    newNode := &Node{data: data, next: nil}

    if list.head == nil {
        list.head = newNode
    } else {
        current := list.head
        for current.next != nil {
            current = current.next
        }
        current.next = newNode
    }
}

func (list *LinkedList) deleteNode(data int) {
    if list.head == nil {
        return
    }

    if list.head.data == data {
        list.head = list.head.next
        return
    }

    current := list.head
    for current.next != nil && current.next.data != data {
        current = current.next
    }

    if current.next == nil {
        return
    }

    current.next = current.next.next
}

func (list *LinkedList) printList() {
    current := list.head
    fmt.Print("Linked List: ")
    for current != nil {
        fmt.Print(current.data, " ")
        current = current.next
    }
    fmt.Println()
}

func main() {
    list := &LinkedList{}

    list.insertAtHead(10)
    list.insertAtEnd(20)
    list.insertAtEnd(30)
    list.insertAtHead(40)
    list.deleteNode(30)
    list.deleteNode(40)
    list.insertAtHead(5)
    list.printList()
}
