#include <conio.h>
#include <string.h>
#include "saveAndLoad.c"

void resetField()
{
    for(int i = 0; i < 20; i++)
    {
        strcpy(field[i], "|                      |");
    }
    strcpy(field[20], "-======================-");
}



void updateNextPiece(int nextBlock, int blockColor)
{
    textColor(BLUE);
    char box[][11] = 
    {
        "NEXT PIECE",
        "  ------ ",
        " |      |",
        " |      |",
        " |      |",
        " |      |",
        "  ------ "
    };

    for(int i = 0; i < 7; i++)
    {
        setCursorPosition(70, i+2);
        printf("%s", box[i]);
    }

    textColor(WHITE);
    for(int i = 0; i < PIECESIZE; i++)
    {
        setCursorPosition(block[nextBlock][0][i][1]+74, block[nextBlock][0][i][0]+6);
        printf("#");
    }
    textColor(blockColor);
}

void updateScore(long long score, int blockColor)
{
    textColor(BLUE);
    setCursorPosition(72,10);
    printf("SCORE");
    setCursorPosition(72,11);
    printf("`````");
    setCursorPosition(72,12);
    textColor(WHITE);
    printf("%05lld     ", score);
    textColor(blockColor);
}

void printField(int nextBlock, int score, int blockColor, int fieldColor)
{
    system("cls");
    textColor(fieldColor);
    for(int i = 0; i < H+1; i++)
    {
        setCursorPosition(45,i+2);
        printf("%s", field[i]);
    }
    
    updateNextPiece(nextBlock, blockColor);
    updateScore(score, blockColor);
}

void countdown()
{

    system("cls");

    textColor(GREEN);
    printf("\n\n\t\t\t\t\t\t\tSTARTING IN\n\n");

    printf("\t\t\t\t\t\t\t   ____\n");
    printf("\t\t\t\t\t\t\t  /    \\\n");
    printf("\t\t\t\t\t\t\t    ___/\n");
    printf("\t\t\t\t\t\t\t       \\\n");
    printf("\t\t\t\t\t\t\t  \\____/\n");

    Sleep(1000);
    system("cls");

    textColor(LIGHT_YELLOW);
    printf("\n\n\t\t\t\t\t\t\tSTARTING IN\n\n");

    printf("\t\t\t\t\t\t\t   ____\n");
    printf("\t\t\t\t\t\t\t  /    \\\n");
    printf("\t\t\t\t\t\t\t       /\n");
    printf("\t\t\t\t\t\t\t     /  \n");
    printf("\t\t\t\t\t\t\t  _/___/\n");

    Sleep(1000);
    system("cls");

    textColor(RED);
    printf("\n\n\t\t\t\t\t\t\tSTARTING IN\n\n");

    printf("\t\t\t\t\t\t\t    _ \n");
    printf("\t\t\t\t\t\t\t   / |\n");
    printf("\t\t\t\t\t\t\t     |\n");
    printf("\t\t\t\t\t\t\t     |\n");
    printf("\t\t\t\t\t\t\t   __|_\n");

    Sleep(1000);
    system("cls");

}

void update(int x, int y, int rotation, int blockNumber, char updateValue, int fieldColor, int blockColor)
{
    for(int i = 0; i < PIECESIZE; i++)
    {
        if( block[blockNumber][rotation][i][1]+(y)-1 > 0 && 
        field[ block[blockNumber][rotation][i][0]+(x)][block[blockNumber][rotation][i][1]+(y)-1] == ' ')
        {
            setCursorPosition(block[blockNumber][rotation][i][1]+(y) + 44, block[blockNumber][rotation][i][0]+(x)+2);
            printf(" ");
        }
        setCursorPosition(block[blockNumber][rotation][i][1]+(y) + 45, block[blockNumber][rotation][i][0]+(x)+2);
        printf("%c", updateValue);
    }
}


int canRotate(int x, int y, int rotation, int blockNumber)
{
    for(int i = 0; i < PIECESIZE; i++)
    {
        field[block[blockNumber][rotation][i][0]+(x)][block[blockNumber][rotation][i][1]+(y)] = 'x';
    }

    for(int i = 0; i < PIECESIZE; i++)
    {
        if(field[block[blockNumber][(rotation+1)%4][i][0]+x][block[blockNumber][(rotation+1)%4][i][1]+y] != ' ' &&
           field[block[blockNumber][(rotation+1)%4][i][0]+x][block[blockNumber][(rotation+1)%4][i][1]+y] != SHADOW &&
           field[block[blockNumber][(rotation+1)%4][i][0]+x][block[blockNumber][(rotation+1)%4][i][1]+y] != 'x')
        {
            for(int i = 0; i < PIECESIZE; i++)
            {
                field[block[blockNumber][rotation][i][0]+(x)][block[blockNumber][rotation][i][1]+(y)] = BRICK;
            }
            return 0;
        }
    }

    for(int i = 0; i < PIECESIZE; i++)
    {
        field[block[blockNumber][rotation][i][0]+(x)][block[blockNumber][rotation][i][1]+(y)] = BRICK;
    }

    return 1;
}

