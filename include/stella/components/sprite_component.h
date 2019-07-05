#pragma once

#include <string>

#include <glm/glm.hpp>
#include <stella/stella.h>

namespace stella {
namespace components {
struct SpriteComponent {
  //inline explicit SpriteComponent(const std::string &tex_name) : TexName(tex_name) { }
  //inline SpriteComponent(const std::string &tex_name, glm::vec2 frame_dimensions, unsigned int frame = 0) : TexName(tex_name), FrameDimensions(frame_dimensions), Frame(frame) { }
  SpriteComponent(const std::string &tex_name, glm::vec2 frame_dimensions, std::string layer_id = "basic", unsigned frame = 0) : TexName(tex_name), FrameDimensions(frame_dimensions), LayerId(layer_id), Frame(frame) { }
  SpriteComponent(const std::string &tex_name, std::string layer_id = "basic") : TexName(tex_name), LayerId(layer_id) { }
  //inline SpriteComponent(const std::string &tex_name, glm::vec2 frame_dimensions, std::string layer_id = "basic") : TexName(tex_name), FrameDimensions(frame_dimensions), LayerId(layer_id) { }

  std::shared_ptr<stella::graphics::Sprite> Sprite = nullptr;
	std::string TexName;
  glm::vec2 FrameDimensions = glm::vec2(0.f, 0.f);
  unsigned int Frame = 0;
  bool InLayer = false, Initialized = false, HasScaled = false;
  std::string LayerId;
};
} // namespace components
} // namespace stella

