#include <algorithm>
#include <iostream>
#include <vector>
#include "hungarian.h"


void hungarian::print_matrix(vector<vector<int>> matrix){
	for(unsigned int x=0;x<cost_matrix.size();x++){
        for(unsigned int y=0;y<cost_matrix[0].size();y++)  {
            cout<<matrix[x][y]<<" ";  
        }
	cout<<endl;  
	}
}
// the process to slove the problem
int hungarian::solve(vector<vector<int>>& cost_matrix){
	int cost=0;
	bool solution=false;
	int num_row = cost_matrix.size();
	int num_col = cost_matrix[0].size();

	// at first we just want to implement the algorithm on square cost matrix
	if ( num_row!=num_col ) {
        throw invalid_argument( "cost matrix should be square" );
    }
	step1(&cost_matrix);
	step2(&cost_matrix);
	step3(&cost_matrix,solution);
	while(solution==false){
		step4(&cost_matrix);
		step3(&cost_matrix,solution);
	}

	vector<int> assignment (cost_matrix.size(),0);
	//i-th element this assignment vector represents worker i do assignment[i] job
	assignment = assign(&cost_matrix);
	for (unsigned int i=0;i<assignment.size();++i){
		cost+=hungarian.OG_cost_matrix[i][assignment[i]];
	}
	return cost;
}

// find all the minimum in each row, and substract it.
void step1(vector<vector<int>>& cost_matrix){
	vector<int> cur_row;
	int min_in_row =0;
	for (unsigned int i = 0; i < cost_matrix.size(); ++i){
		cur_row= cost_matrix[i];
		sort(cur_row.begin(),cur_row.end());
		min_in_row = cur_row[0];
		for (unsigned  int j = 0; j < cost_matrix[0].size(); ++j){
			cost_matrix[i][j]=cost_matrix[i][j]-min_in_row;
		}
	}
	cur_row.clear();
	return;
}

// find all the minimum in each column, and substract it.
void step2(vector<vector<int>>& cost_matrix){
	vector<int> cur_col;
	int min_in_col =0;
	for (unsigned int j = 0; j < cost_matrix[0].size(); ++j){
		for (unsigned  int i = 0; i < cost_matrix.size(); ++i){
			if(cost_matrix[i][j]==0){
				cur_col.clear();
				break;
			}
			cur_col.push_back(cost_matrix[i][j]);
		}
		if(cur_col.size()){
			sort(cur_col.begin(),cur_col.end());
			min_in_col = cur_col[0];
			for (unsigned  int i = 0; i < cost_matrix.size(); ++i){
				cost_matrix[i][j]=cost_matrix[i][j]-min_in_col;
			}
		}
		
	}
	cur_col.clear();
	return;
}

// find the minimal lines to cover all the zeros
// this is the most challange part 
void step3(vector<vector<int>>& cost_matrix, bool solution){
	/**to be implement**/
	int mini_line=0;
	/**First, count the num of 0 in every row and column**/
	int SIZE=cost_matrix.size();
	vector<int> num0perrow (SIZE,0);
	vector<int> num0percol (SIZE,0);
	for (unsigned int i=0;i<SIZE;++i){
		for (unsigned int j=0;j<SIZE;++j){
			if(cost_matrix[i][j]==0){
				num0perrow[i]++;
				num0percol[j]++;
			}
		}
	}
	int max0num=-1;
	int max0line=0;
	bool maxline_is_row = true;
	/*************loop in every column and row to find out the who has the most zero***********/
	while(!all_of(num0perrow.begin(),num0perrow.end(), [](int i) { return i==0; })&&!all_of(num0percol.begin(),num0percol.end(), [](int i) { return i==0; })){
		max0num=-1;
		max0line=0;
		// postive line number represent the horizontal line
		for (int i=0;i<SIZE;i++){
			if(num0perrow[i]>max0num){
				max0num = num0perrow[i];
				max0line=i;
				maxline_is_row = true;
			}
		}
		// negative line number represent the vertical line
		for (int i=0;i<SIZE;i++){
			if(num0percol[i]>max0num){
				max0num = num0percol[i];
				max0line= i;
				maxline_is_row = false;
			}
		}
		// delete zeros in the max0line and update the cross overline
		if(maxline_is_row){
			num0perrow[max0line]=0;
			for(int j=0;j<SIZE;j++){
				if(cost_matrix[max0line][j]==0){
					num0percol[j]--;
				}
			}

		}else{
			num0percol[max0line]=0;
			for(int j=0;j<SIZE;j++){
				if(cost_matrix[j][max0line]==0){
					num0perrow[j]--;
				}
			}
		}
		mini_line++;
	}
	
	/**********make the judgement******/
	if (mini_line==cost_matrix.size()){
		solution =true;
	}
	return;
}
//continue to find the possible solution in matrix
void step4(vector<vector<int>>& cost_matrix){
	/**to be implement**/

}

//find the solution return the assignment in assigment vector
vector<int> assign(vector<vector<int>>& cost_matrix){
	/**to be implement**/
}