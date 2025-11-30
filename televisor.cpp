#include "televisor.h"
#include <Windows.h>

extern HDC hdc;

//start Location::Location
Location::Location(int InitX, int InitY) {
    x = InitX;
    y = InitY;
}//end Location

//start Location::~Location
Location::~Location() 
{
}//end Location::~Location

//Возвращаем координаты
//start Location::CetX
int Location::GetX() 
{ 
    return x; 
}//end Location::GetX

//start Location::GetY
int Location::GetY() 
{ 
    return y; 
}//end Location::GetY

//Изменяем координаты
//start Location::SetX
void Location::SetX(int NewX) 
{ 
    x = NewX; 
}//end Location::SetX

//start Location::SetY
void Location::SetY(int NewY) 
{ 
    y = NewY; 
}//end Location::SetY

//start Point::Point
Point::Point(int InitX, int InitY) : Bounds(InitX, InitY) 
{
    visible = false; // Изначально объект невидим
}//end Point::Point

//start Point::~Point
Point::~Point() 
{
}//end Point::~Point

// Перемещение объекта 
//start Point::MoveTo
void Point::MoveTo(int NewX, int NewY) 
{
    // Если объект уже видим, спрячем его перед перемещением
    if (visible) Hide();
    x = NewX;
    y = NewY;
    Show();
}//end Point::MoveTo

// Базовый класс для телевизоров
//start TVBase::TVBase
TVBase::TVBase(int InitX, int InitY) : Point(InitX, InitY) 
{

}//end TVBase::TVBase

//start Figure::Figure
Figure::Figure(int InitX, int InitY, int figureId) : Point(InitX, InitY) 
{
    id = figureId;
    // Устанавливаем значения по умолчанию
    leftOffset = rightOffset = topOffset = bottomOffset = 5;
    width = height = length = head_size = 0; // Инициализация общих полей
}//end Figure::Figure

//start Figure::~Figure
Figure::~Figure() 
{
}//end Figure::~Figure

//start Figure::SetBounds
void Figure::SetBounds(int left, int right, int top, int bottom) 
{
    leftOffset = left;
    rightOffset = right;
    topOffset = top;
    bottomOffset = bottom;
}//end Figure::SetBounds

//start Figure::SetSize
void Figure::SetSize(int w, int h) 
{
    width = w; 
    height = h; 
}//end Figure::SetSize

//Figure::SetDimensions
void Figure::SetDimensions(int len, int head) 
{
    length = len; 
    head_size = head; 
}//end Figure::SetDimensions

//start Figure::Hide
void Figure::Hide() 
{
    visible = false;
    HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);

    Rectangle(hdc, GetLeft() - 5, GetTop() - 5, GetRight() + 5, GetBottom() + 5);

    SelectObject(hdc, oldBrush);
    SelectObject(hdc, oldPen);
    DeleteObject(brush);
    DeleteObject(pen);
}//end Figure::Hide

// Основной класс телевизора
//start Television::Television
Television::Television(int InitX, int InitY) : TVBase(InitX, InitY) 
{
    id = 0; // Идентификатор базового телевизора
}//end Television::Television

//start Television::~Television
Television::~Television() 
{ 
}//end Television::~Television

// Отрисовка телевизора
//start Television::Show
void Television::Show() 
{
    visible = true;

    // Создание кистей для рисования
    HPEN PenR = CreatePen(PS_SOLID, 2, RGB(139, 69, 19)); // Коричневый - корпус
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));     // Черный - экран и детали

    // Рисование корпуса телевизора
    SelectObject(hdc, PenR);
    Rectangle(hdc, x - 80, y - 60, x + 80, y + 70);

    // Рисование основных элементов
    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 70, y - 50, x + 70, y + 50);  // Основной экран
    Rectangle(hdc, x - 60, y + 30, x + 60, y + 45);  // Панель управления
    RoundRect(hdc, x - 55, y - 35, x + 55, y + 25, 10, 10); // Закругленный экран

    // Рисование кнопок
    Ellipse(hdc, x - 45, y + 42, x - 35, y + 32); // Левая кнопка
    Ellipse(hdc, x - 30, y + 42, x - 20, y + 32); // Центральная кнопка
    Ellipse(hdc, x + 30, y + 42, x + 40, y + 32); // Правая кнопка

    // Рисование ножек
    Rectangle(hdc, x - 70, y + 70, x - 60, y + 80); // Левая ножка
    Rectangle(hdc, x + 60, y + 70, x + 70, y + 80); // Правая ножка

    // Очистка ресурсов
    DeleteObject(PenB);
    DeleteObject(PenR);
}//end Television::Show

