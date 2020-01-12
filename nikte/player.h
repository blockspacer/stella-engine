#pragma once

#include <stella/components.h>
#include <SDL2/SDL.h>

namespace stella
{
namespace graphics
{

  class Display;

}
}

class Player
{
  public:
    entt::registry &m_registry;
    enum State {IDLE, RUNNING, JUMPING, FALLING};
    const entt::registry::entity_type entity = m_registry.create();
  private:
    stella::graphics::Display &Display;
    State current_state = IDLE;

  public:
    Player(entt::registry &registry, stella::graphics::Display &display) 
      : m_registry(registry), Display(display)
    { 
      
    }

    ~Player() { }

    void update()
    {
      auto &body = m_registry.get<stella::components::Body2DComponent>(entity);
      
      //auto previous_state = this->current_state;

      // Handle input
      if (this->Display.IsKeyDown(SDL_SCANCODE_LEFT)) 
      {
        body.Body->MoveLeft();
      }

      if (this->Display.IsKeyDown(SDL_SCANCODE_RIGHT))
      {
        body.Body->MoveRight();
      }

      if (this->Display.IsKeyDown(SDL_SCANCODE_UP))
      {
        body.Body->MoveTop();
      }

      if (this->Display.IsKeyDown(SDL_SCANCODE_DOWN))
      {
        body.Body->MoveBottom();
      }

      //auto &anims = m_registry.get<stella::components::AnimationsComponent>(entity);
      //this->SetState(this->current_state, anims, previous_state);
    }

  private:
    void SetState(Player::State state, stella::components::AnimationsComponent &anims, Player::State previous_state)
    {
      if (previous_state != this->current_state && previous_state == RUNNING)
      {
        
      }

      switch(state)
      {
        case RUNNING:
          //anims.current_animation = "run";
          break;
        case JUMPING:
          //anims.current_animation = "jump";
          break;
        case FALLING:
          //anims.current_animation = "fall";
          break;
        case IDLE:
          //anims.current_animation = "idle";
          break;
        default:
          break;
      }
    }
};
