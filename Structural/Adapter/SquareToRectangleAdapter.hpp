#pragma once

/*
*  Square is the given existing type. However, the protocol that is widely used is Rectangle.
*  Therefore, Square needs to be adapted to Rectangle in order for its implementation to be used and not rewritten.
*/

struct Square
{
    int side{ 0 };

    Square() = default;
    explicit Square(const int side): side(side){};
};

struct Rectangle
{
    virtual int width() const = 0;
    virtual int height() const = 0;

    int area() const
    {
        return width() * height();
    }
};

//the Adapter aggregates the adaptee
struct SquareToRectangleAdapter : public Rectangle
{
    SquareToRectangleAdapter(const Square& square)
    {
        mSquare.side = square.side;
    }

    int width() const {return mSquare.side;};
    int height() const {return mSquare.side;};

    Square mSquare;
};