int canMove(int x, int y, int rotation, int blockNumber, char movementKey)
{
    for(int i = 0; i < PIECESIZE; i++)
    {
        field[block[blockNumber][rotation][i][0]+(x)][block[blockNumber][rotation][i][1]+(y)] = 'x';
    }
    int tempx = x, tempy = y;
    if(movementKey == left) tempy--;
    else if(movementKey == right) tempy++;
    else if(movementKey == down) tempx++;
    else
    {
        for(int i = 0; i < PIECESIZE; i++)
        {
            field[block[blockNumber][rotation][i][0]+(x)][block[blockNumber][rotation][i][1]+(y)] = BRICK;
        }
        return 0;

    }
    if(y > 22 || y < 1 || x > 19 || x < 1)
    {
        for(int i = 0; i < PIECESIZE; i++)
        {
            field[block[blockNumber][rotation][i][0]+(x)][block[blockNumber][rotation][i][1]+(y)] = BRICK;
        }
        return 0;
    }
    
    for(int i = 0; i < PIECESIZE; i++)
    {
        if(field[block[blockNumber][rotation][i][0]+tempx][block[blockNumber][rotation][i][1]+tempy] != ' ' &&
           field[block[blockNumber][rotation][i][0]+tempx][block[blockNumber][rotation][i][1]+tempy] != SHADOW &&
           field[block[blockNumber][rotation][i][0]+tempx][block[blockNumber][rotation][i][1]+tempy] != 'x')
        {
            for(int i = 0; i < PIECESIZE; i++)
            {
                field[block[blockNumber][rotation][i][0]+(x)][block[blockNumber][rotation][i][1]+(y)] = BRICK;
            }
            return 0;
        }
    }
    for(int i = 0; i < PIECESIZE; i++)
    {
        field[block[blockNumber][rotation][i][0]+(x)][block[blockNumber][rotation][i][1]+(y)] = BRICK;
    }
    return 1;
}

int canAccomodate(int x, int y, int rotation, int blockNumber)
{
    int f = 1;
    for(int i = 0; i < PIECESIZE; i++)
    {
        if(field[block[blockNumber][rotation][i][0]+(x)][block[blockNumber][rotation][i][1]+(y)] != ' ' &&
           field[block[blockNumber][rotation][i][0]+(x)][block[blockNumber][rotation][i][1]+(y)] != SHADOW) f = 0;
    }
    if(f)
    {
        for(int i = 0; i < PIECESIZE; i++)
        {
            field[block[blockNumber][rotation][i][0]+(x)][block[blockNumber][rotation][i][1]+(y)] = BRICK;
        }
    }
    return f;
}

void move(int *x, int *y, int rotation, int blockNumber, char movementKey)
{
    if(canMove(*x, *y, rotation, blockNumber, movementKey))
    {
        for(int i = 0; i < PIECESIZE; i++)
        {
            field[block[blockNumber][rotation][i][0]+(*x)][block[blockNumber][rotation][i][1]+(*y)] = ' ';
        }

        if(movementKey == left) (*y)--;
        else if(movementKey == right) (*y)++;
        else if(movementKey == down) (*x)++;
        else return;

        for(int i = 0; i < PIECESIZE; i++)
        {
            field[block[blockNumber][rotation][i][0]+(*x)][block[blockNumber][rotation][i][1]+(*y)] = BRICK;
        }
        // printField();
    }
}

int hardDrop(int *x, int *y, int rotation, int blockNumber)
{
    int tempx = *x;
    while(canMove(*x, *y, rotation, blockNumber,down))
    {
        move(x,y,rotation,blockNumber,down);
    }
    return (*x) - tempx;
}

int rotate(int x, int y, int rotation, int blockNumber)
{
    if(canRotate(x, y, rotation, blockNumber))
    {
        for(int i = 0; i < PIECESIZE; i++)
        {
            field[block[blockNumber][rotation][i][0]+x][block[blockNumber][rotation][i][1]+y] = ' ';
        }
        for(int i = 0; i < PIECESIZE; i++)
        {
            field[block[blockNumber][(rotation+1)%4][i][0]+x][block[blockNumber][(rotation+1)%4][i][1]+y] = BRICK;
        }
        return (rotation+1)%4;
    }
    return rotation;
}

