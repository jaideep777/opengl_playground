#include "../include/glinit.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// string errorString(GLenum err){
// 	if (err == GL_INVALID_ENUM) return "GL_INVALID_ENUM";
// 	else if (err == GL_INVALID_VALUE) return "GL_INVALID_VALUE";
// 	else if (err == GL_INVALID_OPERATION) return "GL_INVALID_OPERATION";
// 	else if (err == GL_STACK_OVERFLOW) return "GL_STACK_OVERFLOW";
// 	else if (err == GL_STACK_UNDERFLOW) return "GL_STACK_UNDERFLOW";
// 	else if (err == GL_OUT_OF_MEMORY) return "GL_OUT_OF_MEMORY";
// 	else return "NO ERROR"; 
// //	else if (err == GL_TABLE_TOO_LARGE) return "GL_TABLE_TOO_LARGE";	
// }

// TODO: Should there be a GLInterface class that controls the globals? 
//       e.g. It will store the active shapes list and active tools list, plus active window, active tool, active camera etc. 
//            Can also separate input form processing
// 		      Maybe not?
//            Maybe yes!

// void checkGLError(const char * file, int line){
// 	GLenum err;
// 	while((err = glGetError()) != GL_NO_ERROR){
// 		cout << file << ":" << line << "   Error: " << errorString(err) << endl;
// 	}
// }

// #define CHECK_GL_ERROR() checkGLError(__FILE__, __LINE__)


// void printStatus(const char *step, GLuint context, GLuint status){
// 	GLint result = GL_FALSE;
// 	CHECK_GL_ERROR();
// 	glGetShaderiv(context, status, &result);
// 	CHECK_GL_ERROR();
// 	if (result == GL_FALSE) {
// 		char buffer[1024];
// 		if (status == GL_COMPILE_STATUS)
// 			glGetShaderInfoLog(context, 1024, NULL, buffer);
// 		else
// 			glGetProgramInfoLog(context, 1024, NULL, buffer);
// 		if (buffer[0])
// 			fprintf(stderr, "%s: %s\n", step, buffer);
// 	}
// }


// GLuint loadShader(string filename, GLenum shader_type){
// 	cout << "Loading shader from " << filename << endl;
// 	ifstream fin(filename.c_str());
// 	string c((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
// 	const char * glsl_src = c.c_str();

// 	GLuint shader_id = glCreateShader(shader_type);
// 	glShaderSource(shader_id, 1, &glsl_src, NULL);
// 	glCompileShader(shader_id);
// 	printStatus(filename.c_str(), shader_id, GL_COMPILE_STATUS);
	
// 	return shader_id;
// }



void processInput(GLFWwindow *window);

// settings
// const unsigned int SCR_WIDTH = 800;
// const unsigned int SCR_HEIGHT = 600;

//const char *vertexShaderSource = "#version 330 core\n"
//    "layout (location = 0) in vec3 aPos;\n"
//    "void main()\n"
//    "{\n"
//    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//    "}\0";
//const char *fragmentShaderSource = "#version 330 core\n"
//    "out vec4 FragColor;\n"
//    "void main()\n"
//    "{\n"
//    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//    "}\n\0";

int main()
{

    // Initialise
    initQuickGL();

//	program = glCreateProgram();
//	glAttachShader(program, vertexShader);
//	glAttachShader(program, fragmentShader);
//	glLinkProgram(program);


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    }; 
    float colours [] = { //added for colours for vertices
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    // unsigned int VBO, VAO, EBO, CBO; //CBO: colours buffer object

    // // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    // glBindVertexArray(VAO);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ARRAY_BUFFER, CBO); //cbo addition
    // glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW); //cbo addition

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// glBindBuffer(GL_ARRAY_BUFFER, VBO);
 //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
 //    glEnableVertexAttribArray(0);

	// glBindBuffer(GL_ARRAY_BUFFER, CBO);
 //    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0); // for colours
 //    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //points: GL_POINTS
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}




