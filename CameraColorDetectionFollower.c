#include<stdio.h>
int main() {
	create_connect(); 
	int vis[] = {0,0,0,0};
	while(get_create_play_button(0.1) == 0) {
	}
	int i = 0;
	int r = 0;
	while(1){
		track_update();     
		printf(" x=%d y=%d count=%d\n", track_x(i, 0), track_y(i, 0), track_count(i));   
		printf("color = %d, state = %d\n" , i,vis[i]);
		if (track_count(i)>0) {
			r = 0;
			vis[i] = 1;
			create_drive_direct( 150+80-track_x(i,0), 150+track_x(i,0)-80); 
		}        
		else {
			if (r == 31) {
				i = (i + 1) % 4;
				r = 0;
			}
			r++;
			create_stop();
			if(!vis[i])
				create_drive_direct(-50,50);
			if(vis[i]){
				
				vis[i] = 0;
				i = (i + 1)%4;
				create_stop();
				while(!black_button()){
				}
			}
			msleep(100);
		} 
	}
	create_stop();
	create_disconnect();
	printf("Program Exit.\n");
}