void removeShadow(int x, int y, int rotation, int blockNumber, int fieldColor, int blockColor)
{
    int ghostx = x, f = 1;
    for(int i = 0; i < PIECESIZE; i++)
    {
        field[block[blockNumber][rotation][i][0]+(x)][block[blockNumber][rotation][i][1]+(y)] = 'x';
    }

    while(1)
    {
        for(int i = 0; i < PIECESIZE; i++)
        {
            if(field[block[blockNumber][rotation][i][0]+(ghostx+1)][block[blockNumber][rotation][i][1]+(y)] != ' ' &&
               field[block[blockNumber][rotation][i][0]+(ghostx+1)][block[blockNumber][rotation][i][1]+(y)] != 'x' &&
               field[block[blockNumber][rotation][i][0]+(ghostx+1)][block[blockNumber][rotation][i][1]+(y)] != SHADOW)
             {
                f = 0;
                // printf("%d %d\n", ghostx+1+block[blockNumber][rotation][i][0], block[blockNumber][rotation][i][1]+(y));
                // system("pause");/////////////////////////
             }
        }
        if(f == 0) break;
        ghostx++;
    }

    for(int i = 0; i < PIECESIZE; i++)
    {
        field[block[blockNumber][rotation][i][0]+(ghostx)][block[blockNumber][rotation][i][1]+(y)] = ' ';
    }

    update(ghostx,y,rotation,blockNumber,' ', fieldColor, blockColor);
    update(x,y,rotation,blockNumber,BRICK, fieldColor, blockColor);

    for(int i = 0; i < PIECESIZE; i++)
    {
        field[block[blockNumber][rotation][i][0]+(x)][block[blockNumber][rotation][i][1]+(y)] = BRICK;
    }

}

void generateShadow(int x, int y, int rotation, int blockNumber, int fieldColor, int blockColor)
{
    int ghostx = x, f = 1;
    for(int i = 0; i < PIECESIZE; i++)
    {
        field[block[blockNumber][rotation][i][0]+(x)][block[blockNumber][rotation][i][1]+(y)] = 'x';
    }

    while(1)
    {
        for(int i = 0; i < PIECESIZE; i++)
        {
            if(field[block[blockNumber][rotation][i][0]+(ghostx+1)][block[blockNumber][rotation][i][1]+(y)] != ' ' &&
               field[block[blockNumber][rotation][i][0]+(ghostx+1)][block[blockNumber][rotation][i][1]+(y)] != 'x' &&
               field[block[blockNumber][rotation][i][0]+(ghostx+1)][block[blockNumber][rotation][i][1]+(y)] != SHADOW)
             f = 0;
        }
        if(f == 0) break;
        ghostx++;
    }
    for(int i = 0; i < PIECESIZE; i++)
    {
        field[block[blockNumber][rotation][i][0]+(ghostx)][block[blockNumber][rotation][i][1]+(y)] = SHADOW;
    }

    update(ghostx, y, rotation, blockNumber, SHADOW, fieldColor, blockColor);
    update(x,y,rotation,blockNumber,BRICK, fieldColor, blockColor);

    for(int i = 0; i < PIECESIZE; i++)
    {
        field[block[blockNumber][rotation][i][0]+(x)][block[blockNumber][rotation][i][1]+(y)] = BRICK;
    }

}

void generatePiece(int *currentPiece, int *nextPiece, int gameType)
{
    *currentPiece = *nextPiece;
    if(gameType == 4)
    {
        *nextPiece = rand()%7;
    }
    else
    {
        *nextPiece = rand()%18 + 7;
    }
}

void helpMenu()
{
    system("cls");
    textColor(WHITE);
    char s[1000] = {0};
    FILE * fp = fopen("help.txt", "r");
    if(!fp) return;
    int i = 0;
    while(fscanf(fp, "%c", &s[i]) != EOF)
    {
        i++;
    }
    char key[6][2] = {{left}, {right}, {up}, {down} ,{hDrop}, {hold}};
    printf(s, left == ' ' ? "SPACE": key[0], right == ' ' ? "SPACE": key[1], up == ' ' ? "SPACE": key[2], down == ' ' ? "SPACE": key[3], hDrop == ' ' ? "SPACE": key[4], hold == ' ' ? "SPACE": key[5]);
    fclose(fp);
    printf("                             ----------------> PRESS ANY KEY TO CONTINUE <----------------");
    _getch();
}


