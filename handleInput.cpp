#include

#define KEY_DOWN(k) (GetAsyncKeyState(k))

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