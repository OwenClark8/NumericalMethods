#ifndef DIRECTIONHEADERDEF
#define DIRECTIONHEADERDEF



class Direction
{
private:
    Direction(int m);

    int mDirection;

public:
    static Direction North();
    static Direction East();
    static Direction South();
    static Direction West();

    int GetDirection() const;

};
#endif // DIRECTIONHEADERDEF
