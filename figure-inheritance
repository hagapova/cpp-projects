#include <iostream>
#include <vector>

// задача - создать класс Figure и унаследовать от него два класса Circle и Square, написав функцию Area для каждого из них;

class Figure {
public:
    virtual double Area() const = 0;
};

class Circle : public Figure {
private:
    double radius;
public:
    Circle(double r) {
        radius = r;
    }
    double Area() const override {
        return (this->radius)*(this->radius)*3.1415926;
    }
};

class Square : public Figure {
private:
    double side;
public:
    Square(double r) {
        side = r;
    }
    double Area() const override {
        return (this->side)*(this->side);
    }
};

int main() {
    std::vector<Figure*> figures;

    std::string type = "Circle";
    double val = 1.0;


    if (type == "Circle")
        figures.push_back(new Circle(val));
    else if (type == "Square")
        figures.push_back(new Square(val));

    for (Figure * f : figures)
        std::cout << f->Area() << "\n";

    for (Figure * f : figures)
        delete f;

}

