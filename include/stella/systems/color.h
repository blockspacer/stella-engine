#pragma once

#include "./system.h"
#include "stella/components/color.h"
#include "stella/components/sprite.h"

namespace stella
{
namespace system
{
  class Color : public System
  {
  public:
    Color (entt::registry& registry)
    {
      registry.on_construct<component::Color>().connect<&Color::initialize_color> (this);
    }

    ~Color() override {}

    void update (entt::registry& registry, const double dt) override
    {
      //   registry.group<component::Color>(entt::get<component::Sprite>).each([&registry](auto
      //   entity, auto &color, auto &sprite)
      //   {

      //   });
    }

  private:
    Color() = delete;

    void initialize_color (entt::registry& registry, entt::entity entity, component::Color& color)
    {
      if (registry.has<component::Sprite> (entity))
      {
        auto sprite = registry.get<component::Sprite> (entity);
        sprite.sprite->SetDirectColor (color.int_color);
      }
    }
  };
} // namespace system
} // namespace stella
