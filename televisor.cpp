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

//start SimpleCircle::SimpleCircle
SimpleCircle::SimpleCircle(int InitX, int InitY, int r) : Figure(InitX, InitY, 2)
{
    radius = r;

    // Область коллизии будет прямоугольной
    SetBounds(radius + 5, radius + 5, radius + 5, radius + 5);

    // Устанавливаем размер (используется для границ)
    SetSize(radius * 2, radius * 2);
}//end SimpleCircle::SimpleCircle

//start SimpleCircle::~SimpleCircle
SimpleCircle::~SimpleCircle()
{
}//end SimpleCircle::~SimpleCircle

// Отрисовка круга
//start SimpleCircle::Show
void SimpleCircle::Show()
{
    visible = true;

    // Рисуем круг (зеленый)
    HPEN circlePen = CreatePen(PS_SOLID, 3, RGB(0, 150, 0));
    HBRUSH circleBrush = CreateSolidBrush(RGB(200, 255, 200));

    HPEN oldPen = (HPEN)SelectObject(hdc, circlePen);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, circleBrush);

    // Рисуем закрашенный круг
    Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);

    // Добавляем контур для лучшей видимости
    HPEN outlinePen = CreatePen(PS_SOLID, 1, RGB(0, 100, 0));
    SelectObject(hdc, outlinePen);
    Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);

    // Добавляем крестик в центре для обозначения центра
    HPEN centerPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    SelectObject(hdc, centerPen);

    // Вертикальная линия крестика
    MoveToEx(hdc, x, y - 5, NULL);
    LineTo(hdc, x, y + 5);

    // Горизонтальная линия крестика
    MoveToEx(hdc, x - 5, y, NULL);
    LineTo(hdc, x + 5, y);

    // Восстанавливаем старые объекты
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);

    // Очистка ресурсов
    DeleteObject(circlePen);
    DeleteObject(circleBrush);
    DeleteObject(outlinePen);
    DeleteObject(centerPen);
}//end SimpleCircle::Show

//start TVBase::TVBase
TVBase::TVBase(int InitX, int InitY) : Point(InitX, InitY)
{
    id = 0;
}//end TVBase::TVBase

//start TVBase::~TVBase
TVBase::~TVBase()
{
}//end TVBase::~TVBase

//start TVBase::Show
void TVBase::Show()
{
    visible = true;

    // Порядок рисования частей телевизора
    DrawSpeakers();    // Динамики (если есть) - рисуем первыми
    DrawBody();        // Корпус
    DrawScreen();      // Экран
    DrawControlPanel();// Панель управления
    DrawButtons();     // Кнопки
    DrawLegs();        // Ножки
    DrawAntenna();     // Антенна (если есть)
}//end TVBase::Show

//start TVBase::Hide
void TVBase::Hide()
{
    visible = false;

    // Создание белых кисти и пера для закрашивания
    HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

    // Сохранение старых объектов и выбор новых
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);

    // Закрашивание области телевизора
    Rectangle(hdc, GetLeft() - 5, GetTop() - 5, GetRight() + 5, GetBottom() + 5);

    // Восстановление старых объектов
    SelectObject(hdc, oldBrush);
    SelectObject(hdc, oldPen);

    // Очистка ресурсов
    DeleteObject(brush);
    DeleteObject(pen);
}//end TVBase::Hide

//start Television::Television
Television::Television(int InitX, int InitY) : TVBase(InitX, InitY)
{
    SetId(0);
}//end Television::Television

//start Television::~Television
Television::~Television()
{
}//end Television::~Television

//start Television::DrawBody
void Television::DrawBody()
{
    HPEN PenR = CreatePen(PS_SOLID, 2, RGB(139, 69, 19));
    SelectObject(hdc, PenR);
    Rectangle(hdc, x - 80, y - 60, x + 80, y + 70);
    DeleteObject(PenR);
}//end Television::DrawBody

//start Television::DrawScreen
void Television::DrawScreen()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 70, y - 50, x + 70, y + 50);
    RoundRect(hdc, x - 55, y - 35, x + 55, y + 25, 10, 10);
    DeleteObject(PenB);
}//end Television::DrawScreen

