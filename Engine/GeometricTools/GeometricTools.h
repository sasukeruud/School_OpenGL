#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace GeometricTools{
  //Array for normalized triangle
  constexpr float UnitTriangle2D[3*2] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f};
  //Array for normalized square
  constexpr float UnitSquare2D[6*2] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f};
  //Color array for a triangle [3*3]
  constexpr float ColorTriangle2D[3*3] = {0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  //Color array for a square [3*4]
  constexpr float ColorSquare2D[3*4] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

  //std::vector<glm::vec3> vertices;      || std::vector<glm::uvec3> indices;

  /*
  * Template function to generate a grid in 2D
  * x is for how many across the width of the grid and y is for how many to create in the height.
  * std::vector<glm::vec3>  ||  std::vector<glm::uvec3> are normaly used
  */
  template<class T, class U> void UnitGridGeometry2D(int x, int y, T vertices, U indices){
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
            }
        }

        //Creates two triangles to make up the square of the grid
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
        }
  };
}
