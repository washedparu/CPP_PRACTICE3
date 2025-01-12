#include <core.hpp>

int main(){

 if(!glfwInit()){ 
   spdlog::error<const char*>("Failed Intiailizing GLFW.\n");
   return EXIT_FAILURE;
 }
 else {
  spdlog::info<const char*>("GLFW Initialized sucessufully\n");
 }


  GLFWwindow* window = glfwCreateWindow(800,600,"Test",NULL,NULL);

 
  if(!window){
     glfwTerminate();
     spdlog::error<const char*>("Couldn't create window!\n");
     return EXIT_SUCCESS;
  }
  else{
   spdlog::info<const char*>("Created window successfully\n");
  }

  glfwMakeContextCurrent(window);
  
  if(glewInit() != GLEW_OK){
    spdlog::error<const char*>("Couldn't initialize GLEW!\n");
    return EXIT_FAILURE;
  }
  else{
     spdlog::info<const char*>("GLEW Initialized successfully!");
  }

  while (!glfwWindowShouldClose(window)) { 
   glClear(GL_COLOR_BUFFER_BIT);
   
   glClearColor(0.1f,0.1f,0.1f,1.0f);
   glColor3f(0.0f,1.0f,0.0f);
   
   Core::drawGeometrie();

   glfwSwapBuffers(window);
 
   glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
