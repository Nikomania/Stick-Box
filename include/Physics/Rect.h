#pragma once
#include <Physics/Vec2.h>

class Rect {
public:
    float x, y, w, h;

    Rect();
    Rect(float x, float y, float width, float height);
    Rect(const Vec2& pos, float width, float height);
    Rect(const Vec2& beg, const Vec2& end);
    Rect(const Rect& other);

    float GetArea() const;
    float GetPerimeter() const;
    Vec2 GetCenter() const;
    float GetDistanceCenters(const Rect& other) const;
    Vec2 GetPos() const;
    float GetDiagonal() const;
  
    Rect operator+(const Vec2& vec) const;
    Rect operator-(const Vec2& vec) const;
    Rect operator*(float scalar) const;
    Rect operator/(float scalar) const;

    Rect& Move(const Vec2& speedVec);
    Vec2 Move(float angle, float speed);

    Rect& SetPos(const Vec2& pos);
    Rect& SetCenter(const Vec2& pos);

    bool Contains(const Vec2& point) const;
    bool Contains(float x, float y) const;
};
