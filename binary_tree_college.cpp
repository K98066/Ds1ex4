#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

typedef char Str40[40];

struct College {
    public:
        int schoolID;
        Str40 school_name;
        int subjectID;
        Str40 subject_name;
        Str40 day_or_night_e;  //  體系別:英文_空格_中文
        Str40 day_or_night_c;
        Str40 level_e;  //  等級別:英文_空格_中文 
        Str40 level_c;
        int student_count;
        int teacher_count;
        int graduate_count;
        int city_n;  //  城市:數字_空格_中文 
        Str40 city_c;
        int system_n;  //  體系別:數字_空格_中文 
        Str40 system_c; 
};

class Tree {
    public:
        College college;
        Tree* right_college;
        Tree* left_college;
    	void addTree(Tree *tree, Tree *add, int dir);
    	void IDsortTree(Tree &tree, Tree add);
    	void NAMEsortTree(Tree &tree, Tree add);
    	
    Tree() : right_college(NULL), left_college(NULL){
	}
};

/*
void readData(Temp *temp) {
	std::cout << std::setw(width) << std::setfill('0') << temp->college.schoolID << std::endl;  //  固定格式 
}
*/

void addTree(Tree *&tree, Tree *add, int dir) {  //  1 to left, 2 to right

	if ( dir == 1 ) {
		tree->left_college = add;
	}
	else if ( dir == 2 ) {
		tree->right_college = add;
	}
}

void IDsortTree(Tree *&tree, Tree *add) {
    if (tree == NULL) {
        tree = add;
        return;
    }
    
    Tree *temp = tree;
    
    int dir = 0;
    //  dir的初始值 
    if (add->college.schoolID < tree->college.schoolID) {
    	dir = 1;
    }
    else {
    	dir = 2;
	}

    while (temp->left_college != NULL && temp->right_college != NULL ) {
    	if (add->college.schoolID < temp->college.schoolID) {
            dir = 1;  // mov to left
        } else if (add->college.schoolID > temp->college.schoolID) {
            dir = 2;  // mov to right
    	}
    	
    	if ( dir == 1 ) {
    		temp = temp->left_college;
		}
		else if ( dir == 2 ) {
			temp = temp->right_college;
		}
	}
	
	addTree(temp, add, dir);
}

void NAMEsortTree(Tree *&tree, Tree *add) {
    if (tree == NULL) {
        tree = add;
        return;
    }

    Tree *temp = tree;
    int dir = 0;

    while (temp != NULL) {
        if ( strcmp(add->college.school_name, tree->college.school_name) < 0 ) {
            dir = 1;  // add to left
            temp = temp->left_college;
        } else if ( strcmp(add->college.school_name, tree->college.school_name) > 0 ) {
            dir = 2;  // add to right
            temp = temp->right_college;
    	}
    }
    
    addTree(temp, add, dir);
}
 
struct Data {
	College college;
	Data* next;
};

void AddLinkedList(Data*& data, Data* addData) {
	data = addData;
} 

void readData(Data*& data, const char* filename) {
    ifstream infile(filename);

    if (!infile) {
        cout << "Error opening file." << endl;
        return;
    }

	Data* newData = new Data;
	Data* temp = data;
	
    // 跳過表頭
    // infile.ignore(256, '\n');
    //  學校代碼	學校名稱	科系代碼	科系名稱	日間∕進修別(先英文字再中文字)	等級別(先英文字再中文字)	學生數	教師數	上學年度畢業生數	縣市名稱	體系別(先數字再中文字) 
    while (!infile.eof()) { 
    
       infile >> newData->college.schoolID >> newData->college.school_name >> newData->college.subjectID >> newData->college.subject_name
       >> newData->college.day_or_night_e >> newData->college.day_or_night_c >> newData->college.level_e >> newData->college.level_c
	   >> newData->college.student_count >> newData->college.teacher_count  >> newData->college.graduate_count >> newData->college.city_n
	   >> newData->college.city_c >> newData->college.system_n >> newData->college.system_c;
		
		if (temp == NULL ) {
    // 如果串列是空的，直接將 newData 設為串列的開頭
    		data = newData;
    		data->next = NULL;
    		temp = data;
		}
		else {
			while ( temp->next != NULL ) {
				temp = temp->next;
			}
			temp->next = newData;
		}
		newData = new Data;
	};
	
    infile.close();
}
 
int main() {
	Data* all_data = NULL;
	if (all_data == NULL)
	readData(all_data, "input.txt");
	
	Tree* tree_top = NULL;
	Tree* add_tree = new Tree;
	Data* temp = all_data;
		
	while ( temp != NULL ) {
		add_tree->college = temp->college;
		IDsortTree(tree_top, add_tree);
		printf("%d\n", tree_top->college.schoolID);
		temp = temp->next; 
	}
	
    return 0;
}
