// Yassin Sidkey 202100433
// Advanced Algorithms CW 1 Tasks

// Task 1 (Removing Duplicates from an Array of Characters)

#include <iostream>
#include <algorithm>

// Function to remove duplicates from an array of characters
int removeDup(char arr[], int c) {
    // If array has 0 or 1 element, no duplicates to remove
    if (c == 0 || c == 1) {
        return c;
    }

    // Initialize a pointer j to keep track of the position of non-duplicate elements
    int j = 0;

    // Traverse the array from the second element
    for (int i = 1; i < c; i++) {
        // If current element is different from the previous non-duplicate element
        if (arr[i] != arr[j]) {
            // Move the current element to the next position after the last non-duplicate element
            arr[++j] = arr[i];
        }
    }
    // Return the new length of the array without duplicates
    return j + 1;
}

int main() {
    // Input array with duplicates
    char alpha[] = {'a', 'b', 'c', 'e', 'a', 'e'};

    // Calculate the length of the array
    int len = sizeof(alpha) / sizeof(alpha[0]);

    // Sorting the array to bring duplicate elements together
    std::sort(alpha, alpha + len);

    // Removing duplicates from the sorted array and updating the length
    len = removeDup(alpha, len);

    // Printing the array without duplicates
    for (int i = 0; i < len; i++) {
        std::cout << alpha[i] << " ";
    }
    return 0;
}

// Task 2 (Implement Quick Sort Using a Doubly Linked List)

#include <iostream>

// Node structure for the doubly linked list
struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

// Function to get the last node of the linked list
Node* getLast(Node* node) {
    while (node && node->next)
        node = node->next;
    return node;
}

// Function to partition the linked list for quick sort
Node* partition(Node* low, Node* high) {
    int pivot = high->data;
    Node* i = low->prev;
    for (Node* j = low; j != high; j = j->next) {
        if (j->data <= pivot) {
            i = (i == nullptr) ? low : i->next;
            std::swap(i->data, j->data);
        }
    }
    i = (i == nullptr) ? low : i->next;
    std::swap(i->data, high->data);
    return i;
}

// Function to perform quick sort on the linked list
void quickSort(Node* low, Node* high) {
    if (high != nullptr && low != high && low != high->next) {
        Node* pi = partition(low, high);
        quickSort(low, pi->prev);
        quickSort(pi->next, high);
    }
}

// Function to print the linked list
void printList(Node* head) {
    while (head) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    // Creating a sample linked list
    Node* head = new Node(12);
    head->next = new Node(8);
    head->next->prev = head;
    head->next->next = new Node(5);
    head->next->next->prev = head->next;
    head->next->next->next = new Node(20);
    head->next->next->next->prev = head->next->next;

    std::cout << "Linked List before sorting:\n";
    printList(head);

    Node* lastNode = getLast(head);
    quickSort(head, lastNode);

    std::cout << "Linked List after sorting:\n";
    printList(head);

    return 0;
}


//Task 3 (Writing Sorting Functions and Performing Comparisons)
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>

// Function to count comparisons in heap sort algorithm
int heap_sort_count(int arr[], int n) {
    int count = 0; // Initialize comparison count
    std::make_heap(arr, arr + n); // Build a max heap
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]); // Move the maximum element to the end
        std::make_heap(arr, arr + i); // Rebuild the max heap excluding the last element
        count += (n - i); // Increment comparison count
    }
    return count;
}

// Function to count comparisons in bubble sort algorithm
int bubble_sort_count(int arr[], int n) {
    int count = 0; // Initialize comparison count
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) { // Compare adjacent elements and swap if necessary
                std::swap(arr[j], arr[j + 1]);
                count++; // Increment comparison count
            }
        }
    }
    return count;
}

// Function to count comparisons in selection sort algorithm
int selection_sort_count(int arr[], int n) {
    int count = 0; // Initialize comparison count
    for (int i = 0; i < n - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_index]) {
                min_index = j; // Find the index of the minimum element
            }
            count++; // Increment comparison count
        }
        std::swap(arr[i], arr[min_index]); // Swap the minimum element with the current element
    }
    return count;
}

