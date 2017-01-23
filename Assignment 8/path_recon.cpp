#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <iomanip>

#define const 99                 

using namespace std;

class Graph{

	int station;                
	int route;                  
	int weight;                 
	int **adjMatrix; 						//Adjacency matrix		
	int **floydMatrix; 						//Matrix for Floyd-Warshall calc
	int **reconMatrix; 						//Matrix for path reconstruction
	string *stationColors;  	

	vector<int> trainPath;					//Vector to print reconstructed path

public:

	Graph(int, int);								//Total number of routes and stations
	void addRoute(int, int, int);					//Add route to adjacency matrix with appropriate weight
	bool isRoute(int, int);   						//Return bool value indicating existence of route              
	~Graph(void);							
	void calcShortestRoutes();    					//Run Floyd on the adjacency matrix to solve all-pairs shortest path                  
	int shortestRoute(string, string);				//Return the shortest route between src and dst stations	
	bool checkColors(string); 						//User input validation check
	int getStationId(string);                 		//Get int value for station
	string getStationColors(int);                
	void setStationColors(int, string); 
	void printPath(string, string);   				//Print reconstructed path

};

Graph::Graph(int stations, int routes)
{
	int i, j;

	stationColors = new string[stations]; 

	station = stations;
	route = routes; 

	adjMatrix = new int* [station];

	for(i = 0; i < station; i++)
	{
		adjMatrix[i] = new int[station];

		for(j = 0; j < station; j++)
		{
			adjMatrix[i][j] = 0;  
		}						
	}

	//Initialize the Floyd Warshall matrix
	floydMatrix = new int* [station];

	for(i = 0; i < station; i++)
	{
		floydMatrix[i] = new int[station];

		for(int j = 0; j < station; j++)
		{
			floydMatrix[i][j] = const; 
		}
	}  

	//Initialize matrix to be used for path reconstruction
	reconMatrix = new int* [station];	

	for(i = 0; i < station; i++)
	{
		reconMatrix[i] = new int[station];

		for(j = 0; j < station; j++)
		{
			reconMatrix[i][j] = -1;
		}
	}

}

//Add route to adjacency matrix with appropriate weight
void Graph::addRoute(int src, int dest, int weight)
{
	adjMatrix[src][dest] = weight; 

	floydMatrix[src][dest] = weight;

	reconMatrix[src][dest] = dest;
}

//Return bool value indicating existence of route
bool Graph::isRoute(int src, int dest)  
{
	bool isPath = false;
	bool visited[station]; 
	queue<int> vertices;

	for(int i = 0; i < station ; i++)
	{
		visited[i] = false;
	}

	visited[src] = true; 
	vertices.push(src);  	//Add start index to queue 

	while(!vertices.empty() && isPath == false )
	{
		int currentInQueue;

		currentInQueue = vertices.front();                  
		vertices.pop();										

		for(int temp = 0; temp < station ; temp++)
		{
			if(adjMatrix[currentInQueue][temp] != 0)
			{       											  
				//Checks for correct node
				if(temp == dest)
				{
					isPath = true;
					break;
				}

				if(visited[temp] == false)
				{ 				  
					//visited
					visited[temp] = true;	

					//enqueue
					vertices.push(temp);                    
				}

			}
		}
	}

	return isPath;
}

void Graph::calcShortestRoutes()
{ 
	int i,j,k;

	for(k = 0; k < station; k++)
	{
		for(i = 0; i < station; i++)
		{

			for(j = 0; j < station; j++)
			{
				if(floydMatrix[i][j] > floydMatrix[i][k] + floydMatrix[k][j])
				{
					floydMatrix[i][j] = floydMatrix[i][k] + floydMatrix[k][j];

					reconMatrix[i][j] = reconMatrix[i][k];
				}

			}

		}

	}

}

int Graph::shortestRoute(string src, string dst)
{
	int a = getStationId(src);
	int b = getStationId(dst);

	return floydMatrix[a][b];  
}

bool Graph::checkColors(string src)
{
	for( int i = 0; i < station; i++ )
	{ 

		if(stationColors[i] == src )
		{
			return true;
		}

	}
	return false;
}

