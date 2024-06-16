//軟創二乙 511172176 李則霖 C語言自主學習週作業
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//define macro
#define TOTAL_STONES 7 //石頭數量
#define HP_INITIAL 100 //波奇體力
#define BOMBS_INITIAL 2 //炸彈數量

//define stone class
#define HARD 2 //堅硬
#define MEDIUM 1 //稍硬
#define EASY 0 //普通

//function prototype 
void generate_stones(int stones[]); // 生成隨機排列的石頭陣列
const char* use_tuning_fork(int stone); // 使用音叉並返回結果
void display_status(int stone_index, int hp, int bombs_left); // 顯示當前狀態

//main functoin
int main() {

    int choice; //工具選擇
    int stones[TOTAL_STONES]; //石頭陣列
    int hp = HP_INITIAL; //波奇體力
    int bombs_left = BOMBS_INITIAL; //炸彈數量
    int stone_index = 0; //石頭索引標註目前第幾顆

    srand(time(NULL));  // 用時間設置隨機數生成器的種子確保不會重複
    generate_stones(stones); // 呼叫生成隨機排列的石頭陣列函數

    while (stone_index < TOTAL_STONES && hp > 0) { //用石頭數量跟波奇體力判斷是否繼續
        //每次選擇前會先印出目前是「第幾顆石頭」，「波奇目前HP」，與「剩餘炸彈數量」
        display_status(stone_index, hp, bombs_left); //呼叫顯示當前狀態函數
      
        printf("選擇工具 (1.音叉 2.鐵鎚 3.電鑽 4.炸彈 5.放棄): ");
        scanf("%d", &choice);

        if (choice == 5) { //選擇(5)放棄：會顯示<< 尋寶失敗>>並結束程式
            printf("尋寶失敗\n");
            break;
        }

        //在選擇完工具後，若能成功擊碎石頭則會顯示<<成功擊碎石頭>>
        //若擊碎石頭失敗時則會顯示<<石頭產生裂痕>>
        switch (choice) {
        case 1: //選擇(1)音叉：它可以敲擊石頭並聆聽聲響，且不會消耗HP
            printf("音叉結果: %s\n", use_tuning_fork(stones[stone_index]));
            break;
        case 2: //選擇(2)鐵鎚：它可以擊碎「普通」的石頭，並消耗10點HP
            if (stones[stone_index] == EASY) {
                hp -= 10;
                printf("成功擊碎石頭\n");
                stone_index++;
            }
            else {
                hp -= 10;
                printf("石頭產生裂痕\n");
            }
            break;
        case 3: //選擇(3)電鑽：它可以擊碎硬度為「稍硬」與「普通」的石頭，並消耗20點HP
            if (stones[stone_index] == EASY || stones[stone_index] == MEDIUM) {
                hp -= 20;
                printf("成功擊碎石頭\n");
                stone_index++;
            }
            else {
                hp -= 20;
                printf("石頭產生裂痕\n");
            }
            break;
        case 4: //選擇(4)炸彈：它可以擊碎所有硬度的石頭，雖它不會消耗HP但炸彈總共數量只有2顆
            if (bombs_left > 0) {
                bombs_left--;
                printf("成功擊碎石頭\n");
                stone_index++;
            }
            else { //如果選擇(4)卻已經沒炸彈可用時，則會顯示<< 炸彈已用盡>>，然後再重新選擇
                printf("炸彈已用盡\n");
            }
            break;
        default:
            printf("無效選擇\n");
        }

        if (hp <= 0 && stone_index != TOTAL_STONES) { //HP耗盡時則會顯示：HP已耗盡...以及<< 尋寶失敗>> 並結束程式
            printf("HP已耗盡... 尋寶失敗\n"); //如果HP耗盡的同時過關以過關為主
            break;
        }
    }

    if (stone_index == TOTAL_STONES) { //成功擊碎7顆石頭時會顯示<< 恭喜獲得寶藏>>並結束程式
        printf("恭喜獲得寶藏\n");
    }

    return 0;
}

// 生成隨機排列的石頭陣列
void generate_stones(int stones[]) {
    // init stone array
    stones[0] = HARD; //一顆堅硬
    stones[1] = MEDIUM; //兩顆稍硬
    stones[2] = MEDIUM; //兩顆稍硬
    for (int i = 3; i < TOTAL_STONES; i++) {
        stones[i] = EASY; //四顆普通
    }

    // 用洗牌算法隨機打亂石頭陣列
    for (int i = 0; i < TOTAL_STONES; i++) {
        int j = rand() % TOTAL_STONES;
        int temp = stones[i];
        stones[i] = stones[j];
        stones[j] = temp;
    }
}

// 使用音叉並返回結果 use pointer
const char *use_tuning_fork(int stone) {
    int chance = (rand() % 100)+1; //隨機出現百分比1~100內的數字
    if (stone == EASY) {
        return (chance < 10) ? "沉重聲" : "清脆聲"; //普通的石頭有10%機率發出沉重聲
    }
    else if (stone == MEDIUM) {
        return (chance < 50) ? "沉重聲" : "清脆聲"; //稍硬的石頭有50%機率發出沉重聲
    }
    else {
        return (chance < 75) ? "沉重聲" : "清脆聲"; //堅硬的石頭有75%機率發出沉重聲
    }
}

// 顯示當前狀態
void display_status(int stone_index, int hp, int bombs_left) {
    printf("第%d顆石頭，波奇目前HP: %d，剩餘炸彈數量: %d\n", stone_index + 1, hp, bombs_left);
}


