#ifndef shape
#define shape



template<int n>
class Shape
{
public:
using Coordinate = std::pair<double,double>;
using Line = std::pair<Coordinate,Coordinate>;
    virtual ~Shape(){};
    Shape(){};

    virtual Line CutViaY(double y)  =0;


};

template<int n>
class Polygon : public Shape<n>
{
public:
//    using Line = std::pair<typename Shape::Coordinate,typename Shape::Coordinate>;
using Coordinate = typename Shape<n>::Coordinate;
using Line = typename Shape<n>::Line;
private:
    std::vector<Line> Vertices;

    double findon(const Line& L,double y)
    {
        //double f=L.first[0];
        std::cout<<"here?";
        std::cout<<L.first[0];
        Coordinate diff{{L.first[0] - L.second[0],L.first[1] - L.second[1]}};
        std::cout<<"here?2";
        double grad = diff[1]/diff[0];
        double c = -(grad * L.first[0]- L.first[1]);
        return grad * y +c;
    };
public:

    Polygon(std::vector<Line>& co):Vertices(co){
            std::cout<<"ff";
            std::cout<<Vertices[0].first[0];
            };

            //std::cout<<Vertices[0].first[0];};


    Line CutViaY(double y)
    {
        std::cout<<"hh";
        auto g(Vertices[0]);
        std::cout<<"hiya";

        auto it1 = std::find_if(Vertices.cbegin(),Vertices.cend(),
                               [y](const Line& c){
                               return ((c.second[1]<= y && c.first[1]>=y)
                                       || (c.second[1]>= y && c.first[1]<=y));});

        auto it2 = std::find_if(it1,Vertices.cend(),
                               [y](const Line& c){
                               return ((c.second[1]<= y && c.first[1]>=y)
                                       || (c.second[1]>= y && c.first[1]<=y));});
        std::cout<<"here?!!";
        //auto DD(it1);
        //Line l1={it1->first,it1->second};
        std::cout<<"wha";
        auto x1 = findon(*it1,y);
        std::cout<<"here?";
        auto x2 = findon(*it2,y);
        Line out{{x1,y},{x2,y}};
        std::cout<<"here?";
        return out;
    };
};

#endif // shape
