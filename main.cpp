#include "main.h"

HWND g_window_handle = 0;
MONITORINFO G_MonitorInfo;

LONG G_MonitorWidth = 0;
LONG G_MonitorHeight = 0;

Transform transformMatrix;
Transform floorMatrix;

int width = 900;
int height = 900;

SCENE_BIT_MAP g_backbuffer;

Mesh Object;
bool loadObject = Object.loadObjFile("./Untitled.obj");

Mesh CheckerboardDebugGrid;
bool loadCheckerboard = CheckerboardDebugGrid.makeDebugChessGrid(20, 2, Pixel(122,122,122) ,Pixel(204,204,204));

Vector3d<double> origin(0, 0, 0);

display DisplayObject(height, width);
Utils UsefulFunctions;

Camera camera(width, height, 90, origin);

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

void DrawObject(Mesh objectToDraw, Vector3d<double> LightRay, Camera camera, Pixel Color, Transform p_transformMatrix, bool Debug)
{
    // setting up the rendering pipeline with Model, view, scale
    Matrix<double,4,4> model = p_transformMatrix.getModelMatrix();
    Matrix<double,4,4> view = camera.getViewMatrix();
    Matrix<double,4,4> proj = camera.getProjectionMatrix();

    Matrix<double,4,4> Perspective = proj.GetFourByFourMatrixMultiplication(view).GetFourByFourMatrixMultiplication(model);

    const std::vector<Vector3d<double>>& vertices = objectToDraw.getVertices();
    std::vector<Vector4d> Pairs;

    for (size_t  i = 0; i < vertices.size(); i++)
    {
        Vector4d current = Perspective.getVector4d(vertices[i]);

        Pairs.push_back(current);
    }

    std::vector<Vector3d<double>> worldVertices;
    worldVertices.reserve(vertices.size());

    for (size_t i = 0; i < vertices.size(); i++)
    {
        Vector4d w = model.getVector4d(vertices[i]);
        worldVertices.push_back(Vector3d<double>(w.x, w.y, w.z));
    }

    std::vector<Triangle> modelTriangles = objectToDraw.getTriangles();
    std::vector<Pixel> modelColors = objectToDraw.getColors();

    for(size_t i = 0; i < modelTriangles.size(); i++)
    {
        Triangle currentTriangle = modelTriangles[i];
        Vector4d pointOne   = Pairs[currentTriangle.v0Index];
        Vector4d pointTwo   = Pairs[currentTriangle.v1Index];
        Vector4d pointThree = Pairs[currentTriangle.v2Index];

        Vector3d<double> PointOneWorldPos   = worldVertices[currentTriangle.v0Index];
        Vector3d<double> PointTwoWorldPos   = worldVertices[currentTriangle.v1Index];
        Vector3d<double> PointThreeWorldPos = worldVertices[currentTriangle.v2Index];
    
        if (pointOne.z + pointOne.w < 0 || pointTwo.z + pointTwo.w < 0 || pointThree.z + pointThree.w < 0) continue;
        if( !UsefulFunctions.backFaceCullingCheck(&pointOne, &pointTwo, &pointThree) ) { continue; }

        std::pair<double,double> ScreenPointOne = UsefulFunctions.putToScreen(&pointOne, width, height);
        std::pair<double,double> ScreenPointTwo = UsefulFunctions.putToScreen(&pointTwo, width, height);
        std::pair<double,double> ScreenPointThree = UsefulFunctions.putToScreen(&pointThree, width, height);

        double faceBrightness = DisplayObject.calculateFaceBrightness(PointOneWorldPos, PointTwoWorldPos, PointThreeWorldPos, LightRay);

        Pixel Painted;
        if(!Debug)  Painted = Color;
        else Painted = modelColors[i];
        Painted.Blue *= faceBrightness;
        Painted.Red *= faceBrightness;
        Painted.Green *= faceBrightness;
        
        

        DisplayObject.paintPixel
                (  ScreenPointOne.first, ScreenPointOne.second, (pointOne.z / pointOne.w),
                   ScreenPointTwo.first, ScreenPointTwo.second, (pointTwo.z / pointTwo.w),
                   ScreenPointThree.first, ScreenPointThree.second, (pointThree.z / pointThree.w),
                   Painted
                );
    }

    return;
}

int DrawScene(HDC DeviceContext)
{

    Vector3d<double> LightRay(0.3, 0.8, 0.5);

    LightRay = LightRay.normalizeVector();

    // // setting up the rendering pipeline with Model, view, scale
    // Matrix<double,4,4> model = transformMatrix.getModelMatrix();
    // Matrix<double,4,4> view = camera.getViewMatrix();
    // Matrix<double,4,4> proj = camera.getProjectionMatrix();

    // Matrix<double,4,4> newPerspecitve = proj.GetFourByFourMatrixMultiplication(view).GetFourByFourMatrixMultiplication(model);

    DrawObject(Object, LightRay, camera, Pixel(255,255,255), transformMatrix, false);
    DrawObject(CheckerboardDebugGrid, LightRay, camera, Pixel(255,0,0), floorMatrix, true);

    paintBitMap(&DisplayObject);
    StretchDIBits(DeviceContext, 0, 0, G_MonitorWidth, G_MonitorHeight, 0, 0, width, height, g_backbuffer.memory_canvas, &g_backbuffer.BitMapInfo, DIB_RGB_COLORS, SRCCOPY);

    DisplayObject.clear();
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    LARGE_INTEGER FrameStart;
    LARGE_INTEGER FrameEnd;
    LARGE_INTEGER Frequency;
    QueryPerformanceFrequency(&Frequency);

    transformMatrix.position = Vector3d<double>(0, 0, -5);
    transformMatrix.rotation = Vector3d<double>(0, 0, 0);   // 90 degrees of yaw
    transformMatrix.scale    = Vector3d<double>(1, 1, 1);

    floorMatrix.position = Vector3d<double>(0, -2, 0);
    floorMatrix.rotation = Vector3d<double>(0, 0, 0);   // 90 degrees of yaw
    floorMatrix.scale    = Vector3d<double>(1, 1, 1);

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
        HDC DeviceContext = GetDC(g_window_handle);
        QueryPerformanceCounter(&FrameStart);
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
        RECT client;
        GetClientRect(g_window_handle, &client);
        int clientWidth  = client.right - client.left;
        int clientHeight = client.bottom - client.top;
        if (clientWidth > 0 && clientHeight > 0) DrawScene(DeviceContext);
        QueryPerformanceCounter(&FrameEnd);

        char c_DebugBuffer[64] = {0};

        double elapsedMs = (double)(FrameEnd.QuadPart - FrameStart.QuadPart) * 1000.0
                 / (double)Frequency.QuadPart;

        sprintf_s(c_DebugBuffer, sizeof(c_DebugBuffer),
                "Frame: %.2f ms (%.0f fps)", elapsedMs, 1000.0 / elapsedMs);
        //this TextOut function prints stuff onto our program!
        TextOutA(DeviceContext, 0,0, c_DebugBuffer, (int) strlen(c_DebugBuffer));
        ReleaseDC(g_window_handle, DeviceContext);
    }
    //ReleaseDC(g_window_handle, DeviceContext);

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