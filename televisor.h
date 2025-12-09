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

//Абстрактный
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

class TVBase : public Point
{
protected:
    virtual void DrawBody() = 0;       // Корпус
    virtual void DrawScreen() = 0;     // Экран
    virtual void DrawControlPanel() = 0; // Панель управления
    virtual void DrawButtons() = 0;    // Кнопки
    virtual void DrawLegs() = 0;       // Ножки
    virtual void DrawAntenna() = 0;    // Антенна
    virtual void DrawSpeakers() = 0;   // Динамики
    virtual void DrawCrackedScreen() = 0; // Треснувший экран

    // Идентификатор телевизора
    int id;

public:
    TVBase(int InitX, int InitY);
    virtual ~TVBase();

    void Show() override;
    void Hide() override;

    // Методы для настройки телевизора
    void SetId(int value) { id = value; }
    int GetId() const { return id; }

    virtual int GetLeft() override { return x - 85; }
    virtual int GetRight() override { return x + 85; }
    virtual int GetTop() override { return y - 65; }
    virtual int GetBottom() override { return y + 85; }
};

// Базовый телевизор 
class Television : public TVBase
{
protected:
    void DrawBody() override;
    void DrawScreen() override;
    void DrawControlPanel() override;
    void DrawButtons() override;
    void DrawLegs() override;
    void DrawAntenna() override { }    // Пустая реализация - нет антенны
    void DrawSpeakers() override { }   // Пустая реализация - нет динамиков
    void DrawCrackedScreen() override { } // Пустая реализация - не сломан

public:
    Television(int InitX, int InitY);
    ~Television() override;

    int GetLeft() override { return x - 85; }
    int GetRight() override { return x + 85; }
    int GetTop() override { return y - 65; }
    int GetBottom() override { return y + 85; }
};

// Телевизор с антенной
class TelevisionWithAntenna : public TVBase
{
protected:
    void DrawBody() override;
    void DrawScreen() override;
    void DrawControlPanel() override;
    void DrawButtons() override;
    void DrawLegs() override;
    void DrawAntenna() override;    // Рисуем антенну
    void DrawSpeakers() override { }   // Пустая реализация - нет динамиков
    void DrawCrackedScreen() override { } // Пустая реализация - не сломан

public:
    TelevisionWithAntenna(int InitX, int InitY);
    ~TelevisionWithAntenna() override;

    int GetTop() override { return y - 125; }
    int GetLeft() override { return x - 90; }
    int GetRight() override { return x + 90; }
};

// Сломанный телевизор
class BrokenTelevision : public TVBase
{
protected:
    void DrawBody() override;
    void DrawScreen() override;
    void DrawControlPanel() override;
    void DrawButtons() override;
    void DrawLegs() override;
    void DrawAntenna() override { }    // Пустая реализация - нет антенны
    void DrawSpeakers() override { }   // Пустая реализация - нет динамиков
    void DrawCrackedScreen() override; // Рисуем треснувший экран

public:
    BrokenTelevision(int InitX, int InitY);
    ~BrokenTelevision() override;

    int GetTop() override { return y - 125; }
    int GetLeft() override { return x - 90; }
    int GetRight() override { return x + 90; }
};

// Телевизор без ножек
class TelevisionWithoutLegs : public TVBase
{
protected:
    void DrawBody() override;
    void DrawScreen() override;
    void DrawControlPanel() override;
    void DrawButtons() override;
    void DrawLegs() override { }       // Пустая реализация - нет ножек
    void DrawAntenna() override { }    // Пустая реализация - нет антенны
    void DrawSpeakers() override { }   // Пустая реализация - нет динамиков
    void DrawCrackedScreen() override { } // Пустая реализация - не сломан

public:
    TelevisionWithoutLegs(int IntX, int IntY);
    ~TelevisionWithoutLegs() override;

    int GetTop() override { return y - 65; }
    int GetLeft() override { return x - 85; }
    int GetRight() override { return x + 85; }
};

// Телевизор без кнопок
class TelevisionWithoutButtons : public TVBase
{
protected:
    void DrawBody() override;
    void DrawScreen() override;
    void DrawControlPanel() override;
    void DrawButtons() override { }    // Пустая реализация - нет кнопок
    void DrawLegs() override;
    void DrawAntenna() override { }    // Пустая реализация - нет антенны
    void DrawSpeakers() override { }   // Пустая реализация - нет динамиков
    void DrawCrackedScreen() override { } // Пустая реализация - не сломан

public:
    TelevisionWithoutButtons(int InitX, int InitY);
    ~TelevisionWithoutButtons() override;

    int GetTop() override { return y - 65; }
    int GetLeft() override { return x - 85; }
    int GetRight() override { return x + 85; }
};

// Телевизор с динамиками
class TelevisionWithSpeakers : public Television
{
protected:

    void DrawLegs() override;
    void DrawAntenna() override { }    // Пустая реализация - нет антенны
    void DrawSpeakers() override;      // Рисуем динамики
    void DrawCrackedScreen() override { } // Пустая реализация - не сломан

public:
    TelevisionWithSpeakers(int InitX, int InitY);
    ~TelevisionWithSpeakers() override;

    int GetLeft() override { return x - 100; }
    int GetRight() override { return x + 100; }
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

class SimpleCircle : public Figure
{
protected:
    int radius; // Радиус круга
public:
    SimpleCircle(int InitX, int InitY, int radius = 40);
    ~SimpleCircle() override;

    void Show() override;
};
