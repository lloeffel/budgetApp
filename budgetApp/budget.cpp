#include <cstdint>
#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <unordered_map>

using namespace std;


struct Category{
	string name;
	int capacity;
	int spending;
	int isOver;
	Category* prev;
	int index;
};

struct Block{
	string name;
	int numCategories;
	Block* prev;
	Category* root;
	int index;
};

struct GlobalVars{
	Block* root;
	bool exit;
	bool back;
	int numBlocks;
	int pageName;
	const int pageNum = 2;
	double totalFunds;
	double totalAllocated;
};

void print(vector<Block> &budget, GlobalVars &gVars){
	cout << "MONTLY BUDGET\n";
	for(int i = 0; i < gVars.numBlocks; ++i){
		//printing the block line (Ex: 1. blockName:)
		cout << i+1 << ". " << budget[i].name <<endl;
		vector<Category*> categories = budget[i].categories;
		for(int j = 0; j < categories.size(); j++){
			cout << "   "<< j + 1 << ". " << categories[j]->name << ": " << categories[j]->spending << "/" << categories[j]->capacity;
			if(categories[j]->isOver == 1){cout << " -- OVERSPENT";}
			cout << endl;
		}
	}	
	return;
}

void addBlock(vector<Block> &budget, GlobalVars &gVars){
	cout << "* Add Block! (Enter N to cancel)\n* Enter Name: ";
	string name;
	cin >> name;
	if(name.compare("N") == 0){
		cout << "* Cancelled Block Addition\n";
		return;
	}
	string line;
	getline(cin,line); //gets the rest of the name if there are spaces
	name += line;
	Block temp;
	temp.name = name;
	temp.numCategories = 0;
	gVars.numBlocks++;
	budget.push_back(temp);
	return;
}
void editFunc(vector<Block> &budget, GlobalVars &gVars){
	gVars.pageName = 0b01;
	return;
}
//displays help menu
void help(vector<Block> &budget, GlobalVars &gVars){
	if(gVars.pageName == 0b10){
		//if on Home Page
		printf("THESE ARE THE COMMANDS:\n");
		printf("     H - Help menu\n");
		printf("     E - Edit mode\n");    
		printf("     P - Print Budget\n");    
		printf("     B - Go Back\n");
		printf("     Q - Quit\n");
	}else if(gVars.pageName == 0b01){
		//if on Edit Page
		printf("THESE ARE THE COMMANDS:\n");
		printf("     H - Help menu\n");    
		printf("     P - Print Budget\n");
		printf("     AB - add a block\n");
		printf("     AC - add a category to a block\n");
		printf("     UBN - update block name\n");
		printf("     UCN - update category name\n");
		printf("     UCC - update capacity\n");
		printf("     UCS - update spending\n");
		printf("     ACS - add to spending\n");
		printf("     DB - Delete Block\n");
		printf("     DC - Delete Category\n");
		printf("     B - Go Back\n");
		printf("     Q - Quit\n");
	}else{
		cout << "Page Name Error" << endl;
		gVars.exit = true;
	}
	return;
}
void back(vector<Block> &budget, GlobalVars &gVars){
	gVars.pageName = 0b10;
	return;
}

void quit(vector<Block> &budget, GlobalVars &gVars){
	gVars.exit = true;
	return;
}

void addCategory(vector<Block> &budget, GlobalVars &gVars){
	cout << "* Add Category! (Enter N to cancel)\n* Enter Block Number: ";
	string number;
	cin >> number;
	if(number.compare("N") == 0){
		cout << "* Cancelled Category Addition\n";
		return;
	}
	cout << "* Enter Category Name: ";
	string name;
	cin >> name;
	if(name.compare("N") == 0){
		cout << "* Cancelled Category Addition\n";
		return;
	}
	Category* temp;
	string line;
	getline(cin,line);
	temp->name = name + line;

	//add a check to make sure these are numbers:

	cout << "* Enter Capacity: ";
	string capacity;
	cin >> capacity;
	if(capacity.compare("N") == 0){
		cout << "* Cancelled Category Addition\n";
		return;
	}

	//add a check to make sure these are numbers:

	temp->capacity = stoi(capacity);
	temp->name = name + line;
	cout << "* Enter Spending: ";
	string spending;
	cin >> spending;
	if(spending.compare("N") == 0){
		cout << "* Cancelled Category Addition\n";
		return;
	}
	temp->spending = stoi(spending);
	if(temp->spending > temp->capacity){
		temp->isOver = 1;
	}
	budget[stoi(number)-1].categories.push_back(temp);
}

