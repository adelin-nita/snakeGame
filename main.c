#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 70
#define HEIGHT 20

int dx = 0, dy = 0;
int snakeX, snakeY;
int foodX, foodY;
int tailX[1000], tailY[1000];
int tailLength = 0;
int score = 0;
int choice = 1;

void drawMenu()
{
    system("cls");

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "en_US.UTF-8");

    CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };
    GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font);
    wcscpy(font.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font);

    printf("\n\n");
    printf("                                   ░██████                         ░██                  \n");
    printf("                                  ░██   ░██                        ░██                  \n");
    printf("                                 ░██         ░████████   ░██████   ░██    ░██ ░███████  \n");
    printf("                                  ░████████  ░██    ░██       ░██  ░██   ░██ ░██    ░██ \n");
    printf("                                         ░██ ░██    ░██  ░███████  ░███████  ░█████████ \n");
    printf("                                  ░██   ░██  ░██    ░██ ░██   ░██  ░██   ░██ ░██        \n");
    printf("                                   ░██████   ░██    ░██  ░█████░██ ░██    ░██ ░███████  \n");
    printf("                                  ----------------------------------------------------- \n");
    printf("\n\n");
    printf("                                                      | Meniu Joc |\n");
    printf("                                                       -----------\n");
    printf("\n\n");
    printf("                                        1. Incepe Jocul\n");
    printf("\n");
    printf("                                        2. Despre\n");
    printf("\n");
    printf("                                        3. Iesi Din Joc\n");

}

void drawBorder()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    int Width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int Height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int offsetX = (Width - (WIDTH + 2)) / 2;
    int offsetY = (Height - (HEIGHT + 2)) / 2;

    COORD pos;

    pos.X = offsetX;
    pos.Y = offsetY;
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("╔");
    for (int i = 0; i < WIDTH; i++) printf("═");
    printf("╗");

    for (int y = 0; y < HEIGHT; y++)
    {
        pos.X = offsetX;
        pos.Y = offsetY + y + 1;
        SetConsoleCursorPosition(hConsole, pos);
        printf("║");
        for (int x = 0; x < WIDTH; x++) printf(" ");
        printf("║");
    }

    pos.X = offsetX;
    pos.Y = offsetY + HEIGHT + 1;
    SetConsoleCursorPosition(hConsole, pos);
    printf("╚");
    for (int i = 0; i < WIDTH; i++) printf("═");
    printf("╝");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // reset colors
}

void menuLogic();
void userInput();

void setDifficulty()
{
    system("cls");
    printf("\n\n");
    printf("                                                    | Dificultate |\n");
    printf("                                                     -------------\n");
    printf("\n\n");
    printf("                                             1. Usor\n");
    printf("\n");
    printf("                                             2. Mediu\n");
    printf("\n");
    printf("                                             3. Greu\n");
    printf("\n");
    printf("                                             4. Inapoi\n");

    while (true)
    {
        printf("\n                                             Selecteaza: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("\n                                             Ati selectat dificultatea: Usor");
                Sleep(1000);
                return;
            case 2:
                printf("\n                                             Ati selectat dificultatea: Mediu");
                Sleep(1000);
                return;
            case 3:
                printf("\n                                             Ati selectat dificultatea: Greu");
                Sleep(1000);
                return;
            case 4:
                menuLogic();
                return;
            default:
                printf("                                             Optiune invalida!");
                break;
        }
    }
}

void resetGame() 
{
    tailLength = 0;
    score = 0;
    dx = 1; 
    dy = 0;
    srand(time(NULL));
    snakeX = WIDTH / 2;
    snakeY = HEIGHT / 2;
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
}

