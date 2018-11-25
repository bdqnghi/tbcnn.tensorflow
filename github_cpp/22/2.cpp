

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


class Tile
{
public:
  
  int id;

  
  

  
  int     packer;
  Rectf   uv;
  TexturePtr texture;

  
  unsigned int colmap;
  TileDescription* desc;

  Tile(unsigned int arg_colmap);

  unsigned int get_colmap() const { return colmap; }

private:
  Tile(const Tile&);
  Tile& operator=(const Tile&);
};

#endif


