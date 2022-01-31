
/*
* Given interface Renderer, it is asked to implement it as VectorRenderer and RasterRenderer.
* Afterwards, use it with base class Shape, such that it mitigates the problem of having the 
* Cartesian product duplication that is given by classes such as: VectorSquare, RasterSquare,
* RasterTriangle, VectorTriangle.
*
* The Renderer interface acts as a bridwe between implementations that perform rendering
* (VectorRenderer and RasterRenderer) and the Shape implementations (Triangle, Square).
*
* After refactoring, classes such as VectorSquare, RasterSquare become deprecated and can be discarded.
*/

#include <string>
using namespace std;

//Bridge interface
struct Renderer
{
    virtual string what_to_render_as(const string& name) const = 0;
};

//Bridge interface implementations
struct VectorRenderer:public Renderer
{
    string what_to_render_as(const string& name) const override
    {
        return "Drawing " + name + " as lines";
    }
};

struct RasterRenderer: public Renderer
{
    string what_to_render_as(const string& name) const override
    {
        return "Drawing " + name + " as pixels";
    }
};

//Interface user is an abstract class acting as root node in inheritance hierarchy
struct Shape
{
    string name;
    Renderer& mRenderer;
    
    Shape(Renderer& rend):mRenderer{rend}{};
    
    virtual string str() const = 0;
};

//First Derived level with 2 classes
struct Triangle : Shape
{
    Triangle(Renderer& rend):Shape{rend}
    {
        name = "Triangle";
    }

    string str() const override
    {
        return mRenderer.what_to_render_as(name);
    }
};

struct Square : Shape
{
    Square(Renderer& rend):Shape{rend}
    {
        name = "Square";
    }

    string str() const override
    {
        return mRenderer.what_to_render_as(name);
    }
};

//Second Derived level with 4 nodes
//Below 4 classes are example of how a class hierarchy can lead to Cartesian product complexity (2x2)
struct VectorSquare : Square
{
    string str() const
    {
        return "Drawing " + name + " as lines";
    }
};

struct RasterSquare : Square
{
    string str() const
    {
        return "Drawing " + name + " as pixels";
    }
};

struct VectorTriangle : Triangle
{
    string str() const
    {
        return "Drawing " + name + " as lines";
    }
};

struct RasterTriangle : Triangle
{
    string str() const
    {
        return "Drawing " + name + " as pixels";
    }
};
