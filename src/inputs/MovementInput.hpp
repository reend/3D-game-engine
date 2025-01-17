#pragma once
#include "raylib-cpp.hpp"

class MovementInput {
public:
    raylib::Vector3 GetMovementDirection(const Vector3& forward) const;
    bool IsJumpRequested() const;
    
private:
    Vector3 CalculateMovementVector(const Vector3& forward, const Vector3& right) const;
};