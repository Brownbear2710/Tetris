#include "control.c"

void showLeaderboard()
{
    char name[10][21] = {0};
    long long score[10] = {0};
    FILE * fp = fopen("ovzw", "rb");
    if(fp)
    {
        fread(name, 1, 10*21, fp);
        fread(score, 8, 10, fp);
        fclose(fp);
    }
    while(1)
    {
        system("cls");
        setCursorPosition(46, 5);
        printf("PRESS R TO RESET");
        setCursorPosition(46, 6);
        printf("PRESS ESC TO RETURN");
        for(int i = 0; i < 10; i++)
        {
            if(i == 0) textColor(GREEN);
            else if(i == 1) textColor(CYAN);
            else if(i == 2) textColor(LIGHT_YELLOW);
            else if(i == 2) textColor(LIGHT_YELLOW);
            else textColor(WHITE);
            setCursorPosition(46, 8+i);
            printf("%02d. %s", i+1, name[i]);
            setCursorPosition(71, 8+i);
            printf("%05ld", score[i]);
        }
        char ch = _getch();
        if(ch == 'r' || ch == 'R')
        {
            for(int i = 0; i < 10; i++)
            {
                strncpy(name[i], " ", 20);
                score[i] = 0;
            }
            fp = fopen("ovzw", "wb");
            fwrite(name, 1, 10*21, fp);
            fwrite(score, 8, 10, fp);
        }
        else if(ch == 27) return;
    }
    
}

void changeColorTheme(int *fieldColor, int *blockColor)
{
    for(int i = 18; i < 20; i++)
    {
        for(int j = 1; j < 22; j++)
        {
            field[i][j] = BRICK;
        }
    }

    textColor(*fieldColor);
    printField(3,123,*blockColor, *fieldColor);
    textColor(*blockColor);
    update(5,6,0,2,BRICK,*fieldColor, *blockColor);
    generateShadow(5,6,0,2,*fieldColor, *blockColor);
    setCursorPosition(0,0);
    textColor(WHITE);
    printf("->USE");
    textColor(RED);
    printf(" 'ARROW UP/DOWN' ");
    textColor(WHITE);
    printf("TO CHANGE THE COLOR OF FALLING BLOCK\n");

    printf("->USE");
    textColor(RED);
    printf(" ARROW 'LEFT/RIGHT' ");
    textColor(WHITE);
    printf("TO CHANGE THE COLOR OF FIELD\n");

    printf("->PRESS");
    textColor(RED);
    printf(" 'SPACE' ");
    textColor(WHITE);
    printf("TO RESTORE DEFAULTS\n");

    printf("->PRESS");
    textColor(RED);
    printf(" 'ESC' ");
    textColor(WHITE);
    printf("TO EXIT\n");

    while(1)
    {
        char key = _getch();
        if(key == -32) key = _getch();
        else if(key == 72 || key == 80 || key == 77 || key == 75) continue;

        if(key == 72)
        {
            *blockColor = ((*blockColor) - 7 + 7)%8 + 7;
        }
        else if(key == 80)
        {
            *blockColor = ((*blockColor) - 7 + 1)%8 + 7;
        }
        else if(key == 77)
        {
            *fieldColor = ((*fieldColor) - 7 + 1)%8 + 7;
        }
        else if(key == 75)
        {
            *fieldColor = ((*fieldColor) - 7 + 7)%8 + 7;
        }
        else if(key == ' ')
        {
            *fieldColor = GREY;
            *blockColor = WHITE;
        }
        else if(key == 27)
        {
            resetField();
            FILE * fp = fopen("theme", "w+");
            fprintf(fp, "%d %d", *fieldColor, *blockColor);
            fclose(fp);
            return;
        }

        textColor(*fieldColor);
        printField(3,123,*blockColor, *fieldColor);
        textColor(*blockColor);
        update(5,6,0,2,BRICK,*fieldColor, *blockColor);
        generateShadow(5,6,0,2,*fieldColor, *blockColor);
        setCursorPosition(0,0);
        textColor(WHITE);
        printf("->USE");
        textColor(RED);
        printf(" 'ARROW UP/DOWN' ");
        textColor(WHITE);
        printf("TO CHANGE THE COLOR OF FALLING BLOCK\n");

        printf("->USE");
        textColor(RED);
        printf(" ARROW 'LEFT/RIGHT' ");
        textColor(WHITE);
        printf("TO CHANGE THE COLOR OF FIELD\n");

        printf("->PRESS");
        textColor(RED);
        printf(" 'SPACE' ");
        textColor(WHITE);
        printf("TO RESTORE DEFAULTS\n");

        printf("->PRESS");
        textColor(RED);
        printf(" 'ESC' ");
        textColor(WHITE);
        printf("TO EXIT\n");
    }
}

