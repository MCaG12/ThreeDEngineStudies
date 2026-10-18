#include <iostream>

#include "Vector3d.h"  
#include "matrix.h"
#include "camera.h"
 
 
int main()
{
    Vector3d<double> startPositionTest(0.1,0.1,5);
    Camera cam(800, 600, 90.0, startPositionTest);

    Matrix<double, 4, 4> TransformationMatrix = cam.getProjectionMatrix();
    Matrix<double, 4, 4> ViewMatrix = cam.getViewMatrix();

    Vector3d<double> TransformedPosition = TransformationMatrix.MovePoint({0.1, 0.1, 0.1});
    Vector3d<double> ViewPosition = ViewMatrix.MovePoint({0.1, 0.1, 0.1});

    Vector3d<double> Test(0.1,0.1,5);

    Matrix<double,4,4> viewProj = TransformationMatrix.GetFourByFourMatrixMultiplication(ViewMatrix);

    Vector3d<double> clip = viewProj.MovePoint(Test);

    std::cout<<"printing all the viewProj stuff now\n";
    for(int i = 0; i < 3; i++)
    {
        std::cout<<clip.getVectorIndex(i)<<"\n";       
    }

    return 0;

}
