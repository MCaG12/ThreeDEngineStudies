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

    bool LookLeftIsDown    = KEY_DOWN(VK_LEFT);
    bool LookRightIsDown   = KEY_DOWN(VK_RIGHT);

    bool LookUpIsDown    = KEY_DOWN(VK_UP);
    bool LookDownIsDown   = KEY_DOWN(VK_DOWN);

    bool RotateRightFoward      = KEY_DOWN('Y');
    bool RotateRightBack        = KEY_DOWN('U');

    bool RotateLeftFoward      = KEY_DOWN('H');
    bool RotateLeftBack        = KEY_DOWN('J');

    bool RotateUpFoward      = KEY_DOWN('N');
    bool RotateUpBack        = KEY_DOWN('M');

    double cameraYaw = (*camera.getCameraYaw());
    double cameraPitch = (*camera.getCameraPitch());

    double step = 0.1;
    double turnStep = 1; 

    Vector3d foward = camera.getFowardVector();
    foward.setVectorIndex(1, 0.0); 
    foward = foward.normalizeVector();

    Vector3d right = camera.getRightVector();
    right.setVectorIndex(1, 0.0); 
    right = right.normalizeVector();

    //Vector3d Up = right.crossProduct(foward);

    //camera manipulation keys
    if(EscKeyIsDown)
    {
        SendMessageA(g_window_handle, WM_CLOSE, 0, 0);
    }

    if(FowardKeyIsDown) 
    {
        Vector3d result = (*camera.getCameraPosition()) + (foward * step);
        camera.setCameraPosition( &result );
        //camera.getCameraPosition()->setVectorIndex(2, ( *camera.getCameraPosition() ) + foward );
    }

    if(BackKeyIsDown) 
    {
        Vector3d result = (*camera.getCameraPosition()) - (foward * step);
        camera.setCameraPosition( &result );
        //camera.getCasmeraPosition()->setVectorIndex(2, camera.getCameraPosition()->getVectorIndex(2) - foward.getVectorIndex(2));
    }

    if(RightKeyIsDown) 
    {
        Vector3d result = (*camera.getCameraPosition()) + (right * step);
        camera.setCameraPosition( &result );
        //camera.getCameraPosition()->setVectorIndex(0, camera.getCameraPosition()->getVectorIndex(0) + 1);
    }

    if(LeftKeyIsDown) 
    {
        Vector3d result = (*camera.getCameraPosition()) - (right * step);
        camera.setCameraPosition( &result );
       // camera.getCameraPosition()->setVectorIndex(0, camera.getCameraPosition()->getVectorIndex(0) - 1);
    }

    if(LookLeftIsDown) 
    {
        camera.setCameraYaw( (*camera.getCameraYaw()) - turnStep);
    }

    if(LookRightIsDown) 
    {
        camera.setCameraYaw( (*camera.getCameraYaw()) + turnStep );
    }

    if(LookUpIsDown) 
    {
        
        double newPitch = cameraPitch + 1;
        if(newPitch > 89.0) newPitch = 89.0;
        camera.setCameraPitch(  newPitch );
    }

    if(LookDownIsDown) 
    {
        double newPitch = cameraPitch - 1;
        if(newPitch < -89.0) newPitch = -89.0;
        camera.setCameraPitch(  newPitch );
    }
        
    //model manipulation keys
    if(UpKeyIsDown) 
    {
        camera.getCameraPosition()->setVectorIndex(1, camera.getCameraPosition()->getVectorIndex(1) - 1);
    }

    if(DownKeyIsDown) 
    {
        camera.getCameraPosition()->setVectorIndex(1, camera.getCameraPosition()->getVectorIndex(1) + 1);
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
