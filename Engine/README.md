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
Not implemented yet

# Shaders
Not implemented yet