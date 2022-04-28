#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <vector>
#include <algorithm>

std::string generatedChar="";
std::vector<std::string> charTypes;
std::vector<std::string> attributes;
std::vector<std::string> minStats;


//function declarations
void runMenu();
void displayText(std::string);
void createLists(std::string);
std::string generateCharacter();
void saveData(std::string,std::string);
void readData(std::string);


//main() function
int main() {
	srand(static_cast<unsigned int>(time(NULL)));
	
	
	runMenu();
	

	std::cout << std::endl;
	system("pause");
	return 0;
}


//functions definitions
void runMenu(){
	
	char wantToRepeat='y';
	int intChoice;
	
	while (wantToRepeat=='y'||wantToRepeat=='Y') {
		std::cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		std::cout<<"\n\tThe Amazing RPG Character Generator\t";
		std::cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		std::cout<<"\n[1] End Testing the Program"<<std::endl;
		std::cout<<"[2] Display 'About' Information"<<std::endl;
		std::cout<<"[3] Read and store data from files"<<std::endl;
		std::cout<<"[4] Generate a random Character"<<std::endl;
		std::cout<<"[5] Save a character to file"<<std::endl;
		std::cout<<"[6] Load saved Characters from file"<<std::endl;
		
		std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
		std::cout<<"Which option would you like? (1-6): "<<std::endl;
		std::cin>>intChoice;
			
			switch (intChoice) {
					
				case 1:
					wantToRepeat='n';
					break;
					
				case 2:
					displayText("RPGAbout.txt");
					std::cout<<std::endl;
					break;
					
				case 3:
					std::cout<<"\n\tData loading from charTypes.txt"<<std::endl;
					createLists("charTypes.txt");
					
					std::cout<<"\tData loading from charAttributes.txt"<<std::endl;
					createLists("charAttributes.txt");
					
					std::cout<<"\tData loading from charAttMins.txt"<<std::endl;
					createLists("charAttMins.txt");
					std::cout<<"\nDone!"<<std::endl;
					break;
					
				case 4:
					generateCharacter();
					break;
					
				case 5:
					std::cout<<generatedChar;
					saveData(generatedChar,"savedCharacters.txt");
					break;
					
				case 6:
					readData("savedCharacters.txt");
					break;
					
				default:
					std::cout<<"You chose an invalid option!";
					break;
			}
		
		if (wantToRepeat=='n') {
			std::cout<<"\nGoodbye!\n";
		}
		
		else{
		std::cout<<"\nDo you want to return to the menu? (y/n): ";
		std::cin>>wantToRepeat;
			if (wantToRepeat=='n'||wantToRepeat=='N') {
				std::cout<<"\nGoodbye!\n";
			}
			if (wantToRepeat=='y'||wantToRepeat=='Y') {
				wantToRepeat='y';
			}
			else{
				while (wantToRepeat!='n'&&wantToRepeat!='N'&&wantToRepeat!='y'&&wantToRepeat!='Y'){
					std::cout<<"You chose an invalid option! Choose again (y/n): ";
					std::cin>>wantToRepeat;
					if (wantToRepeat=='n'||wantToRepeat=='N') {
						std::cout<<"\nGoodbye!\n";
					}
				}
			}
				
		}
			
	}
}



	

void displayText(std::string myFileName){
	std::string fileData="";
	std::fstream fileToRead;
	fileToRead.open(myFileName);
	if (fileToRead.is_open()) {
		while (!fileToRead.eof()) {
			getline(fileToRead, fileData);
			std::cout<<"\n"+fileData;
		}
	}
	else{
		std::cout<<"ERROR: file not found"<<std::endl;
	}
	fileToRead.close();
}



