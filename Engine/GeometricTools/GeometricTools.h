#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>
#include <vector>


namespace GeometricTools{
    //Array for normalized triangle
    constexpr float UnitTriangle2D[3*3] = { -0.5f, -0.5f, 0.0f,
                                             0.5f, -0.5f, 0.0f,
                                             0.0f, 0.5f, 0.0f};
    //Array for normalized square
    constexpr float UnitSquare2D[4*3] = {   0.5f, 0.5f, 0.0f,  
                                            0.5f, -0.5f, 0.0f,
                                            -0.5f, -0.5f, 0.0f, 
                                            -0.5f, 0.5f, 0.0f };
                                            
    //Color array for a triangle [3*3]
    constexpr float ColorTriangle2D[3*3] = {    1.0f, 0.0f, 0.0f,
                                                0.0f, 1.0f, 0.0f, 
                                                0.0f, 0.0f, 1.0f};
    //Color array for a square [3*4]
    constexpr float ColorSquare2D[3*4] = {  0.0f, 0.0f, 0.0f, 
                                            0.0f, 0.0f, 0.0f, 
                                            0.0f, 0.0f, 0.0f, 
                                            0.0f, 0.0f, 0.0f};

    //std::vector<glm::vec3> vertices;      || std::vector<glm::uvec3> indices;

    /*
  * Template function to generate a grid in 2D
  * x is for how many across the width of the grid and y is for how many to create in the height.
  * std::vector<glm::vec3>  ||  std::vector<glm::uvec3> are normaly used
  */
    template<class T> void UnitGridGeometry2D(int x, int y, T vertices){
        for (int j = 0; j <= y; ++j)
        {
            for (int i = 0; i <= x; ++i)
            {
                GLfloat x_location = (float)i / (float)x;
                GLfloat y_location = (float)j / (float)y;
                GLfloat z_location = 0;

                //New location added to the grid
                //TODO: find out how this workes
                vertices.push_back(glm::vec3(x_location * 2.0f - 1.0f, y_location * 2.0f - 1.0f, z_location));

                std::cout << "x_location : " << x_location << std::endl;
                std::cout << "y_location : " << y_location << std::endl;
                std::cout << "z_location : " << z_location << std::endl;
                std::cout << "_______________" << std::endl;
            }
            std::cout << "#################" << std::endl;
        }

        //Creates two triangles to make up the square of the grid
        /*
        for (int j = 0; j < y; ++j) //Goes through all of in height
        {
            for (int i = 0; i < x; ++i) //Goes through the width 
            {
                int row1 = j * (x + 1);
                int row2 = (j + 1) * (x + 1);

                // triangle 1
                indices.push_back(glm::uvec3(row1 + i, row1 + i + 1, row2 + i));

                // triangle 2
                indices.push_back(glm::uvec3(row1 + i, row2 + i + 1, row2 + i));
            }
        }*/
    };

    //For making squares in the grid    :: GL_LINES
    template<class T> void UnitGridTopologySquare(int x, int y, T indices){
        for (int j = 0; j < y; ++j) //Goes through all of in height
        {
            std::cout << j << std::endl;
            std::cout << "=================" << std::endl;
            for (int i = 0; i < x; ++i) //Goes through the width 
            {
                int row1 = j * (x + 1);
                int row2 = (j + 1) * (x + 1);

                
                

                // triangle 1
                indices.push_back(glm::uvec3(row1 + i, row1 + i + 1, row2 + i));
                std::cout << "row1 + i : " << row1 + i << std::endl;
                std::cout << "row1 + i + 1 : " << row1 + i + 1 << std::endl;
                std::cout << "row2 + i : " << row2 + i << std::endl;
                std::cout <<"_______________" << std::endl;

                // triangle 2
                indices.push_back(glm::uvec3(row1 + i, row2 + i + 1, row2 + i));
                std::cout << "row1 + i : " << row1 + i << std::endl;
                std::cout << "row2 + i + 1 : " << row2 + i + 1 << std::endl;
                std::cout << "row2 + i : " << row2 + i << std::endl;
                std::cout <<"_______________" << std::endl;
            }
            
        }
    }

    //Function to make triangles in grid
    template<class T> void UnitGridTopologyTriangles(int x, int y, T indices){
        //Creates two triangles to make up the square of the grid
        for (int j = 0; j < y; ++j) //Goes through all of in height
        {
            for (int i = 0; i < x; ++i) //Goes through the width 
            {
                int row1 = j * (x + 1);
                int row2 = (j + 1) * (x + 1);

                // triangle 1
                indices.push_back(glm::uvec3(row1 + i, row1 + i + 1, row2 + i));

                //indices.push_back(glm::uvec3(row1 + i, row2 + i + 1, row2 + i));

                // triangle 2
                indices.push_back(glm::uvec3(row1 + i, row2 + i + 1, row2 + i));
            }
        }
    }

    template <class T> T UnitGridTopologyTriangles2(int x, int y){
        float test[] = {(UnitTriangle2D[0]/x),(UnitTriangle2D[1]/y),
                        (UnitTriangle2D[2]/x),(UnitTriangle2D[3]/y),
                        (UnitTriangle2D[4]/x),(UnitTriangle2D[5]/y)};

        //std::cout << test[0] << std::endl;
        return test; 
    }
}
