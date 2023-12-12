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
        if (add->college.graduate_count < temp->college.graduate_count) {
            if (temp->left_college == NULL) {
                temp->left_college = add;
                break;
            } else {
                temp = temp->left_college;
            }
        } else if (add->college.graduate_count > temp->college.graduate_count) {
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


void NamesortTree(Tree *&tree, Tree *add) {
    if (tree == NULL) {
        tree = add;
        return;
    }
    
    Tree *temp = tree;
    while (true) {
        if (add->college.school_name < tree->college.school_name) {
            if (temp->left_college == NULL) {
                temp->left_college = add;
                break;
            } else {
                temp = temp->left_college;
            }
        } else if (add->college.school_name > tree->college.school_name) {
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

    data = NULL;
    Data* temp = NULL;
    
    while (true) {
        Data* newData = new Data;
        newData->next = NULL;
        
        if (infile >> newData->college.schoolID >> newData->college.school_name >> newData->college.subjectID >> newData->college.subject_name
            >> newData->college.day_or_night_e >> newData->college.day_or_night_c >> newData->college.level_e >> newData->college.level_c
            >> newData->college.student_count >> newData->college.teacher_count  >> newData->college.graduate_count >> newData->college.city_n
            >> newData->college.city_c >> newData->college.system_n >> newData->college.system_c) {
            
            if (data == NULL) {
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

int calculateTreeHeight(Tree* tree) {
    if (tree == NULL) {
        return 0;
    } else {
        int leftHeight = calculateTreeHeight(tree->left_college);
        int rightHeight = calculateTreeHeight(tree->right_college);

        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
}


int main()
{
    Data *all_data = NULL;
    if (all_data == NULL) readData(all_data, "input.txt");

	Tree *n_tree_top = NULL;
    Tree *g_tree_top = NULL;
    Data *temp = all_data;

    while (temp != NULL)
    {
    	Tree *add_tree = new Tree;
        add_tree->college = temp->college;
        IDsortTree(g_tree_top, add_tree);
        temp = temp->next;
    }

	temp = all_data;
	
	while (temp != NULL) {
    	Tree *add_tree = new Tree;
        add_tree->college = temp->college;
        NamesortTree(n_tree_top, add_tree);
        temp = temp->next;
	}

	int g_treeHeight = calculateTreeHeight(g_tree_top);
    cout << "Binary Tree Height: " << g_treeHeight << endl;
    int n_treeHeight = calculateTreeHeight(n_tree_top);
    cout << "Binary Tree Height: " << n_treeHeight << endl;
	
    return 0;
}
