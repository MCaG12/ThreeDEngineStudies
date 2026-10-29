class Utils
{
    public:
        bool applyClipping(Vector4d *PointA, Vector4d *PointB);
        Vector4d newPositions(Vector4d *PointA, Vector4d *PointB, double transform);
};