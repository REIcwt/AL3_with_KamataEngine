#include "Enemy.h"
#include "DebugCamera.h"
#include "Input.h"
#include "MapChipField.h"
#include <algorithm>
#include <array>
#include <numbers>

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = float(M_PI_2) * 3;

	//
	velocity_ = {-kWalkSpeed, 0, 0};

	walkTimer_ = 0.0f;
}

void Enemy::Update() {
	worldTransform_.translation_.x += velocity_.x;

	walkTimer_ += 0.01f;

	//
	worldTransform_.rotation_.x = std::sin(2 * float(M_PI) * (walkTimer_ / kWalkMotionTime));
	float param = std::sin(2 * float(M_PI) * (walkTimer_ / kWalkMotionTime));
	float radian = kInitialWalkMotionAngle + (kFinalWalkMotionAngle * (param + 1.0f) / 2.0f);
	worldTransform_.rotation_.x = (float(M_PI) * radian) / 180.0f;

	worldTransform_.UpdateMatrix();
}

const Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos{};

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

const AABB Enemy::GetAABB() {
	Vector3 worldPos = GetWorldPosition();

	AABB aabb{};

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

void Enemy::OnCollision(const Player* player) { (void)player; }

void Enemy::Draw() { model_->Draw(worldTransform_, *viewProjection_); }