cmake_minimum_required(VERSION 4.1)

set(PROJECT_NAME roguelike)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_executable(
    ${PROJECT_NAME}
        src/main.cpp
        src/Core/App.cpp                            include/Core/App.h
        
        src/Core/Managers/LevelManager.cpp          include/Core/Managers/LevelManager.h
        src/Core/Managers/EntityManager.cpp         include/Core/Managers/EntityManager.h
        src/Core/Managers/SceneManager.cpp          include/Core/Managers/SceneManager.h
        src/Core/Managers/ResourceManager.cpp       include/Core/Managers/ResourceManager.h
        src/Core/Managers/InputManager.cpp          include/Core/Managers/InputManager.h
        src/Core/Managers/ThemeManager.cpp          include/Core/Managers/ThemeManager.h

        src/Core/Collider.cpp                       include/Core/Collider.h
        src/Core/Hitscan.cpp                        include/Core/Hitscan.h
        
        src/Scenes/Scene.cpp                        include/Scenes/Scene.h
        src/Scenes/GameScene.cpp                    include/Scenes/GameScene.h
        
        src/Utils/Vector.cpp                        include/Utils/Vector.h
        
        src/Core/Managers/ItemManager.cpp           include/Core/Managers/ItemManager.h
        
        src/Entities/DynamicBody.cpp                include/Entities/DynamicBody.h
        src/Entities/Entity.cpp                     include/Entities/Entity.h
        src/Entities/Player.cpp                     include/Entities/Player.h
        src/Entities/Projectile.cpp                 include/Entities/Projectile.h
        src/Entities/Item.cpp                       include/Entities/Item.h

        src/Entities/Enemies/Enemy000.cpp           include/Entities/Enemies/Enemy000.h
        src/Entities/Enemies/Enemy001.cpp           include/Entities/Enemies/Enemy001.h
        src/Entities/Enemies/Enemy002.cpp           include/Entities/Enemies/Enemy002.h
        src/Entities/Enemies/Enemy003.cpp           include/Entities/Enemies/Enemy003.h
        src/Entities/Enemies/Enemy004.cpp           include/Entities/Enemies/Enemy004.h
)   

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System)