int pause(int x, int y, int rotation, int currentBlock, int nextBlock, long long score)
{
    int selection = 0;
    char menu[][9] = {" RESUME ","  SAVE  ", "  HELP  ","  QUIT  "};
    char ch;
    system("cls");
    printf("\n\n\n\n\n");
    textColor(GREEN);
    printf("                                                    >>> RESUME <<<\n");
    textColor(GREY);
    printf("                                                         SAVE\n");
    printf("                                                         HELP\n");
    printf("                                                         QUIT\n");
    while(1)
    {
        ch = _getch();
        if(ch == -32)
        {
            ch = _getch();
        }
        else if(ch == 80 || ch == 72) continue;
        textColor(GREY);
        setCursorPosition(52,selection+5);
        printf("   %s   ", menu[selection]);


        if(ch == down || ch == 80)
        {
            selection = (selection+1)%4;
        }
        else if(ch == up || ch == 72)
        {
            selection = (selection+3)%4;
        }
        else if((ch == 13 || ch == hDrop))
        {
            if(selection == 2) 
            {
                helpMenu();
                system("cls");
                printf("\n\n\n\n\n");
                textColor(GREY);
                printf("                                                        RESUME\n");
                printf("                                                         SAVE\n");
                textColor(BLUE);
                printf("                                                    >>>  HELP  <<<\n");
                textColor(GREY);
                printf("                                                         QUIT\n");
            }
            else if(selection == 1)  /// save game
            {
                save(x,y,rotation,currentBlock,nextBlock, score);
                printf("\n\n\n\n\n");
                textColor(GREY);
                printf("                                                        RESUME\n");
                textColor(LIGHT_YELLOW);
                printf("                                                    >>>  SAVE  <<<\n");
                textColor(GREY);
                printf("                                                         HELP\n");
                printf("                                                         QUIT\n");
            }
            else
            {
                textColor(GREEN);
                return selection;
            }
        }
        else if(ch == 27) // esc
        {
            textColor(GREEN);
            return 0;
        }
        if(selection == 0) textColor(GREEN);
        else if(selection == 1) textColor(LIGHT_YELLOW);
        else if(selection == 2) textColor(BLUE);
        else textColor(RED);
        setCursorPosition(52,selection+5);
        printf(">>>%s<<<", menu[selection]);
    }

}

int countMatching()
{
    int cnt = 0;
    for(int i = 0; i < H; i++)
    {
        int f = 1;
        for(int j = 1; j < W+1; j++)
        {
            if(field[i][j] == ' ') f = 0;
        }
        cnt += f;
        if(f)
        {
            strcpy(field[0], "|                      |");
            for(int j = i; j > 0; j--) 
            {
                strcpy(field[j], field[j-1]);
            }
        }
    }
    return cnt;
}

