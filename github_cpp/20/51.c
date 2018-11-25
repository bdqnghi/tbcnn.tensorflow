#include "stdafx.h"
#include <gtest/gtest.h>
#include <memory>
#include <fstream>

class RedBlackTreeTests : public testing::Test
{
public:
    template<class T>
    class RedBlackTree
    {
    public:
        enum class Color { Red, Black };

        struct Node
        {
            Node(Color c, std::shared_ptr<const Node> const & lft, T val,std::shared_ptr<const Node> const & rgt): 
                color_(c), 
                left_(lft), 
                node_value_(val), 
                right_(rgt) {}
            Color color_;
            std::shared_ptr<const Node> left_;
            T node_value_;
            std::shared_ptr<const Node> right_;
        };
        explicit RedBlackTree(std::shared_ptr<const Node> const & node) : root_(node) {}

    public:
        RedBlackTree() {}
        RedBlackTree(Color c, RedBlackTree const & left, T val, RedBlackTree const & right)
            : root_(std::make_shared<const Node>(c, left.root_, val, right.root_))
        {
            assert(left.IsEmpty() || left.node_value() < val);
            assert(right.IsEmpty() || val < right.node_value());
        }
        RedBlackTree(std::initializer_list<T> init)
        {
            RedBlackTree t;
            for (T v : init)
            {
                t = t.Insert(v);
            }
            root_ = t.root_;
        }
        Color rootColor() const
        {
            assert(!IsEmpty());
            return root_->color_;
        }
        template<class I>
        RedBlackTree(I b, I e)
        {
            RedBlackTree t;
            for_each(b, e, [&t](T const & v) {
                t = t.Insert(v);
            });
            root_ = t.root_;
        }
        bool IsEmpty() const { return !root_; }
        T node_value() const
        {
            assert(!IsEmpty());
            return root_->node_value_;
        }
        RedBlackTree left() const
        {
            assert(!IsEmpty());
            return RedBlackTree(root_->left_);
        }
        RedBlackTree right() const
        {
            assert(!IsEmpty());
            return RedBlackTree(root_->right_);
        }
        bool IsMember(T x) const
        {
            if (IsEmpty())
                return false;
            T y = node_value();
            if (x < y)
                return left().IsMember(x);
            else if (y < x)
                return right().IsMember(x);
            else
                return true;
        }
        RedBlackTree Insert(T x) const
        {
            RedBlackTree t = InsertNode(x);
            return RedBlackTree(Color::Black, t.left(), t.node_value(), t.right());
        }
        
        void assert1() const
        {
            if (!IsEmpty())
            {
                auto lft = left();
                auto rgt = right();
                if (rootColor() == Color::Red)
                {
                    assert(lft.IsEmpty() || lft.rootColor() == Color::Black);
                    assert(rgt.IsEmpty() || rgt.rootColor() == Color::Black);
                }
                lft.assert1();
                rgt.assert1();
            }
        }
        
        
        int countB() const
        {
            if (IsEmpty())
                return 0;
            int lft = left().countB();
            int rgt = right().countB();
            assert(lft == rgt);
            return (rootColor() == Color::Black) ? 1 + lft : lft;
        }
    private:
        RedBlackTree InsertNode(T x) const
        {
            assert1();
            if (IsEmpty())
                return RedBlackTree(Color::Red, RedBlackTree(), x, RedBlackTree());
            T y = node_value();
            Color c = rootColor();
            if (rootColor() == Color::Black)
            {
                if (x < y)
                    return BalanceNodes(left().InsertNode(x), y, right());
                else if (y < x)
                    return BalanceNodes(left(), y, right().InsertNode(x));
                else
                    return *this; 
            }
            else
            {
                if (x < y)
                    return RedBlackTree(c, left().InsertNode(x), y, right());
                else if (y < x)
                    return RedBlackTree(c, left(), y, right().InsertNode(x));
                else
                    return *this; 
            }
        }
        
