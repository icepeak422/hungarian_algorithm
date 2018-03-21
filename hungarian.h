#ifndef HUNGARIAN_H
#define HUNGARIAN_H

class hungarian
{
public:
	vector<vector<int>> OG_cost_matrix;
	hungarian(vector<vector<int>> cost_matrix){
		OG_cost_matrix = cost_matrix;
	};
	~hungarian();
	int solve(vector<vector<int>>);

private:

	
};

#endif