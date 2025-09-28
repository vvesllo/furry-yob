#include "../../include/Entities/Projectile.h"
#include "../../include/Entities/Enemies/Enemy000.h"
#include "../../include/Entities/Player.h"

#include "../../include/Core/EntityManager.h"


Projectile::Projectile(const sf::Vector2f& position, DynamicBody* sender, const ProjectileType type, const sf::Vector2f& direction)
    : DynamicBody(
        "projectile", 
        type == ProjectileType::Friendly ? sf::Color::Yellow : sf::Color::Magenta, 
        {
            position, 
            { 5, 5 }
        }), m_sender{ sender }
{ 
    m_life_time = 5.f;
    m_direction = direction;
    m_type = type;
}

Projectile::~Projectile()
{
}

void Projectile::AI(const float& dt)
{
    velocity.current = m_direction;
    std::vector<std::unique_ptr<DynamicBody>>& dynamic_bodies = EntityManager::getInstance().getEntities();
    
    for (int i=0; i < dynamic_bodies.size(); ++i)
    {
        if (dynamic_bodies[i].get()->isActive() && dynamic_bodies[i].get() != m_sender && rect.findIntersection(dynamic_bodies[i]->getRect()))
        {   
            Entity* target = dynamic_cast<Entity*>(dynamic_bodies[i].get());
            if (target != nullptr)
            {
                target->damage(1);
                if (!target->isActive())
                    ((Entity*)m_sender)->heal(1);
                destroy();
                return;
            }
        }
    }
}

void Projectile::update(const float& dt)
{
    if (m_life_time > 0.f) 
    {
        AI(dt);
        rect.position += velocity.current * dt;
        sprite->setPosition(rect.position + rect.size / 2.f);
        m_life_time -= dt;
    }
    else 
        destroy();
}

const ProjectileType Projectile::getType()
{
    return m_type;
}