// Function to count comparisons in insertion sort algorithm
int insertion_sort_count(int arr[], int n) {
    int count = 0; // Initialize comparison count
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // Move elements greater than key to one position ahead
            j--;
            count++; // Increment comparison count
        }
        arr[j + 1] = key; // Insert the key in the correct position
    }
    return count;
}

// Function to perform comparisons and record results
void test_comparisons() {
    std::ofstream comparisonsFile("comparisons.csv");
    std::ofstream timeFile("time.csv");

    comparisonsFile << "Size,Heap Sort, Bubble Sort, Selection Sort, Insertion Sort\n";
    timeFile << "Size,Heap Sort, Bubble Sort, Selection Sort, Insertion Sort\n";

    for (int size = 1; size <= 30; ++size) {
        long long heap_sort_comp = 0, bubble_sort_comp = 0, selection_sort_comp = 0, insertion_sort_comp = 0;
        double heap_sort_time = 0.0, bubble_sort_time = 0.0, selection_sort_time = 0.0, insertion_sort_time = 0.0;

        for (int iter = 0; iter < 30; ++iter) {
            int arr[size]; // Create an array of given size
            std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count()); // Seed the random number generator
            std::uniform_int_distribution<int> dist(1, size); // Define the range of random numbers

            for (int& x : arr) {
                x = dist(rng); // Fill the array with random numbers
            }

            auto start = std::chrono::high_resolution_clock::now(); // Start the timer
            heap_sort_comp += heap_sort_count(arr, size); // Perform heap sort and count comparisons
            auto end = std::chrono::high_resolution_clock::now(); // Stop the timer
            heap_sort_time += std::chrono::duration<double>(end - start).count(); // Calculate elapsed time

            std::shuffle(arr, arr + size, rng); // Shuffle the array for next sorting algorithm

            start = std::chrono::high_resolution_clock::now(); // Start the timer
            bubble_sort_comp += bubble_sort_count(arr, size); // Perform bubble sort and count comparisons
            end = std::chrono::high_resolution_clock::now(); // Stop the timer
            bubble_sort_time += std::chrono::duration<double>(end - start).count(); // Calculate elapsed time

            std::shuffle(arr, arr + size, rng); // Shuffle the array for next sorting algorithm

            start = std::chrono::high_resolution_clock::now(); // Start the timer
            selection_sort_comp += selection_sort_count(arr, size); // Perform selection sort and count comparisons
            end = std::chrono::high_resolution_clock::now(); // Stop the timer
            selection_sort_time += std::chrono::duration<double>(end - start).count(); // Calculate elapsed time

            std::shuffle(arr, arr + size, rng); // Shuffle the array for next sorting algorithm

            start = std::chrono::high_resolution_clock::now(); // Start the timer
            insertion_sort_comp += insertion_sort_count(arr, size); // Perform insertion sort and count comparisons
            end = std::chrono::high_resolution_clock::now(); // Stop the timer
            insertion_sort_time += std::chrono::duration<double>(end - start).count(); // Calculate elapsed time
        }

        comparisonsFile << size << "," << heap_sort_comp / 30 << "," << bubble_sort_comp / 30 << ","
                        << selection_sort_comp / 30 << "," << insertion_sort_comp / 30 << "\n"; // Write average comparisons to file

        timeFile << size << "," << heap_sort_time / 30 << "," << bubble_sort_time / 30 << ","
                 << selection_sort_time / 30 << "," << insertion_sort_time / 30 << "\n"; // Write average time to file
    }

    comparisonsFile.close(); // Close comparisons file
    timeFile.close(); // Close time file
}

int main() {
    test_comparisons();
    std::cout << "Results saved to comparisons.csv and time.csv" << std::endl;
    return 0;
}


// Task 4 (Rearranging Elements in an Array Recursively)

#include <iostream>
#include <vector>

