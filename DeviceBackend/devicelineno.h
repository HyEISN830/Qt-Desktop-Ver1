#include <QString>


#ifndef DEVICELINENO_H
#define DEVICELINENO_H
enum DeviceLineNo
{
    Unknow,
    All,
    W1,
    W2,
    W3,
    N3,
    N2,
    N1
};

class DC
{
public:
    static QString DC_TOSTRING(DeviceLineNo no)
    {
        switch (no)
        {
        case W1:
            return "W1";
        case W2:
            return "W2";
        case W3:
            return "W3";
        case N3:
            return "N3";
        case N2:
            return "N2";
        case N1:
            return "N1";
        case All:
            return "ALl";
        case Unknow:
            return "Unknow";
        default:
            return "default";
        }
    }
};

#endif // DEVICELINENO_H
