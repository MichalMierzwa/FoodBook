#include "recipe.h"
#include <QDataStream>

recipe::recipe()
{

}

// DEFINICJA KONSTRUKTOR KOPIUJACY - WYLACZAM GO I UZYWAM DOMYSLNEGO!
//recipe::recipe( const recipe &obj)
//{
//    recipeName = obj.recipeName;
//}

recipe::~recipe()
{

}

QDataStream& operator<<(QDataStream& out, const recipe& v)
{
    out << v.recipeName;
    out << v.recipeDescription;
    out << v.recipeCategory;
    out << v.recipeSource;

    out << v.recipePortions;
    out << v.ingredientCounter;
    out << v.prepareTimeHr;
    out << v.prepareTimeMin;
    return out;
}

QDataStream& operator>>(QDataStream& in, recipe& v)
{
    in >> v.recipeName;
    in >> v.recipeDescription;
    in >> v.recipeCategory;
    in >> v.recipeSource;

    in >> v.recipePortions;
    in >> v.ingredientCounter;
    in >> v.prepareTimeHr;
    in >> v.prepareTimeMin;
    return in;
}
