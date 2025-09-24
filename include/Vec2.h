#pragma once

class Vec2 {

public:
    float x, y;

    Vec2();
    Vec2(float x, float y);
    Vec2(const Vec2& other);

    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;
    Vec2 operator*(float scalar) const;
    Vec2 operator/(float scalar) const;
    bool operator==(const Vec2& other) const;
    Vec2 operator+=(const Vec2& other);

    float Magnitude() const;
    float HorAngle() const;
    Vec2 Normalize() const;
    Vec2 Rotate(float angle) const;
    
    float Distance(const Vec2& other) const;
    float Angle(const Vec2& other) const;
    float Slope(const Vec2& other) const;
    float Dot(const Vec2& other) const;
};
