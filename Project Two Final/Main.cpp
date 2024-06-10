// Include necessary libraries
# include <iostream>
# include <iomanip>
# include <string>
# include <vector>
# include <sstream>
# include <fstream>

using namespace std;

// Define a structure for Course which includes course number, name, and prerequisites
struct Course {
    string courseNum;
    string courseName;

    vector<string> PreReqs;

    // Default constructor
    Course() {};

    // Constructor initializing course number and name
    Course(string aCourseNum, string aCourseName) {
        courseNum = aCourseNum;
        courseName = aCourseName;
    }
    // Constructor initializing course number, name, and prerequisites
    Course(string aCourseNum, string aCourseName, vector<string> prereqs) {
        courseNum = aCourseNum;
        courseName = aCourseName;
        vector<string> PreReqs = prereqs;
    }
};

// Define a Node structure for the binary search tree
struct Node {
    Course course;
    Node* left;
    Node* right;

    // Constructor initializing left and right pointers to nullptr
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Constructor initializing the course
    Node(Course acourse) : Node() {
        this->course = acourse;
    }
};

// Binary Search Tree class for handling courses
class BST {
private:
    Node* root;
    void addNode(Course acourse, Node* node);
    void inOrder(Node* node);
    void printCourse(Node* node, string courseNum);

public:
    BST();
    void InOrder();
    void PrintCourse(string courseNum);
    bool loadData();
    bool validatePreReqs(Course course);
    void insert(Course course);
};

// Constructor initializing the root to nullptr
BST::BST() {
    root = nullptr;
}

// Public method to perform in-order traversal of the tree
void BST::InOrder() {
    this->inOrder(root);
}

// Public method to print a specific course
void BST::PrintCourse(string courseNum) {
    this->printCourse(root, courseNum);
}


// Method to insert a new course into the BST
void BST::insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        this->addNode(course, root);
    }
}


// Helper method to add a node to the BST
void BST::addNode(Course acourse, Node* node) {

    if (node->course.courseNum.compare(acourse.courseNum) > 0) {
        if (node->left == nullptr) {
            node->left = new Node(acourse);
        }
        else {
            this->addNode(acourse, node->left);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(acourse);
        }
        else {
            this->addNode(acourse, node->right);
        }
    }
}


// Helper method to perform in-order traversal and print courses
void BST::inOrder(Node* node) {

    if (node != nullptr) {
        inOrder(node->left);
        cout << "Course Number: " << node->course.courseNum;
        cout << " Course Name: " << node->course.courseName;
        cout << " Prerequisite(s): ";
        for (int i = 0; i < node->course.PreReqs.size(); ++i) {
            cout << node->course.PreReqs[i] << " ";
        }
        if (node->course.PreReqs.size() == 0) {
            cout << "None";
        }
        cout << "\n";

        inOrder(node->right);
    }
    return;
}

// Helper method to print a specific course
void BST::printCourse(Node* node, string courseNum) {

    while (node != nullptr) {
        if (node->course.courseNum.compare(courseNum) == 0) {
            cout << "Course Number: " << node->course.courseNum;
            cout << "  Course Name: " << node->course.courseName;
            cout << "  Prerequisite(s): ";
            for (int i = 0; i < node->course.PreReqs.size(); ++i) {
                cout << node->course.PreReqs[i] << " ";
            }
            if (node->course.PreReqs.size() == 0) {
                cout << "None";
            }
            cout << "\n";
            return;
        }
        else if (node->course.courseNum.compare(courseNum) > 0 && node->left != nullptr) {
            node = node->left;
        }
        else if (node->course.courseNum.compare(courseNum) < 0 && node->right != nullptr) {
            node = node->right;
        }
        else {
            cout << "Course not found. Are you sure you entered the right course number? \n";
            return;
        }
    }
    if (root == nullptr) {
        cout << "Error loading data. =[ \n";
        return;
    }
}



bool BST::loadData() {

    ifstream file;
    file.open("ProjectCourseFile.txt");

    if (file.is_open()) {
        while (!file.eof()) {
            vector<string> courseLine;
            string line;

            getline(file, line);
            while (line.length() > 0) {
                unsigned int delim = line.find(',');
                if (delim < 100) {
                    courseLine.push_back(line.substr(0, delim));
                    line.erase(0, delim + 1);
                }
                else {
                    courseLine.push_back(line.substr(0, line.length()));
                    line = "";
                }
            }

            Course course;

            course.courseNum = courseLine[0];
            course.courseName = courseLine[1];
            for (unsigned int i = 2; i < courseLine.size(); i++) {
                course.PreReqs.push_back(courseLine[i]);
            }
            insert(course);
        }
        return true;
    }
    if (!file) {
        cout << "Something went wrong and the file didn't open. Sad day! D: \n";
        return false;
    }
    file.close();
}

bool BST::validatePreReqs(Course course) {
    Node* current = root;
    if (current->course.PreReqs.size() > 0) {
        for (int i = 0; i < course.PreReqs.size(); i++) {
            while (current != nullptr) {
                if (course.PreReqs[i] == current->course.courseNum) {
                    return true;
                }
                else if (course.PreReqs[i].compare(current->course.courseNum) > 0 && current->left != nullptr) {
                    current = current->left;
                }
                else if (course.PreReqs[i].compare(current->course.courseNum) < 0 && current->right != nullptr) {
                    current = current->right;
                }
                else {
                    cout << "Prerequisite not found. \n";
                    return false;
                }
            }
        }
    }
    else {
        return true;
    }
}

int main()
{
    BST* bst = new BST();
    string courseNum;
    int choice = 0;

    cout << "Welcome to the course planner! \n\n";
    while (choice != 4) {
        cout << "**_____________________________**\n";
        cout << "||            MENU             ||\n";
        cout << "||-----------------------------||\n";
        cout << "||[1] Load Data Structure      ||\n";
        cout << "||[2] Print Course List        ||\n";
        cout << "||[3] Print Course             ||\n";
        cout << "||[4] Exit                     ||\n";
        cout << "||_____________________________||\n";
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            bst->loadData();
            break;
        case 2:
            cout << "\nHere is a sample schedule: \n";
            cout << "---------------------------- \n";
            bst->InOrder();
            cout << "\n";
            break;
        case 3:
            cout << "Please enter the course number you would like to search: ";
            cin >> courseNum;
            bst->PrintCourse(courseNum);
            cout << "\n";
            break;
        case 4:
            cout << "\nThank you for using the course planner!\n";
            break;
        default:
            cout << choice << " is not a valid option. Please enter a number 1 - 4.\n";
        }
    }
    return 0;
}