// Скрытие телевизора (закрашивание белым прямоугольником)
//start Television::Hide
void Television::Hide() 
{
    visible = false;

    // Создание белых кисти и пера для закрашивания
    HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

    // Сохранение старых объектов и выбор новых
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);

    // Закрашивание области телевизора
    Rectangle(hdc, x - 85, y - 120, x + 85, y + 85);

    // Восстановление старых объектов
    SelectObject(hdc, oldBrush);
    SelectObject(hdc, oldPen);

    // Очистка ресурсов
    DeleteObject(brush);
    DeleteObject(pen);
}//end Television::Hide

//start Molotok::Molotok
Molotok::Molotok(int InitX, int InitY, int len, int head) : Figure(InitX, InitY, 0) 
{
    // Используем общий метод для установки размеров
    SetDimensions(len, head);
    // Устанавливаем границы через общий метод
    SetBounds(60, 60, 140, 15);
}//end Molotok::Molotok

//start Molotok::~Molotok
Molotok::~Molotok() 
{ 
}//end Molotok::~Molotok

//start Molotok::Show
void Molotok::Show() 
{
    visible = true;

    // Рисование ручки молотка (красная)
    HPEN PenHandle = CreatePen(PS_SOLID, 25, RGB(255, 0, 0));
    SelectObject(hdc, PenHandle);
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x, y - length); // Используем length из Figure

    // Рисование головки молотка (черная)
    HPEN PenHead = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    SelectObject(hdc, PenHead);

    // Расчет размеров головки (используем head_size из Figure)
    int head_height = head_size * 2;
    int head_width = head_size * 4;
    int topY = y - length; // Верхняя точка ручки

    // Создание прямоугольной головки молотка
    POINT headPoints[] = {
        {x - head_width / 2, topY - head_height / 2},
        {x - head_width / 2, topY + head_height / 2},
        {x + head_width / 2, topY + head_height / 2},
        {x + head_width / 2, topY - head_height / 2}
    };
    Polygon(hdc, headPoints, 4);

    // Очистка ресурсов
    DeleteObject(PenHandle);
    DeleteObject(PenHead);
}//end Molotok::Show

// Класс аквариума
//start Aquarium::Aquarium
Aquarium::Aquarium(int InitX, int InitY, int w, int h) : Figure(InitX, InitY, 1) 
{
    // Используем общий метод для установки размеров
    SetSize(w, h);
    // Устанавливаем границы через общий метод
    SetBounds(width / 2 + 15, width / 2 + 15, height / 2 + 15, height / 2 + 15);
}//end Aquarium::Aquarium

//start Aquarium::~Aquarium
Aquarium::~Aquarium() 
{
}//end Aquarium::~Aquarium

