#pragma once
#include <vector>
#include "Math.h"
#include <cstdint>

class Game;
class Component;
class Actor
{
public:
	enum class eState {
		Active,
		Pause,
		Dead
	};
	Actor(Game* game);
	virtual ~Actor();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);
	virtual void ActorInput(const uint8_t* keyState);
	void ProcessInput(const uint8_t* keyState);

	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; mRecomputeWorldTransform = true; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale;  mRecomputeWorldTransform = true; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation;  mRecomputeWorldTransform = true; }
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), Math::Sin(mRotation)); }

	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	Game* GetGame() { return mGame; }

	void RemoveComponent(Component* component);
	void AddComponent(Component* component);



	Actor::eState GetState() {
		return mState;
	}
	void SetState(eState state) {
		mState = state;
	}


private:
	// Actor's state
	eState mState;

	// Transform
	Matrix4 mWorldTransform;
	Vector2 mPosition;
	float mScale;
	float mRotation;
	bool mRecomputeWorldTransform;

	std::vector<Component*> mComponents;

	Game* mGame;
};

