#include <iostream>
#include <algorithm> 
#include <fstream>
#include <string.h>
#include <map>
#include <vector>
using namespace std;

struct node{
	int indegree;
	int outdegree;
	vector<int> adjList;
};
struct tableCoordinate{
	int valid;
	int variableAssigned;
};
std::map<int,node> nodeMapSmall;
std::map<int,node> nodeMapLarge;

void input(char filename[]){
	string line;
	ifstream in;
	in.open(filename);
	if (!in.is_open()){
		cout << "File not found.\n";
	}
	else{
		int v1,v2;
		bool toggle = false;
		while (in >> v1 >> v2){
			if (v1 == 0){
				toggle = true;
				continue;
			}
			if (toggle){
				if (nodeMapSmall.find(v1) != nodeMapSmall.end()){
					nodeMapSmall[v1].outdegree++;
					nodeMapSmall[v1].adjList.push_back(v2);
					if (nodeMapSmall.find(v2) != nodeMapSmall.end()){
						nodeMapSmall[v2].indegree++;
					}
					else{
						node n;
						n.indegree = 1;
						n.outdegree = 0;
						nodeMapSmall[v2] = n;
					}
				}
				else{
					node n;
					n.indegree = 0;
					n.outdegree = 1;
					n.adjList.push_back(v2);
					nodeMapSmall[v1] = n;
					if (nodeMapSmall.find(v2) != nodeMapSmall.end()){
						nodeMapSmall[v2].indegree++;
					}
					else{
						node n1;
						n1.indegree = 1;
						n1.outdegree = 0;
						nodeMapSmall[v2] = n1;
					}
				}
			}
			else{
				if (nodeMapLarge.find(v1) != nodeMapLarge.end()){
					nodeMapLarge[v1].outdegree++;
					nodeMapLarge[v1].adjList.push_back(v2);
					if (nodeMapLarge.find(v2) != nodeMapLarge.end()){
						nodeMapLarge[v2].indegree++;
					}
					else{
						node n;
						n.outdegree = 0;
						n.indegree = 1;
						nodeMapLarge[v2] = n;
					}
				}
				else{
					node n;
					n.indegree = 0;
					n.outdegree = 1;
					n.adjList.push_back(v2);
					nodeMapLarge[v1] = n;
					if (nodeMapLarge.find(v2) != nodeMapLarge.end()){
						nodeMapLarge[v2].indegree++;
					}
					else{
						node n1;
						n1.outdegree = 0;
						n1.indegree = 1;
						nodeMapLarge[v2] = n1;
					}
				}
			}
		}
		ofstream out("data",ios::out);
		out << nodeMapSmall.size() << "\n";
		for (std::map<int,node>::iterator it = nodeMapSmall.begin(); it != nodeMapSmall.end(); ++it){
			out << (it->first) << " ";
		}
		out << "\n";
		out << nodeMapLarge.size() << "\n";
		for (std::map<int,node>::iterator it = nodeMapLarge.begin(); it != nodeMapLarge.end(); ++it){
			out << (it->first) << " ";
		}
		out << "\n";
		out.close();
		//cout << "Large Map : " << endl;
		//for (std::map<int,node>::iterator it = nodeMapLarge.begin(); it != nodeMapLarge.end(); ++it){
		//	// cout << it->first << " : " << (it->second).indegree << " " << (it->second).outdegree << "\n";
		//	vector<int> v = (it->second).adjList;
		//	for (int i = 0; i < v.size(); i++){
		//		cout << it->first << " -> " << v[i] << '\n';
		//	}
		//}
		//cout << "Small Map : " << endl;
		//for (std::map<int,node>::iterator it = nodeMapSmall.begin(); it != nodeMapSmall.end(); ++it){
		//	// cout << it->first << " : " << (it->second).indegree << " " << (it->second).outdegree << "\n";
		//	vector<int> v = (it->second).adjList;
		//	for (int i = 0; i < v.size(); i++){
		//		cout << it->first << " -> " << v[i] << '\n';
		//	}
		//}	
	}
}
tableCoordinate** solve(){
	tableCoordinate** table = new tableCoordinate*[nodeMapSmall.size()];
	int p = 0;
	int q = 0;
	for (std::map<int,node>::iterator it = nodeMapSmall.begin(); it != nodeMapSmall.end(); ++it){
		table[p] = new tableCoordinate[nodeMapLarge.size()];
		q = 0;
		for (std::map<int,node>::iterator it1 = nodeMapLarge.begin(); it1 != nodeMapLarge.end(); ++it1){
			std::vector<int>::iterator it2 = find ((it->second).adjList.begin(), (it->second).adjList.end(), (it1->first));
			if (((it->second).indegree <= (it1->second).indegree) && ((it->second).outdegree <= (it1->second).outdegree))
				table[p][q].valid = 1;
			else
				table[p][q].valid = 0;
			q++;
		}
		p++;
	}
	//cout << "Final Table: \n";
	//for (int i=0; i<nodeMapSmall.size(); i++){
	//	for (int j=0; j<nodeMapLarge.size(); j++){
	//		cout << table[i][j].valid << " ";
	//	}
	//	cout << "\n";
	//}
	return table;
}
void output(tableCoordinate** table, char filename[]){
	int n1 = nodeMapLarge.size();
	int m1 = nodeMapSmall.size();
	int countOfVariables = 0;
	int countOfClauses = m1 + (m1*n1*(n1-1)/2) + (m1*n1*(m1-1)/2) + (m1*n1*((m1*n1)-1)/2) + 3;
	if (table){
		int countArray[nodeMapLarge.size()] = {0};
		//memset(countArray,0,nodeMapLarge.size());
		int countArrayRowwise[nodeMapSmall.size()] = {0};
		//memset(countArrayRowwise,0,nodeMapSmall.size());
		ofstream out(filename, ios::out);
		ofstream out1("data",ios::app);
		long counter = 1;
		for (int i=0; i<nodeMapSmall.size(); i++){
			for (int j=0; j<nodeMapLarge.size(); j++){
				if (table[i][j].valid == 1){
					table[i][j].variableAssigned = counter;
					counter++;
					countArray[j] ++;
					countArrayRowwise[i] ++;
				}
				else{
					table[i][j].variableAssigned = 0;
				}
			}
		}
		countOfVariables = counter-1;
		out << "p cnf " << countOfVariables << " " << countOfClauses << "\n";
		out1 << countOfVariables << "\n";
		for (int i=0; i<nodeMapSmall.size(); i++){
			for (int j=0; j<nodeMapLarge.size(); j++){
				if (table[i][j].valid == 1){
					out1 << table[i][j].variableAssigned << " ";
					out << 	table[i][j].variableAssigned << " ";
				}
				else{
					out1 << "0 ";				
				}
			}
			out << "0\n";
			out1 << "\n";
		}
		for (int j=0; j<nodeMapLarge.size(); j++){
			if (countArray[j] > 1){
				for (int i = 0; i < nodeMapSmall.size(); i++){
					if (table[i][j].valid == 1){
						for (int k = i+1; k < nodeMapSmall.size(); k++){
							if (table[k][j].valid == 1){
								out << "-" << table[i][j].variableAssigned << " -" << table[k][j].variableAssigned << " 0\n";
							}
						}
					}
					else
						continue;
				}
			}
			else{
				continue;
			}	
		}
		for (int i = 0; i < nodeMapSmall.size(); i++){
			if (countArrayRowwise[i] > 1){
				for (int j=0; j<nodeMapLarge.size(); j++){
					if (table[i][j].valid == 1){
						for (int k = j+1; k < nodeMapLarge.size(); k++){
							if (table[i][k].valid == 1){
								out << "-" << table[i][j].variableAssigned << " -" << table[i][k].variableAssigned << " 0\n";
							}
						}
					}
					else
						continue;
				}
			}
			else{
				continue;
			}	
		}
		int row = 0;
		int column = 0;
		int row1 = 0;
		int column1 = 0;
		for (std::map<int,node>::iterator it = nodeMapSmall.begin(); it != nodeMapSmall.end(); ++it){
			column = 0;
			for (std::map<int,node>::iterator it1 = nodeMapLarge.begin(); it1 != nodeMapLarge.end(); ++it1){
				if (table[row][column].valid ==0){
					column ++;
					continue;
				}
				row1 = 0;
				column1 = 0;
				for (std::map<int,node>::iterator it2 = nodeMapSmall.begin(); it2 != nodeMapSmall.end(); ++it2){
					if (row == row1){
						row1++;
						continue;
					}
					column1 = 0;
					for (std::map<int,node>::iterator it3 = nodeMapLarge.begin(); it3 != nodeMapLarge.end(); ++it3){
						if ((table[row1][column1].valid == 0) || (column == column1)){
							column1++;
							continue;
						}
						std::vector<int>::iterator ita = find ((it->second).adjList.begin(), (it->second).adjList.end(), (it2->first));
						std::vector<int>::iterator itb = find ((it1->second).adjList.begin(), (it1->second).adjList.end(), (it3->first));
						if (((ita != (it->second).adjList.end()) && (itb == (it1->second).adjList.end())) || ((ita == (it->second).adjList.end()) && (itb != (it1->second).adjList.end()))){
							out << "-" << table[row][column].variableAssigned << " -" << table[row1][column1].variableAssigned << " 0\n";
						}
						column1++;
					}
					row1++;
				}
				column ++; 
			}
			row++;
		}
		out.close();
		out1.close();
	}	
}
int main(int argc, char * argv[])
{
	char* infile;
	char* infile1;
	infile = argv[1];
	strcpy(infile1,infile);
	strcat(infile,".graphs");
	strcat(infile1,".satinput");
	input(infile);
	tableCoordinate** table = solve();
	output(table,infile1);
	delete table;
	return 0;
}