//start Television::DrawControlPanel
void Television::DrawControlPanel()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 60, y + 30, x + 60, y + 45);
    DeleteObject(PenB);
}//end Television::DrawControlPanel

//start Television::DrawButtons
void Television::DrawButtons()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Ellipse(hdc, x - 45, y + 42, x - 35, y + 32);
    Ellipse(hdc, x - 30, y + 42, x - 20, y + 32);
    Ellipse(hdc, x + 30, y + 42, x + 40, y + 32);
    DeleteObject(PenB);
}//end Television::DrawButtons

//start Television::DrawLegs
void Television::DrawLegs()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 70, y + 70, x - 60, y + 80);
    Rectangle(hdc, x + 60, y + 70, x + 70, y + 80);
    DeleteObject(PenB);
}//end Television::DrawLegs

//start TelevisionWithAntenna::TelevisionWithAntenna
TelevisionWithAntenna::TelevisionWithAntenna(int InitX, int InitY) : TVBase(InitX, InitY)
{
    SetId(1);
}//end TelevisionWithAntenna::TelevisionWithAntenna

//start TelevisionWithAntenna::~TelevisionWithAntenna
TelevisionWithAntenna::~TelevisionWithAntenna()
{
}//end TelevisionWithAntenna::~TelevisionWithAntenna

//start TelevisionWithAntenna::DrawBody 
void TelevisionWithAntenna::DrawBody()
{
    HPEN PenR = CreatePen(PS_SOLID, 2, RGB(139, 69, 19));
    SelectObject(hdc, PenR);
    Rectangle(hdc, x - 80, y - 60, x + 80, y + 70);
    DeleteObject(PenR);
}//end TelevisionWithAntenna::DrawBody

//start TelevisionWithAntenna::DrawScreen
void TelevisionWithAntenna::DrawScreen()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 70, y - 50, x + 70, y + 50);
    RoundRect(hdc, x - 55, y - 35, x + 55, y + 25, 10, 10);
    DeleteObject(PenB);
}//end TelevisionWithAntenna::DrawScreen

//start TelevisionWithAntenna::DrawControlPanel
void TelevisionWithAntenna::DrawControlPanel()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 60, y + 30, x + 60, y + 45);
    DeleteObject(PenB);
}//end TelevisionWithAntenna::DrawControlPanel

//start TelevisionWithAntenna::DrawButtons
void TelevisionWithAntenna::DrawButtons()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Ellipse(hdc, x - 45, y + 42, x - 35, y + 32);
    Ellipse(hdc, x - 30, y + 42, x - 20, y + 32);
    Ellipse(hdc, x + 30, y + 42, x + 40, y + 32);
    DeleteObject(PenB);
}//end TelevisionWithAntenna::DrawButtons

//start TelevisionWithAntenna::DrawLegs
void TelevisionWithAntenna::DrawLegs()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 70, y + 70, x - 60, y + 80);
    Rectangle(hdc, x + 60, y + 70, x + 70, y + 80);
    DeleteObject(PenB);
}//end TelevisionWithAntenna::DrawLegs

//start TelevisionWithAntenna::DrawAntenna
void TelevisionWithAntenna::DrawAntenna()
{
    HPEN PenAntenna = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
    HPEN oldPen = (HPEN)SelectObject(hdc, PenAntenna);

    MoveToEx(hdc, x - 30, y - 60, NULL);
    LineTo(hdc, x - 50, y - 100);
    MoveToEx(hdc, x + 30, y - 60, NULL);
    LineTo(hdc, x + 50, y - 100);

    HPEN PenBall = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(hdc, PenBall);
    Ellipse(hdc, x - 55, y - 105, x - 45, y - 95);
    Ellipse(hdc, x + 45, y - 105, x + 55, y - 95);

    SelectObject(hdc, oldPen);
    DeleteObject(PenAntenna);
    DeleteObject(PenBall);
}//end TelevisionWithAntenna::DrawAntenna
  
