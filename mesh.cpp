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

                std::cout<<"X: "<<x<<"Y: "<<y<<"Z: "<<z<<"\n";
            }

            if(currentWord == "f")
            {
                std::cout<<"found a face here!\n";
            }
        }
    }

    return true;
}