// Function to recursively rearrange elements in the array based on the pivot k
void rearrangeRecursive(std::vector<int>& arr, int k, int start, int end) {
    if (start >= end) return; // Base case: if start index crosses end index, return

    // If the element at the start index is greater than k and the element at the end index is less than or equal to k
    if (arr[start] > k && arr[end] <= k) {
        std::swap(arr[start], arr[end]); // Swap the elements
        rearrangeRecursive(arr, k, start + 1, end - 1); // Recur for the next elements
    }
        // If the element at the start index is less than or equal to k
    else if (arr[start] <= k) {
        rearrangeRecursive(arr, k, start + 1, end); // Recur for the next elements starting from start + 1
    }
        // If the element at the end index is greater than k
    else if (arr[end] > k) {
        rearrangeRecursive(arr, k, start, end - 1); // Recur for the previous elements ending at end - 1
    }
}

// Function to rearrange the array such that elements less than or equal to k come before elements greater than k
void rearrangeArray(std::vector<int>& arr, int k) {
    rearrangeRecursive(arr, k, 0, arr.size() - 1); // Call the recursive function with start = 0 and end = size - 1
}

// Function to print the elements of the array
void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " "; // Print each element followed by a space
    }
    std::cout << std::endl; // Move to the next line after printing all elements
}

// Main function
int main() {
    std::vector<int> arr = {4, 7, 2, 9, 1, 5, 8}; // Initialize an array
    int k = 5; // Set the pivot value

    std::cout << "Original array: ";
    printArray(arr); // Print the original array

    rearrangeArray(arr, k); // Rearrange the array around pivot k

    std::cout << "Array after rearranging with k=" << k << ": ";
    printArray(arr); // Print the rearranged array

    return 0;
}


//Task 5 (Converting a Fully Parenthesized Arithmetic Expression to a Binary Expression Tree)

#include <iostream>
#include <string>
#include <stack>
#include <cctype>

// Structure defining a node in the expression tree
struct TreeNode {
    std::string value; // Value of the node (operator or operand)
    TreeNode* left; // Pointer to the left child node
    TreeNode* right; // Pointer to the right child node

    TreeNode(const std::string& val) : value(val), left(nullptr), right(nullptr) {} // Constructor initializing value and setting children to nullptr
};

// Function to check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/'; // Returns true if the character is one of the specified operators
}

// Function to build the expression tree from the given expression
TreeNode* buildExpressionTree(const std::string& expression) {
    std::stack<TreeNode*> nodeStack; // Stack to hold tree nodes during construction

    for (auto it = expression.begin(); it != expression.end(); ++it) {
        char c = *it;
        if (c == ' ') { // Skip whitespace characters
            continue;
        } else if (c == '(') { // Skip opening parenthesis
            continue;
        } else if (c == ')') { // When encountering closing parenthesis
            TreeNode* right = nodeStack.top(); // Pop the top node as right child
            nodeStack.pop();
            TreeNode* op = nodeStack.top(); // Pop the next node as operator
            nodeStack.pop();
            TreeNode* left = nodeStack.top(); // Pop the next node as left child
            nodeStack.pop();

            op->left = left; // Assign left child
            op->right = right; // Assign right child
            nodeStack.push(op); // Push the operator node back to the stack
        } else if (isOperator(c)) { // When encountering an operator
            TreeNode* newNode = new TreeNode(std::string(1, c)); // Create a new node with the operator as value
            nodeStack.push(newNode); // Push the operator node to the stack
        } else { // Operand
            std::string operand; // String to store the operand
            while (std::isdigit(c)) { // Keep reading digits to form the operand
                operand += c;
                ++it;
                c = *it;
            }
            --it;
            TreeNode* newNode = new TreeNode(operand); // Create a new node with the operand as value
            nodeStack.push(newNode); // Push the operand node to the stack
        }
    }

    return nodeStack.top(); // Return the root of the expression tree
}

// Function to recursively print the expression tree
void printTree(TreeNode* root, int depth = 0) {
    if (root == nullptr) return; // Base case: if the root is null, return

    printTree(root->right, depth + 1); // Recur for the right subtree with increased depth
    std::cout << std::string(depth * 4, ' ') << root->value << std::endl; // Print the value of the current node with indentation based on depth
    printTree(root->left, depth + 1); // Recur for the left subtree with increased depth
}

