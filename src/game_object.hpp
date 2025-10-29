#pragma  once

#include "component.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

public:
    void addComponent(std::shared_ptr<Component> new_component);
    void update(float elapsed_time);
    void draw(sf::VertexArray& canvas);

private:
    std::vector<std::shared_ptr<Component>> components_;
};