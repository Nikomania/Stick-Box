#include <Camera.h>
#include <InputManager.h>
#include <constants.h>

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(0, 0);

void Camera::Follow(GameObject* newFocus) {
  focus = newFocus;
}

void Camera::Unfollow() {
  focus = nullptr;
}

void Camera::Update(float dt) {
  if (focus == nullptr) {
    speed = Vec2();
    InputManager &inputManager = InputManager::GetInstance();
    if (inputManager.IsKeyDown(RIGHT_ARROW_KEY) ||
        inputManager.IsKeyDown(D_KEY)
    ) {
      speed.x += 1;
    }

    if (inputManager.IsKeyDown(LEFT_ARROW_KEY) ||
        inputManager.IsKeyDown(A_KEY)
    ) {
      speed.x -= 1;
    }

    if (inputManager.IsKeyDown(UP_ARROW_KEY) ||
        inputManager.IsKeyDown(W_KEY)
    ) {
      speed.y -= 1;
    }

    if (inputManager.IsKeyDown(DOWN_ARROW_KEY) ||
        inputManager.IsKeyDown(S_KEY)
    ) {
      speed.y += 1;
    }
    speed = speed.Normalize() * CAMERA_SPEED_DEFAULT;
    pos += speed * dt;
  } else {
    pos = focus->box.GetCenter() - Vec2(DEFAULT_SCREEN_WIDTH / 2, DEFAULT_SCREEN_HEIGHT / 2);
  }
}