void changeControls()
{
    system("cls");
    char key[][2] = {{left}, {right}, {down}, {up}, {hDrop}, {hold}};
    char menu[][12] = {"MOVE LEFT ", "MOVE RIGHT", "MOVE DOWN ", "ROTATE    ", "HARD DROP ","HOLD      "};
    int selection = 0;

    textColor(WHITE);
    setCursorPosition(30,1);
    printf("-> PRESS");
    textColor(RED);
    printf(" ARROW UP/DOWN ");
    textColor(WHITE);
    printf("TO NAVIGATE THROUGH THE MENU");

    setCursorPosition(30,2);
    printf("-> PRESS");
    textColor(RED);
    printf(" 'ENTER' ");
    textColor(WHITE);
    printf("TO SELECT THE CONTROL AND CHANGE");

    setCursorPosition(30,3);
    printf("-> PRESS");
    textColor(RED);
    printf(" 'R' ");
    textColor(WHITE);
    printf("TO RESET CONTROL");

    setCursorPosition(30,4);
    printf("-> PRESS");
    textColor(RED);
    printf(" 'ESC' ");
    textColor(WHITE);
    printf("TO RETURN");

    setCursorPosition(45,6);
    printf("%s          < %s >        ", menu[selection] ,key[selection][0] == ' ' ? "SPACE": key[selection]);

    textColor(GREY);
    for(int i = 1; i < 6; i++)
    {
        setCursorPosition(45,i+6);
        printf("%s          < %s >        ", menu[i] ,key[i][0] == ' ' ? "SPACE": key[i]);
    }
    
    while(1)
    {
        char ch = _getch();
        if(ch == -32) ch = _getch();
        if(ch == 72 || ch == 80)
        {
            setCursorPosition(45, selection+6);
            textColor(GREY);
            printf("%s          < %s >       ", menu[selection], key[selection][0] == ' ' ? "SPACE": key[selection]);
            textColor(WHITE);
        }
        if(ch == 72)
        {
            selection = (selection + 5)%6;
        }
        else if(ch == 80)
        {
            selection = (selection+1) % 6;
        }
        else if(ch == 'r' || ch == 'R')
        {
            key[0][0] = 'a';
            key[1][0] = 'd';
            key[2][0] = 's';
            key[3][0] = 'w';
            key[4][0] = ' ';
            key[5][0] = 'c';
            selection = 0;
            textColor(WHITE);
            setCursorPosition(45,6);
            printf("%s          < %s >        ", menu[selection] ,key[selection][0] == ' ' ? "SPACE": key[selection]);

            textColor(GREY);
            for(int i = 1; i < 6; i++)
            {
                setCursorPosition(45,i+6);
                printf("%s          < %s >        ", menu[i] ,key[i][0] == ' ' ? "SPACE": key[i]);
            }
            continue;
        }
        if(ch == 13)
        {
            textColor(WHITE);
            setCursorPosition(35, 20);
            printf("PRESS NEW CONTROL BUTTON (PRESS ESC TO CANCEL)");
            while(1)
            {
                char newButton = _getch();
                if(newButton == -32)
                {
                    newButton = _getch();
                    setCursorPosition(35,21);
                    textColor(RED);
                    printf("YOU CANNOT USE THAT         ");
                    continue;
                }
                int f = 1;
                for(int i = 0; i < 6; i++)
                {
                    if(key[i][0] == newButton)
                    {
                        f = 0;
                        break;
                    }
                }
                if(newButton == 27)
                {
                    setCursorPosition(35, 20);
                    printf("                                                                       ");
                    setCursorPosition(35,21);
                    printf("                                          ");
                    break;
                }
                else if(newButton == 13)
                {
                    setCursorPosition(35,21);
                    textColor(RED);
                    printf("YOU CANNOT USE THAT         ");
                    continue;
                }
                if(f)
                {
                    key[selection][0] = newButton;
                    setCursorPosition(35, 20);
                    printf("                                                                       ");
                    setCursorPosition(35,21);
                    printf("                                          ");
                    break;
                }
                else
                {
                    setCursorPosition(35, 21);
                    textColor(LIGHT_YELLOW);
                    printf("BUTTON IS ALREADY IN USE");
                }
            }
        }
        else if(ch == 27)
        {
            break;
        }
        
        setCursorPosition(45, selection+6);
        textColor(WHITE);
        printf("%s          < %s >        ", menu[selection] ,key[selection][0] == ' ' ? "SPACE": key[selection]);
    }
    left = key[0][0];
    right = key[1][0];
    down = key[2][0];
    up = key[3][0];
    hDrop = key[4][0];
    hold = key[5][0];
    FILE * fp = fopen("control", "w+");
    if(fp)
    {
        for(int i = 0; i < 6; i++)
        {
            fprintf(fp,"%c", key[i][0]);
        }
    }
    // _getch();
}


