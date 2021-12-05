#include "shape.hpp"



//Base class
//Please implement Shape's member functions
//constructor, getName()
Shape::Shape(string name){name_ = name;}
string Shape::getName(){return name_;}
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable



//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
Rectangle::Rectangle(double width, double length):Shape("Rectangle") {width_ = width; length_ = length;}
double Rectangle::getArea()const{return width_ * length_;}
double Rectangle::getVolume()const{return 0;}
Rectangle Rectangle::operator + (const Rectangle& rec){
    Rectangle R3 = Rectangle(0.0, 0.0);
    R3.width_ = width_+ rec.width_;
    R3.length_ = length_ + rec.length_;
    return R3;
}
Rectangle Rectangle::operator - (const Rectangle& rec){
    Rectangle R3(max(0.0, width_ - rec.width_), max(0.0, length_ - rec.length_));
    return R3;
}

double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
Circle::Circle(double radius):Shape("Circle") {radius_ = radius;}
 double Circle::getArea()const{return radius_ * radius_ * 3.141592653589793238462643383279502;}
 double Circle::getVolume()const{return 0;}
double Circle::getRadius()const{return radius_;}

Circle Circle::operator + (const Circle& cir){
    Circle C3(radius_ + cir.radius_);
    return C3;
}
Circle Circle::operator - (const Circle& cir){
    Circle C3(max(0.0, radius_ - cir.radius_));
    return C3;
}


//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
Sphere::Sphere(double radius) : Shape("Sphere") {radius_ = radius;}
double Sphere::getArea()const{return 4 * 3.1415926535 * radius_ * radius_;}
double Sphere::getVolume()const{return (4.0/3.0) * radius_ * radius_ * radius_ * 3.141592;}
double Sphere::getRadius()const{return radius_;}

Sphere Sphere::operator + (const Sphere& sph){
    Sphere S3(radius_ + sph.radius_);
    return S3;
}
Sphere Sphere::operator - (const Sphere& sph){
    Sphere S3(max(0.0, radius_ - sph.radius_));
    return S3;
}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
RectPrism::RectPrism(double width, double length, double height) : Shape("RectPrism") {width_ = width, length_ = length, height_ = height;}
double RectPrism::getArea()const{return 2 * (width_ * length_ + length_ * height_ + width_ * height_);}
double RectPrism::getVolume()const{return length_ * width_ * height_;}


double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}

RectPrism RectPrism::operator + (const RectPrism& rectp){
    RectPrism R3(width_+ rectp.width_, length_ + rectp.length_, height_ + rectp.height_);
    return R3;
}
RectPrism RectPrism::operator - (const RectPrism& rectp){
    RectPrism R3(max(0.0, width_ - rectp.width_), max(0.0, length_ - rectp.length_), max(0.0, height_ - rectp.height_));
    return R3;
}


 
// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
   
    // FILE *fp;
    // fp = fopen(file_name, "r"); 
    string name;
    double w, l, h, r; 
    int num; 
                                          

    ifstream ifs (file_name, std::ifstream::in);
    ifs >> num;
    std::vector<Shape*> shapes;  
   
    int i;
    for(i=0; i<num; i++){
        ifs >> name;
        Shape *ptr;
        if(name == "Rectangle"){
            ifs >> w >> l;
            ptr = new Rectangle(w,l);
            //shapes.push_back(ptr);
            //shapes[i] = new Rectangle(r);
        }
        else if(name == "Circle"){
            ifs >> r;
            ptr = new Circle(r);
            //shapes.push_back(ptr);
            //shapes[i] = new Circle(r);
        }
        else if(name == "Sphere"){
            ifs >> r;
            ptr = new Sphere(r);
            //shapes.push_back(ptr);
            //shapes[i] = new Sphere(r);
        }
        else if(name == "RectPrism"){
            ifs >> w >> l >> h;
            ptr = new RectPrism(w, l , h);
            //shapes.push_back(ptr);
            //shapes[i] = new RectPrism(w,l,h);
        }
        shapes.push_back(ptr);       
    }

    // for(int i = 0, i<num, i++ ){
    //  String name;
    //  double r1, r2, r3;
    //  ifs >>
    // }
    ifs.close();
    return shapes; // please remeber to modify this line to return the correct value
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){
    double max_area = 0;
    for(int i=0; i<shapes.size(); i++){
        if(max_area < shapes[i]->getArea()){
            max_area = shapes[i]->getArea();
        }
    }
   
    return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
    double max_volume = 0;
    for(int i=0; i<shapes.size(); i++){
        if(max_volume < shapes[i]->getVolume()){
            max_volume = shapes[i]->getVolume();
        }
    }

   
    return max_volume;
}