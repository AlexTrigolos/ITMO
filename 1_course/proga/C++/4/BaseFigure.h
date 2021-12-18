#ifndef LABWORK_4_BASEFIGURE_H
#define LABWORK_4_BASEFIGURE_H
#include "IGeoFig.h"
#include "BaseCObject.h"
#include "IPhysObject.h"
#include "IPrintable.h"
#include "IDialogInitiable.h"

class BaseFigure :
    public BaseCObject, public IGeoFig, public IPhysObject,
    public IPrintable, public IDialogInitiable
{

protected:
    double length_;
    double width_;
    int mass_;
    CVector2D position_;
public:
    BaseFigure();
    BaseFigure(int length, int width, int mass, CVector2D vector2D);
    double length();
    double width();
    double square() override;
    double perimeter() override;
    double mass() const override;
    CVector2D position() override;
    void initFromDialog() override;
    bool operator == (const IPhysObject &obj) const override;
    bool operator < (const IPhysObject &obj) const override;
    void draw() override;
    const char* classname() override;
    unsigned int size() override;
};
#endif //LABWORK_4_BASEFIGURE_H