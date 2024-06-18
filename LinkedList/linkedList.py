class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    def insert_at_head(self, data):
        new_node = Node(data)
        new_node.next = self.head
        self.head = new_node

    def insert_at_end(self, data):
        new_node = Node(data)
        new_node.next = None

        if self.head is None:
            self.head = new_node
        else:
            current = self.head
            while current.next is not None:
                current = current.next
            current.next = new_node

    def delete_node(self, data):
        if self.head is None:
            return

        if self.head.data == data:
            temp = self.head
            self.head = self.head.next
            del temp
            return

        current = self.head
        while current.next is not None and current.next.data != data:
            current = current.next

        if current.next is None:
            return

        temp = current.next
        current.next = current.next.next
        del temp

    def print_list(self):
        current = self.head
        output = "Linked List: "
        while current is not None:
            output += str(current.data) + " "
            current = current.next
        print(output)

# Usage example
list = LinkedList()

list.insert_at_head(10)
list.insert_at_end(20)
list.insert_at_end(30)
list.insert_at_head(40)
list.delete_node(30)
list.delete_node(40)
list.insert_at_head(5)
list.print_list()
