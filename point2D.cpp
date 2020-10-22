#include "point2D.h"

Point2D::Point2D() : x(0), y(0) {}
Point2D::Point2D(double a, double b) : x(a), y(b) {}

bool seed_generated = false;

// normalise a vector
Point2D Point2D::normalise()
{
    Point2D temp;

    double magnitude = sqrt(pow(this->x, 2) + pow(this->y, 2));
    temp.x = this->x / magnitude;
    temp.y = this->y / magnitude;

    return(temp);
}

// find distance between two points
double Point2D::distance(Point2D other)
{
    return(sqrt( pow(other.x - this->x, 2) + pow(other.y - this->y, 2) ));
}

double Point2D::angle()
{
    if (y < 0 || (x < 0 && y < 0))     // adding 180 or 360 deg keeps the result between 0 and 360 deg 
        return(atan(this->x / this->y) + 180 * (M_PI / 180));
    else if (x < 0)
        return(atan(this->x / this->y) + 360 * (M_PI / 180));
    else
        return(atan(this->x / this->y));
}

double Point2D::dot(Point2D other)
{
    return(this->x * other.x + this->y * other.y);
}

double Point2D::length(void)
{
    return(sqrt(pow(this->x, 2) + pow(this->y, 2)));
}

Point2D Point2D::operator-(const Point2D& other)
{
    Point2D result;
    result.x = this->x - other.x;
    result.y = this->y - other.y;

    return(result);
}

Point2D Point2D::operator*(const double multiplyer)
{
    Point2D result;
    result.x = this->x * multiplyer;
    result.y = this->y * multiplyer;
    return(result);
}

Point2D Point2D::operator+(const Point2D& other)
{
    Point2D result;
    result.x = this->x + other.x;
    result.y = this->y + other.y;

    return(result);
}

Point2D Point2D::operator+(double other)
{
    Point2D result;
    result.x = this->x + other;
    result.y = this->y + other;

    return(result);
}

bool Point2D::operator==(const Point2D& other)
{
    return(this->x == other.x && this->y == other.y);
}

Point2D Point2D::randomPoint(double xmin, double xmax, double ymin, double ymax)
{
    if (!seed_generated)    // only generate seed once
    {
        srand(time(0));
        seed_generated = true;
    }

    int xminInt = int(xmin * 100);
    int xmaxInt = int(xmax * 100);
    int yminInt = int(xmin * 100);
    int ymaxInt = int(xmax * 100);
  
    Point2D result;
    
    result.x = double(rand() % (xmaxInt + 100 - xminInt) + xminInt) / 100;
    result.y = double(rand() % (ymaxInt + 100 - yminInt) + yminInt) / 100;

    return result;
}