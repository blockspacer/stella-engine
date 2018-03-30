#pragma once

#include <string>
#include <array>

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

namespace stella {
namespace graphics {
class Display {
public:
  Display(GLuint width, GLuint height, const std::string &title);
  ~Display();
  bool IsRunning();
  void Update();
  void Clear();
  void SetClearColor(int r, int g, int b);
  void SetClearColor(GLfloat x, GLfloat y, GLfloat z);
  GLuint GetWidth();
  GLuint GetHeight();
  GLfloat GetTime() { return (GLfloat)SDL_GetTicks(); }
  GLuint GetFrame() { return Frame; }
  GLfloat GetDT() { return DT; }
  GLfloat getFPS();
  void GetMousePos(double &mx, double &my);
	bool IsKeyDown(int key);

private:
  GLuint Width, Height, Frame, LastFrame;

  GLfloat LastTime, LastFPSCheck, DT;
  std::string Title;
  SDL_Window *Window;
  bool Running;
  glm::vec3 ClearColor;

  void updateInput();
  void getDT();
  void checkViewportProportions();
  static void inputCallback(SDL_Window *window, int key, int scancode,
                            int action, int mode);
  static void mouseCallback(SDL_Window *window, double xpos, double ypos);
  static void windowSizeCallback(SDL_Window *window, int width, int height);
  static void errorCallback(int error, const char *description);
};
} // namespace graphics
} // namespace stella
