#ifndef recipe_H
#define recipe_H

#include <QString>
#include <QMap>
#include <QMetaType>



class recipe
{

public:
    recipe();
    //recipe(const recipe &obj); /*: recipeName(obj.recipeName) {}*/

    void setName(const QString Name) { recipeName = Name;}
    QString Name() const { return recipeName; }

    void setSourceName(const QString &source) { recipeSource = source; }
    QString SourceName() const { return recipeSource; }

    void setPortionNumber(const int &portion) { recipePortions = portion; }
    int PortionNumber() const { return recipePortions;  }

    void setCategory(const QString &category) { recipeCategory = category; }
    QString Category() const { return recipeCategory; }

    void setDescription(const QString &description) { recipeDescription = description; }
    QString Description() const { return recipeDescription; }

    void setPrepareTimeHr(const int &prepTimeHr) { prepareTimeHr = prepTimeHr; }
    int PrepareTimeHr() const { return prepareTimeHr;  }

    void setPrepareTimeMin(const int &prepTimeMin) { prepareTimeMin = prepTimeMin; }
    int PrepareTimeMin() const { return prepareTimeMin;  }

    void setIngredientCounter(const int &ingCounter) { ingredientCounter = ingCounter; }
    int IngredientCounter() const { return ingredientCounter;  }

    QList<QString> IngredientList;
    QList<int> IngredientCountList;

    ~recipe();

private:
    //Operator << >> reload to read from QVariant to recipe custom object class;
    friend QDataStream& operator << (QDataStream& out, const recipe& v);
    friend QDataStream& operator >> (QDataStream& in, recipe& v);

    QString recipeName;
    QString recipeCategory;
    QString recipeSource;
    QString recipeDescription;

    int recipePortions;
    int ingredientCounter;
    int prepareTimeHr;
    int prepareTimeMin;

};
Q_DECLARE_METATYPE(recipe)

#endif // recipe_H
