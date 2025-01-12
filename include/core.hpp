#pragma once
// includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <iostream>

// core namespace

namespace Core
{
    void drawGeometrie(){
        glBegin(GL_QUADS);
            glVertex2f(-0.5f,-0.5f); 
            glVertex2f(0.5f,-0.5f); 
            glVertex2f(0.5f,0.5f); 
            glVertex2f(-0.5f,0.5f);  
             glEnd();
   
            glColor3f(0.0f,-0.5f,0.0f);
            glBegin(GL_TRIANGLES);
            glVertex2f(0.0f,0.5f);
            glVertex2f(-0.5f,-0.5f);
            glVertex2f(0.5f,-0.5f);
        glEnd();
    }
} 
