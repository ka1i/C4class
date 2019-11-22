/*
* @Author: LinuxMint
* @File:   2017221101025.cpp
* @Date:   2019-11-21 23:46:44
* @Site:   https://www.mardan.wiki
* @Email:  Mardan137@outlook.com
* @Last Modified by:   LinuxMint
* @Last Modified time: 2019-11-21 23:48:18
* @CopyRight: Copyright © Mardan. All Rights Reserved.
*/

#include <iostream>
#include <iomanip>

using namespace std;


class Point3D
{

private:
/*    typedef struct Coordinate{
        double coordinate_dx;
        double coordinate_dy;
        double coordinate_dz;
    }Coordinate3d;*/

    double coordinate_dx,coordinate_dy,coordinate_dz;

    //Coordinate3d* coordinate_system = nullptr;//new Coordinate3d();
    //Coordinate3d* coordinate_system = (Coordinate3d *)malloc(sizeof(Coordinate3d));


public:
     /*! 
     *  @brief default constructor.
     *  @param so A stream object.
     *  @param s  A Point3D object.

     *  @return Stream object containing Point3D content.
     */
    //@}
	Point3D(){
        //coordinate_system = (Coordinate3d *)malloc(sizeof(Coordinate3d));

        coordinate_dx = 0.0;
        coordinate_dy = 0.0;
        coordinate_dz = 0.0;

    };

    Point3D(double dx):Point3D(){

        coordinate_dx = dx;
    }
    Point3D(double dx,double dy):Point3D(){

        coordinate_dx = dx;
        coordinate_dy = dy;
    }
    Point3D(double dx,double dy,double dz):Point3D(){

        coordinate_dx = dx;
        coordinate_dy = dy;
        coordinate_dz = dz;
    }
    Point3D(const Point3D& point):Point3D(){

        coordinate_dx = point.coordinate_dx;
        coordinate_dy = point.coordinate_dy;
        coordinate_dz = point.coordinate_dz;
    }
    Point3D(Point3D&& point):Point3D(){

        coordinate_dx = point.coordinate_dx;
        coordinate_dy = point.coordinate_dy;
        coordinate_dz = point.coordinate_dz;

        point.coordinate_dx = 0;point.coordinate_dy = 0;point.coordinate_dz = 0;


    }

	~Point3D(){
        coordinate_dx = 0;coordinate_dy = 0;coordinate_dz = 0;
    };

    int empty(){
        coordinate_dx = 0;
        coordinate_dy = 0;
        coordinate_dz = 0;
        return 0;
    }

	Point3D translate(double dx,double dy,double dz){
        coordinate_dx += dx;
        coordinate_dy += dy;
        coordinate_dz += dz;
        
        Point3D& temp = *this;
		return temp;
	};

	Point3D scale(double sx,double sy,double sz){

        coordinate_dx = coordinate_dx * sx;        
        coordinate_dy = coordinate_dy * sy;
        coordinate_dz = coordinate_dz * sz;

        Point3D& temp = *this;
        return temp;
	};

	 /*! 
     *  @brief Stream operators.
     *  @param so A stream object.
     *  @param s  A Point3D object.
     *  @return Stream object containing Point3D content.
     */
    //@}
    friend std::ostream& operator<< (std::ostream& os, const Point3D& p) {
        
        if (true) {
            os << setiosflags(std::ios::fixed) << setprecision(2);
            os << "(";
            os << p.coordinate_dx <<","<<p.coordinate_dy <<","<<p.coordinate_dz;
            os << ")";
        } else os << "";    
        return os;
    };   

    friend std::istream& operator>> (std::istream& is, Point3D& p) {
        is >> p.coordinate_dx;
        is >> p.coordinate_dy;
        is >> p.coordinate_dz;
        return is;
    };
    //@{

        /*! 
     *  @brief Sets Point3D value.
     *  @param[in] p A Point3D object.
     *  @return A Point3D reference to *this.
     *  @post Point3D will be equivalent to @a p.
     */
    Point3D& operator= (const Point3D& p) {   
        empty();
        coordinate_dx = p.coordinate_dx;
        coordinate_dy = p.coordinate_dy;
        coordinate_dz = p.coordinate_dz;
        empty();
        return *this;
    };

    Point3D& operator= (Point3D&& p) {   
        empty();
        coordinate_dx = p.coordinate_dx;
        coordinate_dy = p.coordinate_dy;
        coordinate_dz = p.coordinate_dz;

        p.empty();
        return *this;
    };
};

int main()
{
	Point3D p1,p2;

	std::cin >> p1;

	p2 = p1.translate(2,3,4);
	p1 = p2.scale(1.5,0.5,2.5);
	std::cout << p1;

	return 0;
}