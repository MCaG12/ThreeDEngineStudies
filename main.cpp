#include <iostream>

#include "Vector3d.h"  
#include "matrix.h"
#include "camera.h"
#include "mesh.h"

#include "display.h"
#include <windows.h>
#include "transform.h"
#include "utils.h"

#define KEY_DOWN(k) (GetAsyncKeyState(k))

const int width = 900;
const int height = 900;

HWND g_window_handle = 0;
MONITORINFO G_MonitorInfo;

LONG G_MonitorWidth = 0;
LONG G_MonitorHeight = 0;

Transform transformMatrix;

typedef struct SCENE_BIT_MAP
{
    BITMAPINFO BitMapInfo;
    void* memory_canvas;
} SCENE_BIT_MAP;

SCENE_BIT_MAP g_backbuffer;

void handleInput(void)
{
    bool EscKeyIsDown     = KEY_DOWN(VK_ESCAPE);

    bool UpKeyIsDown      = KEY_DOWN(VK_SPACE);
    bool DownKeyIsDown    = KEY_DOWN(VK_SHIFT);

    bool FowardKeyIsDown  = KEY_DOWN('W');
    bool BackKeyIsDown    = KEY_DOWN('S');

    bool RightKeyIsDown   = KEY_DOWN('D');
    bool LeftKeyIsDown    = KEY_DOWN('A');

    bool RotateRight      = KEY_DOWN('R');
    bool RotateLeft       = KEY_DOWN('E');

    if(EscKeyIsDown)
    {
        SendMessageA(g_window_handle, WM_CLOSE, 0, 0);
    }


    if(FowardKeyIsDown) 
    {
        transformMatrix.position.setVectorIndex(2, transformMatrix.position.getVectorIndex(2) + 1);
    }

    if(BackKeyIsDown) 
    {
        transformMatrix.position.setVectorIndex(2, transformMatrix.position.getVectorIndex(2) - 1);
    }


    if(RightKeyIsDown) 
    {
        transformMatrix.position.setVectorIndex(0, transformMatrix.position.getVectorIndex(0) + 1);
    }

    if(LeftKeyIsDown) 
    {
        transformMatrix.position.setVectorIndex(0, transformMatrix.position.getVectorIndex(0) - 1);
    }

    if(UpKeyIsDown) 
    {
        transformMatrix.position.setVectorIndex(1, transformMatrix.position.getVectorIndex(1) - 1);
    }

    if(DownKeyIsDown) 
    {
        transformMatrix.position.setVectorIndex(1, transformMatrix.position.getVectorIndex(1) + 1);
    }

    if(RotateRight) 
    {
        for(int i = 0; i < 3; i++)
        {
            transformMatrix.rotation.setVectorIndex(i, transformMatrix.rotation.getVectorIndex(i) + 1);
        }
    }

    if(RotateLeft) 
    {
        for(int i = 0; i < 3; i++)
        {
            transformMatrix.rotation.setVectorIndex(i, transformMatrix.rotation.getVectorIndex(i) - 1);
        }
    }
}

void paintBitMap(display *DisplayObject)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            const Pixel& currentPixel = DisplayObject->pixelMap[y][x];
            memcpy_s((Pixel*)g_backbuffer.memory_canvas + (width * y) + x, sizeof(currentPixel), &currentPixel, sizeof(Pixel));

        }
    }
}

