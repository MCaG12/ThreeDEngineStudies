#include <iostream>

#include "Vector3d.h"  
#include "matrix.h"
#include "camera.h"
 
 
int main()
{
    Vector3d<double> startPositionTest(1,1,1);
    Camera cam(800, 600, 90.0, startPositionTest);

    Matrix<float, 4, 4> TransformationMatrix = cam.getProjectionMatrix();

        std::cout<<"0:0 "<<TransformationMatrix.MatrixArray[0][0]<<" 1:1"<<TransformationMatrix.MatrixArray[1][1]<<" 2:2"<<TransformationMatrix.MatrixArray[2][2]
    <<" 2:3"<<TransformationMatrix.MatrixArray[2][3];

    Vector3d<double> testPoint(0, 0, 5);
    Vector3d<double> result = TransformationMatrix.MovePoint(testPoint);

    std::cout<<" Result Stuff \n";
    for(int i = 0; i < 3 ; i++)
    {
        std::cout<<result.getVectorIndex(i)<<" ";
    }

    return 0;

}
