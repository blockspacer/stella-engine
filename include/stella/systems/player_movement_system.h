#pragma once

#include <entityx/entityx.h>

namespace ex = entityx;

namespace stella {
namespace graphics {
  class Display;
}
}

namespace stella {
namespace systems {
class PlayerMovementSystem : public ex::System<PlayerMovementSystem> {
public:
  PlayerMovementSystem(const int &boundx, stella::graphics::Display &display);
  ~PlayerMovementSystem();
  void update(ex::EntityManager &es, ex::EventManager &events,
              ex::TimeDelta dt) override;

	enum State {IDLE, RUNNING, JUMPING, FALLING};

private:
  void SetState(PlayerMovementSystem::State state, entityx::ComponentHandle<stella::components::AnimationsComponent, entityx::EntityManager> anims);

  const int BoundX;
	stella::graphics::Display &Display;
	State current_state = IDLE;
};
} // namespace systems
} // namespace stella