//start BrokenTelevision::BrokenTelevision
BrokenTelevision::BrokenTelevision(int InitX, int InitY) : TVBase(InitX, InitY)
{
    SetId(2);
}//end BrokenTelevision::BrokenTelevision

//start BrokenTelevision::~BrokenTelevision
BrokenTelevision::~BrokenTelevision()
{
}//end BrokenTelevision::~BrokenTelevision

//start BrokenTelevision::DrawBody
void BrokenTelevision::DrawBody()
{
    HPEN PenR = CreatePen(PS_SOLID, 2, RGB(139, 69, 19));
    SelectObject(hdc, PenR);
    Rectangle(hdc, x - 80, y - 60, x + 80, y + 70);
    DeleteObject(PenR);
}//end BrokenTelevision::DrawBody

//start BrokenTelevision::DrawScreen
void BrokenTelevision::DrawScreen()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 70, y - 50, x + 70, y + 50);
    RoundRect(hdc, x - 55, y - 35, x + 55, y + 25, 10, 10);
    DeleteObject(PenB);
}//end BrokenTelevision::DrawScreen

//start BrokenTelevision::DrawControlPanel
void BrokenTelevision::DrawControlPanel()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 60, y + 30, x + 60, y + 45);
    DeleteObject(PenB);
}//end BrokenTelevision::DrawControlPanel

//start BrokenTelevision::DrawControlPanel
void BrokenTelevision::DrawButtons()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Ellipse(hdc, x - 45, y + 42, x - 35, y + 32);
    Ellipse(hdc, x - 30, y + 42, x - 20, y + 32);
    Ellipse(hdc, x + 30, y + 42, x + 40, y + 32);
    DeleteObject(PenB);
}//end BrokenTelevision::DrawControlPanel

//start BrokenTelevision::DrawLegs
void BrokenTelevision::DrawLegs()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 70, y + 70, x - 60, y + 80);
    Rectangle(hdc, x + 60, y + 70, x + 70, y + 80);
    DeleteObject(PenB);
}//end BrokenTelevision::DrawLegs

//start BrokenTelevision::DrawCrackedScreen
void BrokenTelevision::DrawCrackedScreen()
{
    HPEN gridPen = CreatePen(PS_SOLID, 1, RGB(100, 100, 255));
    SelectObject(hdc, gridPen);

    for (int i = 1; i <= 8; i++)
    {
        int lineX = x - 55 + (i * 12);
        MoveToEx(hdc, lineX, y - 35, NULL);
        LineTo(hdc, lineX, y + 25);
    }

    for (int i = 1; i <= 5; i++)
    {
        int lineY = y - 35 + (i * 10);
        MoveToEx(hdc, x - 55, lineY, NULL);
        LineTo(hdc, x + 55, lineY);
    }

    DeleteObject(gridPen);
}//end BrokenTelevision::DrawCrackedScreen

//start TelevisionWithoutLegs::TelevisionWithoutLegs
TelevisionWithoutLegs::TelevisionWithoutLegs(int InitX, int InitY) : TVBase(InitX, InitY)
{
    SetId(3);
}//end TelevisionWithoutLegs::TelevisionWithoutLegs

//start TelevisionWithoutLegs::~TelevisionWithoutLegs
TelevisionWithoutLegs::~TelevisionWithoutLegs()
{
}//end TelevisionWithoutLegs::~TelevisionWithoutLegs

//start TelevisionWithoutLegs::DrawBody
void TelevisionWithoutLegs::DrawBody()
{
    HPEN PenR = CreatePen(PS_SOLID, 2, RGB(139, 69, 19));
    SelectObject(hdc, PenR);
    Rectangle(hdc, x - 80, y - 60, x + 80, y + 70);
    DeleteObject(PenR);
}//end TelevisionWithoutLegs::DrawBody

//start TelevisionWithoutLegs::DrawScreen
void TelevisionWithoutLegs::DrawScreen()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 70, y - 50, x + 70, y + 50);
    RoundRect(hdc, x - 55, y - 35, x + 55, y + 25, 10, 10);
    DeleteObject(PenB);
}//end TelevisionWithoutLegs::DrawScreen