void createLists(std::string charFileName){
	
	if (charFileName=="charTypes.txt") {
		
		std::string line="";
		std::fstream fileToRead;
		fileToRead.open(charFileName);
		if (fileToRead.is_open()) {
			while (!fileToRead.eof()) {
				for (int counter=0; counter<6; counter++) {
					getline(fileToRead, line);
					charTypes.push_back(line);
				}
			}
		}
		else {
			std::cout<<"ERROR: unable to access file"<<std::endl;
		}
		fileToRead.close();
	}
	
	else if (charFileName=="charAttributes.txt"){
		
		std::string line="";
		std::fstream fileToRead;
		fileToRead.open(charFileName);
		if (fileToRead.is_open()) {
			while (!fileToRead.eof()) {
				for (int counter=0; counter<6; counter++) {
					getline(fileToRead, line);
					attributes.push_back(line);
				}
			}
		}
		else{
			std::cout<<"ERROR: unable to access file"<<std::endl;
		}
		fileToRead.close();
	}
	
	else if (charFileName=="charAttMins.txt"){
		
		std::string line="";
		std::fstream fileToRead;
		fileToRead.open(charFileName);
		if (fileToRead.is_open()) {
			while (!fileToRead.eof()) {
				for (int counter=0; counter<6; counter++) {
					getline(fileToRead, line);
					minStats.push_back(line);
				}
			}
		}
		else{
			std::cout<<"ERROR: unable to access file"<<std::endl;
		}
		fileToRead.close();
	}
}



std::string generateCharacter(){
	createLists("charTypes.txt");
	createLists("charAttributes.txt");
	createLists("charAttMins.txt");
	
	std::string randChar="";
	
	if (charTypes.size()!=0&&attributes.size()!=0&&minStats.size()!=0) {
		int randTypeInt=rand()%charTypes.size();
			
		std::string typeString="\n"+charTypes[randTypeInt] + "\n~~~~~~~~~~~~~~~~~\n";	//displays character type & curly lines underneath it
		std::string randChar=typeString;
		
		std::vector<std::string>::iterator charTypesIter;
		charTypesIter=find(charTypes.begin(), charTypes.end(), charTypes[randTypeInt]);
		short charIndex=charTypesIter-charTypes.begin();	//gets index of randomly generated character

		const int ROW_SIZE=6;
		const int COL_SIZE=6;
		int statsArray[ROW_SIZE][COL_SIZE]={{1,2,2,3,3,4},{1,2,2,4,3,4},{4,3,5,5,4,2},{6,5,5,5,3,1},{4,4,3,2,0,0},{5,2,1,3,1,1}};
	
		
		for (int counter=0; counter<6; counter++) {
			
			
			std::string attributeString=attributes[counter];
			attributeString.erase(attributeString.length()-1);
			
			int randValue=0;
			randValue=rand()%6;
			std::string randValueString=std::to_string(randValue);
			
			int minStats=statsArray[counter][charIndex];
			std::string minStatsString=std::to_string(minStats);
			
			int minInitialStats= minStats+randValue;
			std::string minIniStatsString= std::to_string(minInitialStats);
			
			std::string wordString="The minimum "+attributeString+" is "+minStatsString+" and the random value is "+randValueString;
			
			std::string finalString=attributeString+": "+minIniStatsString+" ["+wordString+"]"+"\n";
			
			randChar+=finalString;
		}
		generatedChar=randChar;
		std::cout<<randChar;
		
	}
	else{
		std::cout<<"ERROR: collection lists are empty!"<<std::endl;
	}
	return randChar;
}





void saveData(std::string myCharName, std::string myFileName){
	if (myCharName!="") {
		char userInput='a';
		std::cout<<"\nDo you want to save this character? (y/n): "<<std::endl;
		std::cin>>userInput;
		
		if (userInput=='y'||userInput=='Y') {
			std::ofstream writeFile;
			writeFile.open("savedCharacters.txt", std::ios::app);
			if (writeFile.is_open()) {
				writeFile<<generatedChar;
				std::cout<<"\nCharacter has been saved.\n";
			}
			else{
				std::cout<<"ERROR: file not found"<<std::endl;
			}
			writeFile.close();
		}
		
		else if (userInput=='n'||userInput=='N'){
			
		}
		
		else if (userInput!='n'&&userInput!='N'&&userInput!='y'&&userInput!='Y'){
				std::cout<<"ERROR: invalid option!"<<std::endl;
		}
	}
	else{
		std::cout<<"ERROR: generate a random character first!"<<std::endl;
	}
	
}




void readData(std::string myFileName){
	std::ifstream readFromFile;
	std::string fileData;
	readFromFile.open(myFileName);
	if (readFromFile.is_open()) {
		while (!readFromFile.eof()) {
			getline(readFromFile, fileData);
			std::cout<<"\n"+fileData;
		}
	}
	else{
		std::cout<<"ERROR: file not found"<<std::endl;
	}
	readFromFile.close();
}