int DrawScene()
{

    HDC DeviceContext = GetDC(g_window_handle);

    Vector3d<double> origin(0, 0, 0);

    Camera camera(width, height, 90, origin);

    Matrix<double,4,4> model = transformMatrix.getModelMatrix();
    Matrix<double,4,4> view = camera.getViewMatrix();
    Matrix<double,4,4> proj = camera.getProjectionMatrix();

    Matrix<double,4,4> newPerspecitve = proj.GetFourByFourMatrixMultiplication(view).GetFourByFourMatrixMultiplication(model);

    Mesh Object;
    Object.makeDebugCube();
    
    const std::vector<Vector3d<double>>& vertices = Object.getVertices();
    std::vector<std::pair<double,double>> Pairs;

    for (size_t  i = 0; i < vertices.size(); i++)
    {
        Vector3d<double> newVertex = newPerspecitve.MovePoint(vertices[i]);
        double screenX = (newVertex.getVectorIndex(0) + 1) * 0.5 * width;
        double screenY = (newVertex.getVectorIndex(1) + 1) * 0.5 * height;

        std::pair<double, double> currentXY = {screenX, screenY};
        Pairs.push_back(currentXY);
    }

    display DisplayObject(height, width);

    int edges[12][2] = {
        {0,1},{1,2},{2,3},{3,0},
        {4,5},{5,6},{6,7},{7,4},
        {0,4},{1,5},{2,6},{3,7}
    };

    for(int i = 0; i < 12; i++)
    {
        std::pair<double,double> pointOne = Pairs[edges[i][0]];
        std::pair<double,double> pointTwo = Pairs[edges[i][1]];

        DisplayObject.drawLine(pointOne.first, pointOne.second, pointTwo.first, pointTwo.second);    
    }

    paintBitMap(&DisplayObject);
    StretchDIBits(DeviceContext, 0, 0, G_MonitorWidth, G_MonitorHeight, 0, 0, width, height, g_backbuffer.memory_canvas, &g_backbuffer.BitMapInfo, DIB_RGB_COLORS, SRCCOPY);

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    transformMatrix.position = Vector3d<double>(0, 0, -5);
    transformMatrix.rotation = Vector3d<double>(0, 0, 0);   // 90 degrees of yaw
    transformMatrix.scale    = Vector3d<double>(1, 1, 1);


    (void)hPrevInstance;
    (void)lpCmdLine;
    const char CLASS_NAME[] = "RendererWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc   = WindowProc;       // Window procedure callback
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    G_MonitorInfo.cbSize = sizeof(MONITORINFO);

    if (GetMonitorInfoA(MonitorFromWindow(g_window_handle, MONITOR_DEFAULTTOPRIMARY), &G_MonitorInfo) == 0)// this takes 2 input parameters a monitor handle a and monitor data structure our monitor handle is a function call that returns a handle for our monitor
    {
        return -1;
    };

    G_MonitorWidth = G_MonitorInfo.rcMonitor.right - G_MonitorInfo.rcMonitor.left;
    G_MonitorHeight = G_MonitorInfo.rcMonitor.bottom - G_MonitorInfo.rcMonitor.top;

    // here we are registering our bitmap info
    g_backbuffer.BitMapInfo.bmiHeader.biWidth = width;
    // make sure we are supplying a negative height for windows to make use of our buffer top -> down supplying it with a positive inverts this direction and for some reason pixels are not drawn
    g_backbuffer.BitMapInfo.bmiHeader.biHeight = -height;
    g_backbuffer.BitMapInfo.bmiHeader.biSize = sizeof(g_backbuffer.BitMapInfo.bmiHeader);
    g_backbuffer.BitMapInfo.bmiHeader.biCompression = BI_RGB;
    g_backbuffer.BitMapInfo.bmiHeader.biBitCount = 32;
    g_backbuffer.BitMapInfo.bmiHeader.biPlanes = 1;

    g_backbuffer.memory_canvas = VirtualAlloc(NULL, width * height * sizeof(Pixel), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    RegisterClass(&wc);

     g_window_handle = CreateWindowEx(
        0,                          // Optional window styles
        CLASS_NAME,                 // Window class name
        "3D render Window",          // Window title
        WS_OVERLAPPEDWINDOW,        // Window style

        // Position & size (x, y, width, height)
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (g_window_handle == NULL) return 0;

    ShowWindow(g_window_handle, nCmdShow);
    UpdateWindow(g_window_handle);

    MSG msg = {};
    bool running = true;

    while (running)
    {
        while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                running = false;
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (!running) break;

        //processInput();
        handleInput();
        DrawScene();
    }


    
    return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:

            return 0;


        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}