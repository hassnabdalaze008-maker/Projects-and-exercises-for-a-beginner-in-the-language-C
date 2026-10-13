#include <stdio.h>
#define MOVE_UP 1.0
#define MOVE_DOWN 0.4
#define MOVE_LEFT 0.5
#define MOVE_RIGHT 0.5
#define MOVE_FORWARD 0.5
#define MOVE_BACK 0.5
#define HOVER 0.2
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define FORWARD 'f'
#define BACK 'b'
#define STATIC 'c'

char user_input();

float Distance();

int calculate(float *battray, float move, float distance);

void drone_control();

int main(void)
{
    drone_control();
    return 0;
}
char user_input()
{
    char move;
    printf("enter move: ");
    scanf(" %c", &move);
    return move;
}
float Distance()
{
    float d;
    do
    {
        printf("enter distance per meter: ");
        scanf("%f", &d);
        if (d <= 0)
            printf("please enter a positive value\n");
    }
    while (d <= 0);
    return d;
}
int calculate(float *battray, float move, float distance)
{
    if(*battray >= move * distance)
    {
        *battray -= move * distance;
        printf("battay charging: %.2f\n", *battray);
        return 1;
    }
    else
    {
        printf("the battray is insufficient\n");
        printf("battray charging: %.2f\n", *battray);
        return 0;
    }
}
void drone_control()
{
    float x, y, z = 0;
    float battray = 100;
    char move;
    short is_move = 0;
    float distance;
    short status = 0;
    printf("moves: up, down, left, right, state, forward, back\n");
    while(battray > 0.01)
    {
        move = user_input();
        switch (move)
        {
            case UP: distance = Distance(); calculate(&battray, MOVE_UP, distance);   y += distance; break;
            case DOWN:distance = Distance();calculate(&battray, MOVE_DOWN, distance); y -= distance; break;
            case LEFT:distance = Distance();calculate(&battray, MOVE_LEFT, distance); x -= distance; break;
            case RIGHT:distance= Distance();calculate(&battray, MOVE_RIGHT, distance);x += distance; break;
            case FORWARD:distance=Distance();calculate(&battray, MOVE_FORWARD, distance);z-=distance;break;
            case BACK:distance = Distance();calculate(&battray, MOVE_BACK, distance); z -= distance; break;
            default:
                break;
        }
        printf("position: x = %.2f, y = %.2f, z = %.2f\n", x, y, z);
    }
}
