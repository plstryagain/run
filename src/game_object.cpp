#include "game_object.hpp"
#include "update_component.hpp"
#include "graphics_component.hpp"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}


void GameObject::addComponent(std::shared_ptr<Component> new_component)
{
    components_.push_back(new_component);
}

void GameObject::update(float elapsed_time)
{
    for (auto& component : components_) {
        if (component->isUpdateComponent()) {
            std::static_pointer_cast<UpdateComponent>(component)->update(elapsed_time);
        }
    }
}

void GameObject::draw(sf::VertexArray& canvas)
{
    for (auto& component : components_) {
        if (component->isGraphicsComponent()) {
            std::static_pointer_cast<GraphicsComponent>(component)->draw(canvas);
        }
    }
}
