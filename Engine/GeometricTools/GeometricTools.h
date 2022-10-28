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

    //https://stackoverflow.com/questions/58494179/how-to-create-a-grid-in-opengl-and-drawing-it-with-lines
    template<class T, class U> void GenGrid(int N, T &verticies, U &indicies){
        int half_N = N/2;
        /*for (int j = -N/2; j <= N/2; j++)
        {
            for (int i = -N/2; i <= N/2; i++)
            {
                float x = (float)i/(float)N;
                float y = (float)j/(float)N;
                //float z = sin(x*2.0f*3.141526f) * sin(y*2.0f*3.141526f) * 0.1f;
                float z = 0;
                verticies.push_back(glm::vec3(x,y,z));
            }
            
        }

        for (int j = 0; j < N; j++)
        {
            for (int i = 0; i < N; i++)
            {
                int row1 = j * (N+1);
                int row2 = (j+1) * (N+1);

                //Triangle 1
                indicies.push_back(glm::uvec4(row1+i, row1+i+1, row1+i+1, row2+i+1));

                //Triangle 2
                indicies.push_back(glm::uvec4(row2+i+1, row2+i, row2+i, row1+i));
            }
            
        }*/
        for (float j = 0; j <= N; j++)
        {
            for (float i = 0; i <= N; i++)
            {
                float x = (float)i/(float)N;
                float y = (float)j/(float)N;
                //float z = sin(x*2.0f*3.141526f) * sin(y*2.0f*3.141526f) * 0.1f;
                float z = 0;
                verticies.push_back(glm::vec3(x,y,z));
            }
            
        }

        for (int j = 0; j < N; j++)
        {
            for (int i = 0; i < N; i++)
            {
                int row1 = j * (N+1);
                int row2 = (j+1) * (N+1);

                //Triangle 1
                indicies.push_back(glm::uvec3(row1 + i,row1 + i + 1,row2 + i + 1));

                //Triangle 2
                indicies.push_back(glm::uvec3(row1 + i, row2 + i + 1, row2 + i));
            }
            
        }
    }

    template<class T, class U> void GenColorGrid(int N, T &verticies, U &indicies){
                int half_N = N/2;
        for (float j = -(N/2); j <= (float)N/2; j++)
        {
            for (float i = -(N/2); i <= N/2; i++)
            {
                float r = 0.0f;
                float g = 0.0f;
                float b = 0.0f;
                verticies.push_back(glm::vec3(r,g,b));
            }
            
        }
    }

    template<class T, class U> void GenGrid(int X, int Y, T &verticies, U &indices){
        for (size_t i = 0; i < X/2; i++)
        {
            for (size_t j = 0; j < Y/2; j++)
            {
                float x_location = (float)i/(float)X;
                float y_location = (float)j/(float)Y;
                float z_location = sin(x*2.0f*3.141526f) * sin(y*2.0f*3.141526f) * 0.1f;
                verticies.push_back(glm::vec3(x_location,y_location,z_location));
            }
            
        }
        
        for (int j = 0; j < X; j++)
        {
            for (int i = 0; i < Y; i++)
            {
                int row1 = j * (X+1);
                int row2 = (j+1) * (X+1);

                //Triangle 1
                indicies.push_back(glm::uvec3(row1 + i,row1 + i + 1,row2 + i + 1));

                //Triangle 2
                indicies.push_back(glm::uvec3(row1 + i, row2 + i + 1, row2 + i));
            }
            
        }
    }
}