// Function to recursively evaluate the expression tree
int evaluateExpressionTree(TreeNode* root) {
    if (root->left == nullptr && root->right == nullptr) { // If both children are null, the node is a leaf
        return std::stoi(root->value); // Convert the value to an integer and return
    }

    int leftValue = evaluateExpressionTree(root->left); // Recursively evaluate the left subtree
    int rightValue = evaluateExpressionTree(root->right); // Recursively evaluate the right subtree

    // Perform the operation based on the operator value of the root node
    if (root->value == "+") {
        return leftValue + rightValue;
    } else if (root->value == "-") {
        return leftValue - rightValue;
    } else if (root->value == "*") {
        return leftValue * rightValue;
    } else if (root->value == "/") {
        return leftValue / rightValue;
    }

    return 0;
}

// Main function
int main() {
    std::string expression;
    std::cout << "Enter a fully parenthesized arithmetic expression: ";
    std::getline(std::cin, expression); // Take input from the user

    TreeNode* root = buildExpressionTree(expression); // Build the expression tree

    std::cout << "Expression Tree:" << std::endl;
    printTree(root); // Print the expression tree

    std::cout << "Evaluation result: " << evaluateExpressionTree(root) << std::endl; // Evaluate the expression tree and print the result

    return 0;
}


//Task 6 (Text Wrapping)

#include <iostream>
#include <string>

// Function to wrap text to fit within a specified line width
void wrapText(const std::string& text, int lineWidth) {
    std::string line; // String to store the current line being built
    int currentLineWidth = 0; // Variable to track the current line width

    for (char c : text) {
        if (c == ' ') { // If the character is a space
            if (currentLineWidth + line.size() <= lineWidth) { // If adding the space to the current line does not exceed the line width
                line += c; // Add the space to the current line
                currentLineWidth += 1; // Update the current line width (only for the space)
            } else { // If adding the space exceeds the line width
                std::cout << line << std::endl; // Print the current line
                line.clear(); // Clear the current line
                currentLineWidth = 0; // Reset the current line width
            }
        } else { // If the character is not a space (i.e., part of a word)
            if (currentLineWidth + line.size() + 1 <= lineWidth) { // If adding the character to the current line does not exceed the line width
                line += c; // Add the character to the current line
                currentLineWidth += 1; // Increment the current line width
            } else { // If adding the character exceeds the line width
                std::cout << line << std::endl; // Print the current line
                line.clear(); // Clear the current line
                currentLineWidth = 0; // Reset the current line width
                line += c; // Add the character to the new line
                currentLineWidth += 1; // Increment the current line width
            }
        }
    }

    if (!line.empty()) { // If there is any remaining content in the current line
        std::cout << line << std::endl; // Print the remaining content
    }
}

// Main function
int main() {
    std::string text = "Mary loves to sing and perform tapdancing."; // Input text to be wrapped
    int lineWidth = 10; // Width of each line

    std::cout << "Output:" << std::endl; // Print the output
    wrapText(text, lineWidth); // Wrap the text

    return 0;
}


// Task 7 (Finding Largest Connected Groups in a Directed Graph)

#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>

// Class representing a graph
class Graph {
private:
    int V; // Number of vertices
    std::vector<std::unordered_set<int>> adj; // Adjacency list representing edges

public:
    Graph(int V) : V(V), adj(V) {} // Constructor initializing the number of vertices and adjacency list

    // Function to add an edge between vertices u and v
    void addEdge(int u, int v) {
        adj[u].insert(v); // Add v to the adjacency list of u
    }

    // Utility function for depth-first search (DFS)
    void DFSUtil(int v, std::unordered_set<int>& visited, std::unordered_set<int>& connectedGroup) {
        visited.insert(v); // Mark v as visited
        connectedGroup.insert(v); // Add v to the current connected group

        // Iterate through all neighbors of v
        for (int neighbor : adj[v]) {
            if (visited.find(neighbor) == visited.end()) { // If the neighbor is not visited
                DFSUtil(neighbor, visited, connectedGroup); // Recursively explore the neighbor
            }
        }
    }