void playGame(int currentBlock, int nextBlock, int blockColor, int fieldColor, int gameType, long long score)
{

    int t = 0, x = gameType-3,y = 11, r = 0, speedControl = 14, canSwap = 1;

    if(currentBlock == -1) // Checking if it is a saved game or not. If it is not, generate new blocks
    {
        generatePiece(&currentBlock, &nextBlock, gameType);
        generatePiece(&currentBlock, &nextBlock, gameType);
    }

    canAccomodate(x,y,r,currentBlock);
    system("cls");

    countdown();
    textColor(fieldColor);

    system("cls");
    printField(nextBlock, score, blockColor, fieldColor);
    update(x,y,r,currentBlock, BRICK, fieldColor, blockColor);
    generateShadow(x,y,r,currentBlock, fieldColor, blockColor);
    Sleep(1000);
    
    while(1)
    {
        char ch;
        // if(speedControl > 5 && score%4000 == 0) speedControl--;
        // if(speedControl > 5)
        // {
        if(score < 4000) speedControl = 14;
        else if(score < 8000) speedControl = 13;
        else if(score < 12000) speedControl = 12;
        else if(score < 16000) speedControl = 11;
        else if(score < 20000) speedControl = 10;
        else if(score < 24000) speedControl = 9;
        else if(score < 28000) speedControl = 8;
        else if(score < 36000) speedControl = 7;
        else if(score < 36000) speedControl = 6;
        else if(score < 40000) speedControl = 5;
        else  speedControl = 4;
        // }
        if(t%speedControl == 0)
        {
            t = 0;
            if(canMove(x, y, r, currentBlock, down))
            {
                removeShadow(x,y,r,currentBlock, fieldColor, blockColor);
                update(x,y,r,currentBlock, ' ', fieldColor, blockColor);
                move(&x, &y, r, currentBlock, down);
                update(x,y,r, currentBlock, BRICK, fieldColor, blockColor);
                generateShadow(x,y,r,currentBlock, fieldColor, blockColor);
                // printField();
            }
            else
            {
                // check for match & update score
                int n = countMatching();
                if(n) score += n*125 - 25;
                updateScore(score, blockColor);
                //Reset Piece info
                x = gameType-3, y = 11;
                r = 0;


                //generate next piece
                generatePiece(&currentBlock, &nextBlock, gameType);

                canSwap = 1;


                // Check if next piece can be accomodated
                if(!canAccomodate(x,y,r,currentBlock))
                {
                    //save score;
                    system("cls");
                    textColor(RED);
                    printf("\n\n\n\n\n\t\t\t\t\t\t[ GAME OVER !!]\n\n\n\n");
                    system("pause");
                    updateLeaderboard(score);
                    resetField();
                    textColor(WHITE);
                    return;
                }
                
                textColor(fieldColor);
                printField(nextBlock, score, blockColor, fieldColor);
                textColor(blockColor);
                update(x,y,r,currentBlock, BRICK, fieldColor, blockColor);
                generateShadow(x,y,r, currentBlock, fieldColor, blockColor);
            }
        }
        if(kbhit())
        {
            ch = _getch();
            if(ch == -32) // Arrow key
            {  
                ch = _getch();
                if(ch == 77) ch = right;      // Right Arrow
                else if(ch == 75) ch = left;  // Left  Arrow
                else if(ch == 72) ch = up;    // Up    Arrow
                else if(ch == 80) ch = down;  // Down  Arrow
            }

            if(ch == hDrop || ch == 13) // Hard drop
            {
                update(x,y,r,currentBlock, ' ', fieldColor, blockColor);
                score += 2*hardDrop(&x, &y, r, currentBlock);
                update(x,y,r,currentBlock,BRICK, fieldColor, blockColor);
                updateScore(score, blockColor);
                t = speedControl;
                continue;
            }
            else if(ch == up) //Rotate
            {
                removeShadow(x,y,r,currentBlock, fieldColor, blockColor);
                update(x,y,r,currentBlock,' ', fieldColor, blockColor);
                r =  rotate(x, y, r, currentBlock);
                update(x,y,r,currentBlock,BRICK, fieldColor, blockColor);
                generateShadow(x,y,r,currentBlock, fieldColor, blockColor);
            }
            else if(ch == down) // Soft drop
            {
                if(canMove(x,y,r,currentBlock, down))
                {
                    score++;
                    updateScore(score, blockColor);
                }
                update(x,y, r, currentBlock, ' ', fieldColor, blockColor);
                move(&x,&y,r, currentBlock, ch);
                update(x,y, r, currentBlock, BRICK, fieldColor, blockColor);

            }
            else if(ch == hold && canSwap) // Hold current piece
            {
                removeShadow(x,y,r,currentBlock, fieldColor, blockColor);
                for(int i = 0; i < PIECESIZE; i++)
                {
                    field[block[currentBlock][r][i][0]+(x)][block[currentBlock][r][i][1]+(y)] = ' ';
                }
                update(x,y,r,currentBlock, ' ', fieldColor, blockColor);
                int temp = currentBlock;
                currentBlock = nextBlock;
                nextBlock = temp;
                x = gameType-3, y = 11, r = 0;
                for(int i = 0; i < PIECESIZE; i++)
                {
                    field[block[currentBlock][r][i][0]+(x)][block[currentBlock][r][i][1]+(y)] = BRICK;
                }
                update(x,y,r,currentBlock, BRICK, fieldColor, blockColor);
                generateShadow(x,y,r,currentBlock, fieldColor, blockColor);
                updateNextPiece(nextBlock, blockColor);
                canSwap = 0;
                
            }
            else if(ch == 27) // Pause the game
            {
                int selection = pause(x, y, r, currentBlock, nextBlock, score);
                if(selection == 0)
                {
                    countdown();
                    textColor(fieldColor);
                    printField(nextBlock, score, blockColor, fieldColor);
                    update(x,y,r,currentBlock, BRICK, fieldColor, blockColor);
                    generateShadow(x,y,r,currentBlock, fieldColor, blockColor);
                }
                else 
                {
                    textColor(WHITE);
                    resetField();
                    return;
                }
            }
            else if(ch == left || ch == right) // Move sideways
            {
                removeShadow(x,y,r,currentBlock, fieldColor, blockColor);
                update(x,y,r,currentBlock, ' ', fieldColor, blockColor);
                move(&x, &y, r, currentBlock, ch);
                update(x,y,r,currentBlock, BRICK, fieldColor, blockColor);
                generateShadow(x,y,r,currentBlock, fieldColor, blockColor);
            }
        }
        t++;
        Sleep(20);
    }
}