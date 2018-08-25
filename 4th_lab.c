// Created on Thu Sep 28 2017
#include <stdio.h>
int light_angle = 3, drive_angle = 0, right_speed = 0, left_speed = 0;
int flag = 0;
int maxx(int a,int b){
	if(a > b)
		return a;
	else
		return b;
}
void avoid_obstacles(){
	while (1) {
		int dr = analog(0);
		int ds = analog(1);
		int dl = analog(2);
		printf("Distance Sensors: %d %d %d\n" , dr,ds,dl);
		if (maxx(dr, maxx(dl, ds)) < 100) {
			drive_angle = 0;
		}
		else if (ds > 100) {
			if (abs(dr - dl) <= 10 && (dr > 100 || dl > 100))
				drive_angle = 3;
			else if (dr < dl)
				drive_angle = 1;
			else
				drive_angle = 2;
		}
		else {
			if (abs(dr - dl) < 10 && (dr > 100 || dl > 100))
				drive_angle = 3;
			else if (dr < dl)
				drive_angle = 1;
			else
				drive_angle = 2;
		}
		sleep(0.1);
	}
}
void track_light(){
	enable_servos();
	//int direction = 0;
	int i = 1024;
	while(1){
		int rs = analog10(4);
		int ls = analog10(3);
		printf("light sensors: %d %d %d\n", rs,ls,i);
		set_servo_position(0,i);
		if(rs <= 18 && ls <= 18){
			if(i < 950){
				light_angle = 1;
			}
			else if( i > 1100){
				light_angle = 2;
			}
			else{
				light_angle = 0;
			}
		}
		else{
			light_angle = 3;
			if(i < 950){
				right_speed = 1;
				left_speed = 0;
				}
			else if(i > 1100){
				right_speed = 0;
				left_speed = 1;
			}
			else{
				right_speed = left_speed = 1;
			}
		}
		if(rs > ls)
			i+=20;
		else if(rs < ls)
			i-=20;
		if(i >= 2000)
			i-=20;
		if(i <= 100)
			i+=20;
		sleep(0.1);
	}
}
void drive(){
	int speed = 200;
    while(1){
        printf("drive_angle = %d Light_angle = %d %d %d\n" ,drive_angle, light_angle,right_speed,left_speed);
        if(drive_angle == 0){
			if(light_angle == 0){
				flag = 1;
				break;
			}
			else if(light_angle == 3){
				if(right_speed < left_speed)
					create_drive_direct(20, 100);
				else if(left_speed < right_speed)
					create_drive_direct(100, 20);
				else
					create_drive_direct(50,50);
				sleep(1);
			}
			else if(light_angle == 1){
				create_drive_direct(100,-100);
				flag = 1;
				break;
			}
			else{
				create_drive_direct(-100,100);
				flag = 1;
				break;
			}
			sleep(0.1);
		}
		else{
			if(drive_angle == 1){
				create_drive_direct(-speed/2, speed/2);
			}
			else if(drive_angle == 2){
				create_drive_direct(speed/2, -speed/2);
			}
			else{
			create_drive_direct(speed,-speed);
			sleep(1);
		}
			}
		sleep(0.2);
    }
}
/*void drive(){
	while(1){
		printf("Light_angle = %d\n" , light_angle);
		int speed = 200;
		if(drive_angle == 0){
			if (light_angle == 0)
				create_drive_direct(100, 100);
			else if (light_angle == 2)
				create_drive_direct(left_speed, right_speed);
			else if(light_angle == 1)
				create_drive_direct(100,-100);
			else
				create_drive_direct(-100,100);
		}
		else{
			if(drive_angle == 1){
			create_drive_direct(-speed/2, speed/2);
			}
			else if(drive_angle == 2){
				create_drive_direct(speed/2, -speed/2);
			}
			else{
			create_drive_direct(speed,-speed);
			sleep(0.2);
		}
			}
		sleep(0.2);
	}
}
*/
int main() 
{
	set_each_analog_state(1,1,1,0,0,0,0,0);
	create_connect();
	int pid,pid1,pid2;
	pid = start_process(avoid_obstacles);
	pid1 = start_process(track_light);
	pid2 = start_process(drive);
	while(!flag){
	}
	return 0;
}
