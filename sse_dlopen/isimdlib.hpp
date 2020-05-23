#ifndef H_SIMDLIB_WRAPPER
#define H_SIMDLIB_WRAPPER
class ISimdLib {
public:
    ISimdLib(){};
    virtual ~ISimdLib(){};
    virtual void doStuffFast() = 0;
};
#endif
