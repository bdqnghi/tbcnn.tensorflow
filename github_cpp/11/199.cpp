
#include <string>
#include <vector>

#include "./BoundaryBox.h"
#include "./Node.h"

#include "./QuadTree.h"

QuadTree::QuadTree( BoundaryBox boundaryBox )
: mBoundaryBox(boundaryBox), mNorthWest(NULL), mNorthEast(NULL), mSouthWest(NULL), mSouthEast(NULL)
{
}

QuadTree::~QuadTree()
{
   if ( this->mNorthWest != NULL ) delete this->mNorthWest;
   if ( this->mNorthEast != NULL ) delete this->mNorthEast;
   if ( this->mSouthWest != NULL ) delete this->mSouthWest;
   if ( this->mSouthEast != NULL ) delete this->mSouthEast;
}

bool QuadTree::insert( Node node )
{

  // ensure correct bounds
  if ( !this->mBoundaryBox.containsCoordinate( node.mOrigin ) ) {
    return false;
  }

  // if space available here, add it
  if ( this->mNodes.size() < this->NODE_CAPACITY ) {
    this->mNodes.push_back( node );
    return true;
  }

  // create child quads
  if ( this->mNorthWest == NULL ) this->subdivide();

  // otherwise subdivide and add to first available quad
  if ( this->mNorthWest->insert( node ) ) return true;
  if ( this->mNorthEast->insert( node ) ) return true;
  if ( this->mSouthWest->insert( node ) ) return true;
  if ( this->mSouthEast->insert( node ) ) return true;

  return false;
}

void QuadTree::subdivide()
{

  double newHalfSize = this->mBoundaryBox.mHalfSize / 2;

  Coordinate nwCenter = Coordinate( this->mBoundaryBox.mOrigin.mX - newHalfSize, this->mBoundaryBox.mOrigin.mY + newHalfSize );
  Coordinate neCenter = Coordinate( this->mBoundaryBox.mOrigin.mX + newHalfSize, this->mBoundaryBox.mOrigin.mY + newHalfSize );
  Coordinate swCenter = Coordinate( this->mBoundaryBox.mOrigin.mX - newHalfSize, this->mBoundaryBox.mOrigin.mY - newHalfSize );
  Coordinate seCenter = Coordinate( this->mBoundaryBox.mOrigin.mX + newHalfSize, this->mBoundaryBox.mOrigin.mY - newHalfSize );

  BoundaryBox bbNw = BoundaryBox( nwCenter, newHalfSize );
  BoundaryBox bbNe = BoundaryBox( neCenter, newHalfSize );
  BoundaryBox bbSw = BoundaryBox( swCenter, newHalfSize );
  BoundaryBox bbSe = BoundaryBox( seCenter, newHalfSize );

  this->mNorthWest = new QuadTree( bbNw );
  this->mNorthEast = new QuadTree( bbNe );
  this->mSouthWest = new QuadTree( bbSw );
  this->mSouthEast = new QuadTree( bbSe );

}

std::vector<Node> QuadTree::queryRange( BoundaryBox boundaryBox )
{

  std::vector<Node> results = std::vector<Node>();

  if ( !this->mBoundaryBox.intersectsBoundaryBox( boundaryBox ) ) return results;

  // add from this quad
  for ( unsigned int i = 0; i < this->mNodes.size(); i++ ) {
    Node node = this->mNodes.at( i );
    if ( boundaryBox.containsCoordinate( node.mOrigin ) ) {
      results.push_back( node );
    }
  }

  // add from child quads
  if ( this->mNorthWest != NULL ) {
    std::vector<Node> queryNodes = this->mNorthWest->queryRange( boundaryBox );
    results.insert( results.end(), queryNodes.begin(), queryNodes.end() );
  }
  if ( this->mNorthEast != NULL ) {
    std::vector<Node> queryNodes = this->mNorthEast->queryRange( boundaryBox );
    results.insert( results.end(), queryNodes.begin(), queryNodes.end() );
  }
  if ( this->mSouthWest != NULL ) {
    std::vector<Node> queryNodes = this->mSouthWest->queryRange( boundaryBox );
    results.insert( results.end(), queryNodes.begin(), queryNodes.end() );
  }
  if ( this->mSouthEast != NULL ) {
    std::vector<Node> queryNodes = this->mSouthEast->queryRange( boundaryBox );
    results.insert( results.end(), queryNodes.begin(), queryNodes.end() );
  }

  return results;
}

// Printable
std::string QuadTree::toString()
{
  return std::string( "QuadTree(mBoundaryBox:" + this->mBoundaryBox.toString() + ")" );
}
