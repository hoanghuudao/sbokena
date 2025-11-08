#pragma once

/*A file implementing the structure for moveable objects that are placed on top
 * of files. These include the player and boxes, which can be pushed around by
 * the player. To open a door, a box needs to be on top of its respective
 * button. */

enum class ObjectType { Box = 0, Player = 1 };

class Object {
public:
  Object() : type(ObjectType::Box) {}
  explicit Object(ObjectType type) : type(type) {}
  virtual ~Object() = default;
  ObjectType GetType() const {
    return type;
  }

private:
  ObjectType type;
};

class Player : public Object {
public:
  Player() : Object(ObjectType::Player) {}
};

class Box : public Object {
public:
  Box() : Object(ObjectType::Box) {}
};