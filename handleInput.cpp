#include "main.h"

void handleInput(void)
{
    bool EscKeyIsDown     = KEY_DOWN(VK_ESCAPE);

    bool UpKeyIsDown      = KEY_DOWN(VK_SPACE);
    bool DownKeyIsDown    = KEY_DOWN(VK_SHIFT);

    bool FowardKeyIsDown  = KEY_DOWN('W');
    bool BackKeyIsDown    = KEY_DOWN('S');

    bool RightKeyIsDown   = KEY_DOWN('D');
    bool LeftKeyIsDown    = KEY_DOWN('A');

    bool RotateRightFoward      = KEY_DOWN('Y');
    bool RotateRightBack        = KEY_DOWN('U');

    bool RotateLeftFoward      = KEY_DOWN('H');
    bool RotateLeftBack        = KEY_DOWN('J');

    bool RotateUpFoward      = KEY_DOWN('N');
    bool RotateUpBack        = KEY_DOWN('M');

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

    if(RotateRightFoward) 
    {
        transformMatrix.rotation.setVectorIndex(0, transformMatrix.rotation.getVectorIndex(0) + 10);
    }

    if(RotateRightBack) 
    {
        transformMatrix.rotation.setVectorIndex(0, transformMatrix.rotation.getVectorIndex(0) - 10);
    }

    if(RotateLeftFoward) 
    {
        transformMatrix.rotation.setVectorIndex(1, transformMatrix.rotation.getVectorIndex(1) + 10);
    }

    if(RotateLeftBack) 
    {
        transformMatrix.rotation.setVectorIndex(1, transformMatrix.rotation.getVectorIndex(1) - 10);
    }

    if(RotateUpFoward) 
    {
        transformMatrix.rotation.setVectorIndex(2, transformMatrix.rotation.getVectorIndex(2) + 10);
    }

    if(RotateUpBack) 
    {
        transformMatrix.rotation.setVectorIndex(2, transformMatrix.rotation.getVectorIndex(2) - 10);
    }

}