    // Function to find all connected groups in the graph using DFS
    std::vector<std::unordered_set<int>> findConnectedGroups() {
        std::unordered_set<int> visited; // Set to store visited vertices
        std::vector<std::unordered_set<int>> connectedGroups; // Vector to store connected groups

        // Iterate through all vertices in the graph
        for (int v = 0; v < V; ++v) {
            if (visited.find(v) == visited.end()) { // If v is not visited
                std::unordered_set<int> connectedGroup; // Create a new connected group
                DFSUtil(v, visited, connectedGroup); // Explore the connected group starting from v
                connectedGroups.push_back(connectedGroup); // Add the connected group to the vector
            }
        }

        return connectedGroups; // Return the vector of connected groups
    }
};

// Main function
int main() {
    Graph graph(9); // Create a graph with 9 vertices
    graph.addEdge(0, 1); // Add edges between vertices
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
    graph.addEdge(5, 6);
    graph.addEdge(6, 3);
    graph.addEdge(7, 8);

    std::vector<std::unordered_set<int>> connectedGroups = graph.findConnectedGroups(); // Find connected groups in the graph

    std::cout << "Largest connected groups:" << std::endl;
    int i = 1;
    for (const auto& group : connectedGroups) { // Iterate through each connected group
        std::cout << "Group " << i << ": ";
        for (int node : group) { // Iterate through nodes in the group
            std::cout << node << " "; // Print each node
        }
        std::cout << std::endl;
        i++;
    }

    return 0; // Return 0 to indicate successful execution
}


// Task 8 (Parallel Multiplication of Matrices using Pthreads)

#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>

// Class representing a graph
class Graph {
private:
    int V; // Number of vertices
    std::vector<std::unordered_set<int>> adj; // Adjacency list representing edges

public:
    Graph(int V) : V(V), adj(V) {} // Constructor initializing the number of vertices and adjacency list

    // Function to add an edge between vertices u and v
    void addEdge(int u, int v) {
        adj[u].insert(v); // Add v to the adjacency list of u
    }

    // Utility function for depth-first search (DFS)
    void DFSUtil(int v, std::unordered_set<int>& visited, std::unordered_set<int>& connectedGroup) {
        visited.insert(v); // Mark v as visited
        connectedGroup.insert(v); // Add v to the current connected group

        // Iterate through all neighbors of v
        for (int neighbor : adj[v]) {
            if (visited.find(neighbor) == visited.end()) { // If the neighbor is not visited
                DFSUtil(neighbor, visited, connectedGroup); // Recursively explore the neighbor
            }
        }
    }

    // Function to find all connected groups in the graph using DFS
    std::vector<std::unordered_set<int>> findConnectedGroups() {
        std::unordered_set<int> visited; // Set to store visited vertices
        std::vector<std::unordered_set<int>> connectedGroups; // Vector to store connected groups

        // Iterate through all vertices in the graph
        for (int v = 0; v < V; ++v) {
            if (visited.find(v) == visited.end()) { // If v is not visited
                std::unordered_set<int> connectedGroup; // Create a new connected group
                DFSUtil(v, visited, connectedGroup); // Explore the connected group starting from v
                connectedGroups.push_back(connectedGroup); // Add the connected group to the vector
            }
        }

        return connectedGroups; // Return the vector of connected groups
    }
};

// Main function
int main() {
    Graph graph(9); // Create a graph with 9 vertices
    graph.addEdge(0, 1); // Add edges between vertices
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
    graph.addEdge(5, 6);
    graph.addEdge(6, 3);
    graph.addEdge(7, 8);

    std::vector<std::unordered_set<int>> connectedGroups = graph.findConnectedGroups(); // Find connected groups in the graph

    std::cout << "Largest connected groups:" << std::endl;
    int i = 1;
    for (const auto& group : connectedGroups) { // Iterate through each connected group
        std::cout << "Group " << i << ": ";
        for (int node : group) { // Iterate through nodes in the group
            std::cout << node << " "; // Print each node
        }
        std::cout << std::endl;
        i++;
    }

    return 0; // Return 0 to indicate successful execution
}