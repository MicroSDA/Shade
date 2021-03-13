#include "stdafx.h"
#include "CollisionShape.h"

se::CollisionShape::CollisionShape(const se::CollisionShape::Shape& shape):
    m_ShapeType(shape)
{
}

const se::CollisionShape::Shape& se::CollisionShape::GetShape() const
{
    return m_ShapeType;
}
