#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdlib.h>
#include <time.h>

class Point2D
{
public:
	double x;
	double y;

	Point2D();		//default constructor
	Point2D(double a, double b);		//overloaded constructor

	Point2D normalise();				// normalise a vecor
	double distance(Point2D other);		// find distance between 2 points
	double angle();						// find the angle of a vector
	double dot(Point2D other);			// find the dot product
	double length();					// find the length of a vector

	Point2D operator-(const Point2D& other);
	Point2D operator*(const double multiplyer);
	Point2D operator+(const Point2D& other);
	Point2D operator+(double other);
	bool operator==(const Point2D& other);

	static Point2D randomPoint(double xmin, double xmax, double ymin, double ymax);
};