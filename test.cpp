// Example program
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include "hungarian.h"

using namespace std;

void print_matrix(vector<vector<int>> matrix){
	for(unsigned int x=0;x<matrix.size();x++){
        for(unsigned int y=0;y<matrix[0].size();y++)  {
            cout<<matrix[x][y]<<" ";  
        }
	cout<<endl;  
	}
}

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
void step3(vector<vector<int>>& cost_matrix, bool &solution,vector<int>& uncovered_row,vector<int>& uncovered_col,vector<int>& covered_row,vector<int>& covered_col){
	covered_row.clear();
 	covered_col.clear();
 	uncovered_row.clear();
 	uncovered_col.clear();
 	for (int i=0;i<cost_matrix.size();i++){
		uncovered_row.push_back(i);
		uncovered_col.push_back(i);
 	}
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
	int maxline_is_row = 0;
	/*************loop in every column and row to find out the who has the most zero***********/
	while(!all_of(num0perrow.begin(),num0perrow.end(), [](int i) { return i==0; })&&!all_of(num0percol.begin(),num0percol.end(), [](int i) { return i==0; })){
		max0num=-1;
		max0line=0;
		maxline_is_row = 0;
		// postive line number represent the horizontal line
		for (int i=0;i<SIZE;i++){
			if(num0perrow[i]>=max0num){
				if(num0perrow[i]==max0num){
					maxline_is_row++;
				}else{
					maxline_is_row = 1;
					max0num = num0perrow[i];
					max0line=i;
				}
			}
		}
		for (int i=0;i<SIZE;i++){
			if(num0percol[i]>=max0num){
				if(num0percol[i]==max0num){
					maxline_is_row--;
				}else{
					max0num = num0percol[i];
					maxline_is_row = -1;
					max0line= i;
				}
				
			}
		}
		cout<<"max_is_row:"<<maxline_is_row<<endl;
		// delete zeros in the max0line and update the cross overline
		if(maxline_is_row>=0){
			num0perrow[max0line]=0;
			cout<<"we cover a row:"<<max0line<<endl;
			covered_row.push_back(max0line);
			auto position = find(uncovered_row.begin(), uncovered_row.end(), max0line);
			if (position != uncovered_row.end()) // == myVector.end() means the element was not found
				uncovered_row.erase(position);
			for(int j=0;j<SIZE;j++){
				if(cost_matrix[max0line][j]==0){
					num0percol[j]--;
				}
			}

		}else{
			num0percol[max0line]=0;
			covered_col.push_back(max0line);
			cout<<"we cover a column:"<<max0line<<endl;
			auto position = find(uncovered_col.begin(), uncovered_col.end(), max0line);
			if (position != uncovered_col.end()) // == myVector.end() means the element was not found
				uncovered_col.erase(position);
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
void step4(vector<vector<int>>& cost_matrix, vector<int>& uncovered_row,vector<int>& uncovered_col,vector<int>& covered_row,vector<int>& covered_col){
	/**to be implement**/
	int minimum_ele = INT_MAX;
// find the minimum in uncovered row and col
	for (auto itx:uncovered_row){
		for(auto ity:uncovered_col){
			cout<<cost_matrix[itx][ity]<<endl;
			if (cost_matrix[itx][ity]<minimum_ele){
				minimum_ele = cost_matrix[itx][ity];
			}
		}
	}
	cout<<"min is:"<<minimum_ele<<endl;
// substract the minimum_ele from every uncovered element
	for (auto itx:uncovered_row){
		for(auto ity:uncovered_col){
			cost_matrix[itx][ity]-=minimum_ele;
		}
	}

// add it to the element covered twice
	for (auto itx:covered_row){
		for(auto ity:covered_col){
			cost_matrix[itx][ity]+=minimum_ele;
		}
	}
	return;	
}

bool help_assign(int worker,vector<int> &left,hungarian &hun,vector<int> &each_ret, vector<vector<int>> &ret){
	bool assigned = false;
	if(worker==hun.CUR_cost_matrix.size()){
		return true;
	}
	for (int j=0;j<left.size();j++){
		if(hun.CUR_cost_matrix[worker][left[j]]==0){
			cout<<"here fuck"<<left[j]<<endl;
			int assigned_position = left[j];
			left.erase(left.begin()+j);
			assigned = help_assign(worker+1,left,hun,each_ret,ret);
			if(assigned&&each_ret.size()==hun.CUR_cost_matrix.size()){
				ret.push_back(each_ret);
			}else{
				left.push_back(assigned_position);
			}
			each_ret.pop_back();
		} 
	}
	return assigned;
}
//find the solution return the assignment in assigment vector
vector<vector<int>> assign(hungarian &hun){
	/**to be implement**/
	vector<vector<int>> ret;
	vector<int> left;
	for(int i=0;i<hun.CUR_cost_matrix.size();i++){
		left.push_back(i);
	}
	int worker = 0;
	vector<int> each_ret;
	bool assigned=help_assign(worker,left,hun,each_ret,ret);
	return ret;	
}

int main()
{
  vector<vector<int>> cost_matrix={{82,83,69,92},
									 {77,37,49,92},
									 {11,69,5,86},
									 {8,9,98,23}};
 hungarian hun(cost_matrix);
 bool solution = false;
 step1(hun.CUR_cost_matrix);
 step2(hun.CUR_cost_matrix);
 step3(hun.CUR_cost_matrix,solution,hun.uncovered_row,hun.uncovered_col,hun.covered_row,hun.covered_col);
 while(!solution){
 	 step4(hun.CUR_cost_matrix,hun.uncovered_row,hun.uncovered_col,hun.covered_row,hun.covered_col);
 	print_matrix(hun.CUR_cost_matrix);
 	step3(hun.CUR_cost_matrix,solution,hun.uncovered_row,hun.uncovered_col,hun.covered_row,hun.covered_col);
 }
 cout<<solution<<endl;
 vector<vector<int>> ret = assign(hun);
 cout<<ret.size()<<endl;
 return 0;
}