//start TelevisionWithoutLegs::DrawControlPanel
void TelevisionWithoutLegs::DrawControlPanel()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 60, y + 30, x + 60, y + 45);
    DeleteObject(PenB);
}//end TelevisionWithoutLegs::DrawControlPanel

//start TelevisionWithoutLegs::DrawButtons
void TelevisionWithoutLegs::DrawButtons()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Ellipse(hdc, x - 45, y + 42, x - 35, y + 32);
    Ellipse(hdc, x - 30, y + 42, x - 20, y + 32);
    Ellipse(hdc, x + 30, y + 42, x + 40, y + 32);
    DeleteObject(PenB);
}//end TelevisionWithoutLegs::DrawButtons

//start TelevisionWithoutButtons::TelevisionWithoutButtons
TelevisionWithoutButtons::TelevisionWithoutButtons(int InitX, int InitY) : TVBase(InitX, InitY)
{
    SetId(4);
}//end TelevisionWithoutButtons::TelevisionWithoutButtons

//start TelevisionWithoutButtons::~TelevisionWithoutButtons
TelevisionWithoutButtons::~TelevisionWithoutButtons()
{
}//end TelevisionWithoutButtons::~TelevisionWithoutButtons

//start TelevisionWithoutButtons::DrawBody
void TelevisionWithoutButtons::DrawBody()
{
    HPEN PenR = CreatePen(PS_SOLID, 2, RGB(139, 69, 19));
    SelectObject(hdc, PenR);
    Rectangle(hdc, x - 80, y - 60, x + 80, y + 70);
    DeleteObject(PenR);
}//end TelevisionWithoutButtons::DrawBody

//start TelevisionWithoutButtons::DrawScreen
void TelevisionWithoutButtons::DrawScreen()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 70, y - 50, x + 70, y + 50);
    RoundRect(hdc, x - 55, y - 35, x + 55, y + 25, 10, 10);
    DeleteObject(PenB);
}//end TelevisionWithoutButtons::DrawScreen

//start TelevisionWithoutButtons::DrawControlPanel
void TelevisionWithoutButtons::DrawControlPanel()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 60, y + 30, x + 60, y + 45);
    DeleteObject(PenB);
}//end TelevisionWithoutButtons::DrawControlPanel

//start TelevisionWithoutButtons::DrawLegs
void TelevisionWithoutButtons::DrawLegs()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 70, y + 70, x - 60, y + 80);
    Rectangle(hdc, x + 60, y + 70, x + 70, y + 80);
    DeleteObject(PenB);
}//end TelevisionWithoutButtons::DrawLegs

//start TelevisionWithSpeakers::TelevisionWithSpeakers
TelevisionWithSpeakers::TelevisionWithSpeakers(int InitX, int InitY) : Television(InitX, InitY)
{
    SetId(5);
}//end TelevisionWithSpeakers::TelevisionWithSpeakers

//start TelevisionWithSpeakers::~TelevisionWithSpeakers
TelevisionWithSpeakers::~TelevisionWithSpeakers()
{
}//end TelevisionWithSpeakers::~TelevisionWithSpeakers

//start TelevisionWithSpeakers::DrawLegs
void TelevisionWithSpeakers::DrawLegs()
{
    HPEN PenB = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, PenB);
    Rectangle(hdc, x - 70, y + 70, x - 60, y + 100); 
    Rectangle(hdc, x + 60, y + 70, x + 70, y + 100);
    DeleteObject(PenB);
}//end TelevisionWithSpeakers::DrawLegs

//start TelevisionWithSpeakers::DrawSpeakers
void TelevisionWithSpeakers::DrawSpeakers()
{
    HPEN PenGray = CreatePen(PS_SOLID, 2, RGB(128, 128, 128));
    SelectObject(hdc, PenGray);

    Rectangle(hdc, x - 100, y - 40, x - 85, y + 40);
    Rectangle(hdc, x + 85, y - 40, x + 100, y + 40);

    DeleteObject(PenGray);
}//end TelevisionWithSpeakers::DrawSpeakers
