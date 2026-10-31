#include "vector4d.h"
#include <utility>
class Utils
{
    public:
        bool applyClipping(Vector4d *PointA, Vector4d *PointB);
        Vector4d newPositions(Vector4d *PointA, Vector4d *PointB, double transform);
        std::pair<double,double> putToScreen(Vector4d *Point, int Width, int Height);
        bool backFaceCullingCheck(Vector4d *PointA, Vector4d *PointB, Vector4d *PointC);
};