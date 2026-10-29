void handleInput(void)
{
    bool EscKeyIsDown     = KEY_DOWN(VK_ESCAPE);
    //bool UpKeyIsDown      = KEY_DOWN('W');
    //bool LeftKeyIsDown    = KEY_DOWN('A');
    //bool RightKeyIsDown   = KEY_DOWN('D');
    //bool DownKeyIsDown    = KEY_DOWN('S');
    bool RotateRight      = KEY_DOWN('R');
    bool RotateLeft      = KEY_DOWN('E');

    if(EscKeyIsDown)
    {
        SendMessageA(g_window_handle, WM_CLOSE, 0, 0);
    }

    if(RotateRight) 
    {
        for(int i = 0; i < 3; i++)
        {
            transformMatrix.rotation.setVectorIndex(i, transformMatrix.rotation->getIndex(i) + 0.1);
        }
    }

    if(RotateLeft) 
    {
        for(int i = 0; i < 3; i++)
        {
            transformMatrix.rotation.setVectorIndex(i, transformMatrix.rotation->getIndex(i) - 0.1);
        }
    }
}