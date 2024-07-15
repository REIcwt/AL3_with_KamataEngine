#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "cassert"
#include <numbers>

class Player {
public:
	Player();
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model"></param>
	/// <param name="textureHandle"></param>
	/// <param name="viewProjection"></param>
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	const WorldTransform& GetWorldTransform() const;

	const Vector3& GetVelocity() const { return velocity_; }

private:
	// 3D
	Model* model_ = nullptr;
	// ViewProjection
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;

	// Speed
	Vector3 velocity_ = {};
	static inline const float kAcceleration = 0.02f;
	static inline const float kAttenuation = 0.1f;
	static inline const float kLimitRunSpeed = 0.3f;
	//

	// Jump
	bool onGround_ = true;
	// Gravity(down)
	static inline const float kGravityAcceleration = 0.04f;
	// Max down speed
	static inline const float kLimitFallSpeed = 0.5f;
	// jump initialize speed
	static inline const float kJumpAcceleration = 0.5f;
	static inline const float kAttenuationLanding = 0.1f;

	// direction
	enum class LRDirection {
		kRight,
		kLeft,
	};
	LRDirection lrDirection_ = LRDirection::kRight;
	float turnFirstRotation_ = 0.0f;
	float turnTimer_ = 0.0f;
	static inline const float kTimeTurn = 0.3f;
};