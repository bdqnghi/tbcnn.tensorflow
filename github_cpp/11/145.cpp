#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include <cg/visualization/viewer_adapter.h>
#include <cg/visualization/draw_util.h>

#include <cg/io/point.h>

#include <cg/primitives/point.h>


#include "node.h"


using cg::point_2;
using cg::point_2f;

struct qdt_viewer : cg::visualization::viewer_adapter
{
   qdt_viewer()
   {
	root = new Node<double>();
   }

   void draw_node(Node<double> *node, cg::visualization::drawer_type & drawer) const
   {

    drawer.set_color(Qt::green);
    drawer.draw_point(node->point, 3);
	
	if(node->children[0] == NULL)
		return;

    drawer.set_color(Qt::white);

    point_2t<double> c = node->boundary.position;
    double d = node->boundary.dimension;

    point_2 p1(c.x + d, c.y+d/2);
    point_2 p2(c.x + d/2, c.y+d);
    point_2 p3(c.x, c.y+d/2);
    point_2 p4(c.x+d/2, c.y);

	drawer.draw_line(p1, p3);
	drawer.draw_line(p2, p4);

	draw_node(node->children[0], drawer);
	draw_node(node->children[1], drawer);
	draw_node(node->children[2], drawer);
	draw_node(node->children[3], drawer);
   }

    // draws all the points and lines
   void draw(cg::visualization::drawer_type & drawer) const
   {
      draw_node(root, drawer);
   }

    // print in the corner
   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "press mouse rbutton to add point" << cg::visualization::endl
                        << "points: " << pts_.size() << cg::visualization::endl;
   }


    // mouse rbutton click
   bool on_release(const point_2f & p)
   {
     root->insert(point_2t<double>(p.x, p.y));
	pts_.push_back(p);

      return true;
   }

private:

   Node<double>* root;
   std::vector<point_2> pts_;
};

int main(int argc, char ** argv)
{
    // TODO: specify canva's size!!
   QApplication app(argc, argv);
   qdt_viewer viewer;
   cg::visualization::run_viewer(&viewer, "quad-tree");
}
