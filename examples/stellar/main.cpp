#include <iostream>
#include <stella/stella.h>

#include "game.h"

int main(int argc, char *argv[]) {
  GLboolean Keys[1024] = {0};
  stella::graphics::Display display(720, 405, "S T E L L A R", Keys);
  display.SetClearColor(0, 0, 0);

  // TODO Move this block to init on singleton class
  GLint tex_ids[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

  stella::graphics::Shader shader("assets/shaders/basic_shader.vsh",
                                  "assets/shaders/basic_shader.fsh");
  shader.Enable();
  shader.SetIntv("textures", tex_ids, 10);
  shader.Disable();
  // End of block

  Game game(display, &shader, (const bool *)Keys);

  while (display.IsRunning()) {
    display.Clear();

    game.Update(display.GetDT());
    display.Update();
  }

  return 0;
}
