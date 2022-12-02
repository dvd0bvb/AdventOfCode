#pragma once

#include <exception>

enum class Outcome
{
    win,
    lose,
    tie
};

inline unsigned GetOutcomePoints(Outcome outcome)
{
    switch (outcome)
    {
    case Outcome::win:
        return 6;
    case Outcome::lose:
        return 0;
    case Outcome::tie:
        return 3;
    }

    throw std::exception("Invalid outcome value supplied to GetOutcomePoints()");
}

enum class Shape
{
    rock,
    paper,
    scissors
};

inline Shape ShapeNeededToWin(Shape shape)
{
    switch (shape)
    {
    case Shape::rock:
        return Shape::paper;
    case Shape::paper:
        return Shape::scissors;
    case Shape::scissors:
        return Shape::rock;
    }

    throw std::exception("Invalid shape supplied to ShapeNeededToWin()");
}

inline Shape ShapeNeededToLose(Shape shape)
{
    switch (shape)
    {
    case Shape::rock:
        return Shape::scissors;
    case Shape::scissors:
        return Shape::paper;
    case Shape::paper:
        return Shape::rock;
    }

    throw std::exception("Invalid shape supplied to ShapeNeededToLose()");
}

inline bool operator< (Shape lh, Shape rh)
{
    return rh == ShapeNeededToWin(lh);
}

inline unsigned ShapeToPoints(Shape shape)
{
    switch (shape)
    {
    case Shape::rock:
        return 1;
    case Shape::paper:
        return 2;
    case Shape::scissors:
        return 3;
    }

    throw std::exception("Invalid shape value supplied to ShapeToPoints()");
}

inline Shape CharToShape(char c)
{
    switch (c)
    {
    case 'A':
    case 'X':
        return Shape::rock;
    case 'B':
    case 'Y':
        return Shape::paper;
    case 'C':
    case 'Z':
        return Shape::scissors;
    }

    throw std::exception("Invalid char value supplied to CharToShape()");
}

inline Outcome CharToOutcome(char c)
{
    switch (c)
    {
    case 'X':
        return Outcome::lose;
    case 'Y':
        return Outcome::tie;
    case 'Z':
        return Outcome::win;
    }

    throw std::exception("Invalid char value supplied to CharToOutcome()");
}