#include <core.hpp>

int main(){
 if(!glfwInit()){ 
   std::cout << "Failed Intiailizing GLFW.\n";
   return EXIT_FAILURE;
 }
 else {
  std::cout << "GLFW Initialized sucessufully\n";
 }


  GLFWwindow* window = glfwCreateWindow(800,600,"Test",NULL,NULL);


  if(!window){
     glfwTerminate();
     std::cerr << "Couldn't create window!\nExiting..\n";
     return EXIT_SUCCESS;
  }
  else{
    std::cout << "Created window Sucessfully\n";
  }

  glfwMakeContextCurrent(window);

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
