#include "factory.hpp"
#include "level_update_component.hpp"
#include "player_graphics_component.hpp"
#include "player_update_component.hpp"
#include "input_dispatcher.hpp"

#include <iostream>
#include <memory>

Factory::Factory(sf::RenderWindow* window)
    : window_{window},texture_{new sf::Texture{}}
{
    if (!texture_->loadFromFile("assets/graphics/texture.png")) {
        std::cout << "Texture not loaded!" << std::endl;
        return;
    }
}

Factory::~Factory()
{

}

void Factory::loadLevel(std::vector<GameObject>& game_objects, sf::VertexArray& canvas, InputDispatcher& input_dispatcher)
{
    GameObject level;
    std::shared_ptr<LevelUpdateComponent> level_update_component = std::make_shared<LevelUpdateComponent>();
    level.addComponent(level_update_component);
    game_objects.push_back(level);

    GameObject player;
    std::shared_ptr<PlayerUpdateComponent> player_update_component = 
        std::make_shared<PlayerUpdateComponent>();
    player_update_component->assemble(level_update_component, nullptr);
    player.addComponent(player_update_component);
    input_dispatcher.registerNewInputReceiver(player_update_component->getInputReceiver());

    std::shared_ptr<PlayerGraphicsComponent> player_graphics_component = 
        std::make_shared<PlayerGraphicsComponent>();
    player_graphics_component->assemble(canvas, player_update_component, 
        sf::IntRect{PLAYER_TEX_LEFT, PLAYER_TEX_TOP, PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT});
    player.addComponent(player_graphics_component);
    game_objects.push_back(player);

    level_update_component->assemble(nullptr, player_update_component);
}