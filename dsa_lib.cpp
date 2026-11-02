// ============================================================
//  dsa_lib.cpp  --  SIMPLE VERSION
//  All DSA functions live here. The data is also kept global in this
//  file, so we don't have to pass anything into the functions.
// ============================================================
#ifndef DSA_LIB_H          // include guard: don't include this file twice
#define DSA_LIB_H

#include <iostream>
#include <string>
using namespace std;

struct Flight {
    int id;
    string from;
    string to;
    int price;
};

// ============================================================
//  1. ARRAY  -- list of all flights
// ============================================================
Flight flights[50];
int flightCount = 0;

// Add a new flight at the end
void addFlight(int id, string from, string to, int price) {
    flights[flightCount].id = id;
    flights[flightCount].from = from;
    flights[flightCount].to = to;
    flights[flightCount].price = price;
    flightCount++;
}

void showFlights() {
    cout << "ID\tFrom\t\tTo\t\tPrice\n";
    for (int i = 0; i < flightCount; i++) {
        cout << flights[i].id << "\t" << flights[i].from << "\t\t"
             << flights[i].to << "\t\t" << flights[i].price << endl;
    }
}

// Linear Search: check one by one. Returns the index if found, else -1
int linearSearch(int id) {
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].id == id)
            return i;
    }
    return -1;
}

// Bubble Sort: arrange flights by ID, smallest to largest
void bubbleSort() {
    for (int i = 0; i < flightCount - 1; i++) {
        for (int j = 0; j < flightCount - i - 1; j++) {
            if (flights[j].id > flights[j + 1].id) {
                Flight temp = flights[j];
                flights[j] = flights[j + 1];
                flights[j + 1] = temp;
            }
        }
    }
}

// Binary Search: the array must be sorted, so we call bubbleSort() first
int binarySearch(int id) {
    bubbleSort();                      // sort first
    int low = 0, high = flightCount - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (flights[mid].id == id)
            return mid;
        else if (flights[mid].id < id)
            low = mid + 1;             // search the right half
        else
            high = mid - 1;            // search the left half
    }
    return -1;
}

// ============================================================
//  2. LINKED LIST  -- list of passengers
// ============================================================
struct Node {
    int ticketId;
    string name;
    Node *next;
};

Node *head = NULL;

// Add a new passenger at the end
void addPassenger(int ticketId, string name) {
    Node *newNode = new Node;
    newNode->ticketId = ticketId;
    newNode->name = name;
    newNode->next = NULL;

    if (head == NULL) {            // list is empty
        head = newNode;
        return;
    }
    Node *temp = head;
    while (temp->next != NULL)     // go to the last node
        temp = temp->next;
    temp->next = newNode;
}

// Remove a passenger by ticket ID
void removePassenger(int ticketId) {
    if (head == NULL)
        return;

    if (head->ticketId == ticketId) {   // removing the first node
        Node *toDelete = head;
        head = head->next;
        delete toDelete;
        return;
    }
    Node *temp = head;
    while (temp->next != NULL && temp->next->ticketId != ticketId)
        temp = temp->next;

    if (temp->next != NULL) {           // found it
        Node *toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
    }
}

void showPassengers() {
    if (head == NULL) {
        cout << "No passengers yet.\n";
        return;
    }
    Node *temp = head;
    while (temp != NULL) {
        cout << "Ticket " << temp->ticketId << " : " << temp->name << endl;
        temp = temp->next;
    }
}

// ============================================================
//  3. STACK (LIFO)  -- used to undo the last booking
// ============================================================
int undoStack[100];
int top = -1;

void push(int ticketId) {
    top++;
    undoStack[top] = ticketId;
}

// Remove and return the top element. Returns -1 if the stack is empty
int pop() {
    if (top == -1)
        return -1;
    int ticketId = undoStack[top];
    top--;
    return ticketId;
}

// ============================================================
//  4. QUEUE (FIFO)  -- waiting list
// ============================================================
string waitingList[50];
int front = 0;
int rear = 0;      // front == rear means the queue is empty

void enqueue(string name) {
    waitingList[rear] = name;
    rear++;
}

// Remove and return the first element. Returns "" if the queue is empty
string dequeue() {
    if (front == rear)
        return "";
    string name = waitingList[front];
    front++;
    return name;
}

void showWaitingList() {
    if (front == rear) {
        cout << "Waiting list is empty.\n";
        return;
    }
    for (int i = front; i < rear; i++)
        cout << i - front + 1 << ". " << waitingList[i] << endl;
}

