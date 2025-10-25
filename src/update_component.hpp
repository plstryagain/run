#pragma once

#include "component.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

class LevelUpdateComponent;
class PlayerUpdateComponent;
class UpdateComponent : public Component
{
public:
    UpdateComponent();
    virtual ~UpdateComponent();

public:
    virtual void assemble(std::shared_ptr<LevelUpdateComponent> level_update,
                            std::shared_ptr<PlayerUpdateComponent> player_update) = 0;
    virtual void update(float time_since_last_update) = 0;
};