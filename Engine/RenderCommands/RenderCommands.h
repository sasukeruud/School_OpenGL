#pragma once

#include <glad/glad.h>
#include "VertexArray.h"

namespace RenderCommands{
    /*
    * Clear buffer data
    */
    inline void Clear(GLuint mode = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT){ glClear(mode); }
    /*
    * Setts polygon mode with input given
    * face: the faces of vertecies
    * mode: how to render the primitives
    */
    inline void SetPolygonMode(GLenum face, GLenum mode){ glPolygonMode(face, mode); }
    /*
    * Setts polygon mode to just draw the frame
    */
    inline void SetWireframeMode(){glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);}
    /*
    * Sets polygon to fill in the primitive that's drawned 
    */
    inline void SetFillMode(){glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);}
    /*
    * Sets background color of the window
    */
    inline void SetClearColor(glm::vec3 color){glClearColor(color.x,color.y,color.z,1.0f);}
    /*
    * For rendering 3D
    */
    inline void DepthRendering(){glEnable(GL_DEPTH_TEST);}

    
    //inline void DrawIndex(const std::shared_ptr<VertexArray>& vao, GLenum primitive){ glDrawElements(primitive, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr); }

}