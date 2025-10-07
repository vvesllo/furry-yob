cmake_minimum_required(VERSION 4.1)

set(PROJECT_NAME roguelike)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_executable(
    ${PROJECT_NAME}
        src/main.cpp
        src/App.cpp                         include/App.h
        
        src/Core/LevelManager.cpp           include/Core/LevelManager.h
        src/Core/EntityManager.cpp          include/Core/EntityManager.h
        src/Core/SceneManager.cpp           include/Core/SceneManager.h
        src/Core/ResourceManager.cpp        include/Core/ResourceManager.h
        src/Core/InputManager.cpp           include/Core/InputManager.h
        src/Core/ColorManager.cpp           include/Core/ColorManager.h
        src/Core/DynamicBody.cpp            include/Core/DynamicBody.h
        src/Core/Scene.cpp                  include/Core/Scene.h
        src/Core/Collider.cpp               include/Core/Collider.h
        
        src/Scenes/GameScene.cpp            include/Scenes/GameScene.h
        
        src/Utils/Vector.cpp                include/Utils/Vector.h
        
        src/Core/Hitscan.cpp                include/Core/Hitscan.h
        
        src/Entities/Entity.cpp             include/Entities/Entity.h
        src/Entities/Player.cpp             include/Entities/Player.h
        src/Entities/Projectile.cpp         include/Entities/Projectile.h

        src/Entities/Enemies/Enemy000.cpp   include/Entities/Enemies/Enemy000.h
        src/Entities/Enemies/Enemy001.cpp   include/Entities/Enemies/Enemy001.h
        src/Entities/Enemies/Enemy002.cpp   include/Entities/Enemies/Enemy002.h
        src/Entities/Enemies/Enemy003.cpp   include/Entities/Enemies/Enemy003.h
        src/Entities/Enemies/Enemy004.cpp   include/Entities/Enemies/Enemy004.h
)

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System)