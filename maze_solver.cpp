// Created on Fri Dec 8 2017

#include <iostream>
#include<vector>
#include<string>
using namespace std;
string fix(string s) {
	string temp;
	for (int i = 1; i < s.size(); ++i) {
		if (s[i] != s[i - 1])
			temp.push_back(s[i - 1]);
	}
	temp.push_back(s[s.size() - 1]);
	for (int i = 1; i < temp.size(); ++i) {
		if (s[i] == 'u') {
			if (s[i - 1] == 'l' && s[i + 1] == 's') {
				s[i + 1] = 'r';
				s[i] = '-1';
				s[i - 1] = s[i];
			}
			else if (s[i - 1] == 'l' && s[i + 1] == 'l') {
				s[i + 1] = 's';
				s[i] = '-1';
				s[i - 1] = s[i];
			}
		}
	}

}
int main() 
{
	create_connect();
	set_each_analog_state(1,1,1,0,0,0,0,0);
	int state = 0;
	string d;
	int val = 400;
	int val2 = 500;
	while(true){
		int r = analog10(0);
		int s = analog10(1);
		int l = analog10(2);
			if(get_create_lbump(0.0))
				create_spin_CW(100);
			else if(get_create_rbump(0.0))
				create_spin_CCW(100);
		cout << r <<" "<<s <<" "<< l << endl;
		if(r <= val && s <= val && l <= val){
			cout << "Finished maze" << endl;
			state++;
			if(state == 50)
				break;
		}
		else if(l >= val2 && r >= val2 && s >= val2){
			state = 0;
			cout << "have to Uturn" << endl;
			d.push_back('u');
			create_stop();
			create_spin_CCW(100);
			while (get_create_normalized_angle(0.0) <= 160){
				cout << get_create_normalized_angle(0.0) << endl;}
			set_create_normalized_angle(0);
		}
		else if (l <= val) {
			state = 0;
			cout << "have to take left" << endl;
			create_stop();
			set_create_distance(0);
			while(get_create_distance(0.0) <= 130)
				create_drive_direct(50,50);
			if (s <= val || r <= val)
				d.push_back('l');
			create_spin_CCW(100);
			while (get_create_normalized_angle(0.0) <= 70){
				cout << get_create_normalized_angle(0.0) << endl; 
			}
			set_create_distance(0);
			while(get_create_distance(0.0) <= 300)
				create_drive_direct(50,50);
			set_create_normalized_angle(0);
		}
		else if (s <= val) {
			state = 0;
			cout << "Have to go straight" << endl;
			if (r <= val) {
				d.push_back('s');
			}
			create_drive_direct(50, 50);
		}
		else if(r <= val){
			state = 0;
			cout << "Have to go right" << endl;
			create_stop();
			set_create_distance(0);
			while(get_create_distance(0.0) <= 130)
				create_drive_direct(50,50);
			set_create_normalized_angle(359);
			create_spin_CW(100);
			while (get_create_normalized_angle(0.0) >= 280){
				cout << get_create_normalized_angle(0.0) << endl; 
			}
			set_create_distance(0);
			while(get_create_distance(0.0) <= 300)
				create_drive_direct(50, 50);
			set_create_normalized_angle(0);
		}
		sleep(0.1);
	}
	d = fix(d);
	create_stop();
	create_disconnect();
	return 0;
}
