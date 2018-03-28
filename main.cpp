#include <iostream>
#include "hungarian.h"

using namespace std;
int main(){
	vector<vector<int>> cost_matrix={{82,83,69,92},
									 {77,37,49,92},
									 {11,69,5,86},
									 {8,9,98,23}};

	hungarian hun(cost_matrix);
	int min_cost = hun.slove(cost_matrix);
	cout<<"the min cost is:"<<min_cost<<endl;

	return 0;
}