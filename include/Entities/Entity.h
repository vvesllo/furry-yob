#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>

#include "DynamicBody.h"
#include "Projectile.h"

#include "../Core/Managers/ItemManager.h"
#include "../Core/Collider.h"


enum class EntityType : short
{
    Player,
    Enemy,
    Projectile
};

class Projectile;

class Entity : public DynamicBody
{
protected:
    enum class LookingDirection : short
    {
        Left,
        Right,
    };

    // current velocity linear interpolate to terminal
    struct {
        sf::Vector2f terminal;
        sf::Vector2f current;
    } velocity;
    
    // entity data
    struct EntityData {
        float shot_delay;
        
        float speed;
        float acceleration;
        float dash_delay;
        
        bool standing;
        
        EntityType type;

        float health_points;
        float max_health_points;
    };

    // entity_data
    EntityData entity_data;

    // register entity data
    void regist(const EntityData& data);

    // every move processing
    void movement(const float& dt);
    
    // dashing by direction with invincibility time 
    void dash(const sf::Vector2f& direction);
    
    // hitscan attack(ray)
    void shootHitscan(const sf::Vector2f& position, const sf::Vector2f& direction, const bool piercing);
    
    // projectile attack (virtual instanity 2:40 aahhhhhhhhhhhhhhhhh)
    void shootProjectile(
        const std::string& name, 
        const sf::FloatRect& rect, 
        const sf::Vector2f& direction, 
        const float& speed,
        const float& lifetime,
        const bool piercing,
        const std::function<void(Projectile*)> ai);

    // calls before entity get hit by sender
    virtual const bool preHit(Entity* sender);
    
    // update function for children classes
    virtual void AI(const float& dt)=0;

    // sets looking direction from child class
    virtual const std::optional<LookingDirection> processDirection()=0;
    
private:

    // data for items update
    EntityData m_static_entity_data;

    // movement animation (lil jump + lil rotation)
    size_t m_moving_frames;
    
    bool m_shoot;

    // INVINCIBLE
    float m_invincibility_time;
    
    float m_shoot_cooldown;
    float m_dash_cooldown;

    LookingDirection m_looking_direction;

    // sets direction to left/right
    void lookAt(const std::optional<LookingDirection>& direction);


    enum class ColliderCheckAxis : short { X, Y };
    
    // check collision by Y, and then X
    void checkColliding(const ColliderCheckAxis& axis);
    void checkCollidingX(const std::unique_ptr<Collider>& collider);
    void checkCollidingY(const std::unique_ptr<Collider>& collider);
    
public:

    Entity(const std::string& texture_name, const sf::Color& color, const sf::FloatRect& rect);
    virtual ~Entity()=default;

    void update(const float& dt) override;
    virtual void updateItems();

    void hit(Entity* sender, const float& damage_amount);
    void heal(const float& heal_amount);

    const bool isInvincible();
    const EntityType getType();
    const sf::Vector2f getVelocity();

    // for items buffs
    friend class ItemManager;
};