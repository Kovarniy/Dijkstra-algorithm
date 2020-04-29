
#include "pch.h"
#include <iostream>
#include <vector>
//#include <bits/stdc++.h>

using namespace std;

class WeightedGraph {
private:
	vector<vector<int>> adjMatrix;
	vector<vector<int>> patches; 
	int matrixSize;
	vector<int> dist, used, reach;

public: 
	WeightedGraph(vector<vector <int>> v) {
		matrixSize = v.size();
		dist.resize(matrixSize, 1e9);
		used.resize(matrixSize, 0);
		reach.resize(matrixSize, 0);
		patches.resize(matrixSize, vector<int>());
		adjMatrix.resize(matrixSize, vector<int>(matrixSize));
		copy(v.begin(), v.end(), adjMatrix.begin());
		
	}

	void daekstra(int num) {
		dist[num] = 0;
		patches[num].push_back(num);
		//for (int i = 0; i < patches.size(); i++)
			//patches[i].push_back(num);
	
		for (int i = 0; i < matrixSize; i++){
			int mn = 1e9, num;

			// Ищем самый дешевый и незадействованный путь
			for (int j = 0; j < matrixSize; j++) 
				if (!used[j] && dist[j] < mn) {
					mn = dist[j];
					num = j;
				}
			
			used[num] = 1;
			reach[num] = 1;

			for (int j = 0; j < matrixSize; j++) {
				if (!used[j] && adjMatrix[num][j] != -1 && dist[j] > dist[num] + adjMatrix[num][j]) {
					// Заносим данные в массив путей. 
					if (dist[j] == 1e9) {
						for (auto iter : patches[num]) 
							patches[j].push_back(iter);
						patches[j].push_back(j);
					}
					else {
						patches[j].clear();
						for (auto iter : patches[num]) 
							patches[j].push_back(iter);
						patches[j].push_back(j);
					}
					dist[j] = dist[num] + adjMatrix[num][j];
				}
			}

		}
	}

	void printPatches() {
		//cout << patches[0][0] << endl;
		for (int i = 0; i < patches.size(); i++, cout << endl)
			for (int j = 0; j < patches[i].size(); j++)
				cout << patches[i][j] << " ";
	}
	

};



int main()
{
	vector<vector<int>> task1({ { -1, 7, 10, -1, -1, -1, -1 },
								{ -1, -1, -1, 9, 14, -1, -1 },
								{ -1, -1, -1, 8, -1, -1, 41 },
								{ -1, -1, -1, -1, -1, 11, 44 },
								{ -1, -1, -1, 4, -1, 8, -1 },
								{ -1, -1, -1, -1, -1, -1, 5 },
								{ -1, -1, -1, -1, -1, -1, -1 } });

	WeightedGraph g1(task1);
	g1.daekstra(0);
	g1.printPatches();

	cout << "************************" << endl;
	
	vector<vector<int>> task2({ { -1, 10, 6, 4 },
								{ 8, -1, 6, 14 },
								{ 2, 15, -1, 22 },
								{ 1, 5, 6, -1 }});
	WeightedGraph g2(task2);
	g2.daekstra(0);
	g2.printPatches();
}
