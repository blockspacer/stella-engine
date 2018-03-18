#pragma once

#include "renderable.h"
#include "spritesheet.h"
#include "animator.h"

namespace stella { namespace graphics { 
  struct VertexData
  {
    glm::vec3 vertex;
    glm::vec2 uv;
    GLfloat tid;
    unsigned int color;
  };

  class Sprite : public Renderable
  {
    public:
      Animator Animations;

      Sprite(GLint x, GLint y, Texture &texture, const std::vector<GLuint> &frames);
      Sprite(GLint x, GLint y, Texture &texture, GLuint frame = 0);
      Sprite(GLint x, GLint y, GLint w, GLint h, Texture &texture, GLuint frame = 0);
      ~Sprite();

      void Update();

      // Getters
      inline const glm::vec4 GetColor() const { return Color; }
      inline const GLuint GetCurrentFrame() const { return Frame; }
      inline const SpriteSheet GetSpriteSheet() const { return *Sprites; }
      inline const glm::vec2 GetFrameCoords() const { return Sprites->GetUV(this->Frame); }

      // Setters
      void SetColor(int r, int g, int b) { Color.x = r/255.0f; Color.y = g/255.0f; Color.z = b/255.0f; }
      void SetFrame(GLuint frame);
      void SetDirectFrame(GLuint frame);

    private:
      glm::vec4 Color;
      std::vector<GLuint> Frames;
      GLuint Frame, NumberOfFrames;
      SpriteSheet* Sprites;
  };
} }