int Graph::getStationId(string color)
{
	int id = 0; 

	for(int i = 0; i < station; i++)
	{  
		if(stationColors[i] == color)
		{
			return id;
		}

		if(id < station)
		{
			id++; 
		}
	}
}

string Graph::getStationColors(int id)
{
	return stationColors[id];
}

void Graph::setStationColors(int id, string color)
{
	stationColors[id] = color;
}

//Print the path from path reconstruction
void Graph::printPath(string src, string dst)
{
	//Calls to getStationId to convert the string values to int values
	int i = getStationId(src);
	int j = getStationId(dst);

	trainPath = vector<int> (1,0);

	if(reconMatrix[i][j] == -1)
	{
		return;
	}

	trainPath[0] = i;	//First node is initialized 

	while(i != j)
	{
		i = reconMatrix[i][j];
		trainPath.push_back(i);
	}

	cout << endl << "Your path will be ";

	int a, b;

	for(a = 0; a < trainPath.size(); a++)
	{
		cout << getStationColors(trainPath[a]);

		//print arrow while loop isn't on the last node
		if(a < trainPath.size() - 1)
		{
			cout << "->";
		}
	}

	cout << endl;
}

//Deconstructor to delete dynamically allocated memory
Graph::~Graph(void)
{
	int i;

	for(i = 0 ; i < station; i++)
	{
		delete adjMatrix[i];
	}

	delete adjMatrix;

	for(i = 0 ; i < station; i++)
	{
		delete floydMatrix[i];
	}

	for(i = 0; i < station; i++)
	{
		delete reconMatrix[i];
	}

	delete reconMatrix;

	delete floydMatrix;

	delete[] stationColors;

	stationColors = NULL;
}

//Main function
int main(void)
{
	ifstream file;
	file.open("routes.txt");
	
	if(!file.is_open())
	{
		cout << "File Error";
		return -1;
	}

	int afile;
	int bfile;
	int cfile;

	file >> afile >> bfile;

	Graph mainMtrx = Graph(afile, bfile);

	while (file >> afile >> bfile >> cfile)
	{
		mainMtrx.addRoute(afile, bfile, cfile);
	}


	ifstream file2;
	file2.open("stations.txt");

	if(!file2.is_open())
	{
		cout << "Error opening that file";
		return -1;
	}

	int num;
	string color;
	
	while ( file2 >> num >> color )
	{
		mainMtrx.setStationColors(num,color);
	}

	mainMtrx.calcShortestRoutes();

	int choice = 1; 

	//enter while loop for continuous menu
	while(choice == 1)
	{
		cout << endl << "-- Menu --" << endl;

		cout << "     0 -> Exit" << endl;		
		cout << "     1 -> Print Menu" << endl;
		cout << "     2 -> Check if path exists" << endl;
		cout << "     ENTER: ";

		cin >> choice;

		//Terminate program when 0 is entered
		if(choice == 0)
		{
			break;
		}

		if(choice == 2)
		{
			string source;
			string destination;

			cout << endl << "From what station are you leaving? ";
			cin >> source;

			//Input validation
			while(mainMtrx.checkColors(source) == false)
			{
				cout << source << " is not a valid name, please enter again: ";
				cin >> source;
			}

			cout << endl << "To what station are you traveling? ";
			cin >> destination;

			//Input validation
			while(mainMtrx.checkColors(destination) == false)
			{
				cout << destination << " is not a valid name, please enter again: ";
				cin >> destination;
			}
			
			int a = mainMtrx.getStationId(source);
			int b = mainMtrx.getStationId(destination);

			if(mainMtrx.isRoute(a,b))
			{	
				int minRoute = mainMtrx.shortestRoute(source, destination);

				cout << endl << "There is a route between " << source << " and " << destination << " with a minimum distance of " << minRoute << " miles." << endl;
				
				//Call to print out path reconstruction
				mainMtrx.printPath(source, destination);
				choice = 1;
			}
			else
			{
				cout << "There is no route between " << source << " and " << destination << endl;
				choice = 1;
			}
		}
	}

	//Graph::~Graph();

	file.close();
	file2.close();

	return 0;
}