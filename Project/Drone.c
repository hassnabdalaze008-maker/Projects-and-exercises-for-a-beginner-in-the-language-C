#include <stdio.h>

#define MOVE_UP 1.0
#define MOVE_DOWN 0.4
#define MOVE_LEFT 0.5
#define MOVE_RIGHT 0.5
#define MOVE_FORWARD 0.5
#define MOVE_BACK 0.5
#define HOVER 0.2
#define DELTA_X_Z 130
#define DELTA_Y 100

char user_input();

float Distance();

int calculate(float *battray, float move, float distance);

int max_distance(float current, float distance, float limit);

void drone_control();

int main()
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

int max_distance(float current, float distance, float limit)
{
    if (current + distance > limit) {
        printf("Max limit reached!\n");
        return 0;
    }
    return 1;
}

void drone_control()
{
    float x = 0;
    float y = 0;
    float z = 0;
    float battray = 100;
    char move;
    printf("moves: up, down, left, right, state, forward, back\n");
    while(battray > 0.01)
    {
        move = user_input();
        float dx = 0, dy = 0, dz = 0;
        float rate = 0;
        int needs_distance = 0;
        int valid = 1;
        switch (move) {
            case 'w': dy = 1;  rate = MOVE_UP;      needs_distance = 1; break;
            case 's': dy = -1; rate = MOVE_DOWN;    needs_distance = 1; break;
            case 'a': dx = -1; rate = MOVE_LEFT;    needs_distance = 1; break;
            case 'd': dx = 1;  rate = MOVE_RIGHT;   needs_distance = 1; break;
            case 'f': dz = 1;  rate = MOVE_FORWARD; needs_distance = 1; break;
            case 'b': dz = -1; rate = MOVE_BACK;    needs_distance = 1; break;
            case 'c': rate = HOVER; break;
            case 'q': battray = 0; valid = 0; break;
            default:  printf("invalid move\n"); valid = 0; break;
        }
        if (valid && move != 'q') {
            float distance = 1.0;
            if (needs_distance) {
                distance = Distance();
                if(dx != 0 && !max_distance(x, dx * distance, DELTA_X_Z))
                    continue;
                if(dy != 0 && !max_distance(y, dy * distance, DELTA_Y))
                    continue;
                if(dz != 0 && !max_distance(z, dz * distance, DELTA_X_Z))
                    continue;
            }
        if (calculate(&battray, rate, distance)) {
            x += dx * distance;
            y += dy * distance;
            z += dz * distance;
        }
        }
        printf("position: x = %.2f, y = %.2f, z = %.2f\n", x, y, z);
    }
    printf("charge battray = 0!");
}
