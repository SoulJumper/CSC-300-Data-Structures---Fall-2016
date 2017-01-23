#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CharacterTree
{

private:
	vector<string> vTree; 

public:
	CharacterTree();  
	void insert(string s, int index);
	string getIndex(int index);
	void resizeTree(int index);

}; 

CharacterTree::CharacterTree() 
{	
	vTree = vector<string> (3, "");
	vTree[0] = "Captain America";
}

void CharacterTree::insert(string s, int index)
{
	//Insert into the correct index of the vector
	if(index * 2 > vTree.size()) 
	{
		vTree.resize( index * 2  , "");                     
	}
	
	vTree[index] = s;                              
}

string CharacterTree::getIndex(int index)
{
	if(index < vTree.size())
	{
		return vTree.at(index); 
	}
	else
	{
		return "";
	}
	
}

int main(void)
{
	
	CharacterTree myTree = CharacterTree(); 
	string answer = "y";                    
	string yesOrNo;                         
	string characterName;                   
	string characterQuestion;               

	while(answer == "y")
	{	
		int treeIndex = 0; 

		cout << "Are you thinking of your favorite character? (y/n) ";
		getline (cin,answer);

		while( (answer != "y") && (answer != "n")  )
		{
			cout << "Are you thinking of your favorite character? (y/n) ";
			getline (cin,answer);
		}
		
		if(answer == "n")
		{
			continue; 
		}

		while(myTree.getIndex( (2 * treeIndex) + 1) != "" )
		{
			cout << myTree.getIndex(treeIndex) << " (y/n) ";
			getline (cin,yesOrNo);

			//Error check for answer of y or n
			while( (yesOrNo != "y") && (yesOrNo != "n") )
			{
				cout << "Please enter again: " << myTree.getIndex(treeIndex) << " (y/n) ";
				getline (cin,yesOrNo);
			}

			if(yesOrNo == "y")
			{
				treeIndex = (2 * treeIndex) + 2; //access to right child
			}
			else
			{
				treeIndex = (2 * treeIndex) + 1; //access to left child
			}

		}
		
		//Guesses based off of what it has "learned"
		cout << "Is it " << myTree.getIndex(treeIndex) << "? (y/n) ";
		getline (cin,yesOrNo);  

		//Error check for an answer of y or n
		while( (yesOrNo != "y") && (yesOrNo != "n") )
		{
			cout << "Please enter again: Is it " << myTree.getIndex(treeIndex) << " (y/n) ";
			getline (cin,yesOrNo);
		}  

		if(yesOrNo == "y")
		{
			cout << "I rule!" << endl << endl;  
			continue;                           
		}

		cout << "What is the character's name? ";	
		getline (cin, characterName);	

		cout << "What question would distinguish " << characterName << " from " << myTree.getIndex(treeIndex) << "? ";
		getline (cin, characterQuestion);
 
		string temp;  
		temp = myTree.getIndex(treeIndex);
		
		myTree.insert(characterQuestion, treeIndex);

		cout << "If the character were " << characterName << ", what would the answer be? (y/n) ";
		getline (cin,yesOrNo); 
		cout << endl;  

		//Error check to y or n for answer to entered question
		while((yesOrNo != "y") && (yesOrNo != "n") )
		{
			cout << "Please enter again: (y/n) ";
			getline (cin,yesOrNo);
		}

		if(yesOrNo == "y")
		{
			myTree.insert(temp, (2 * treeIndex) + 1);
			myTree.insert(characterName, (2 * treeIndex) + 2);
		}
		else
		{
			myTree.insert(characterName, (2 * treeIndex) + 1);
			myTree.insert(temp, (2 * treeIndex) + 2);	
		}

	}
	
	return 0;
}