#ifndef IPHYSOBJECT_H

#define IPHYSOBJECT_H



#include "CVector2D.h"



class IPhysObject

{

public:

    virtual double mass() const = 0 ;

    virtual CVector2D position() = 0;

    virtual bool operator == (const IPhysObject &obj) const = 0;

    virtual bool operator < (const IPhysObject &obj) const = 0;

};



#endif //LABWORK_4_IPHYSOBJECT_H