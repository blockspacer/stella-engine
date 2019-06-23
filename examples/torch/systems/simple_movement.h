#pragma once

#include <entityx/entityx.h>
namespace ex = entityx;

class SimpleMovementSystem : public ex::System<SimpleMovementSystem> {
public:
  SimpleMovementSystem();
  ~SimpleMovementSystem();
  void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) override;

private:
};

