#include <iostream>
#include <algorithm> 
#include <fstream>
#include <string.h>
#include <map>
#include <vector>
using namespace std;

void input(char filename[], char filename1[]){
	ifstream in1;
	in1.open(filename);
	if (!in1.is_open()){
		cout << "File not found.\n";
	}
	else{
		string line;
		getline(in1,line);
		ofstream out(filename1,ios::out);
		if (line.compare("UNSAT") == 0){
			out << "0\n";
			out.close();
		}
		else{
			ifstream in;
			in.open("data");
			if (!in.is_open()){
				cout << "File1 not found.\n";
			}
			else{
				vector<int> smallGraph;
				vector<int> largeGraph;
				int sizeOfSmall;
				int sizeOfLarge;
				int noOfVariables;
				in >> sizeOfSmall;
				for (int i=0; i<sizeOfSmall; i++){
					int v;
					in >> v;
					smallGraph.push_back(v);
				}
				in >> sizeOfLarge;
				for (int i=0; i<sizeOfLarge; i++){
					int v;
					in >> v;
					largeGraph.push_back(v);
				}
				in >> noOfVariables;
				std::map<int,bool> variables;
				for (int i=0; i<noOfVariables; i++){
					int v;
					in1 >> v;
					if (v<0)
						variables[-v] = false;
					else
						variables[v] = true;
				}
				in1.close();				
				int n = 0;
				for (int i=0; i<sizeOfSmall; i++){
					for (int j=0; j<sizeOfLarge; j++){
						in >> n;
						if (n==0){
							continue;
						}	
						else{
							if (variables[n] == true){
								out << smallGraph[i] << " " << largeGraph[j] << "\n";							
							}
						}
					}
				}
				out.close();	
			}
		}
	}		
}
int main(int argc, char * argv[])
{
	char* infile;
	infile = argv[1];
	char* infile1 = (char*)malloc(strlen(infile)+1);	
	if (infile1){	
		strcpy(infile1,infile);
		strcat(infile,".satoutput");
		strcat(infile1,".mapping");
		input(infile,infile1);
	}
	return 0;
}
