#include "snake.h"

Snake::Snake(entityx::EntityManager &entities, const bool keys[1024]) : entities(entities), keys(keys){
	this->Velocity = 1;
	this->Dimension = 32;
	this->create(20);
}

Snake::~Snake() {
	delete SnakeTex;
}

void Snake::Update() {
	if (this->body.size() > 0) {
		entityx::ComponentHandle<MovementComponent> hmov = this->head.component<MovementComponent>();

		int lastDir = hmov->Direction;
		for (auto i = this->body.begin(); i != this->body.end(); ++i) {
			entityx::ComponentHandle<MovementComponent> mov = i->component<MovementComponent>();
			mov->NewDirection = lastDir;
			lastDir = mov->Direction;
		}
	}	
	else {
		std::cout << "LOST!" << std::endl;
	}
}

void Snake::create(size_t size) {
	SnakeTex = new stella::graphics::Texture("snake-tex", "assets/gfx/snake/snake.png");
	this->head = entities.create();

	this->head.assign<TextureComponent>(this->Dimension, this->Dimension, *SnakeTex, 0);
	this->head.assign<SpatialComponent>(this->Dimension, this->Dimension, 320, 320);
	this->head.assign<MovementComponent>(1, this->Velocity);
	this->head.assign<InputComponent>(keys);

	for (unsigned int i = 0; i < size; ++i) {
		this->AddBodyPart();
	}
}

void Snake::RemoveBodyPart() {
	assert(this->body.size() > 0);
	entityx::Entity& ent = this->body.back();
	ent.destroy();
	this->body.pop_back();

	entityx::Entity& bent = this->body.back();
	entityx::ComponentHandle<TextureComponent> tex = bent.component<TextureComponent>();
	tex->sprite->SetDirectFrame(2);
}

void Snake::AddBodyPart() {
	entityx::ComponentHandle<TextureComponent> tex;
	entityx::ComponentHandle<SpatialComponent> spa;
	entityx::ComponentHandle<MovementComponent> mov;

	if (this->body.size() > 0) {
		entityx::Entity& bent = this->body.back();
		tex = bent.component<TextureComponent>();
		spa = bent.component<SpatialComponent>();
		mov = bent.component<MovementComponent>();
		tex->sprite->SetDirectFrame(1);
	}
	else {
		spa = this->head.component<SpatialComponent>();
		mov = this->head.component<MovementComponent>();
	}

	entityx::Entity body_part = entities.create();
	switch(mov->Direction) {
		case 0:
			body_part.assign<SpatialComponent>(this->Dimension, this->Dimension, spa->x, spa->y + this->Dimension);
			break;
		case 1:
			body_part.assign<SpatialComponent>(this->Dimension, this->Dimension, spa->x - this->Dimension, spa->y);
			break;
		case 2:
			body_part.assign<SpatialComponent>(this->Dimension, this->Dimension, spa->x, spa->y - this->Dimension);
			break;
		case 3:
			body_part.assign<SpatialComponent>(this->Dimension, this->Dimension, spa->x + this->Dimension, spa->y);
			break;
	}

	body_part.assign<MovementComponent>(mov->Direction, this->Velocity);
	body_part.assign<TextureComponent>(this->Dimension, this->Dimension, *SnakeTex, 2);
	this->body.push_back(body_part);
}

