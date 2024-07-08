
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream> 
using namespace std;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();
    cout << glGetString(GL_VERSION) << endl;

    unsigned int buffer1;
    glGenBuffers(1, &buffer1);
    //creates a buffer object with id buffer

    glBindBuffer(GL_ARRAY_BUFFER, buffer1);
    //this binds the buffer object linked with unsigned int buffer to the array buffer (Array buffer is the target)
    float points[6] = {
        0.0f, -0.5f,
        -0.5f, -0.5f,
        0.0f, 0.5f
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(points),points,GL_STATIC_DRAW);
    //Here i copied all the data from the points array into the GLarrayBuffer which is bound to the unsigned int buffer ; 

    glEnableVertexAttribArray(0);
        //Allow

    glVertexAttribPointer(0, 2, GL_FLOAT,GL_FALSE, sizeof(float) * 2, 0); 
    // index 
    // size = number of data items in each vertex attribute
    // type =    Data type of each attribute
    // If it has to be normalised or not 
    // stride = size of each set of attributes ( x , y ) , texture ... aka vertex 
    // pointer = size of each attribute 


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
  
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}