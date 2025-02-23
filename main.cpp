#include <iostream>
#include <raylib.h>

using namespace std;

#define OUTLIMIT 25

int main () {

    const int SCREEN_WIDTH = 1440;
    const int SCREEN_HEIGHT = 860;
    float a_rectangle_lenx = 50;
    float a_rectangle_leny = 250;
    float a_rectangle_pos_x = 60;
    float a_rectangle_pos_y = 100;
    float b_rectangle_lenx = 50;
    float b_rectangle_leny = 250;
    float b_rectangle_pos_x = 1340;
    float b_rectangle_pos_y = 100;
    float ball_pos_x = 720;
    float ball_pos_y = 400;
    float ball_speed_x = 5;
    float ball_speed_y = 5;
    float ball_radius = 15;
    int score_a = 0;
    int score_b = 0;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pongers");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){

        ball_pos_x += ball_speed_x;
        ball_pos_y += ball_speed_y;

        if(CheckCollisionCircleRec({ball_pos_x, ball_pos_y}, ball_radius, {a_rectangle_pos_x,a_rectangle_pos_y,a_rectangle_lenx,a_rectangle_leny}))
        {
            ball_speed_x *= -1.05;
        }
        
        if(CheckCollisionCircleRec({ball_pos_x, ball_pos_y}, ball_radius, {b_rectangle_pos_x,b_rectangle_pos_y,b_rectangle_lenx,b_rectangle_leny}))
        {
            ball_speed_x *= -1.05;
        }

        if(ball_pos_x + ball_radius >= b_rectangle_pos_x + OUTLIMIT)
        {
            score_a += 1;
            ball_pos_x = 720;
            ball_pos_y = 400;
            ball_speed_x = 5;
            ball_speed_y = 5;
        }
        
        if(ball_pos_x - ball_radius <= a_rectangle_pos_x + a_rectangle_lenx - OUTLIMIT)
        {
            score_b += 1;
            ball_pos_x = 720;
            ball_pos_y = 400;
            ball_speed_x = 5;
            ball_speed_y = 5;
        }

        if(ball_pos_x + ball_radius >= SCREEN_WIDTH || ball_pos_x - ball_radius <= 0)
        {
            ball_speed_x *= -1;
        }

        if(ball_pos_y + ball_radius >= SCREEN_HEIGHT || ball_pos_y - ball_radius <= 0)
        {
            ball_speed_y *= -1;
        }

        if(a_rectangle_pos_y <= 0)
        {
            a_rectangle_pos_y = 0;
        }

        if(a_rectangle_pos_y + a_rectangle_leny >= SCREEN_HEIGHT)
        {
            a_rectangle_pos_y = SCREEN_HEIGHT - a_rectangle_leny;
        }

        if(b_rectangle_pos_y <= 0)
        {
            b_rectangle_pos_y = 0;
        }

        if(b_rectangle_pos_y + b_rectangle_leny >= SCREEN_HEIGHT)
        {
            b_rectangle_pos_y = SCREEN_HEIGHT - b_rectangle_leny;
        }

        if (IsKeyDown(KEY_W)) a_rectangle_pos_y -= 5.0f;
        if (IsKeyDown(KEY_S)) a_rectangle_pos_y += 5.0f;

        if (IsKeyDown(KEY_UP)) b_rectangle_pos_y -= 5.0f;
        if (IsKeyDown(KEY_DOWN)) b_rectangle_pos_y += 5.0f;
        

        BeginDrawing();
            ClearBackground(BLACK);
            int textWidth = MeasureText(TextFormat("SCORE: %d - %d", score_a, score_b), 100);
            DrawText(TextFormat("SCORE: %d - %d", score_a, score_b), (SCREEN_WIDTH - textWidth) / 2, 10, 100, RAYWHITE);
            DrawRectangle(a_rectangle_pos_x, a_rectangle_pos_y, a_rectangle_lenx, a_rectangle_leny, RAYWHITE);
            DrawRectangle(b_rectangle_pos_x, b_rectangle_pos_y, b_rectangle_lenx, b_rectangle_leny, RAYWHITE);
            DrawCircle(ball_pos_x, ball_pos_y, ball_radius, RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
}