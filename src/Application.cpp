
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream> 
#include <string>

using namespace std;

static unsigned int CompileShader( unsigned int type , const string& source ) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    // returns the pointer to the character at the first pos of the string 
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result; 
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length; 
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* output = (char*)calloc(length, sizeof(char));
        glGetShaderInfoLog(id, length, &length, output);
        cout << "Failed to compile " << output << endl;
        glDeleteShader(id);
        free(output);
        return 0;

    }

    return id;
}


static unsigned int CreateShader(const string& vertexshader, const string& fragmentshader) {
    unsigned int program = glCreateProgram(); 
    unsigned int vs = CompileShader(GL_VERTEX_SHADER , vertexshader );
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentshader);
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
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

    string vertexshader = "#version 330 core \n"
        "layout(location = 0) in vec4 points ; \n"
        "void main () {\n"
        "gl_Position = points; \n "
        "}\n"; 


    string fragmentshader = "#version 330 core \n"

        "  layout(location = 0) out vec4 color ; \n"
        "void main () {\n"
        "color = vec4(1.0, 0.0, 0.0, 1.0); \n"
        "}\n";

    unsigned int shader = CreateShader(vertexshader, fragmentshader);
    glUseProgram(shader);

        

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