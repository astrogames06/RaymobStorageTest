#include <raymob.h>
#include <string>
#include <iostream>
#include <vector>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int points;

struct Circle
{
    float x;
    float y;
    Color color;
};
std::vector<Circle> circles;

// THIS SECTION IS AI GENERATED
/************************/
template <typename T>
bool SaveData(const char *filepath, const T &data)
{
    return WriteToAppStorage(filepath, (void *)&data, sizeof(T));
}

template <typename T>
T LoadData(const char *filepath)
{
    int dataSize = 0;

    void *loadedData = ReadFromAppStorage(filepath, &dataSize);

    if (loadedData == NULL || dataSize != sizeof(T))
    {
        if (loadedData != NULL)
            RL_FREE(loadedData);

        return T();
    }

    T data;
    memcpy(&data, loadedData, sizeof(T));

    RL_FREE(loadedData);

    return data;
}

template <typename T>
std::vector<T> LoadVector(const char *filepath)
{
    int dataSize = 0;

    void *loadedData = ReadFromAppStorage(filepath, &dataSize);

    if (loadedData == NULL)
        return {};

    if (dataSize % sizeof(T) != 0)
    {
        RL_FREE(loadedData);
        return {};
    }

    std::vector<T> data(dataSize / sizeof(T));

    memcpy(data.data(), loadedData, dataSize);

    RL_FREE(loadedData);

    return data;
}
/************************/

int main(void)
{
    InitWindow(0, 0, "raylib [core] example - basic window");
    SetTargetFPS(60);

    points = LoadData<int>("storages_test_points.dat");

    std::vector<Circle> circles_data = LoadVector<Circle>("storages_test_circles.dat");
    circles = circles_data;

    std::cout << "Storage Path: " << GetAppStoragePath() << '\n';

    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            bool did_collide = false;
            for (int i = 0; i < circles.size(); i++)
            {
                Circle c = circles[i];
                if (CheckCollisionPointCircle(GetMousePosition(), {c.x,c.y}, 50.f))
                {
                    did_collide = true;
                }

                if (did_collide)
                {
                    circles.erase(circles.begin() + i);
                    break;
                }
            }

            if (!did_collide)
            {
                Circle new_circle = {(float)GetMouseX(), (float)GetMouseY(), RED};
                circles.push_back(new_circle);

                // Saving data
                /*  circles.size() * sizeof(Circle) makes that it
                    accounts for the number of items and how much each one takes up.
                */
                WriteToAppStorage("storages_test_circles.dat", circles.data(), circles.size() * sizeof(Circle));
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (Circle& c : circles)
        {
            DrawCircle(c.x, c.y, 50.f, c.color);
        }

        std::string points_str = "Points: " + std::to_string(points);
        DrawText(points_str.c_str(), 20, 20, GetScreenWidth()/20, BLACK);

        if (GuiButton({20, 150, 200, 150}, "Add Points!"))
        {
            points++;
            WriteToAppStorage("storages_test_points.dat", &points, sizeof(points));
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}