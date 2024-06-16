//�n�ФG�A 511172176 ���h�M C�y���ۥD�ǲ߶g�@�~
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//define macro
#define TOTAL_STONES 7 //���Y�ƶq
#define HP_INITIAL 100 //�i�_��O
#define BOMBS_INITIAL 2 //���u�ƶq

//define stone class
#define HARD 2 //��w
#define MEDIUM 1 //�y�w
#define EASY 0 //���q

//function prototype 
void generate_stones(int stones[]); // �ͦ��H���ƦC�����Y�}�C
const char* use_tuning_fork(int stone); // �ϥέ��e�ê�^���G
void display_status(int stone_index, int hp, int bombs_left); // ��ܷ�e���A

//main functoin
int main() {

    int choice; //�u����
    int stones[TOTAL_STONES]; //���Y�}�C
    int hp = HP_INITIAL; //�i�_��O
    int bombs_left = BOMBS_INITIAL; //���u�ƶq
    int stone_index = 0; //���Y���޼е��ثe�ĴX��

    srand(time(NULL));  // �ήɶ��]�m�H���ƥͦ������ؤl�T�O���|����
    generate_stones(stones); // �I�s�ͦ��H���ƦC�����Y�}�C���

    while (stone_index < TOTAL_STONES && hp > 0) { //�Υ��Y�ƶq��i�_��O�P�_�O�_�~��
        //�C����ܫe�|���L�X�ثe�O�u�ĴX�����Y�v�A�u�i�_�ثeHP�v�A�P�u�Ѿl���u�ƶq�v
        display_status(stone_index, hp, bombs_left); //�I�s��ܷ�e���A���
      
        printf("��ܤu�� (1.���e 2.�K�� 3.�q�p 4.���u 5.���): ");
        scanf("%d", &choice);

        if (choice == 5) { //���(5)���G�|���<< �M�_����>>�õ����{��
            printf("�M�_����\n");
            break;
        }

        //�b��ܧ��u���A�Y�ন�\���H���Y�h�|���<<���\���H���Y>>
        //�Y���H���Y���Ѯɫh�|���<<���Y���͵���>>
        switch (choice) {
        case 1: //���(1)���e�G���i�H�V�����Y�ò�ť�n�T�A�B���|����HP
            printf("���e���G: %s\n", use_tuning_fork(stones[stone_index]));
            break;
        case 2: //���(2)�K��G���i�H���H�u���q�v�����Y�A�î���10�IHP
            if (stones[stone_index] == EASY) {
                hp -= 10;
                printf("���\���H���Y\n");
                stone_index++;
            }
            else {
                hp -= 10;
                printf("���Y���͵���\n");
            }
            break;
        case 3: //���(3)�q�p�G���i�H���H�w�׬��u�y�w�v�P�u���q�v�����Y�A�î���20�IHP
            if (stones[stone_index] == EASY || stones[stone_index] == MEDIUM) {
                hp -= 20;
                printf("���\���H���Y\n");
                stone_index++;
            }
            else {
                hp -= 20;
                printf("���Y���͵���\n");
            }
            break;
        case 4: //���(4)���u�G���i�H���H�Ҧ��w�ת����Y�A�������|����HP�����u�`�@�ƶq�u��2��
            if (bombs_left > 0) {
                bombs_left--;
                printf("���\���H���Y\n");
                stone_index++;
            }
            else { //�p�G���(4)�o�w�g�S���u�i�ήɡA�h�|���<< ���u�w�κ�>>�A�M��A���s���
                printf("���u�w�κ�\n");
            }
            break;
        default:
            printf("�L�Ŀ��\n");
        }

        if (hp <= 0 && stone_index != TOTAL_STONES) { //HP�Ӻɮɫh�|��ܡGHP�w�Ӻ�...�H��<< �M�_����>> �õ����{��
            printf("HP�w�Ӻ�... �M�_����\n"); //�p�GHP�Ӻɪ��P�ɹL���H�L�����D
            break;
        }
    }

    if (stone_index == TOTAL_STONES) { //���\���H7�����Y�ɷ|���<< ������o�_��>>�õ����{��
        printf("������o�_��\n");
    }

    return 0;
}

// �ͦ��H���ƦC�����Y�}�C
void generate_stones(int stones[]) {
    // init stone array
    stones[0] = HARD; //�@����w
    stones[1] = MEDIUM; //�����y�w
    stones[2] = MEDIUM; //�����y�w
    for (int i = 3; i < TOTAL_STONES; i++) {
        stones[i] = EASY; //�|�����q
    }

    // �ά~�P��k�H�����å��Y�}�C
    for (int i = 0; i < TOTAL_STONES; i++) {
        int j = rand() % TOTAL_STONES;
        int temp = stones[i];
        stones[i] = stones[j];
        stones[j] = temp;
    }
}

// �ϥέ��e�ê�^���G use pointer
const char *use_tuning_fork(int stone) {
    int chance = (rand() % 100)+1; //�H���X�{�ʤ���1~100�����Ʀr
    if (stone == EASY) {
        return (chance < 10) ? "�I���n" : "�M���n"; //���q�����Y��10%���v�o�X�I���n
    }
    else if (stone == MEDIUM) {
        return (chance < 50) ? "�I���n" : "�M���n"; //�y�w�����Y��50%���v�o�X�I���n
    }
    else {
        return (chance < 75) ? "�I���n" : "�M���n"; //��w�����Y��75%���v�o�X�I���n
    }
}

// ��ܷ�e���A
void display_status(int stone_index, int hp, int bombs_left) {
    printf("��%d�����Y�A�i�_�ثeHP: %d�A�Ѿl���u�ƶq: %d\n", stone_index + 1, hp, bombs_left);
}


