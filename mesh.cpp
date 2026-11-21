#include "mesh.h"

bool 
Mesh::loadObjFile(std::string ObjFilePath)
{
    std::ifstream ObjFile(ObjFilePath);

    if( !ObjFile.is_open() )
    {
        std::cout<<"failed to open the specified file!\n";
        return false;
    }

    (*this).mesh_vertices.clear();
    (*this).mesh_triangles.clear();
    std::string line;

    while (std::getline(ObjFile, line)) 
    {
        std::stringstream currentFileLine(line);
        std::string currentWord;

        while (currentFileLine >> currentWord) 
        {
            if(currentWord == "v")
            {
                std::cout<<"found a vector here!\n";
                double x,y,z;
                currentFileLine >> x >> y >> z;
                Vector3d currentEdge(x, y, z);
                (this)->mesh_vertices.push_back(currentEdge);

            }

            else if (currentWord == "f")                  
            {
                std::vector<int> corners;
                std::string token;
                while (currentFileLine >> token)
                {

                    int index = std::stoi(token.substr(0, token.find('/')));
                    index = (index < 0) ? (*this).mesh_vertices.size() + index   
                                        : index - 1;                     
                    corners.push_back(index);
                }

                for (size_t k = 1; k + 1 < corners.size(); k++)
                    (*this).mesh_triangles.push_back({ corners[0], corners[k], corners[k + 1] });
            }
        }
    }
    //std::cout << mesh_vertices.size() << " vertices, " << mesh_triangles.size() << " triangles\n";
    for (int i = 0; i < 5; i++)
        std::cout << mesh_vertices[i].getVectorIndex(0) << " "
                  << mesh_vertices[i].getVectorIndex(1) << " "
                  << mesh_vertices[i].getVectorIndex(2) << "\n";
    return true;
}

bool
Mesh::makeDebugChessGrid(int width, int tileWidth, Pixel CheckerBoardColorDark, Pixel CheckerBoardColorLight)
{
    this->mesh_vertices.clear();
    this->mesh_triangles.clear();

    double middleOfGrid = (width * tileWidth) / 2;
    int stride  = width + 1;

    for(int z = 0; z <= width; z++)
    {
        for(int x = 0; x <= width; x++)
        {
            mesh_vertices.push_back(Vector3d(x * tileWidth - middleOfGrid, 0.0, z * tileWidth - middleOfGrid));
        }
    }

    for(int z = 0; z < width; z++)
    {
        for(int x = 0; x < width; x++)
        {
            int TopLeftEdge    = z * (stride) + x;
            int TopRightEdge   = TopLeftEdge + 1;
            int BottomLeftEdge = TopLeftEdge + (stride); 
            int BottomRightEdge = BottomLeftEdge + 1; 
            
            Triangle triangle_one(TopLeftEdge, BottomLeftEdge, TopRightEdge);
            Triangle triangle_two(TopRightEdge, BottomLeftEdge, BottomRightEdge);

            this->mesh_triangles.push_back(triangle_one);
            this->mesh_triangles.push_back(triangle_two);

            Pixel color = ((x + z) % 2 == 0) ? CheckerBoardColorDark : CheckerBoardColorLight;

            this->mesh_triangles_colors.push_back(color);
            this->mesh_triangles_colors.push_back(color);

        }
    }
    return true;
}