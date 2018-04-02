#include <vector>
#include <iostream>
#ifndef HUNGARIAN_H
#define HUNGARIAN_H


using namespace std;

class hungarian
{
public:
	vector<vector<int>> OG_cost_matrix;
	vector<vector<int>> CUR_cost_matrix;
	vector<int> uncovered_row;
	vector<int> uncovered_col;
	vector<int> covered_row;
	vector<int> covered_col;
	hungarian(vector<vector<int>> cost_matrix){
		OG_cost_matrix = cost_matrix;
		CUR_cost_matrix = cost_matrix;
		for (int i=0;i<cost_matrix.size();i++){
			uncovered_row.push_back(i);
		}
		uncovered_col = uncovered_row;
	};
	int solve(vector<vector<int>>);

private:

	
};

#endif