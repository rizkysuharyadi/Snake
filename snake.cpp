#include <cstdlib>
#include <ncurses.h>
using namespace std;

bool gameOver;
const int width = 30, height = 30;
int x, y, FruitX, FruitY, score;
enum SnakeDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
SnakeDirection dir;

int TailX[100], TailY[100];
int nTail = 0;


void Setup()
{

    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    
    gameOver = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    FruitX = (rand() % width)+1;
    FruitY = (rand() % height)+1;
    score = 0;   

}

void Draw()
{
    
    clear();
    
    for (int i =0; i < width+2; i++)
        mvprintw(0,i,"+");
    
    for (int i = 0; i < height+2; i++)
    {
        for (int j = 0; j < width+2; j++)
        {
            if (i == 0 | i == 31)
                mvprintw(i,j,"+");
            else if (j == 0 |  j == 31)
                mvprintw(i,j,"+");
            else if (i == y && j == x)
                mvprintw(i,j,"O");
            else if (i == FruitY && j == FruitX)
                mvprintw(i,j,"@");         
            else 
                for (int m = 0; m < nTail; m++)
                {
                    if (TailX[m] == j && TailY[m] == i)
                        mvprintw(i,j,"o");
                }
        }
    }

    mvprintw(6,45,"Welcome to Snake Game!"); 
    mvprintw(7,38,"Press any controls to start the game");  
    mvprintw(12,52,"Controls:");
    mvprintw(13,42,"Up Arrow to move the snake up");
    mvprintw(14,40,"Down Arrow to move the snake down");
    mvprintw(15,40,"Left Arrow to move the snake left");
    mvprintw(16,39,"Right Arrow to move the snake right");
    mvprintw(20,53,"Rules:");
    mvprintw(21,39,"Don't let the snake touch the walls!");
    mvprintw(22,39,"The snake CANNOT move in 180 degrees");
    mvprintw(23,34,"Be careful if you reach the score of 5 and 10!");
    mvprintw(24,48,"Have fun playing!");
    mvprintw(27,52,"Score: %d",score);
            
    refresh();
       
    
}

void Input()
{

    keypad(stdscr, TRUE);
    halfdelay(3);
    if (score >= 5 && score < 10){
        halfdelay(2);
    }
    else if (score >= 10){
        halfdelay(1);
    }
    
    int c = getch();
    
    switch(c)
    {
    case KEY_LEFT:
        dir = LEFT;
        break;
    case KEY_RIGHT:
        dir = RIGHT;
        break;
    case KEY_UP:
        dir = UP;
        break;
    case KEY_DOWN:
        dir = DOWN;
        break;
    case 113:
        gameOver = true;
        break;
    }

}

void Logic()
{
    int prevX = TailX[0];
    int prevY = TailY[0];
    int prev2X, prev2Y;
    TailX[0] = x;
    TailY[0] = y;
    
    for (int i = 1; i < nTail; i++)
    {
        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
        
    switch(dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    
    if (x > width || x < 1 || y < 1 || y > height)
        gameOver = true;

    if (x == FruitX && y == FruitY)
    {
        score++;
        FruitX = (rand() % width)+1;
        FruitY = (rand() % height)+1;      
        nTail++;
    } 
    for (int i = 0; i < nTail; i++)
        if (TailX[i] == x && TailY[i] == y)
        {
            gameOver = true;
        }
}

int main()
{

        Setup();

        while(!gameOver)
        {
            Draw();
            Input();
            Logic();
        }
        
        getch();
        endwin();
        
        return 0;
    

    
}
