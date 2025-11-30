#pragma once
#include <Windows.h>

class IShow 
{
public:
    virtual void Show() = 0;
};

class Location 
{
protected:
    int x;
    int y;
public:
    Location(int InitX, int InitY);
    virtual ~Location();

    int GetX();
    int GetY();
    void SetX(int NewX);
    void SetY(int NewY);
};

//Абстрактный
class Bounds : public Location 
{
public:
    Bounds(int InitX, int InitY) : Location(InitX, InitY) {}
    virtual int GetLeft() = 0;
    virtual int GetRight() = 0;
    virtual int GetTop() = 0;
    virtual int GetBottom() = 0;
};

class Point : public Bounds 
{
protected:
    bool visible;
public:
    Point(int InitX, int InitY);
    virtual ~Point();

    virtual void Show() = 0;
    virtual void Hide() = 0;

    void MoveTo(int NewX, int NewY);

    int GetLeft() override { return x - 5; }
    int GetRight() override { return x + 5; }
    int GetTop() override { return y - 5; }
    int GetBottom() override { return y + 5; }
};

//Абстрактный
class TVBase : public Point 
{
public:
    TVBase(int InitX, int InitY);
    virtual void Show() = 0;
    virtual void Hide() = 0;
};

class Television : public TVBase 
{
public:
    int id;
public:
    Television(int InitX, int InitY);
    ~Television() override;
    void Show() override;
    void Hide() override;

    int GetLeft() override { return x - 85; }
    int GetRight() override { return x + 85; }
    int GetTop() override { return y - 65; }
    int GetBottom() override { return y + 85; }
};

class Figure : public Point, public IShow 
{
protected:
    int id;                    // Общее поле для идентификатора
    int leftOffset;           // Смещение для левой границы
    int rightOffset;          // Смещение для правой границы  
    int topOffset;            // Смещение для верхней границы
    int bottomOffset;         // Смещение для нижней границы

    //Общие поля для размеров
    int width;                // Ширина объекта
    int height;               // Высота объекта  
    int length;               // Длина объекта (для молотка)
    int head_size;            // Размер головки (для молотка)

public:
    Figure(int InitX, int InitY, int id = 0);
    ~Figure();

    int GetLeft() override { return x - leftOffset; }
    int GetRight() override { return x + rightOffset; }
    int GetTop() override { return y - topOffset; }
    int GetBottom() override { return y + bottomOffset; }

    // Метод установки смещений границ (общий метод для наследников)
    void SetBounds(int left, int right, int top, int bottom);

    // Методы установки размеров (общие методы для наследников)
    void SetSize(int w, int h);
    void SetDimensions(int len, int head);

    virtual void Hide() override;
    virtual void Show() override = 0;
};

class Molotok : public Figure 
{
public:
    Molotok(int InitX, int InitY, int len = 80, int head = 20);
    ~Molotok() override;
    void Show() override;
};

class Aquarium : public Figure 
{
public:
    Aquarium(int InitX, int InitY, int w = 200, int h = 150);
    ~Aquarium() override;
    void Show() override;
};

class TelevisionWithAntenna : public Television 
{
public:
    TelevisionWithAntenna(int InitX, int InitY);
    ~TelevisionWithAntenna() override;
    void Show() override;
    void Hide() override;

    int GetTop() override { return y - 125; }
    int GetLeft() override { return x - 90; }
    int GetRight() override { return x + 90; }
};

class BrokenTelevision : public Television 
{
public:
    BrokenTelevision(int InitX, int InitY);
    ~BrokenTelevision() override;
    void Show() override;
    void Hide() override;

    int GetTop() override { return y - 125; }
    int GetLeft() override { return x - 90; }
    int GetRight() override { return x + 90; }
};

class TelevisionWithoutLegs : public Television 
{
public:
    TelevisionWithoutLegs(int IntX, int IntY);
    ~TelevisionWithoutLegs() override;

    void Show() override;
    void Hide() override;

    int GetTop() override { return y - 125; }
    int GetLeft() override { return x - 90; }
    int GetRight() override { return x + 90; }
};

class TelevisionWithoutButtons : public Television 
{
public:
    TelevisionWithoutButtons(int InitX, int InitY);
    ~TelevisionWithoutButtons() override;
    void Show() override;
    void Hide() override;

    int GetTop() override { return y - 125; }
    int GetLeft() override { return x - 90; }
    int GetRight() override { return x + 90; }
};
