#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_ROW 10
#define MAX_COL 10
#define DEFAULT_MINE_COUNT 10//默认地雷个数

int Menu(){
	printf("========================\n");
	printf("输入1,开始游戏\n");
	printf("输入0,退出游戏\n");
	printf("========================\n");
	int choice = 0;
	scanf("%d", &choice);
	return choice;


}
void Init(char show_map[MAX_ROW + 2][MAX_COL + 2],
	char mine_map[MAX_ROW + 2][MAX_COL + 2]){
	for (int row = 0; row < MAX_ROW + 2; ++row){
		for (int col = 0; col < MAX_COL + 2; ++col){
			show_map[row][col] = '*';
		}
	}
	for (int row = 0; row < MAX_ROW + 2; ++row){
		for (int col = 0; col < MAX_COL + 2; ++col){
			mine_map[row][col] = '0';
		}
	}
	int mine_count = DEFAULT_MINE_COUNT;
	while (mine_count > 0){
		int row = rand() % 10 + 1;
		int col = rand() % 10 + 1;
		if (mine_map[row][col]=='1'){
			continue;//当前位置已经有雷了,需要重新产生随机数
		}
		mine_map[row][col] = '1';
		--mine_count;
	}

}
void Displaymap(char map[MAX_ROW + 2][MAX_COL + 2]){
	printf("    ");
	for (int i = 1; i <= MAX_COL;++i){
		printf("%02d ", i);
	}
	printf("\n");
	for (int i = 1; i <= MAX_COL; ++i){
		printf("----");
	}
	printf("\n");
	for (int row = 1; row <= MAX_ROW; ++row){
		printf("%02d| ", row);
		for (int col = 1; col <= MAX_COL; ++col){
			printf("%c  ", map[row][col]);
		}
		printf("\n");
	}
}
void UpdateShowMap(char show_map[MAX_ROW + 2][MAX_COL + 2],
	char mine_map[MAX_ROW + 2][MAX_COL + 2], int row, int col){
	int mine_cnt = (mine_map[row - 1][col - 1] - '0')
		+ (mine_map[row - 1][col] - '0')
		+ (mine_map[row - 1][col + 1] - '0')
		+ (mine_map[row][col - 1] - '0')
		+ (mine_map[row][col + 1] - '0')
		+ (mine_map[row + 1][col - 1] - '0')
		+ (mine_map[row + 1][col] - '0')
		+ (mine_map[row + 1][col + 1] - '0');
	show_map[row][col] = '0' + mine_cnt;

}

void Game(){
	//未先开用*表示 
	//已经掀开用一个数字来表示 '1'
	char show_map[MAX_ROW + 2][MAX_COL + 2];
	//1.地雷使用'1'表示 不是地雷用'0'表示 
	char mine_map[MAX_ROW + 2][MAX_COL + 2];
	int blank_cnt = 0;
	//对数组进行初始化
	Init(show_map, mine_map);
	Displaymap(show_map);
	while (1){
		int row = 0;
	    int col = 0;
		printf("请输入坐标:");
		scanf("%d %d", &row, &col);
		if (row <= 0 || row >MAX_ROW || col <=0 || col >MAX_COL){
			printf("您输入的坐标不合法,请重新输入\n");
			continue;
		}
		if (mine_map[row][col]=='1'){
			printf("Game over!\n");
			Displaymap(mine_map);
			break;
		}
		blank_cnt;
		if (blank_cnt == MAX_ROW * MAX_COL - DEFAULT_MINE_COUNT){
			printf("YOU WIN!\n");
			Displaymap(mine_map);
			break;
		}
		UpdateShowMap(show_map,mine_map,row,col);
		Displaymap(show_map);
	}
}

void Start(){
	while (1){
		int choice = Menu();
		if (choice == 0){
			break;
		}
		Game();
	}
}

int main(){
	Start();
    system("pause");
	return 0;
}