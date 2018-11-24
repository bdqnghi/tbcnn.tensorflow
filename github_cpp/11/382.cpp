////////////////////////////////////////////////////////////////////////
// QuadTree.cpp
// Super Mario Project
// Copyright (C) 2011  
// Lionel Joseph lionel.r.joseph@gmail.com
// Olivier Guittonneau openmengine@gmail.com
////////////////////////////////////////////////////////////////////////

#include "QuadTree.hpp"
#include "BlockOccurrence.hpp"

using namespace std;
using namespace sf;

namespace smp
{

	bool QuadTree::isLeaf()
	{
		return _subTree1 == nullptr &&
			_subTree2 == nullptr &&
			_subTree3 == nullptr &&
			_subTree4 == nullptr;
	}

	void QuadTree::buildTree(vector<BlockOccurrence*>& obj)
	{
		sf::Vector2i size;
		sf::Vector2f center;

		if(!obj.empty() && _depth < MAX_DEPTH)
		{
			size.x = _size.x / 2;
			size.y = _size.y / 2;

			if(size.x >= 2 * obj.front()->getHitboxSize().x
				&& size.y >= 2 * obj.front()->getHitboxSize().y)
			{

				/* create sub trees */
				center.x = _center.x - _size.x / 4;
				center.y = _center.y + _size.y / 4;
				_subTree1 = new QuadTree(center, size, _depth + 1);

				center.x +=  _size.x / 2;
				_subTree2 = new QuadTree(center, size, _depth + 1);

				center.x = _center.x - _size.x / 4;
				center.y -= _size.y / 2;
				_subTree3 = new QuadTree(center, size, _depth + 1);

				center.x += _size.x / 2;
				_subTree4 = new QuadTree(center, size, _depth + 1);

				/* create subvector */
				std::vector<BlockOccurrence*> subTab1, subTab2, subTab3, subTab4;
				center = _center;

				for(vector<BlockOccurrence*>::iterator itObj = obj.begin(); itObj != obj.end(); ++itObj)
				{
					Vector2f point_BL = (*itObj)->getHitboxPosition();
					float x = point_BL.x + (*itObj)->getHitboxSize().x;
					float y = point_BL.y + (*itObj)->getHitboxSize().y;
					Vector2f point_HR = Vector2f(x,y);

					if(point_HR.x <= center.x)
					{
						if(point_HR.y <= center.y)
						{
							subTab3.push_back(*itObj);
						}
						else if(point_BL.y >= center.y)
						{
							subTab1.push_back(*itObj);
						}
						else
						{
							_elements.push_back(*itObj);
						}
					}
					else
					{
						if(point_HR.y <= center.y)
						{
							subTab4.push_back(*itObj);
						}
						else if(point_BL.y >= center.y)
						{
							subTab2.push_back(*itObj);
						}
						else
						{
							_elements.push_back(*itObj);
						}
					}
				}

				/* build subTrees */
				_subTree1->buildTree(subTab1);
				_subTree2->buildTree(subTab2);
				_subTree3->buildTree(subTab3);
				_subTree4->buildTree(subTab4);
			}
			else
			{
				/* We store blocks */
				_elements.insert(_elements.end(), obj.begin(), obj.end());
			}
		}
	}

	void QuadTree::getBlocks(sf::Vector2f& position, sf::Vector2i& size, vector<BlockOccurrence*>* blocks)
	{
		if(!isLeaf())
		{
			/* Left side */
			if((position.x >= _center.x - _size.x / 2 && position.x <= _center.x)
				|| (position.x + size.x >= _center.x - _size.x / 2 && position.x + size.x <= _center.x))
			{
				if(position.y >= _center.y - _size.y / 2 && position.y <= _center.y)
				{
					/* subTree 3 */
					if(_subTree3 != NULL)
					{
						_subTree3->getBlocks(position, size, blocks);
					}
				}

				if(position.y + size.y >= _center.y  && position.y + size.y <= _center.y + _size.y / 2)
				{
					/* subTree 1 */
					if(_subTree1 != NULL)
					{
						_subTree1->getBlocks(position, size, blocks);
					}
				}
			}

			/* Right side */
			if((position.x + size.x >= _center.x && position.x + size.x <= _center.x + _size.x / 2)
				|| (position.x >= _center.x && position.x <= _center.x + _size.x / 2))
			{
				if(position.y >= _center.y - _size.y / 2 && position.y <= _center.y)
				{
					/* subTree 4 */
					if(_subTree4 != NULL)
					{
						_subTree4->getBlocks(position, size, blocks);
					}
				}

				if(position.y + size.y >= _center.y && position.y + size.y <= _center.y + _size.y / 2)
				{
					/* subTree 2 */
					if(_subTree2 != NULL)
					{
						_subTree2->getBlocks(position, size, blocks);
					}
				}
			}
		}
		else
		{
			blocks->insert(blocks->end(), _elements.begin(), _elements.end());
		}
	}

	void QuadTree::render(RenderWindow& app)
	{
		Vector2f pointBL, pointHL, pointHR, pointBR;

		pointBL.x = _center.x - _size.x / 2;
		pointBL.y = _center.y - _size.y / 2;

		pointHR.x = _center.x + _size.x / 2;
		pointHR.y = _center.y + _size.y / 2;

		sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(pointHR.x - pointBL.x, pointHR.y - pointBL.y));
		rect.setOutlineColor(sf::Color::Red);
		rect.setPosition(pointBL);

		app.draw(rect);

		if(_subTree1 != nullptr)
			_subTree1->render(app);

		if(_subTree2 != nullptr)
			_subTree2->render(app);

		if(_subTree3 != nullptr)
			_subTree3->render(app);

		if(_subTree4 != nullptr)
			_subTree4->render(app);
	}

	QuadTree::~QuadTree()
	{
		delete _subTree1;
		delete _subTree2;
		delete _subTree3;
		delete _subTree4;
	}
}
