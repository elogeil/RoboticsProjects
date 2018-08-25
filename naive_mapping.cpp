#include <iostream>
#include<vector>
#include<cstdlib>
#include<time.h>
using namespace std;
int main() {	
	vector<int> movements;
	vector<int> left;
	vector<int> right;
	srand(time(NULL));
	create_connect();
	while(get_create_distance(0.1) < 3000){
		if(!get_create_lbump(0.1) && !get_create_rbump(0.1)){ //successful move
			create_drive_direct(100,100);
			movements.push_back(1);
			cout << "HERE" <<endl;
		}
		else if(get_create_lbump(0.1)){//unsuccessful from the left side
			//create_drive_direct(-100,-100);
			movements.push_back(-1);
			create_spin_CW(100);
			movements.push_back(2);
			}
		else{//unsuccessful from both or the right side
			//create_drive_direct(-100,-100);
			movements.push_back(-1);
			create_spin_CCW(100);
			movements.push_back(3);
			}
			sleep(0.1);
		}
	//finished learning
		create_stop();
		create_disconnect();
		vector<int> final,final1;
		vector<int> time; 
		for(int i = 0; i < movements.size(); i++){ //array parsing for swift movements
			if(movements[i] == -1)
				continue;
			final.push_back(movements[i]);
		}
		for(int i = 0; i < final.size();){
			int val = final[i];
			int number = 0;
			while(final[i] == val){
				i++;
				number++;
			}
			time.push_back(number);
			final1.push_back(val);
		}
		cout << final1.size() << " " << time.size() << endl;
		for(int i = 0; i < final1.size(); ++i)
			cout << final1[i] << " ";
		cout << endl;
		while(!black_button());
	create_connect();
	for(int i = 0; i < final1.size(); ++i){//smart navigation phase
		cout << "state : " << final1[i] <<" " << "amount of times: " << time[i] << endl;
		int j = 0;
		if(final1[i] == 1 && time[i] < 5)
			continue;
		if(final1[i] == 1){
			create_drive_direct(100,100);
			while(j <= time[i]+5){
			j++;
			/*time added to decrease the trajectory error rate
			the times tried were the same (0.1) -> (0.2) by 0.01 increase
			the best time we found that mapped the actual learning trajectory to the navigation one was 0.15
			though we needed to add more to the times we run the successful command so that we could be able to have similar trajectories*/
			sleep(0.15); 
			}
			continue;
		}
		else if(final1[i] == 2){
			create_spin_CW(100);
		}
		else{
			create_spin_CCW(100);
		}
		while(j <= time[i]){
			j++;
			sleep(0.15);
			}
	}	
	return 0;
}
