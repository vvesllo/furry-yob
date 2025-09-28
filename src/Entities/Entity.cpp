#include "../../include/Entities/Entity.h"
#include "../../include/Utils/Vector.h"
#include "../../include/Core/ResourceManager.h"
#include "../../include/Core/EntityManager.h"

#include <print>

Entity::Entity(const std::string& texture_name, const sf::Color& color, const sf::FloatRect& rect)
    : DynamicBody(texture_name, color, rect)
{

}

void Entity::update(const float& dt)
{
    if (entity_data.health_points <= 0)
    {
        destroy();
        return;
    }

    velocity.terminal = sf::Vector2f{};

    AI(dt);

    velocity.current = VectorUtils::lerp(
        velocity.current, 
        velocity.terminal, 
        entity_data.acceleration > 0 ? entity_data.acceleration * dt : 1.f
    );

    const float current_speed = velocity.current.length();
    const double additional_transformation_value = current_speed * std::sin(m_moving_frames_amount / 5.f);

    if (current_speed < 0.05f)
        m_moving_frames_amount = 0;
    else
        ++m_moving_frames_amount;

    rect.position += entity_data.speed * velocity.current * dt;
    
    sprite->setRotation(sf::degrees(additional_transformation_value * 10.f));
    sprite->setPosition(
        rect.position + rect.size / 2.f - sf::Vector2f(
            0, 5.f * std::abs(additional_transformation_value)
        )
    );
}

void Entity::lookAt(const LookingDirection direction)
{
    switch (direction)
    {
    case LookingDirection::Right:
        sprite->setScale({ 1, 1 });
        break;
    case LookingDirection::Left:
        sprite->setScale({-1, 1 });
        break;
    }
    entity_data.looking_direction = direction;
}

const EntityType Entity::getType()
{
    return entity_data.type;
}

void Entity::damage(const float& damage_amount)
{
    entity_data.health_points -= damage_amount;
    if (entity_data.health_points <= 0)
        destroy();
}

void Entity::heal(const float& heal_amount)
{
    entity_data.health_points += heal_amount;
}