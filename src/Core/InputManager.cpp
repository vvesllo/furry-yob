#include "../../include/Core/InputManager.h"


InputManager::InputManager()
{
	m_mouse.left_button = false;
	m_mouse.right_button = false;
}

InputManager& InputManager::getInstance()
{
	static InputManager instance;
	return instance;
}

InputManager::Mouse& InputManager::getMouse()
{
	return m_mouse;
}
