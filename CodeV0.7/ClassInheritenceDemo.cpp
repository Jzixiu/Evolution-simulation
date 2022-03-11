#include <iostream>
 
using namespace std;
 
// 基类
class Shape 
{
   public:
   Shape(){}
   ~Shape(){}
      void setWidth(int w)
      {
         width = w;
      }
      void setHeight(int h)
      {
         height = h;
      }
    virtual int getPerimeter() = 0;
   protected:
      int width;
      int height;
};

// 派生类
class Rectangle: public Shape
{
   public:
      int getArea()
      { 
         return (width * height); 
      }
      int getPerimeter()
      {
          return(2*(width+height));
      }
};

class triangle: public Shape
{
    public:
    int getArea()
    {
        return (width*height/2);
    }
    int getPerimeter()
    {
        return(10);
    }
};

void test(Shape &temp)
{
    cout<<temp.getPerimeter();
}

int main(void)
{
   Rectangle Rect;
 
   Rect.setWidth(5);
   Rect.setHeight(7);
   // 输出对象的面积
   //cout << "Total area: " << Rect.getArea() <<" "<<Rect.getPerimeter() << endl;
    test(Rect);

    triangle obj1;
    obj1.setHeight(2);
    obj1.setWidth(3);
    //cout<<obj1.getArea()<<" "<<obj1.getPerimeter();
    test(obj1);
   return 0;
}