void playGame()
{
    resetGame();
    setDifficulty();
    
    int speed;
    if (choice == 1) speed = 100;
    else if (choice == 2) speed = 50;
    else if (choice == 3) speed = 25;

    system("cls");
    printf("Jocul va incepe imediat...");
    Sleep(1000);
    system("cls");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info = {100, FALSE};
    SetConsoleCursorInfo(hConsole, &info);

    drawBorder();
    
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int Width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int Height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    int offsetX = (Width - (WIDTH + 2)) / 2;
    int offsetY = (Height - (HEIGHT + 2)) / 2;

    bool isGameOver = false;
    COORD pos;

    while (!isGameOver)
    {
        userInput();

        // saves the previous position of the tail to clear it later
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        
        tailX[0] = snakeX;
        tailY[0] = snakeY;
        
        for (int i = 1; i < tailLength; i++)
        {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

        // head movement
        snakeX += dx;
        snakeY += dy;

        // wall collision logic
        if (snakeX < 0 || snakeX >= WIDTH || snakeY < 0 || snakeY >= HEIGHT) {
            isGameOver = true;
        }

        // body collision logic
        for (int i = 0; i < tailLength; i++) {
            if (tailX[i] == snakeX && tailY[i] == snakeY) {
                isGameOver = true;
            }
        }

        // food logic
        if (snakeX == foodX && snakeY == foodY) {
            score += 10;
            tailLength++;
            
            // generate new food position, ensuring it doesn't spawn on the snake
            bool foodOnSnake;
            do {
                foodOnSnake = false;
                foodX = rand() % WIDTH;
                foodY = rand() % HEIGHT;
                
                if(foodX == snakeX && foodY == snakeY) foodOnSnake = true;
                for(int i = 0; i < tailLength; i++) {
                    if(foodX == tailX[i] && foodY == tailY[i]) foodOnSnake = true;
                }
            } while(foodOnSnake);
        }

        if (isGameOver) break;
        
        // deletes the last tail position
        if (tailLength > 0) {
            pos.X = prevX + 1 + offsetX;
            pos.Y = prevY + 1 + offsetY;
        } else {
            pos.X = tailX[0] + 1 + offsetX;
            pos.Y = tailY[0] + 1 + offsetY;
        }
        SetConsoleCursorPosition(hConsole, pos);
        printf(" ");

        // draws the snake body
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        for (int i = 0; i < tailLength; i++) {
            pos.X = tailX[i] + 1 + offsetX;
            pos.Y = tailY[i] + 1 + offsetY;
            SetConsoleCursorPosition(hConsole, pos);
            printf("o");
        }

        // draws the snake head
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        pos.X = snakeX + 1 + offsetX;
        pos.Y = snakeY + 1 + offsetY;
        SetConsoleCursorPosition(hConsole, pos);
        printf("█");

        // draws the food
        pos.X = foodX + 1 + offsetX;
        pos.Y = foodY + 1 + offsetY;
        SetConsoleCursorPosition(hConsole, pos);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("●");

        // prints the score
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        pos.X = offsetX;
        pos.Y = offsetY - 1;
        SetConsoleCursorPosition(hConsole, pos);
        printf("Scor: %d", score);

        Sleep(speed);
    }

    // game over screen
    system("cls");
    printf("\n\n\t\t\tGAME OVER!");
    printf("\n\t\t\tScorul tau final a fost: %d\n", score);
    printf("\n\t\t\tApasa orice tasta pentru a reveni la meniu...");
    _getch();
}

void userInput()
{
    if (_kbhit())
    {
        char key = _getch();
        // prevent 180-degree turns
        switch(key)
        {
            case 'w':
                if(dy == 1) break; 
                dx = 0; dy = -1; break;
            case 's':
                if(dy == -1) break;
                dx = 0; dy = 1; break;
            case 'a':
                if(dx == 1) break;
                dx = -1; dy = 0; break;
            case 'd':
                if(dx == -1) break;
                dx = 1; dy = 0; break;
        }
    }
}

void showAbout()
{
    system("cls");

    printf("\n\n");
    printf("                                                   | Despre Joc |\n");
    printf("                                                    ------------\n\n");
    printf("                  Snake - colecteaza puncte fara sa atingi coada.\n");
    printf("                  3 nivele de dificultate, in functie de viteza lui: Usor | Mediu | Greu.\n");
    printf("                  Joc creat in C cu Windows API.\n\n");
    printf("                                                    | Creator |\n");
    printf("                                                     ---------\n\n");
    printf("                  Joc creat de Adelin.\n");
    printf("                  Student UPB, Facultatea de Automatică și Calculatoare.");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("                                     apasa orice tasta pentru a reveni la meniu...");
    _getch();
}

void menuLogic()
{
    int option;
    do
    {
        drawMenu();
        printf("\n                                             Selecteaza: ");
        if (scanf("%d", &option) != 1) {
            // clears the buffer if the input is not an integer
            while (getchar() != '\n'); 
            option = -1;
        }

        switch(option) {
            case 1: playGame(); break;
            case 2: showAbout(); break;
            case 3: ExitProcess(0); break;
            default:
                printf("\n                                            Optiune invalida!");
                Sleep(1000);
                break;
        }

    } while(option != 3);
}

int main()
{
    menuLogic();
    return 0;
}