#include "../../include/Entities/Projectile.h"
#include "../../include/Entities/Enemies/Enemy000.h"
#include "../../include/Entities/Player.h"

#include "../../include/Core/EntityManager.h"


Projectile::Projectile(
    const sf::FloatRect& rect, 
    DynamicBody* sender,
    const std::string& texture_name,
    const sf::Vector2f& direction,
    const float& life_time,
    const bool& piercing
) : DynamicBody(texture_name, 
                sender->getColor(),
                rect), 
    m_sender{ sender },
    m_piercing{ piercing }
{ 
    m_life_time = life_time;
    m_direction = direction;
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
        Entity* target = dynamic_cast<Entity*>(dynamic_bodies[i].get());

        if (target != nullptr && !target->isInvincible() && target != m_sender && rect.findIntersection(target->getRect()))
        {  
            target->damage(1);

            if (!target->isActive()) ((Entity*)m_sender)->heal(1);
            
            if (!m_piercing)
            {
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
