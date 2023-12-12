#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

typedef char Str40[40];

struct College
{
public:
    int schoolID;
    Str40 school_name;
    int subjectID;
    Str40 subject_name;
    Str40 day_or_night_e;
    Str40 day_or_night_c;
    Str40 level_e;
    Str40 level_c;
    int student_count;
    int teacher_count;
    int graduate_count;
    int city_n;
    Str40 city_c;
    int system_n;
    Str40 system_c;
};

class Tree
{
public:
    College college;
    Tree *right_college;
    Tree *left_college;
    void addTree(Tree *tree, Tree *add, int dir);
    void IDsortTree(Tree &tree, Tree add);
    void NAMEsortTree(Tree &tree, Tree add);

    Tree() : right_college(NULL), left_college(NULL)
    {
    }
};

void addTree(Tree *&tree, Tree *add, int dir)
{ //  1 to left, 2 to right

    if (dir == 1)
    {
        tree->left_college = add;
    }
    else if (dir == 2)
    {
        tree->right_college = add;
    }
}

void IDsortTree(Tree *&tree, Tree *add) {
    if (tree == NULL) {
        tree = add;
        return;
    }

    Tree *temp = tree;
    while (true) {
        if (add->college.schoolID < temp->college.schoolID) {
            if (temp->left_college == NULL) {
                temp->left_college = add;
                break;
            } else {
                temp = temp->left_college;
            }
        } else if (add->college.schoolID > temp->college.schoolID) {
            if (temp->right_college == NULL) {
                temp->right_college = add;
                break;
            } else {
                temp = temp->right_college;
            }
        } else {
            break;
        }
    }
}

void NAMEsortTree(Tree *&tree, Tree *add)
{
    if (tree == NULL)
    {
        tree = add;
        return;
    }

    Tree *temp = tree;
    int dir = 0;

    while (temp != NULL)
    {
        if (strcmp(add->college.school_name, tree->college.school_name) < 0)
        {
            dir = 1; // add to left
            temp = temp->left_college;
        }
        else if (strcmp(add->college.school_name, tree->college.school_name) > 0)
        {
            dir = 2; // add to right
            temp = temp->right_college;
        }
    }

    addTree(temp, add, dir);
}

struct Data
{
    College college;
    Data *next;
};

void AddLinkedList(Data *&data, Data *addData)
{
    data = addData;
}

void readData(Data *&data, const char *filename) {
    ifstream infile(filename);

    if (!infile) {
        cout << "Error opening file." << endl;
        return;
    }

    data = nullptr;
    Data* temp = nullptr;
    
    while (true) {
        Data* newData = new Data;
        newData->next = nullptr;
        
        if (infile >> newData->college.schoolID >> newData->college.school_name >> newData->college.subjectID >> newData->college.subject_name
            >> newData->college.day_or_night_e >> newData->college.day_or_night_c >> newData->college.level_e >> newData->college.level_c
            >> newData->college.student_count >> newData->college.teacher_count  >> newData->college.graduate_count >> newData->college.city_n
            >> newData->college.city_c >> newData->college.system_n >> newData->college.system_c) {
            
            if (data == nullptr) {
                data = newData;
                temp = data;
            } else {
                temp->next = newData;
                temp = newData;
            }
        } else {
            delete newData;
            break;
        }
    }
    infile.close();
}

void printInOrder(Tree* tree) {
    if (tree != NULL) {
        printInOrder(tree->left_college);
        cout << tree->college.schoolID << endl;
        printInOrder(tree->right_college);
    }
}

int main()
{
    Data *all_data = NULL;
    if (all_data == NULL) readData(all_data, "input401.txt");

    Tree *tree_top = NULL;
    Tree *add_tree = new Tree;
    Data *temp = all_data;

    while (temp != NULL)
    {
        add_tree->college = temp->college;
        IDsortTree(tree_top, add_tree);
        printf("%d\n", tree_top->college.schoolID);
        temp = temp->next;
    }

    return 0;
}
