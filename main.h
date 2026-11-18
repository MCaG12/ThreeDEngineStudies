#pragma once

#include <iostream>
#include "Vector3d.h"  
#include "matrix.h"
#include "camera.h"
#include "mesh.h"

#include "display.h"
#include <windows.h>
#include "transform.h"
#include "utils.h"
#include "handleInput.h"

extern Transform transformMatrix;
extern int width;
extern int height;
extern HWND g_window_handle;


#define KEY_DOWN(k) (GetAsyncKeyState(k))

typedef struct SCENE_BIT_MAP
{
    BITMAPINFO BitMapInfo;
    void* memory_canvas;
} SCENE_BIT_MAP;