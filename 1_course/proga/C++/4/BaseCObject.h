#ifndef BASECOBJECT_H

#define BASECOBJECT_H



class BaseCObject

{

public:

    virtual const char* classname() = 0;

    virtual unsigned int size() = 0;

};



#endif //LABWORK_4_BASECOBJECT_H