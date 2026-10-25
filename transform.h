#include "Vector3d.h"  
#include "matrix.h"


constexpr double M_PI = 3.14159265358979323846; // for some reason the complier is ignoreing both cmath and numbers 

class Transform {
    public:
        Vector3d<double> position;
        Vector3d<double> rotation;
        Vector3d<double> scale;

        Transform() : position(0,0,0), rotation(0,0,0), scale(1,1,1) {}

        Matrix<double,4,4> getIdentityMatrix(void); //creates a matrix with diagonal 1's
        Matrix<double,4,4> getTranslationMatrix(const Vector3d<double> &position);
        Matrix<double,4,4> getScaleMatrix(const Vector3d<double> &scale);
        Matrix<double,4,4> getRotationX(double degrees);
        Matrix<double,4,4> getRotationY(double degrees);
        Matrix<double,4,4> getRotationZ(double degrees);
        Matrix<double,4,4> getModelMatrix(void);

    private:

};

Matrix<double,4,4> 
Transform::getIdentityMatrix(void)
{
    Matrix<double,4,4> identity(0);

    identity.MatrixArray[0][0] = 1;
    identity.MatrixArray[1][1] = 1;
    identity.MatrixArray[2][2] = 1;
    identity.MatrixArray[3][3] = 1;

    return identity;
}


Matrix<double,4,4> 
Transform::getTranslationMatrix(const Vector3d<double> &position)
{
    Matrix<double,4,4> identity = this->getIdentityMatrix();

    identity.MatrixArray[0][3] = position.getVectorIndex(0);
    identity.MatrixArray[1][3] = position.getVectorIndex(1);
    identity.MatrixArray[2][3] = position.getVectorIndex(2);

    return identity;
}

Matrix<double, 4, 4>
Transform::getScaleMatrix(const Vector3d<double> &scale)
{
    Matrix<double,4,4> scaleMatrix = this->getIdentityMatrix();
    
    scaleMatrix.MatrixArray[0][0] = scale.getVectorIndex(0);
    scaleMatrix.MatrixArray[1][1] = scale.getVectorIndex(1);
    scaleMatrix.MatrixArray[2][2] = scale.getVectorIndex(2);

    return scaleMatrix;
}

Matrix<double, 4, 4>
Transform::getRotationX(double degrees)
{
    double degreeInRad = (degrees * M_PI) / 180;
    Matrix<double,4,4> rotation = this->getIdentityMatrix();

    rotation.MatrixArray[1][1] =  cos(degreeInRad);
    rotation.MatrixArray[1][2] = -sin(degreeInRad);
    rotation.MatrixArray[2][1] =  sin(degreeInRad);
    rotation.MatrixArray[2][2] =  cos(degreeInRad);

    return rotation;
}

Matrix<double, 4, 4>
Transform::getRotationY(double degrees)
{
    double degreeInRad = (degrees * M_PI) / 180;
    Matrix<double,4,4> rotation = this->getIdentityMatrix();

    rotation.MatrixArray[0][0] =  cos(degreeInRad);
    rotation.MatrixArray[0][2] = sin(degreeInRad);
    rotation.MatrixArray[2][0] =  -sin(degreeInRad);
    rotation.MatrixArray[2][2] =  cos(degreeInRad);

    return rotation;
}

Matrix<double, 4, 4>
Transform::getRotationZ(double degrees)
{
    double degreeInRad = (degrees * M_PI) / 180;
    Matrix<double,4,4> rotation = this->getIdentityMatrix();

    rotation.MatrixArray[0][0] =  cos(degreeInRad);
    rotation.MatrixArray[0][1] = -sin(degreeInRad);
    rotation.MatrixArray[1][0] =  sin(degreeInRad);
    rotation.MatrixArray[1][1] =  cos(degreeInRad);

    return rotation;
}

Matrix<double,4,4> 
Transform::getModelMatrix(void)
{
    Matrix<double,4,4> TranslationMatrix = this->getTranslationMatrix(this->position);
    Matrix<double,4,4> ScaleMatrix = this->getScaleMatrix(this->scale);
    Matrix<double,4,4> RotationMatrix = getRotationY(this->rotation.getVectorIndex(1))
                                        .GetFourByFourMatrixMultiplication(getRotationX(rotation.getVectorIndex(0)))
                                        .GetFourByFourMatrixMultiplication(getRotationZ(rotation.getVectorIndex(2)));

    return TranslationMatrix.GetFourByFourMatrixMultiplication(RotationMatrix).GetFourByFourMatrixMultiplication(ScaleMatrix);
}