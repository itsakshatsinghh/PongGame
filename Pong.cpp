#include <raylib.h>

#include <iostream>

using namespace std;

Color c1darkb = Color{73, 61, 158, 255};

Color c2blue = Color{178, 165, 255, 255};

Color c3 = Color{};

Color c4yellow = Color{255, 242, 175, 255};

int player_score = 0;

int cpu_score = 0;

class Ball
{

public:
    float x, y;

    int speedx, speedy;

    int radius;

    Ball()
    {

        x = 640; // Center of the screen

        y = 400;

        speedx = 15;

        speedy = 15;

        radius = 20;
    }

    void Draw()
    {

        DrawCircle(x, y, radius, c4yellow);
    }

    void Update()
    {

        x += speedx;

        y += speedy;

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {

            speedy *= -1;
        }

        if (x + radius >= GetScreenWidth())
        { // CPU wins

            cpu_score++;

            Resetball();
        }

        if (x - radius <= 0)
        { // Player wins

            player_score++;

            Resetball();
        }
    }

    void Resetball()
    {

        x = GetScreenWidth() / 2;

        y = GetScreenHeight() / 2;

        int speed_choices[2] = {-5, 5};

        speedx = speed_choices[GetRandomValue(0, 1)];

        speedy = speed_choices[GetRandomValue(0, 1)];
    }
};

class Paddle
{

public:
    float x, y;

    float widthP, heightP;

    int speed;

    Paddle()
    {

        x = 0;

        y = 0;

        widthP = 25;

        heightP = 120;

        speed = 10;
    }

    void Draw()
    {

        DrawRectangle(x, y, widthP, heightP, WHITE);
    }

    void Update()
    {

        if (IsKeyDown(KEY_UP))
        {

            y -= speed;
        }

        if (IsKeyDown(KEY_DOWN))
        {

            y += speed;
        }

        limitMovement();
    }

private:
    void limitMovement()
    {

        if (y <= 0)
        {

            y = 0;
        }

        if (y + heightP >= GetScreenHeight())
        {

            y = GetScreenHeight() - heightP;
        }
    }
};

class CpuPaddle : public Paddle
{

public:
    void Update(int ballY)
    {

        if (y + heightP / 2 > ballY)
        {

            y -= speed;
        }

        if (y + heightP / 2 < ballY)
        {

            y += speed;
        }

        limitMovement();
    }

private:
    void limitMovement()
    {

        if (y <= 0)
        {

            y = 0;
        }

        if (y + heightP >= GetScreenHeight())
        {

            y = GetScreenHeight() - heightP;
        }
    }
};

int main()
{

    cout << "Starting the game" << endl;

    const int width = 1280;

    const int height = 800;

    InitWindow(width, height, "---Pong Game---");

    SetTargetFPS(60);

    Paddle player;

    CpuPaddle cpu;

    Ball ball;

    player.x = width - player.widthP - 10;

    player.y = height / 2 - player.heightP / 2;

    cpu.x = 10;

    cpu.y = height / 2 - cpu.heightP / 2;

    while (!WindowShouldClose())
    {

        /* Updating */

        ball.Update();

        player.Update();

        cpu.Update(ball.y);

        /* Checking for Collisions */

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.widthP, player.heightP}))
        {

            ball.speedx *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.widthP, cpu.heightP}))
        {

            ball.speedx *= -1;
        }

        BeginDrawing();

        ClearBackground(c1darkb);
        DrawRectangle(width / 2, 0, width / 2, height, c2blue);
        DrawCircle(width / 2, height / 2, 150, c3);
        /* Drawing */

        DrawLine(width / 2, 0, width / 2, height, WHITE);

        ball.Draw();

        player.Draw();

        cpu.Draw();

        /* Displaying Score */

        DrawText(TextFormat("%i", cpu_score), width / 4 - 20, 20, 80, WHITE);

        DrawText(TextFormat("%i", player_score), 3 * width / 4 - 20, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
