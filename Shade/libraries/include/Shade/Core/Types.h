#pragma once

// Use when you cannot manage life for specific object, see std::shared_ptr
template<typename T>
using ShadeShared = std::shared_ptr<T>;