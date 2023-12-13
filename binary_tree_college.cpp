//  DS1ex3  27  11020117林子皓  11020134呂宗凱 

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
        if (strcmp(add->college.school_name, temp->college.school_name) < 0) {
            if (temp->left_college == NULL) {
                temp->left_college = add;
                break;
            } else {
                temp = temp->left_college;
            }
        } else if (strcmp(add->college.school_name, temp->college.school_name) > 0) {
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

    std::string line;
    int linesToSkip = 4;  // 指定要跳過的行數

    // 跳過開頭指定行數
    for (int i = 0; i < linesToSkip; ++i) {
        std::getline(infile, line);
    }

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

void searchAndPrintMore(Tree* tree, int value, int& count) {
    if (tree == NULL) {
        return;
    }

    // 如果節點值比指定值小，則印出並繼續搜尋左子樹
    if (tree->college.graduate_count > value) {
    	count++;
    	//  lots to print!! 
        cout << '[' << count << "]\t" << tree->college.school_name
		<< '\t' << tree->college.subject_name << '\t' << tree->college.day_or_night_e
		<< ' ' << tree->college.day_or_night_c << '\t' << tree->college.level_e
		<< ' ' << tree->college.level_c << '\t' << tree->college.student_count
		<< '\t' << tree->college.teacher_count << '\t' << tree->college.graduate_count << endl; 
        searchAndPrintMore(tree->left_college, value, count);
    }

    // 搜尋右子樹
    searchAndPrintMore(tree->right_college, value, count);
}

void searchAndPrintSame(Tree* tree, Str40 name, int& count) {
    if (tree == NULL) {
        return;
    }
	if ( strcmp(tree->college.school_name, name) == 0 ) {
		cout << '[' << count << "]\t" << tree->college.school_name
		<< '\t' << tree->college.subject_name << '\t' << tree->college.day_or_night_e
		<< ' ' << tree->college.day_or_night_c << '\t' << tree->college.level_e
		<< ' ' << tree->college.level_c << '\t' << tree->college.student_count
		<< '\t' << tree->college.teacher_count << '\t' << tree->college.graduate_count << endl; 
	}
    // 如果節點值比指定值小，則印出並繼續搜尋左子樹
    else if ( strcmp(tree->college.school_name, name) < 0 ) {
        searchAndPrintSame(tree->left_college, name, count);
    }

    // 搜尋右子樹
    searchAndPrintSame(tree->right_college, name, count);
}

void deleteTree(Tree* node) {
    if (node == NULL)
        return;

    // Delete the left and right subtrees
    deleteTree(node->left_college);
    deleteTree(node->right_college);

    // Delete the current node
    delete node;
}

// Call this function with the root of the tree
void deleteEntireTree(Tree* root) {
    deleteTree(root);
    root = NULL; // Set the root to null to indicate that the tree is deleted
}

// 刪除比給定數字小的節點
Tree* deleteSmallerNodes(Tree* tree, int value, int count) {
    if (tree == NULL) {
        return NULL;
    }

    // 如果節點的數值小於給定數字，刪除該節點
    if (tree->college.graduate_count < value) {
    	
    	cout << '[' << count << "]\t" << tree->college.school_name
		<< '\t' << tree->college.subject_name << '\t' << tree->college.day_or_night_e
		<< ' ' << tree->college.day_or_night_c << '\t' << tree->college.level_e
		<< ' ' << tree->college.level_c << '\t' << tree->college.student_count
		<< '\t' << tree->college.teacher_count << '\t' << tree->college.graduate_count << endl;
    	
        Tree* temp = tree;
        tree = tree->right_college;
        delete temp;
    } else {
        // 遞迴刪除左子樹和右子樹中比給定數字小的節點
        tree->left_college = deleteSmallerNodes(tree->left_college, value, count);
        tree->right_college = deleteSmallerNodes(tree->right_college, value, count);
    }

    return tree;
}

int main() {
	
	int command;
	Tree *n_tree_top = NULL;
	Tree *g_tree_top = NULL;
	
	while (true) {
		cout << "\n";
    	cout << "*** University Graduate Information System ***\n";
    	cout << "* 0. Quit                                    *\n";
    	cout << "* 1. Create Two Binary Search Trees          *\n";
    	cout << "* 2. Search by Number of Graduates           *\n";
    	cout << "* 3. Search by School Name                   *\n";
    	cout << "* 4. Removal by Number of Graduates          *\n";
    	cout << "**********************************************\n";
    	cout << "Input a command(0, 1-4): ";
    	cin >> command;
		
		if (command == 0) {
			return 0;
		}
		else if (command == 1) {
			cout << "\nInput a file number:";
			
    		std::string fileName;
    		// 從使用者輸入中讀取檔案編號
    		cin >> fileName;

    		// 組合檔案名稱	 ex:"input401.txt"
			fileName = "input" + fileName + ".txt";
			
			Data *all_data = NULL;
    		readData(all_data,fileName.c_str());

    		Data *temp = all_data;
    		
    		deleteEntireTree(g_tree_top);
    		deleteEntireTree(n_tree_top);
    		
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
			
    		int n_treeHeight = calculateTreeHeight(n_tree_top);
    		cout << "Tree Height{School name}: " << n_treeHeight << endl;
			int g_treeHeight = calculateTreeHeight(g_tree_top);
    		cout << "Tree Height{Number of graduates}: " << g_treeHeight << endl;

		}
		else if(command == 2) {
			
			if (n_tree_top == NULL) {
				cout << "Please enter command 1 first!";
			}
			else {
				int graduate;
				cout << "Input the number of graduates:";
				cin >> graduate;
				int count = 0;
				searchAndPrintMore(g_tree_top, graduate, count);
				if (count == 0) {
					cout << "There is no match!" << endl;
				} 
			}		
		}
		else if(command == 3) {
			if (n_tree_top == NULL) {
				cout << "Please enter command 1 first!";
			}
			else {
				Str40 school_name;
				cout << "Input the number of graduates:";
				cin >> school_name;
				int count = 0;
				searchAndPrintSame(n_tree_top, school_name, count);
				if (count == 0) {
					cout << "There is no match!" << endl;
				}
			}		
		}
		else if(command == 4) {
			int graduate;
			cout << "Input the number of graduates:";
			cin >> graduate;
			
			int count = 0;
			deleteSmallerNodes(n_tree_top, graduate, count);
			count = 0;
			deleteSmallerNodes(g_tree_top, graduate, count);		
			
			int n_treeHeight = calculateTreeHeight(n_tree_top);
    		cout << "Tree Height{School name}: " << n_treeHeight << endl;
			int g_treeHeight = calculateTreeHeight(g_tree_top);
    		cout << "Tree Height{Number of graduates}: " << g_treeHeight << endl;
		}
	}
}
