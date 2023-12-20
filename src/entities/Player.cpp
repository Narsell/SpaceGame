#include <SDL.h>
#include <iostream>

#include "Player.hpp"
#include "GameManager.hpp"
#include "MovementComponent.hpp"
#include "Projectile.hpp"
#include "Renderer.hpp"
#include "WindowBounds.hpp"
#include "Renderer.hpp"


Player::Player(const Transform& transform, TextureResource* texture, const char* name)
	:
	GameObject(transform, texture, name),
	m_projectileSpawnPoint(texture->GetDimensions().x / 2, -50),
	m_windowBounds(nullptr)
{
	m_transform.SetRotation(90.0);

	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));
	m_movementComponent->SetSpeed(5.f);
	m_movementComponent->SetRotationFollowsVelocity(false);

	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->AddCollider(texture->GetDimensions(), Vector2::ZERO, true, "Ship Collision");
	m_collisionComponent->SetCanRender(false);

	std::function<void(HitInformation&)> OnCollisionDelegate = std::bind(&Player::OnCollision, this, std::placeholders::_1);
	m_collisionComponent->SetCollisionDelegate(OnCollisionDelegate);

}

Player::~Player()
{
	//std::cout << GetDisplayName() << " destroyed on Player destructor!\n";

}

void Player::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);

	//Handle events
	for (SDL_Event &frameEvent : GameManager::GetFrameEvents()) {
		if (frameEvent.type == SDL_KEYDOWN)
		{
			SDL_Keycode pressedKey = frameEvent.key.keysym.sym;
			if (pressedKey == SDLK_SPACE) {
				ShootProjectile();
			}

			if (pressedKey == SDLK_d) {
				m_movementComponent->SetVelocity(Vector2::RIGHT);
			}
			else if (pressedKey == SDLK_a) {
				m_movementComponent->SetVelocity(Vector2::LEFT);
			}
			else if (pressedKey == SDLK_w) {
				m_movementComponent->SetVelocity(Vector2::UP);
			}
			else if (pressedKey == SDLK_s) {
				m_movementComponent->SetVelocity(Vector2::DOWN);
			}
			
		}
		else if (frameEvent.type == SDL_KEYUP && frameEvent.key.keysym.sym != SDLK_SPACE) {
			m_movementComponent->SetVelocity(Vector2::ZERO);
		}
	}
}

void Player::SetWindowBounds(WindowBounds* windowBounds)
{
	m_windowBounds = windowBounds;
	m_collisionComponent->ListenForCollisions(m_windowBounds);
}

void Player::OnCollision(HitInformation& hitInformation)
{
	if (hitInformation.hitGameObject->GetDisplayName() == "Window Bounds") {
		m_transform.SetPosition(hitInformation.hitLocation);
	}
}

void Player::ShootProjectile()
{
	assert(Renderer::projectileTexture);

	int* mouseX = new int(0);
	int* mouseY = new int(0);

	SDL_GetMouseState(mouseX, mouseY);
	const Vector2 mousePosition = Vector2(static_cast<float>(*mouseX), static_cast<float>(*mouseY));
	const Vector2 spawnPosition = m_transform.GetPosition() + m_projectileSpawnPoint;
	const Vector2 velocity = (mousePosition - spawnPosition).Normalized();
	const double angle = Math::GetAngleFromDirection(velocity);

	Transform spawnTransform = Transform(spawnPosition, angle);

	Projectile* projectile = new Projectile(spawnTransform, Renderer::projectileTexture, "Projectile");
	projectile->GetMovementComponent()->SetVelocity(velocity);
	projectile->GetCollisionComponent()->ListenForCollisions(m_windowBounds);

	m_projectiles.emplace_back(
		GameManager::SpawnGameObject(projectile)
	);

}
