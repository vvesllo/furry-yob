#include "include/Core/Hitscan.h"
#include "include/Core/Managers/EntityManager.h"

Hitscan::Hitscan(
    DynamicBody* sender,
    const sf::Vector2f& position,
    const sf::Vector2f& direction,
    const bool& piercing
) : m_sender(sender),
    m_piercing(piercing)
{
    m_line = sf::VertexArray(sf::PrimitiveType::Lines, 2);
    m_line[0] = sf::Vertex(position, sender->getColor());

    m_max_life_time = .2f;
    m_life_time = m_max_life_time;

    shoot(direction);
}

Hitscan::~Hitscan()
{
    
}

bool Hitscan::rayIntersectsAABB(
    const sf::Vector2f& ray_origin, 
    const sf::Vector2f& ray_direction, 
    const sf::FloatRect& aabb,
    float& t
)
{
    constexpr float INF = std::numeric_limits<float>::max();

    float inverted_direction_x = (std::abs(ray_direction.x) > 1e-6f) ? 1.0f / ray_direction.x : INF;
    float inverted_direction_y = (std::abs(ray_direction.y) > 1e-6f) ? 1.0f / ray_direction.y : INF;

    sf::Vector2f t1 = {
        (aabb.position.x - ray_origin.x) * inverted_direction_x,
        (aabb.position.y - ray_origin.y) * inverted_direction_y
    };

    sf::Vector2f t2 = {
        (aabb.position.x + aabb.size.x - ray_origin.x) * inverted_direction_x,
        (aabb.position.y + aabb.size.y - ray_origin.y) * inverted_direction_y
    };

    float tmin = std::max(std::min(t1.x, t2.x), std::min(t1.y, t2.y));
    float tmax = std::min(std::max(t1.x, t2.x), std::max(t1.y, t2.y));

    if (tmax < 0 || tmin > tmax)
        return false;

    t = tmin >= 0 ? tmin : tmax;
    return t >= 0;
}

void Hitscan::shoot(const sf::Vector2f& direction)
{
    std::vector<std::unique_ptr<DynamicBody>>& dynamic_bodies = EntityManager::getInstance().getEntities();

    float closest_target = std::numeric_limits<float>::max();
    std::vector<std::pair<Entity*, float>> hit_targets;

    for (const auto& body : dynamic_bodies)
    {
        Entity* target = dynamic_cast<Entity*>(body.get());

        if (!target || target == m_sender || target->isInvincible())
            continue;
            
        sf::FloatRect target_rect = target->getRect();
        float t;

        if (rayIntersectsAABB(m_line[0].position, direction, target_rect, t))
            hit_targets.push_back({target, t});
    }

    std::sort(
        hit_targets.begin(),
        hit_targets.end(),
        [] (const std::pair<Entity*, float>& left, 
            const std::pair<Entity*, float>& right)
        {
            return left.second < right.second; 
        }
    );

    float distance = 1000.f;

    if (!hit_targets.empty())
    {
        Entity* sender_entity = dynamic_cast<Entity*>(m_sender);
        
        for (const auto& target : hit_targets)
        {
            target.first->hit(sender_entity, 1);

            if (!target.first->isActive() && sender_entity)
                sender_entity->heal(1);

            if (!m_piercing) 
            {
                distance = target.second;
                break;
            }
        }   
    }

    m_line[1] = sf::Vertex(m_line[0].position + direction * distance, m_sender->getColor());
}

void Hitscan::update(const float& dt)
{
    m_life_time -= dt;
}

void Hitscan::draw(std::unique_ptr<sf::RenderWindow>& target)
{
    sf::VertexArray scaled(sf::PrimitiveType::TriangleStrip, 4);
    
    sf::Vector2f direction = (m_line[1].position - m_line[0].position).normalized();
    sf::Vector2f offset = direction * .8f * (m_life_time / m_max_life_time);
    
    scaled[0] = sf::Vertex{
        m_line[0].position + offset.rotatedBy(sf::degrees(90)),
        m_line[0].color
    };
    
    scaled[1] = sf::Vertex{
        m_line[1].position + offset.rotatedBy(sf::degrees(90)),
        m_line[1].color
    };
    
    scaled[2] = sf::Vertex{
        m_line[0].position + offset.rotatedBy(sf::degrees(-90)),
        m_line[0].color
    };
    
    scaled[3] = sf::Vertex{
        m_line[1].position + offset.rotatedBy(sf::degrees(-90)),
        m_line[1].color
    };

    target->draw(scaled);
}

bool Hitscan::isActive()
{
    return m_life_time > 0;
}