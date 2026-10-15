#pragma once
#include "Vector3d.h"
#include "matrix.h"


constexpr double PI = 3.14159265358979323846; // for some reason the complier is ignoreing both cmath and numbers 

class Camera
{
    private:
        Vector3d<double> cameraPosition;
        double yaw, pitch;
        double fov;
        double aspectRatio;
        double nearPlane = 0.1;
        double farPlane  = 1000.0;
    public:

        Camera(int Width, int Height, double FOV, Vector3d<double>& Position);
        double getCameraYaw(void);
        double getCameraPitch(void);
        double getCameraAspectRatio(void);
        Vector3d<double> getCameraPosition(void);

        double getFovRad(void);

        Matrix<float, 4, 4> getProjectionMatrix(void);

        
};

Camera::Camera(int Width, int Height, double FOV,
               Vector3d<double>& Position)
    : cameraPosition(Position),
      yaw(-90),
      pitch(0),
      fov(FOV),
      aspectRatio(Width / (double)Height)
{
}

double
Camera::getCameraYaw(void)
{
    return this->yaw;
}

double
Camera::getCameraPitch(void)
{
    return this->pitch;
}

double 
Camera::getFovRad(void)
{
    double  fovRad = (this->fov * PI  )/ 180;
    return fovRad;
}

double 
Camera::getCameraAspectRatio(void)
{
    return this->aspectRatio;
}

Vector3d<double>
Camera::getCameraPosition(void)
{
    return this->cameraPosition;
}

Matrix<float, 4, 4> 
Camera::getProjectionMatrix(void)
{
    double scalingFactor  = ( 1 / tan(this->getFovRad() /2.0 ) );
    Matrix<float, 4,4> projectionMatrix (0);

    projectionMatrix.MatrixArray[0][0] = scalingFactor / (this)->aspectRatio;
    projectionMatrix.MatrixArray[1][1] = scalingFactor;
    projectionMatrix.MatrixArray[2][2] = (this->farPlane + this->nearPlane)/(this->nearPlane - this->farPlane);
    projectionMatrix.MatrixArray[3][2] = -1;
    projectionMatrix.MatrixArray[2][3] = (2 * this->farPlane * this->nearPlane)/(this->nearPlane - this->farPlane);

    return projectionMatrix;
}