#pragma once

#include "renderable.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>

namespace stella { namespace graphics{
  class Text : public Renderable
  {
    public:
      Text(std::string text);
      ~Text();

      void Render();

    private:
      std::string TextString;
  };
} }
