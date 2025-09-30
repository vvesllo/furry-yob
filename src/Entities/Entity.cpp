#include "../../include/Entities/Entity.h"
#include "../../include/Utils/Vector.h"
#include "../../include/Core/ResourceManager.h"
#include "../../include/Core/EntityManager.h"
#include "../../include/Core/LevelManager.h"

#include <print>

Entity::Entity(const std::string& texture_name, const sf::Color& color, const sf::FloatRect& rect)
    : DynamicBody(texture_name, color, rect)
{
    m_invincibility_time = 0.f;
}

void Entity::update(const float& dt)
{
    if (entity_data.health_points <= 0)
    {
        destroy();
        return;
    }

    m_invincibility_time = (float)std::max(0.f, (float)m_invincibility_time - dt);
    velocity.terminal = sf::Vector2f{};

    AI(dt);

    velocity.current = VectorUtils::lerp(
        velocity.current, 
        velocity.terminal, 
        entity_data.acceleration > 0 ? entity_data.acceleration * dt : 1.f
    );

    const float current_speed = velocity.current.length();
    const double additional_transformation_value = std::sin(m_moving_frames / 5.f);

    if (current_speed < 0.05f)
        m_moving_frames = 0;
    else
        ++m_moving_frames;

    rect.position += entity_data.speed * velocity.current * dt;
    
    sprite->setRotation(sf::degrees(current_speed * additional_transformation_value * 10.f));
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

void Entity::dash(const sf::Vector2f& direction)
{
    m_invincibility_time = .2f;
    velocity.current = direction;
}

const EntityType Entity::getType()
{
    return entity_data.type;
}

void Entity::damage(const float& damage_amount)
{
    m_invincibility_time = .05f;
    entity_data.health_points -= damage_amount;

    LevelManager::getInstance().addBlood(getCenter(), m_color);

    if (entity_data.health_points <= 0)
        destroy();
}

void Entity::heal(const float& heal_amount)
{
    entity_data.health_points = std::min(entity_data.health_points + heal_amount, entity_data.max_health_points);
}

bool Entity::isInvincible()
{
    return m_invincibility_time > 0.f;
}

const sf::Vector2f Entity::getVelocity()
{
    return velocity.current;
}
