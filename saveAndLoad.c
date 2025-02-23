#include <stdio.h>
#include <windows.h>
#include "necessary.h"



void save(int x, int y, int rotation, int currentBlock, int nextBlock, long long score)
{
    FILE *fp = fopen("hzev", "wb+");
    system("cls");
    textColor(WHITE);
    if(!fp)
    {
        setCursorPosition(47,6);
        printf("FAILED TO SAVE GAME\n\n");
        system("pause");
        system("cls");
        return;
    }
    for(int i = 0; i < 5; i++)
    {
        field[block[currentBlock][rotation][i][0]+(x)][block[currentBlock][rotation][i][1]+(y)] = ' ';
    }
    fwrite(&currentBlock, 4, 1, fp);
    fwrite(&nextBlock, 4, 1, fp);
    fwrite(&score, 8, 1, fp);
    char space = ' ';
    for(int i = 0; i < 21; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            if(field[i][j] != '+') fwrite(&field[i][j],1,1,fp);
            else fwrite(&space,1,1,fp);
        }
    }
    fwrite(field, 1, 21*25, fp);
    fclose(fp);

    for(int i = 0; i < 5; i++)
    {
        field[block[currentBlock][rotation][i][0]+(x)][block[currentBlock][rotation][i][1]+(y)] = BRICK;
    }

    setCursorPosition(45,6);
    printf("[SUCCESSFULLY SAVED THE GAME]\n\n\n\n");
    // setCursorPosition(45, 8);
    printf("                             ----------------> PRESS ANY KEY TO CONTINUE <----------------");
    _getch();
    system("cls");
    return;
}

int load(int *currentBlock, int *nextBlock, long long *score)
{
    FILE *fp = fopen("hzev", "rb");
    system("cls");
    if(!fp)
    {
        return 0;
    }

    fread(currentBlock, 4, 1, fp);
    fread(nextBlock, 4, 1, fp);
    fread(score, 8, 1, fp);
    fread(field, 1, 21*25, fp);
    fclose(fp);

    for(int i = 0; i < 21; i++)
    {
        for(int j = 0; j < 24 ; j++)
        {
            if(field[i][j] == 'B') field[i][j] = BRICK;
        }
    }
    remove("hzev");

    return 1;
}

void updateLeaderboard(long long score)
{
    system("cls");
    char names[11][21] = {0};
    long long scr[11] = {0};
    char ch;
    FILE * fp = fopen("ovzw", "rb");
    if(fp)
    {
        fread(names,1,10*21,fp);
        fread(scr, 8, 10, fp);
        fclose(fp);
    }
    scr[10] = score;
    showCursor();
    setCursorPosition(45, 5);
    textColor(WHITE);
    printf("ENTER YOUR NAME (AT MOST 20 CHARACTERS) : ");
    setCursorPosition(45, 6);
    fgets(names[10],20,stdin);
    hidecursor();

    int i = 10;
    while(i > 0)
    {
        if(scr[i] > scr[i-1])
        {
            int tmp = scr[i];
            scr[i] = scr[i-1];
            scr[i-1] = tmp;

            char s[21];
            strncpy(s, names[i],20);
            strncpy(names[i], names[i-1], 20);
            strncpy(names[i-1], s, 20);
        }
        i--;
    }

    fp = fopen("ovzw", "wb+");
    fwrite(names,1,10*21,fp);
    fwrite(scr, 8, 10, fp);
    fclose(fp);
}