#include "main.h"

std::vector<CP_Vector> poly1vertices;
std::vector<CP_Vector> poly2vertices;

MeshCollider poly1, poly2;
CircleCollider circle1;
bool isHolding = false;
bool holdPoly1, holdPoly2, holdCircle1;
CP_Color baseColor, hitColor;
std::vector<Collider*> colliderList;

void game_init(void)
{
    srand(static_cast<unsigned int>(time(NULL)));
    //CP_System_ShowConsole();
    CP_System_SetWindowSize(800, 450);

    baseColor = CP_Color_Create(200, 200, 200, 255);
    hitColor = CP_Color_Create(255, 100, 100, 255);
    
    CP_Vector screenMid = { CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f };

    poly1.color = baseColor;
    poly1.position = screenMid;
    poly1.scale = 50;
    poly1.vertices = CreateConvexPolygonVertices(4, poly1.scale);
    colliderList.push_back(&poly1);

    poly2.color = baseColor;
    poly2.position = screenMid;
    poly2.scale = 50;
    poly2.vertices = CreateConvexPolygonVertices(8, poly2.scale);
    colliderList.push_back(&poly2);

    circle1.color = baseColor;
    circle1.position = screenMid;
    circle1.radius = 20;
    colliderList.push_back(&circle1);
}

void HandleInput(CP_Vector& mousePos)
{
    if (IsPointInRadius(poly1.position, poly1.scale, mousePos))
    {
        if (CP_Input_MouseDown(MOUSE_BUTTON_1))
        {
            if (!isHolding)
            {
                isHolding = true; holdPoly1 = true;
            }

            if (holdPoly1)
            {
                poly1.position = mousePos;
            }
        }
        else if (CP_Input_MouseReleased(MOUSE_BUTTON_1))
        {
            isHolding = false; holdPoly1 = false;
        }
    }

    if (IsPointInRadius(poly2.position, poly2.scale, mousePos))
    {
        if (CP_Input_MouseDown(MOUSE_BUTTON_1))
        {
            if (!isHolding)
            {
                isHolding = true; holdPoly2 = true;
            }

            if (holdPoly2)
            {
                poly2.position = mousePos;
            }
        }
        else if (CP_Input_MouseReleased(MOUSE_BUTTON_1))
        {
            isHolding = false; holdPoly2 = false;
        }
    }

    if (IsPointInRadius(circle1.position, circle1.radius, mousePos))
    {
        if (CP_Input_MouseDown(MOUSE_BUTTON_1))
        {
            if (!isHolding)
            {
                isHolding = true; holdCircle1 = true;
            }

            if (holdCircle1)
            {
                circle1.position = mousePos;
            }
        }
        else if (CP_Input_MouseReleased(MOUSE_BUTTON_1))
        {
            isHolding = false; holdCircle1 = false;
        }
    }
}

void game_update(void)
{
    CP_Vector mousePos = CP_Vector{ (float)CP_Input_GetMouseWorldX(), (float)CP_Input_GetMouseWorldY() };
    CP_System_SetFrameRate(60);
    CP_Graphics_ClearBackground(CP_Color_Create(120, 120, 120, 255));

    HandleInput(mousePos);

    for (Collider* col_pri : colliderList)
    {
        Simplex termSimp;
        Collision col;

        col_pri->color = baseColor;

        for (Collider* col_tar : colliderList)
        {
            if (col_pri == col_tar)
            {
                continue;
            }

            if (GJK_Reduced(col_pri, col_tar, termSimp))
            {
                col_pri->color = hitColor;

                col = EPA(termSimp, col_pri, col_tar);

                ResolveCollision_Static(col, col_pri, col_tar);
            }
        }

        col_pri->DrawCollider();

        //CP_Vector scaledNormal = CP_Vector_Scale(col.colNormal, 10);

        //CP_Graphics_DrawLine(col_pri->position.x, col_pri->position.y,
        //    col_pri->position.x + scaledNormal.x, col_pri->position.y + scaledNormal.y);

    }


}

void game_exit(void)
{

}
