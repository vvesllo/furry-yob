#include "../../include/Entities/Player.h"
#include "../../include/Entities/Projectile.h"
#include "../../include/Entities/Enemies/Enemy000.h"

#include "../../include/Core/InputManager.h"
#include "../../include/Core/EntityManager.h"
#include "../../include/Core/LevelManager.h"
#include "../../include/Core/ColorManager.h"

Player::Player(const sf::Vector2f& position)
    : Entity(
        "player", 
        ColorManager::getInstance().getColors().player,
        { position, { 12, 16 } }
    )
{
    entity_data.type = EntityType::Player;

    entity_data.max_health_points = 5;
    entity_data.health_points = entity_data.max_health_points;

    entity_data.shot_delay = .5f;

    entity_data.dash_delay = 1.f;
    entity_data.acceleration = 10.f;
    entity_data.speed = 160.f;
}

void Player::AI(const float& dt)
{
    sf::Vector2f mouse_direction = (InputManager::getInstance().getMouse().position - getCenter()).normalized();
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) velocity.terminal.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) velocity.terminal.x += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) velocity.terminal.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) velocity.terminal.y += 1;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) 
        dash(velocity.terminal * 5.f);

    if (InputManager::getInstance().getMouse().left_button) 
        shootHitscan(getCenter(), mouse_direction, false);

    LevelManager::getInstance().setPlayerIcon(entity_data.health_points);
}

const std::optional<Player::LookingDirection> Player::processDirection()
{
    const sf::Vector2f& mouse_position = InputManager::getInstance().getMouse().position;

    if (getCenter().x < mouse_position.x) return LookingDirection::Right;
    if (getCenter().x > mouse_position.x) return LookingDirection::Left;

    return std::nullopt;
}
