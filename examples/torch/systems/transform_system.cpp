#include "transform_system.h"

#include "../components/game_components.h"

TransformSystem::TransformSystem() {

}

TransformSystem::~TransformSystem() {

}

void TransformSystem::update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) {
  es.each<TransformComponent, DimensionComponent, SpriteComponent>([this](ex::Entity entity,
                                                      TransformComponent &trans,
                                                      DimensionComponent &dim,
                                                      SpriteComponent &spr) {

    if ((int)(spr.Sprite->RealDimensions.x) != dim.w) {
      trans.Scale.x *= static_cast<float>(dim.w/spr.Sprite->Dimensions.x);
      spr.Sprite->RealDimensions.x = dim.w;
    }
    if ((int)(spr.Sprite->RealDimensions.y) != dim.h) {
      trans.Scale.y *= static_cast<double>(dim.h/spr.Sprite->Dimensions.y);
      spr.Sprite->RealDimensions.y = dim.h;
    }
    spr.Sprite->SetScale(trans.Scale);
    spr.Sprite->SetRotation(trans.Rotation);
  });
}

