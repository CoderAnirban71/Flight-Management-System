// ============================================================
//  main.cpp  --  Flight Management System (SIMPLE VERSION)
//  This file only has the menu. The real DSA work is done by the
//  functions in dsa_lib.cpp.
//
//  Compile:  g++ main.cpp -o flight
//  Run:      ./flight      (Windows: flight.exe)
//  Note: enter names and cities as a single word (Rahul, Delhi)
// ============================================================
#include "dsa_lib.cpp"

int nextTicketId = 1001;

// Add a new flight to the array, the tree and the graph
void addNewFlight(int id, string from, string to, int price) {
    addFlight(id, from, to, price);          // ARRAY

    Flight f;
    f.id = id;
    f.from = from;
    f.to = to;
    f.price = price;
    root = insertBST(root, f);               // TREE

    addRoute(from, to);                      // GRAPH
}

// Book a ticket: LINKED LIST + HASH + STACK
void bookTicket(string name) {
    int ticketId = nextTicketId;
    nextTicketId++;

    addPassenger(ticketId, name);            // LINKED LIST
    insertHash(ticketId, name);              // HASHING
    push(ticketId);                          // STACK
    cout << "Ticket booked! Ticket ID: " << ticketId << endl;
}

int main() {
    // Sample flights
    addNewFlight(103, "Mumbai", "Bangalore", 3500);
    addNewFlight(101, "Delhi", "Mumbai", 5000);
    addNewFlight(105, "Kolkata", "Chennai", 4000);
    addNewFlight(102, "Delhi", "Kolkata", 4500);
    addNewFlight(104, "Bangalore", "Chennai", 2500);

    int choice;
    do {
        cout << "\n====== FLIGHT MANAGEMENT SYSTEM ======\n";
        cout << "-- ARRAY --\n";
        cout << " 1. View all flights\n";
        cout << " 2. Sort flights (Bubble Sort)\n";
        cout << " 3. Search flight (Linear Search)\n";
        cout << " 4. Search flight (Binary Search)\n";
        cout << "-- TREE --\n";
        cout << " 5. View flights in ID order (Inorder)\n";
        cout << " 6. Search flight (BST Search)\n";
        cout << "-- LINKED LIST / HASH / STACK / QUEUE --\n";
        cout << " 7. Book a ticket\n";
        cout << " 8. Undo last booking (Stack)\n";
        cout << " 9. View all passengers (Linked List)\n";
        cout << "10. Find passenger by ticket ID (Hashing)\n";
        cout << "11. Add a name to the waiting list (Queue)\n";
        cout << "12. Book the first person on the waiting list (Queue)\n";
        cout << "13. View waiting list\n";
        cout << "-- GRAPH --\n";
        cout << "14. View all routes\n";
        cout << "15. Visit cities (BFS)\n";
        cout << "16. Visit cities (DFS)\n";
        cout << " 0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            showFlights();
        }
        else if (choice == 2) {
            bubbleSort();
            cout << "Sorted:\n";
            showFlights();
        }
        else if (choice == 3) {
            int id;
            cout << "Flight ID: ";
            cin >> id;
            int index = linearSearch(id);
            if (index == -1)
                cout << "Flight not found.\n";
            else
                cout << "Found! " << flights[index].from << " -> " << flights[index].to << endl;
        }
        else if (choice == 4) {
            int id;
            cout << "Flight ID: ";
            cin >> id;
            int index = binarySearch(id);    // sorting happens inside binarySearch
            if (index == -1)
                cout << "Flight not found.\n";
            else
                cout << "Found! " << flights[index].from << " -> " << flights[index].to << endl;
        }
        else if (choice == 5) {
            cout << "ID\tFrom\t\tTo\t\tPrice\n";
            inorder(root);
        }
        else if (choice == 6) {
            int id;
            cout << "Flight ID: ";
            cin >> id;
            TreeNode *found = searchBST(root, id);
            if (found == NULL)
                cout << "Flight not found.\n";
            else
                cout << "Found! " << found->data.from << " -> " << found->data.to << endl;
        }
        else if (choice == 7) {
            string name;
            cout << "Passenger name: ";
            cin >> name;
            bookTicket(name);
        }
        else if (choice == 8) {
            int ticketId = pop();            // the latest booking
            if (ticketId == -1) {
                cout << "Nothing to undo.\n";
            } else {
                removePassenger(ticketId);
                deleteHash(ticketId);
                cout << "Ticket " << ticketId << " cancelled.\n";
            }
        }
        else if (choice == 9) {
            showPassengers();
        }
        else if (choice == 10) {
            int ticketId;
            cout << "Ticket ID: ";
            cin >> ticketId;
            string name = searchHash(ticketId);
            if (name == "")
                cout << "Ticket not found.\n";
            else
                cout << "Passenger: " << name << endl;
        }
        else if (choice == 11) {
            string name;
            cout << "Name: ";
            cin >> name;
            enqueue(name);
            cout << "Added to the waiting list.\n";
        }
        else if (choice == 12) {
            string name = dequeue();         // the person who joined first
            if (name == "")
                cout << "Waiting list is empty.\n";
            else
                bookTicket(name);
        }
        else if (choice == 13) {
            showWaitingList();
        }
        else if (choice == 14) {
            showRoutes();
        }
        else if (choice == 15) {
            string start;
            cout << "Start city: ";
            cin >> start;
            cout << "BFS order: ";
            bfs(start);
        }
        else if (choice == 16) {
            string start;
            cout << "Start city: ";
            cin >> start;
            cout << "DFS order: ";
            startDfs(start);
        }
        else if (choice != 0) {
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    cout << "Thank you!\n";
    return 0;
}