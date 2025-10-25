#include "component.hpp"

Component::Component()
{

}

Component::~Component()
{

}

bool Component::isGraphicsComponent() const
{
    return is_graphics_component_;
}

bool Component::isUpdateComponent() const
{
    return is_update_component_;
}