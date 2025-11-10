#pragma once

#include "object.hh"
#include "types.hh"

using sbokena::types::Direction;
using sbokena::types::Position;

/* A class implementing the tiles in the grid inside the editor. The tile
 * contains its absolute/relative position within the grid (still contested),
 * the list of objects above it (for example, the character or the box above the
 * floor), and its sprite image.*/

// An enum containing types of tiles.
enum class TileType {
  Wall,
  Floor,
  OneDir,
  Goal,
  Portal,
  Door,
  Button,
};

// An abstract class contaning common fields and functions that all tiles share.
class Tile {
public:
  explicit Tile(TileType type, Position<> pos)
    : type(type), pos(pos), object(nullptr) {}

  virtual ~Tile() = default;

  TileType GetType() const {
    return type;
  }

  Position<> GetPos() const {
    return pos;
  }

  void SetPos(const Position<> &newpos) {
    pos = newpos;
  }

  virtual bool HasObject() const {
    return (object != nullptr);
  }

  virtual Object *GetObject() {
    return object;
  }

  virtual const Object *GetObject() const {
    return object;
  }

  virtual void SetObject(Object *obj) {
    object = obj;
  }

  virtual void RemoveObject() {
    object = nullptr;
  }

private:
  TileType type;
  Position<> pos;
  Object *object;
};

// Foward declarations.
class Portal;
class Door;
class Button;

// The default type for a tile. Does not contain any object.
class Wall : public Tile {
public:
  Wall(Position<> pos) : Tile(TileType::Wall, pos) {}

  bool HasObject() const override {
    return false;
  }

  Object *GetObject() override {
    return nullptr;
  }

  const Object *GetObject() const override {
    return nullptr;
  }

  void SetObject(Object *obj) override {}

  void RemoveObject() override {}
};

// The basic, most common type of non-wall tile. Can contain an object.
class Floor : public Tile {
public:
  Floor(Position<> pos) : Tile(TileType::Floor, pos) {}
};

// Similar to floor but only lets object move through one specified way.
class OneDir : public Tile {
public:
  OneDir(Direction dir, Position<> pos)
    : Tile(TileType::OneDir, pos), dir(dir) {}

  Direction GetDir() const {
    return dir;
  }

  void SetDir(Direction newdir) {
    dir = newdir;
  }

private:
  Direction dir;
};

// If the player arrives into this tile, the level is completed.
class Goal : public Tile {
public:
  Goal(Position<> pos) : Tile(TileType::Goal, pos) {}
};

// Must be linked to another portal to be valid. Can teleport objects to the
// linked portal.
class Portal : public Tile {
public:
  Portal(Position<> pos) : Tile(TileType::Portal, pos), linked(nullptr) {}

  Portal *GetLinked() {
    return linked;
  }

  const Portal *GetLinked() const {
    return linked;
  }

  void SetLinked(Portal *newlinked) {
    linked = newlinked;
  }

  void RemoveLinked() {
    linked = nullptr;
  }

  bool IsValid() const {
    return (linked != nullptr);
  }

private:
  Portal *linked;
};

// Opens when a specific button is opened.
class Door : public Tile {
public:
  Door(Position<> pos) : Tile(TileType::Door, pos), opened(false) {}
  void Open() {
    opened = true;
  }
  void Close() {
    opened = false;
  }
  bool IsOpened() const {
    return opened;
  }

private:
  bool opened;
};

// Must be linked to another door to be valid. When contains an object
// (pressed), opens the linked door.
class Button : public Tile {
public:
  Button(Position<> pos) : Tile(TileType::Button, pos), door(nullptr) {}

  Door *GetLinked() {
    return door;
  }

  const Door *GetLinked() const {
    return door;
  }

  void SetLinked(Door *newdoor) {
    door = newdoor;
  }

  void RemoveLinked() {
    door = nullptr;
  }

  bool IsValid() const {
    return (door != nullptr);
  }

private:
  Door *door;
};