void addCategorySpending(vector<Block> &budget, GlobalVars &gVars){
	cout << "* Add Spending to a Category! (Enter N to cancel)\n* Enter Block Number: ";
	string blockNumber;
	cin >> blockNumber;
	if(blockNumber.compare("N") == 0){
		cout << "* Cancelled Category Spending Addition\n";
		return;
	}
	cout << "* Enter Category Number: ";
	string categoryNumber;
	cin >> categoryNumber;
	if(categoryNumber.compare("N") == 0){
		cout << "* Cancelled Category Spending Addition\n";
		return;
	}
	
	cout << "* Enter Spending to Add: ";
	string spending;
	cin >> spending;
	if(categoryNumber.compare("N") == 0){
		cout << "* Cancelled Category Spending Addition\n";
		return;

	budget[stoi(blockNumber)-1].categories[stoi(categoryNumber)-1]->spending += stoi(spending);
	if(budget[stoi(blockNumber)-1].categories[stoi(categoryNumber)-1]->spending > budget[stoi(blockNumber)-1].categories[stoi(categoryNumber)-1]->capacity){
		budget[stoi(blockNumber)-1].categories[stoi(categoryNumber)-1]->isOver = 1;
	}else{
		budget[stoi(blockNumber)-1].categories[stoi(categoryNumber)-1]->isOver = 0;
	}
	return;
}

void deleteBlock(vector<Block> &budget, GlobalVars &gVars){
	
}

void deleteCategory(vector<Block> &budget, GlobalVars &gVars){

}
void updateBlockName(vector<Block> &budget, GlobalVars &gVars){

}
void updateCategoryName(vector<Block> &budget, GlobalVars &gVars){

}
void updateCategoryCapacity(vector<Block> &budget, GlobalVars &gVars){

}
void updateCategorySpending(vector<Block> &budget, GlobalVars &gVars){

}


int main (int argc, char *argv[]){
	if(argc != 2){
		cerr << "invalid usage: ./budget assets/budgetFile.txt" << endl;
		return 1;
	}

	//getting edit file
	ifstream budgetFile;
	string filename = argv[1];
	budgetFile.open(filename);
	if(!(budgetFile.is_open())){
		cerr << "editAssets not found!" << endl;
		return 1;
	}
	GlobalVars gVars;
	gVars.exit = false;
	gVars.back = false;
	gVars.numBlocks = 0;
	gVars.pageName = 0b10;

	//vars
	string name;                //input name
	int capacity;               //input capacity
	int spending;               //input spending
	int isOver;                 //input isOver
	budgetFile >> gVars.numBlocks;
	vector<Block> budget;       //stores the budget
	budget.resize(gVars.numBlocks);
	
	//input vars
	int block;
	int numCategories;
	Block* last = new Block;
	last->prev = NULL;
	//rebuilding the budget data structure
	while(budgetFile >> name >> block >> numCategories){
		last->numCategories = numCategories;
		last->index = block;
		last->name = name;
		for(int i = 0; i < numCategories; ++i){
			budgetFile >> name >> spending >> capacity >> isOver;
			Category* temp = new Category;
			if(i == 0){
				temp->prev = NULL;
				last->root = temp; 
			}
		}
	}
	char command;
	string stringInput;

	unordered_map<string,function<void(vector<Block>&,GlobalVars&)>> commands;                //command -> command function
	unordered_map<string,string> translator;                                                  //synonym -> actual command
	unordered_map<string,int> validCommands;                                                  //command -> pageNames
	unordered_map<int,string> pageNames;

	//mapping each command to its name
	commands["H"] = help;
	commands["E"] = editFunc;
	commands["P"] = print;
	commands["B"] = back;
	commands["Q"] = quit;
	commands["AB"] = addBlock;
	commands["AC"] = addCategory;
	commands["ACS"] = addCategorySpending;
	commands["DB"] = deleteBlock;
	commands["DC"] = deleteCategory;
	commands["UBN"] = updateBlockName;	
	commands["UCN"] = updateCategoryName;
	commands["UCC"] = updateCategoryCapacity;
	commands["UCS"] = updateCategorySpending;

	//mapping each synonym to its command
	translator["H"] = "H";
	translator["E"] = "E";
	translator["P"] = "P";
	translator["B"] = "B";
	translator["Q"] = "Q";
	translator["AB"] = "AB";
	translator["AC"] = "AC";
	translator["ACS"] = "ACS";
	translator["DB"] = "DB";
	translator["DC"] = "DC";
	translator["UBN"] = "UBN";	
	translator["UCN"] = "UCN";
	translator["UCC"] = "UCC";
	translator["UCS"] = "UCS";
	translator["h"] = "H";

	//mapping commands to the pages they can be executed in
	//each bit is a page 1-accessible 0-nonaccessible
	validCommands["H"] = 0b11;
	validCommands["E"] = 0b10;
	validCommands["P"] = 0b11;
	validCommands["B"] = 0b01;
	validCommands["Q"] = 0b11;
	validCommands["AB"] = 0b01;
	validCommands["AC"] = 0b01;
	validCommands["ACS"] =0b01;
	validCommands["DB"] = 0b01;
	validCommands["DC"] = 0b01;
	validCommands["UBN"] = 0b01;	
	validCommands["UCN"] = 0b01;
	validCommands["UCC"] = 0b01;
	validCommands["UCS"] = 0b01;

	//mapping each page number to their name
	pageNames[0b10] = "Home";
	pageNames[0b01] = "Edit";

	cout << "Press H for a list of commands\n";
	string input;
	//input loop
	while(!gVars.exit){
		cout << pageNames[gVars.pageName] << "> ";
		cin >> input;
		if(validCommands.find(translator[input]) == validCommands.end()){ //if the command doesnt exist
			cin.clear();
		cin.ignore(10000,'\n');
			cout << "invalid Command -- Press H for Help\n";
		}else{
			int valid = validCommands[translator[input]]&gVars.pageName;
			if(valid != gVars.pageName){                 //make sure we are on the correct page
				cin.clear();
				cin.ignore(10000,'\n');
				cout << "invalid Command -- Press H for Help\n";
				continue;
			}
			commands[translator[input]](budget,gVars);
		}

	}
	budgetFile.close();
};