// Отрисовка аквариума
//start Aquarium::Show
void Aquarium::Show() 
{
    visible = true;

    // Рисование внешнего контура аквариума
    HPEN PenAquarium = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
    SelectObject(hdc, PenAquarium);
    Rectangle(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2); // Используем width и height из Figure

    // Заливка водой (голубой цвет)
    HBRUSH brushWater = CreateSolidBrush(RGB(173, 216, 230));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brushWater);
    Rectangle(hdc, x - width / 2 + 5, y - height / 2 + 5,
        x + width / 2 - 5, y + height / 2 - 5);
    SelectObject(hdc, oldBrush);

    // Рисование песка на дне
    HBRUSH brushSand = CreateSolidBrush(RGB(210, 180, 140));
    SelectObject(hdc, brushSand);
    int sand_height = height / 6; // Используем height из Figure
    Rectangle(hdc, x - width / 2 + 10, y + height / 2 - sand_height - 5,
        x + width / 2 - 10, y + height / 2 - 5);

    // Рисование водорослей
    HPEN PenPlant = CreatePen(PS_SOLID, 3, RGB(0, 100, 0));
    SelectObject(hdc, PenPlant);
    // Левая водоросль
    MoveToEx(hdc, x - width / 4, y + height / 2 - sand_height - 5, NULL);
    LineTo(hdc, x - width / 4, y - height / 4);
    // Правая водоросль
    MoveToEx(hdc, x + width / 4, y + height / 2 - sand_height - 5, NULL);
    LineTo(hdc, x + width / 4, y);

    // Очистка ресурсов
    DeleteObject(PenAquarium);
    DeleteObject(PenPlant);
    DeleteObject(brushWater);
    DeleteObject(brushSand);
}//end Aquarium::Show

// Телевизор с антенной
//start TelevisionWithAntenna::TelevisionWithAntenna
TelevisionWithAntenna::TelevisionWithAntenna(int InitX, int InitY) : Television(InitX, InitY) 
{
    id = 1; // Идентификатор телевизора с антенной
}//end TelevisionWithAntenna::TelevisionWithAntenna

//start TelevisionWithAntenna::~TelevisionWithAntenna
TelevisionWithAntenna::~TelevisionWithAntenna() 
{
}//end TelevisionWithAntenna::~TelevisionWithAntenna

// Отрисовка телевизора с антенной
//start TelevisionWithAntenna::Show
void TelevisionWithAntenna::Show() 
{
    // рисуем базовый телевизор
    Television::Show();

    // добавляем антенну
    HPEN PenAntenna = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
    HPEN oldPen = (HPEN)SelectObject(hdc, PenAntenna);

    // Левая антенна
    MoveToEx(hdc, x - 30, y - 60, NULL);
    LineTo(hdc, x - 50, y - 100);

    // Правая антенна
    MoveToEx(hdc, x + 30, y - 60, NULL);
    LineTo(hdc, x + 50, y - 100);

    // Шарики на концах антенн
    HPEN PenBall = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(hdc, PenBall);
    Ellipse(hdc, x - 55, y - 105, x - 45, y - 95); // Левый шарик
    Ellipse(hdc, x + 45, y - 105, x + 55, y - 95); // Правый шарик

    // Восстановление пера и очистка ресурсов
    SelectObject(hdc, oldPen);
    DeleteObject(PenAntenna);
    DeleteObject(PenBall);
}//end TelevisionWithAntenna::Show

//start TelevisionWithAntenna::Hide
void TelevisionWithAntenna::Hide() 
{
    Television::Hide();
}//end TelevisionWithAntenna::Hide

// Разбитый телевизор (с сеткой на экране)
//start BrokenTelevision::BrokenTelevision
BrokenTelevision::BrokenTelevision(int InitX, int InitY) : Television(InitX, InitY) 
{
    id = 2; // Идентификатор разбитого телевизора
}//end BrokenTelevision::BrokenTelevision

//BrokenTelevision::~BrokenTelevision
BrokenTelevision::~BrokenTelevision() 
{ 
}//end BrokenTelevision::~BrokenTelevision

// Отрисовка разбитого телевизора
//start BrokenTelevision::Show
void BrokenTelevision::Show() 
{
    //Рисуем базовый телевизор
    Television::Show();

    //Добавляем сетку "разбитого" экрана
    HPEN gridPen = CreatePen(PS_SOLID, 1, RGB(100, 100, 255));
    SelectObject(hdc, gridPen);

    // Вертикальные линии сетки
    for (int i = 1; i <= 8; i++) 
    {
        int lineX = x - 55 + (i * 12);
        MoveToEx(hdc, lineX, y - 35, NULL);
        LineTo(hdc, lineX, y + 25);
    }//end for

    // Горизонтальные линии сетки
    for (int i = 1; i <= 5; i++) 
    {
        int lineY = y - 35 + (i * 10);
        MoveToEx(hdc, x - 55, lineY, NULL);
        LineTo(hdc, x + 55, lineY);
    }//end for 

    DeleteObject(gridPen);
}//end BrokenTelevision::Show

