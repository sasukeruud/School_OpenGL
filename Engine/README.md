# Engine

# Geometric tools
This will make it easier to formulate different arrays for drawing different shapes on the screen

# GLFWApplication
This part of the engine is to make it easier to run GLFW.

## Functions 

### virtual unsigned int ParseArguments(int argc, char** argv);
This function is to make it possible to pass arguments trough the terminal when starting the program.

Arguments implemented:
```
-c --console

-w --width "For deciding the width of the window"

-H --height "For deciding the height of the window"
```

### virtual unsigned Init();
This functions job is to initializes GLFW and GLAD for the rest of the program. Will terminate the process if anything goes wrong.

### virtual unsigned Run();
Loop for keeping the window open. Will also destroy the window and terminate the process when the loop have ended.

### virtual unsigned int Destroy();
For destroying the window and terminating the process.

# IndexBuffer
Not implemented yet

# VertexBuffer
For creating VBO(vertex buffer object) and binding it to a VAO(vertex array object).

## Functions
List over the funstions the class implements.

### VertexBuffer
Constructor for the class. There is three ways to create. The two under and a default that is not configurated yet. 

```
VertexBuffer(GLsizei size)

VertexBuffer(const void* vertices, GLsizei size)
```

### SetData
Function to set the spesific data that will be stored on the buffer. <br>
The function takes two paramenters to set the buffer data.
```
verticies	: Data that will be copied onto the buffer
target		: Spesify what type of buffer object to use.                Normaly GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
```

### Bind
Function to bind the VBO to a VAO attribute. <br>
Takes parameters to bind the VBO corectly.
```
index	: index number of vertex attribute
size	: How many components per vertex
TODO: add more options
``` 

### Unbind
For unbinding the currently bound buffer.

### BufferSubData
Not implemented yet

# Shaders
Not implemented yet