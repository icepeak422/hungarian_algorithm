// Example program
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

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
	/**********make the judgement******/
	if (mini_line==cost_matrix.size()){
		solution =true;
	}
	return;
}
int main()
{
  vector<vector<int>> cost_matrix={{82,0,69,92},
									 {77,37,49,92},
									 {11,0,0,86},
									 {8,9,98,23}};
 int ret = step3(cost_matrix);
 cout<<ret<<endl;
}