int showOptions(int *fieldColor, int * blockColor)
{
    system("cls");
    textColor(WHITE);
    // printf("                                     _____   ______  _______   _____   _____   ____\n");
    // printf("                                    |     \\ |           |     |     \\    |    /    \\\n");
    // printf("                                    |_____/ |____       |     |_____/    |    \\____\n");
    // printf("                                    |       |           |     |    \\     |         \\\n");
    // printf("                                    |       |______     |     |     \\  __|__  \\____/\n");
    printf("                                    _______  ______   _______   _____   _____   ____\n");
    printf("                                       |     |           |     |     \\    |    /    \\\n");
    printf("                                       |     |____       |     |_____/    |    \\____\n");
    printf("                                       |     |           |     |    \\     |         \\\n");
    printf("                                       |     |______     |     |     \\  __|__  \\____/\n");
    char option[][19] = {"CHANGE COLOR THEME", " CHANGE CONTROLS  ", "     GO BACK      "};
    int selection = 0;

    setCursorPosition(48,8);
    printf(">>> CHANGE");
    textColor(BLUE);
    printf(" C");
    textColor(GREEN);
    printf("O");
    textColor(LIGHT_YELLOW);
    printf("L");
    textColor(RED);
    printf("O");
    textColor(PURPLE);
    printf("R ");
    textColor(WHITE);
    printf("THEME <<<");

    textColor(GREY);
    setCursorPosition(48,9);
    printf("    %s    ", option[1]);
    setCursorPosition(48,10);
    printf("    %s    ", option[2]);
    while(1)
    {
        char key = _getch();
        if(key == -32) key = _getch();
        else if(key == 72 || key == 80) continue;
        textColor(GREY);
        setCursorPosition(48,selection+8);
        printf("    %s    ", option[selection]);

        if(key == 80 || key == down)
        {
            selection = (selection+1)%3;
        }
        else if( key == 72 || key == up)
        {
            selection = (selection+2)%3;
        }
        else if(key == 13 || key == hDrop)
        {
            textColor(WHITE);
            system("cls");
            return selection;
        }
        else if(key == 27)
        {
            textColor(WHITE);
            return 2;
        }
        if(selection == 0)
        {
            setCursorPosition(48,8);
            textColor(WHITE);
            printf(">>> CHANGE");
            textColor(BLUE);
            printf(" C");
            textColor(GREEN);
            printf("O");
            textColor(LIGHT_YELLOW);
            printf("L");
            textColor(RED);
            printf("O");
            textColor(PURPLE);
            printf("R ");
            textColor(WHITE);
            printf("THEME <<<");
        }
        else
        {
            textColor(WHITE);
            setCursorPosition(48,8+selection);
            printf(">>> %s <<<", option[selection]);
        }
    }
}


int showMainMenu()
{
    system("cls");
    textColor(WHITE);
    // printf("                                     _____   ______  _______   _____   _____   ____\n");
    // printf("                                    |     \\ |           |     |     \\    |    /    \\\n");
    // printf("                                    |_____/ |____       |     |_____/    |    \\____\n");
    // printf("                                    |       |           |     |    \\     |         \\\n");
    // printf("                                    |       |______     |     |     \\  __|__  \\____/\n");
    printf("                                    _______  ______   _______   _____   _____   ____\n");
    printf("                                       |     |           |     |     \\    |    /    \\\n");
    printf("                                       |     |____       |     |_____/    |    \\____\n");
    printf("                                       |     |           |     |    \\     |         \\\n");
    printf("                                       |     |______     |     |     \\  __|__  \\____/\n");
    char menu[][16] = {"   NEW GAME    ", "LOAD SAVED GAME","  LEADERBOARD  ", "    OPTIONS    ", "  HOW TO PLAY  ", "     EXIT      "};
    int selection = 0;
    setCursorPosition(49,7);
    textColor(GREEN);
    printf(">>> %s <<<", menu[0]);
    textColor(GREY);
    for(int i = 1; i < 6; i++)
    {
        setCursorPosition(49,i+7);
        printf("    %s    ", menu[i]);
    }
    while(1)
    {
        char ch = _getch();
        if(ch == -32) ch = _getch();
        else if(ch == 72 || ch == 80) continue;

        textColor(GREY);
        setCursorPosition(49,7+selection);
        printf("    %s    ", menu[selection]);
        if(ch == 80 || ch == down)
        {
            selection = (selection+1)%6;
        }
        else if(ch == 72 || ch == up)
        {
            selection = (selection+5)%6;
        }
        else if(ch == 13 || ch == hDrop)
        {
            textColor(WHITE);
            system("cls");
            return selection;
        }
        if(selection == 0) textColor(GREEN);
        else if(selection == 1) textColor(LIGHT_YELLOW);
        else if(selection == 2 || selection == 3) textColor(WHITE);
        else if(selection == 4) textColor(BLUE);
        else if(selection == 5) textColor(RED);
        // textColor(WHITE);
        setCursorPosition(49,7+selection);
        printf(">>> %s <<<", menu[selection]);
    }
}