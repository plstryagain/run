#pragma once

class Component
{
public:
    Component();
    virtual ~Component();

public:
    bool isUpdateComponent() const;
    bool isGraphicsComponent() const;

protected:
    bool is_update_component_ = false;
    bool is_graphics_component_ = false;
};