#include "include/Entities/Player.h"
#include "include/Entities/Projectile.h"

#include "include/Core/Managers/InputManager.h"
#include "include/Core/Managers/EntityManager.h"
#include "include/Core/Managers/LevelManager.h"
#include "include/Core/Managers/ThemeManager.h"

Player::Player(const sf::Vector2f& position)
    : Entity(
        "player", 
        ThemeManager::getInstance().getTheme().player,
        { position, { 12, 16 } }
    )
{
    EntityData data;

    data.type = EntityType::Player;

    data.max_health_points = 5;
    data.health_points = data.max_health_points;

    data.shot_delay = .5f;

    data.dash_delay = 1.f;
    data.acceleration = 10.f;
    data.speed = 100.f;

    regist(data);
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
