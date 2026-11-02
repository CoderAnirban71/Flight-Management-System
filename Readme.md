# Flight Management System (DSA Project)

A simple console application in C++ that demonstrates the main Data Structures
and Algorithms concepts through a flight management system.

The goal is **not** to build a full production system. The goal is to show each
DSA concept working as a real feature of the project, with code that is simple
enough to explain line by line.

## Project Structure

```
.
├── dsa_lib.cpp   # All DSA functions (works like a library)
├── main.cpp      # Driver file: menu that calls the library functions
├── README.md
└── .gitignore
```

`main.cpp` includes `dsa_lib.cpp`, so you only compile `main.cpp`.

## How to Compile and Run

```bash
g++ main.cpp -o flight
./flight          # Windows: flight.exe
```

> Do not run `g++ main.cpp dsa_lib.cpp`. `dsa_lib.cpp` is already included
> inside `main.cpp`, so compiling both causes a "multiple definition" error.

## DSA Concepts and Where They Are Used

| DSA | Feature in the project | Functions |
|---|---|---|
| Array | Stores the list of all flights | `addFlight`, `showFlights`, `linearSearch`, `bubbleSort`, `binarySearch` |
| Linked List | Stores the list of passengers | `addPassenger`, `removePassenger`, `showPassengers` |
| Stack (LIFO) | Undo the last booking | `push`, `pop` |
| Queue (FIFO) | Waiting list | `enqueue`, `dequeue`, `showWaitingList` |
| Hashing | Find a passenger instantly by ticket ID (linear probing) | `hashFunction`, `insertHash`, `searchHash`, `deleteHash` |
| Graph | Cities are nodes, flight routes are edges (adjacency matrix) | `addRoute`, `showRoutes`, `bfs`, `dfs` |
| Tree (BST) | Flights kept in ID order | `insertBST`, `searchBST`, `inorder` |

## Menu Options

| # | Option | DSA used |
|---|---|---|
| 1 | View all flights | Array |
| 2 | Sort flights by ID | Bubble Sort |
| 3 | Search flight | Linear Search |
| 4 | Search flight | Binary Search |
| 5 | View flights in ID order | BST Inorder |
| 6 | Search flight | BST Search |
| 7 | Book a ticket | Linked List + Hashing + Stack |
| 8 | Undo last booking | Stack |
| 9 | View all passengers | Linked List |
| 10 | Find passenger by ticket ID | Hashing |
| 11 | Add a name to the waiting list | Queue |
| 12 | Book the first person on the waiting list | Queue |
| 13 | View waiting list | Queue |
| 14 | View all routes | Graph |
| 15 | Visit cities from a start city | BFS |
| 16 | Visit cities from a start city | DFS |

## Notes

- Enter names and cities as a single word (for example `Rahul`, `Delhi`).
- Binary search needs a sorted array, so `binarySearch` calls `bubbleSort` first.
- The hash table has only 10 slots and the graph supports up to 10 cities.
  This keeps the code simple for demonstration.
- Sample flights are loaded automatically when the program starts.

## Sample Flights

| ID | From | To | Price |
|---|---|---|---|
| 101 | Delhi | Mumbai | 5000 |
| 102 | Delhi | Kolkata | 4500 |
| 103 | Mumbai | Bangalore | 3500 |
| 104 | Bangalore | Chennai | 2500 |
| 105 | Kolkata | Chennai | 4000 |