        static RedBlackTree BalanceNodes(RedBlackTree const & left, T value, RedBlackTree const & right)
        {
            if (left.doubledLeft())
                return RedBlackTree(Color::Red
                    , left.left().paint(Color::Black)
                    , left.node_value()
                    , RedBlackTree(Color::Black, left.right(), value, right));
            else if (left.doubledRight())
                return RedBlackTree(Color::Red
                    , RedBlackTree(Color::Black, left.left(), left.node_value(), left.right().left())
                    , left.right().node_value()
                    , RedBlackTree(Color::Black, left.right().right(), value, right));
            else if (right.doubledLeft())
                return RedBlackTree(Color::Red
                    , RedBlackTree(Color::Black, left, value, right.left().left())
                    , right.left().node_value()
                    , RedBlackTree(Color::Black, right.left().right(), right.node_value(), right.right()));
            else if (right.doubledRight())
                return RedBlackTree(Color::Red
                    , RedBlackTree(Color::Black, left, value, right.left())
                    , right.node_value()
                    , right.right().paint(Color::Black));
            else
                return RedBlackTree(Color::Black, left, value, right);
        }
        bool doubledLeft() const
        {
            return !IsEmpty()
                && rootColor() == Color::Red
                && !left().IsEmpty()
                && left().rootColor() == Color::Red;
        }
        bool doubledRight() const
        {
            return !IsEmpty()
                && rootColor() == Color::Red
                && !right().IsEmpty()
                && right().rootColor() == Color::Red;
        }
        RedBlackTree paint(Color c) const
        {
            assert(!IsEmpty());
            return RedBlackTree(c, left(), node_value(), right());
        }
    private:
        std::shared_ptr<const Node> root_;
    };

    void static PrintNullNode(int key, int nullcount, std::ofstream& output_stream)
    {
        output_stream << "    null" << nullcount << " [shape=point];\n";
        output_stream << "    " << key << " -> null" << nullcount << ";\n";
    }
    template<class T>
    void static PrintNode(RedBlackTree<T> const & t, std::ofstream& output_stream)
    {
        static int nullcount = 0;

        if (!t.left().IsEmpty())
        {
            output_stream << "    node [fillcolor=";
            if (t.rootColor() == RedBlackTree<T>::Color::Black)
            {
                output_stream << "\"#0000005f\"];\n";
            }
            else
            {
                output_stream << "\"#ff00005f\"];\n";
            }
            output_stream << "    " << t.node_value() << " -> " << t.left().node_value() << ";\n";
            PrintNode(t.left(), output_stream);
        }
        else
        {
            PrintNullNode(t.node_value(), nullcount++, output_stream);
        }

        if (!t.right().IsEmpty())
        {
            output_stream << "    node [fillcolor=";
            if (t.rootColor() == RedBlackTree<T>::Color::Black)
            {
                output_stream << "\"#0000005f\"];\n";
            }
            else
            {
                output_stream << "\"#ff00005f\"];\n";
            }
            output_stream << "    " << t.node_value() << " -> " << t.right().node_value() << ";\n";
            PrintNode(t.right(), output_stream);
        }
        else
        {
            PrintNullNode(t.node_value(), nullcount++, output_stream);
        }
    }
    template<class T>
    void static PrintTree(RedBlackTree<T> const & t, std::ofstream& output_stream, int offset = 0)
    {
        output_stream << "digraph BST {\n";
        output_stream << "    node [fontname=\"Arial\" style=filled];\n";
        if (t.IsEmpty())
        {
            output_stream << "\n";
        }
        else if (t.right().IsEmpty() && t.left().IsEmpty())
        {
            output_stream << "    " << t.node_value() << ";\n";
        }
        else
        {
            PrintNode(t, output_stream);
        }
        output_stream << "}\n";
    }
    template<class T>
    RedBlackTree<T> TreeUnion(RedBlackTree<T> const & a, RedBlackTree<T> const & b)
    {
        
        RedBlackTree<T> tree_result = a;
        forEach(b, [&tree_result, &a](T const & v) 
        {
            if (!a.IsMember(v))
                tree_result.Insert(v);
        });
        return tree_result;
    }



protected:
    RedBlackTreeTests() {}
    virtual ~RedBlackTreeTests() {}
};


TEST_F(RedBlackTreeTests, Test2)
{
    RedBlackTree<int> t{ 50, 40, 30, 10, 20, 30, 100, 0, 45, 55, 25, 15 };
    std::ofstream myfile;
    myfile.open("example.txt");
    PrintTree(t, myfile, 0);
    EXPECT_EQ(0.0F, 0.0F);
}