#pragma once

#include "placeable.hh"
#include "types.hh"
#include <vector>

using namespace sbokena::types;

/*A class implementing the tiles in the grid inside the editor. The tile
 * contains its absolute/relative position within the grid (still contested),
 * the list of objects above it (for example, the character or the box above the
 * floor), and its sprite image.*/

class Tile {
private:
  Position<u8> pos;
  std::vector<Placeable> objects;
};