// ============================================================
//  5. HASHING  -- find a name instantly from a ticket ID
//     The table has only 10 slots. If a slot is taken, we try the next one
//     (this is called Linear Probing)
// ============================================================
int hashId[10];        // 0 means the slot is empty
string hashName[10];

// Hash function: turns a ticket ID into an index from 0 to 9
int hashFunction(int ticketId) {
    return ticketId % 10;
}

void insertHash(int ticketId, string name) {
    int i = hashFunction(ticketId);
    while (hashId[i] != 0)         // slot is taken, move to the next one
        i = (i + 1) % 10;
    hashId[i] = ticketId;
    hashName[i] = name;
}

// Returns the name. Returns "" if not found
string searchHash(int ticketId) {
    int i = hashFunction(ticketId);
    for (int count = 0; count < 10; count++) {
        if (hashId[i] == ticketId)
            return hashName[i];
        if (hashId[i] == 0)        // found an empty slot, so the ticket doesn't exist
            return "";
        i = (i + 1) % 10;
    }
    return "";
}

// Delete: we only clear the name (the ID stays so that searching doesn't break)
void deleteHash(int ticketId) {
    int i = hashFunction(ticketId);
    for (int count = 0; count < 10; count++) {
        if (hashId[i] == ticketId) {
            hashName[i] = "";
            return;
        }
        if (hashId[i] == 0)
            return;
        i = (i + 1) % 10;
    }
}

// ============================================================
//  6. GRAPH  -- cities = nodes, routes = edges
//     Adjacency matrix: route[i][j] = 1 means there is a flight between i and j
// ============================================================
string cities[10];
int cityCount = 0;
int route[10][10];     // all zeros at the start
bool visited[10];

// Return the city's number. If the city is new, add it first
int getCity(string name) {
    for (int i = 0; i < cityCount; i++) {
        if (cities[i] == name)
            return i;
    }
    cities[cityCount] = name;
    cityCount++;
    return cityCount - 1;
}

void addRoute(string a, string b) {
    int i = getCity(a);
    int j = getCity(b);
    route[i][j] = 1;
    route[j][i] = 1;       // flights go both ways
}

void showRoutes() {
    for (int i = 0; i < cityCount; i++) {
        cout << cities[i] << " -> ";
        for (int j = 0; j < cityCount; j++) {
            if (route[i][j] == 1)
                cout << cities[j] << "  ";
        }
        cout << endl;
    }
}

// BFS: visit nearby cities first, then the ones further away (uses a queue)
void bfs(string start) {
    for (int i = 0; i < 10; i++)
        visited[i] = false;

    int queue[10];
    int qFront = 0, qRear = 0;

    int s = getCity(start);
    visited[s] = true;
    queue[qRear++] = s;

    while (qFront < qRear) {
        int current = queue[qFront++];
        cout << cities[current] << "  ";
        for (int next = 0; next < cityCount; next++) {
            if (route[current][next] == 1 && !visited[next]) {
                visited[next] = true;
                queue[qRear++] = next;
            }
        }
    }
    cout << endl;
}

// DFS: go as deep as possible along one path, then come back (uses recursion)
void dfs(int current) {
    visited[current] = true;
    cout << cities[current] << "  ";
    for (int next = 0; next < cityCount; next++) {
        if (route[current][next] == 1 && !visited[next])
            dfs(next);
    }
}

void startDfs(string start) {
    for (int i = 0; i < 10; i++)
        visited[i] = false;
    dfs(getCity(start));
    cout << endl;
}

// ============================================================
//  7. TREE (Binary Search Tree)  -- flights kept in ID order
//     Rule: smaller ID goes to the left, bigger ID goes to the right
// ============================================================
struct TreeNode {
    Flight data;
    TreeNode *left;
    TreeNode *right;
};

TreeNode *root = NULL;

TreeNode* insertBST(TreeNode *node, Flight f) {
    if (node == NULL) {                 // found an empty spot, place it here
        TreeNode *newNode = new TreeNode;
        newNode->data = f;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    if (f.id < node->data.id)
        node->left = insertBST(node->left, f);
    else
        node->right = insertBST(node->right, f);
    return node;
}

// Returns the node if found, otherwise NULL
TreeNode* searchBST(TreeNode *node, int id) {
    if (node == NULL || node->data.id == id)
        return node;
    if (id < node->data.id)
        return searchBST(node->left, id);
    return searchBST(node->right, id);
}

// Inorder: left, then root, then right -> prints IDs in sorted order
void inorder(TreeNode *node) {
    if (node == NULL)
        return;
    inorder(node->left);
    cout << node->data.id << "\t" << node->data.from << "\t\t"
         << node->data.to << "\t\t" << node->data.price << endl;
    inorder(node->right);
}

#endif