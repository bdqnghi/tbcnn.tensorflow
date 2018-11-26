/*
**  Windstille - A Sci-Fi Action-Adventure Game
**  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HEADER_WINDSTILLE_TILE_TILE_HPP
#define HEADER_WINDSTILLE_TILE_TILE_HPP

#include <GL/glew.h>

#include "display/texture.hpp"
#include "math/rect.hpp"

enum TileType {
  TILE_EMPTY  = 0,
  TILE_SOLID  = (1 << 0),
  TILE_STAIRS = (1 << 1),
  TILE_LEFT   = (1 << 2),
  TILE_RIGHT  = (1 << 3)
};

class TileDescription;

/** A Tile is a surface or sprite together with information for
 *  collision detection (aka colmap). The collision map is at a
 *  resolution of 8x8 bits. Position information is handled in the
 *  TileMap and not here. (flyweight pattern). */
class Tile
{
public:
  /** The id of the Tile by which the tilemap refers to it */
  int id;

  // FIXME: Using a surface here might be a worthy consideration, just
  // need to find a way to properly bucket-sort the request

  /**
   * Id of the packer
   */
  int     packer;
  Rectf   uv;
  TexturePtr texture;

  /** bitmap that holds the collision attributes for this tile */
  unsigned int colmap;
  TileDescription* desc;

  Tile(unsigned int arg_colmap);

  unsigned int get_colmap() const { return colmap; }

private:
  Tile(const Tile&);
  Tile& operator=(const Tile&);
};

#endif

/* EOF */
