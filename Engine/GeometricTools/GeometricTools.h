#ifndef GEOMETRICTOOLS_H_
#define GEOMETRICTOOLS_H_

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
    constexpr float UnitSquare2D[6*3] = {   -0.5f, -0.5f, .0f,
	                                         0.5f, -0.5f, .0f,
	                                         0.5f,  0.5f, .0f,
	                                         0.5f,  0.5f, .0f,
	                                        -0.5f,  0.5f, .0f,
	                                        -0.5f, -0.5f, .0f };
    //Color array for a triangle [3*3]
    constexpr float ColorTriangle2D[3*3] = {    1.0f, 0.0f, 0.0f,
                                                0.0f, 1.0f, 0.0f, 
                                                0.0f, 0.0f, 1.0f};
    //Color array for a square [3*4]
    constexpr float ColorSquare2D[3*6] = {  .0f, 1.0f, 0.0f, 
                                            0.0f, 1.0f, 0.0f, 
                                            0.0f, 1.0f, .0f, 
                                            0.0f, 1.0f, 0.0f,
                                            0.0f, 1.0f, 0.0f,
                                            0.0f, 1.0f, 0.0f};
    //Cube vertecies
    constexpr float UnitCube[6*6*3] = { -0.5f, -0.5f, -0.5f,
	                                     0.5f, -0.5f, -0.5f,
	                                     0.5f,  0.5f, -0.5f,
	                                     0.5f,  0.5f, -0.5f,
	                                    -0.5f,  0.5f, -0.5f,
	                                    -0.5f, -0.5f, -0.5f,

	                                    -0.5f, -0.5f,  0.5f,
	                                     0.5f, -0.5f,  0.5f,
	                                     0.5f,  0.5f,  0.5f,
	                                     0.5f,  0.5f,  0.5f,
                                        -0.5f,  0.5f,  0.5f,
                                        -0.5f, -0.5f,  0.5f,

	                                    -0.5f,  0.5f,  0.5f,
	                                    -0.5f,  0.5f, -0.5f,
	                                    -0.5f, -0.5f, -0.5f,
	                                    -0.5f, -0.5f, -0.5f,
	                                    -0.5f, -0.5f,  0.5f,
	                                    -0.5f,  0.5f,  0.5f,

	                                     0.5f,  0.5f,  0.5f,
	                                     0.5f,  0.5f, -0.5f,
                                         0.5f, -0.5f, -0.5f,
	                                     0.5f, -0.5f, -0.5f,
	                                     0.5f, -0.5f,  0.5f,
                                         0.5f,  0.5f,  0.5f,

	                                    -0.5f, -0.5f, -0.5f,
	                                     0.5f, -0.5f, -0.5f,
	                                     0.5f, -0.5f,  0.5f,
	                                     0.5f, -0.5f,  0.5f,
	                                    -0.5f, -0.5f,  0.5f,
	                                    -0.5f, -0.5f, -0.5f,

	                                    -0.5f,  0.5f, -0.5f,
	                                     0.5f,  0.5f, -0.5f,
                                         0.5f,  0.5f,  0.5f,
	                                     0.5f,  0.5f,  0.5f,
	                                    -0.5f,  0.5f,  0.5f,
	                                    -0.5f,  0.5f, -0.5f
	                                    };

    //https://stackoverflow.com/questions/58494179/how-to-create-a-grid-in-opengl-and-drawing-it-with-lines
    template<class T, class U> void GenGrid(int N, T &verticies, U &indicies){
        int half_N = N/2;

        for (float j = 0; j <= N; j++)
        {
            for (float i = 0; i <= N; i++)
            {
                float x = (float)i/(float)N;
                float y = (float)j/(float)N;
                //float z = sin(x*2.0f*3.141526f) * sin(y*2.0f*3.141526f) * 0.1f;
                float z = 0;
                float t_x = (float)i/(float)N;
                float t_y = (float)j/(float)N;
                verticies.push_back(glm::vec3(x,y,z));
                //verticies.push_back(glm::vec4(x,y,t_x,t_y));
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

    //https://stackoverflow.com/questions/58494179/how-to-create-a-grid-in-opengl-and-drawing-it-with-lines
    template<class T, class U> void GenGridTexture(int N, T &verticies, U &indicies){
        int half_N = N/2;
        for (float j = 0; j <= N; j++)
        {
            for (float i = 0; i <= N; i++)
            {
                float x = (float)i/(float)N;
                float y = (float)j/(float)N;
                //float z = sin(x*2.0f*3.141526f) * sin(y*2.0f*3.141526f) * 0.1f;
                float z = 0;
                float t_x = (float)i/(float)N;
                float t_y = (float)j/(float)N;
                verticies.push_back(glm::vec4(x,y,t_x,t_y));
                //verticies.push_back(glm::vec4(x,y,t_x,t_y));
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

    template<class T, class U> void GenGridT(int N, T &verticies, U &indicies){
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
}
#endif GEOMETRICTOOLS_H_