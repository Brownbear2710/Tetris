#include "interface.c"

int main(void)
{
    int fieldColor = GREY, blockColor = WHITE, currentBlock = -1, nextBlock = -1, gameType = 4;
    long long score = 0;
    // system("pause");
    FILE * fp = fopen("theme", "r");
    if(fp)
    {
        fscanf(fp,"%d %d", &fieldColor, &blockColor);
        fclose(fp);
    }
    fp = fopen("control", "r+");
    if(fp)
    {
        fscanf(fp, "%c%c%c%c%c%c", &left, &right,&down, &up, &hDrop, &hold);
        fclose(fp);
    }
    hidecursor();
    system("cls");
    while(1)
    {
        int selection = showMainMenu(), f;
        if(selection == 0) score = 0;///
        switch (selection)
        {
            case 1:
                f = load(&currentBlock, &nextBlock, &score);
                if(!f)
                {
                    setCursorPosition(42,5);
                    printf("NO PREVIOUSLY SAVED GAME FOUND !!  :(");
                    setCursorPosition(42,9);
                    printf("--->> PRESS ANY KEY TO CONTINUE <<---");
                    _getch();
                    break;
                }
            case 0:
                playGame(currentBlock,nextBlock, blockColor, fieldColor, gameType, score);
                break;
            case 2:
                showLeaderboard();
                break;
            case 3:
            while(1)
                {
                    int selection = showOptions(&fieldColor, &blockColor);
                    if(selection == 0) changeColorTheme(&fieldColor, &blockColor);
                    else if(selection == 1) changeControls();
                    else if(selection == 2) break;
                }
                break;
            case 4:
                helpMenu();
                break;
            case 5:
                return 0;
            default:
                break;
        }
    }
    return 0;
}