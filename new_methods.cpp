#include "televisor.h"

// Функция для проверки столкновения между телевизором и фигурой
bool CheckCollision(Television* tv, Figure* figure) {
    return !(tv->GetRight() < figure->GetLeft() ||
        tv->GetLeft() > figure->GetRight() ||
        tv->GetBottom() < figure->GetTop() ||
        tv->GetTop() > figure->GetBottom());
}