#pragma once

namespace stella
{
namespace components
{
  struct PositionComponent
  {
    PositionComponent (float x, float y, float z = 0.f) : x (x), y (y), z (z), last_x (x), last_y (y), last_z (z) {}
    float x, y, z;
    float last_x, last_y, last_z;

    const bool has_changed() const
    {
      return ((last_x != x) || (last_y != y) || (last_z != z));
    }
  };
} // namespace components
} // namespace stella
