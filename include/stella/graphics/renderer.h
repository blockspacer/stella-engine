#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "sprite.h"
#include "texture.h"

#define MAX_SPRITES 10000
#define VERTEX_SIZE sizeof(VertexData)
#define SPRITE_SIZE 4 * VERTEX_SIZE
#define BUFFER_SIZE MAX_SPRITES * SPRITE_SIZE
#define INDICES_SIZE 6 * MAX_SPRITES

namespace stella {
namespace graphics {
enum Index { VERTEX_INDEX, UV_INDEX, TID_INDEX, COLOR_INDEX };

class Renderer {
public:
  Renderer();
  ~Renderer();
  void Begin();
  void Submit(const Sprite &sprite);
  void End();
  void Draw();

  void PushTransformation(glm::mat4& mat, bool override = false);
	void PopTransformation();

private:
  VertexData *VertexBuffer;
  GLuint VAO, VBO, EBO;
	std::vector<glm::mat4> TransformationStack;
	glm::mat4* TransformationBack;
  GLsizei IndexCount;
  std::vector<Texture *> Textures;
  bool TexturesBinded;

  void init();
};
} // namespace graphics
} // namespace stella
