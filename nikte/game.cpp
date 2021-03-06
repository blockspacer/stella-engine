#include "game.h"
#include <random>

namespace nikte
{
Game::Game() : stella::core::Game (896, 504, "Nikte")
{
  m_script_api.set_function ("e_get_player_id", [this]() { return m_player.entity; });
  m_script_api.run_script ("scripts/main.lua");
  m_script_api.run_function ("load_assets");

  this->add_system<stella::system::Render> (m_registry, m_textures, m_display);
  this->add_system<stella::system::Color> (m_registry);
  this->add_system<stella::system::Timer> (m_registry);
  this->add_system<stella::system::Animation> (m_registry);
  this->add_system<stella::system::Physics> (m_tile_map, m_registry);
  this->add_system<stella::system::Tile> (m_tile_map, m_camera, m_registry);
  this->add_system<stella::system::Text> (m_registry, m_fonts);
  this->add_system<stella::system::Speech>();
  this->add_system<stella::system::NPC> (m_registry, m_player.entity);
  this->add_system<stella::system::CharacterAnimation>();

  m_tile_map.create_tile_entities (0, m_display.GetWidth(), 0, m_display.GetHeight());
  m_script_api.set_variable<int> ("e_map_width", m_tile_map.width());
  m_script_api.set_variable<int> ("e_map_height", m_tile_map.height());
  m_script_api.set_variable<int> ("e_screen_width", this->width());
  m_script_api.set_variable<int> ("e_screen_height", this->height());

  m_script_api.run_function ("load_game");
  //m_load_flowers();

  this->update_systems (0.0);
}

Game::~Game()
{
  // m_script_api.run_function("quit_game");
}

void Game::update (const double dt)
{
  this->update_systems (dt);

  m_player.update();
  m_script_api.run_function ("update_game", dt);
  m_script_api.run_function ("render_game", dt);
}

void Game::m_load_flowers()
{
  int number_of_flowers = 500;
  int n = 0;

  std::uniform_int_distribution<int> m_x_distribution{0, static_cast<int>(m_tile_map.width()*m_tile_map.tile_dimension())};
  std::uniform_int_distribution<int> m_y_distribution{0, static_cast<int>(m_tile_map.height()*m_tile_map.tile_dimension())};
  
  while (n < number_of_flowers)
  {

    int random_x = m_x_distribution(m_generator);
    int random_y = m_y_distribution(m_generator);

    for (const auto& layer : m_tile_map.layers)
    {
      const auto& tile = layer->get_value(random_x/m_tile_map.tile_dimension(), random_y/m_tile_map.tile_dimension());
      if (tile.value == 1)
      {
        m_load_flower(random_x, random_y);
        ++n;
        break;
      }
    }

  }
}

void Game::m_load_flower(const int x, const int y)
{ 
  int frame = 15;
  switch (m_flower_frame_distribution(m_generator))
  {
    case 0:
      frame = 10;
      break;
    case 1:
      frame = 10;
      break;
    case 2:
      frame = 15;
      break;
    default:
      break;
  }

  auto flower = m_registry.create();
  m_registry.assign<stella::component::Position>(flower, x, y, 2);
  m_registry.assign<stella::component::Dimension>(flower, 16, 16);
  m_registry.assign<stella::component::Sprite>(flower, "flowers", glm::vec2(16.f, 16.f), "tiles", frame);
}
} // namespace nikte
