#include <assert.h>
#include <iostream>

#include "BaseEntity.hpp"

BaseEntity::BaseEntity()
	:
	m_id(""),
	m_displayName("NA_BaseEntity"),
	m_isVisible(false),
	m_canUpdate(true)
{
}

BaseEntity::BaseEntity(const char* entityId, const char* entityName, const bool canRender, const bool canUpdate)
	:
	m_id(entityId),
	m_displayName(entityName),
	m_isVisible(canRender),
	m_canUpdate(canUpdate)

{
}

BaseEntity::~BaseEntity()
{
	std::cout << GetDisplayName() << " destroyed on BaseEntity destructor!\n";
}

void BaseEntity::Render(SDL_Renderer* renderer)
{
	assert(renderer);
}

void BaseEntity::Update(const float deltaTime)
{
}