//start BrokenTelevision::Hide
void BrokenTelevision::Hide() 
{
    Television::Hide();
}//end BrokenTelevision::Hide

// Телевизор без ножек
//start TelevisionWithoutLegs::TelevisionWithoutLeg
TelevisionWithoutLegs::TelevisionWithoutLegs(int InitX, int InitY) : Television(InitX, InitY) 
{
    id = 3; // Идентификатор телевизора без ножек
}//end TelevisionWithoutLegs::TelevisionWithoutLeg

//start TelevisionWithoutLegs::~TelevisionWithoutLegs
TelevisionWithoutLegs::~TelevisionWithoutLegs() 
{
}//TelevisionWithoutLegs::~TelevisionWithoutLegs

// Отрисовка телевизора без ножек
//start TelevisionWithoutLegs::Show
void TelevisionWithoutLegs::Show() 
{
    visible = true;

    HPEN PenR = CreatePen(PS_SOLID, 2, RGB(139, 69, 19)); // Коричневый
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));     // Черный

    // Рисуем те же элементы, что и базовый телевизор, но без ножек
    SelectObject(hdc, PenR);
    Rectangle(hdc, x - 80, y - 60, x + 80, y + 70);

    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 70, y - 50, x + 70, y + 50);
    Rectangle(hdc, x - 60, y + 30, x + 60, y + 45);
    RoundRect(hdc, x - 55, y - 35, x + 55, y + 25, 10, 10);

    // Кнопки 
    Ellipse(hdc, x - 45, y + 42, x - 35, y + 32);
    Ellipse(hdc, x - 30, y + 42, x - 20, y + 32);
    Ellipse(hdc, x + 30, y + 42, x + 40, y + 32);

    DeleteObject(PenB);
    DeleteObject(PenR);
}//end TelevisionWithoutLegs::Show

//start TelevisionWithoutLegs::Hide
void TelevisionWithoutLegs::Hide() 
{
    Television::Hide();
}//end TelevisionWithoutLegs::Hide

// Телевизор без кнопок
//start TelevisionWithoutButtons::TelevisionWithoutButtons
TelevisionWithoutButtons::TelevisionWithoutButtons(int InitX, int InitY) : Television(InitX, InitY) 
{
    id = 4; // Идентификатор телевизора без кнопок
}//end TelevisionWithoutButtons::TelevisionWithoutButtons

//start TelevisionWithoutButtons::~TelevisionWithoutButtons
TelevisionWithoutButtons::~TelevisionWithoutButtons() 
{ 
}//end TelevisionWithoutButtons::~TelevisionWithoutButtons

// Отрисовка телевизора без кнопок
//start TelevisionWithoutButtons::Show
void TelevisionWithoutButtons::Show() 
{
    visible = true;

    HPEN PenR = CreatePen(PS_SOLID, 2, RGB(139, 69, 19)); // Коричневый
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));     // Черный

    SelectObject(hdc, PenR);
    Rectangle(hdc, x - 80, y - 60, x + 80, y + 70);

    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 70, y - 50, x + 70, y + 50);
    Rectangle(hdc, x - 60, y + 30, x + 60, y + 45);
    RoundRect(hdc, x - 55, y - 35, x + 55, y + 25, 10, 10);

    // Ножки
    Rectangle(hdc, x - 70, y + 70, x - 60, y + 80);
    Rectangle(hdc, x + 60, y + 70, x + 70, y + 80);

    DeleteObject(PenB);
    DeleteObject(PenR);
}//end TelevisionWithoutButtons::Show

//start TelevisionWithoutButtons::Hide
void TelevisionWithoutButtons::Hide() 
{
    Television::Hide();
}//end TelevisionWithoutButtons::Hide 