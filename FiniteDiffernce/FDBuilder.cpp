#include "FDBuilder.h"


std::unique_ptr<GridFunction<2>> FDBuilder::GetProduct()
{
    return std::move(mGF);
}

FDBuilder::FDBuilder(std::unique_ptr<Shape<2>> s, double xstepsize,double ystepsize,double ymax,
              double ymin,double xmax,double xmin):
                  mShape(std::move(s)),mxstepsize(xstepsize),mystepsize(ystepsize),maxy(ymax),
                  miny(ymin),maxx(xmax),minx(xmin)
{
    //auto line = mShape->CutViaY(0.5);
}


void FDBuilder::BuildPart()
{
    //auto line2 = mShape->CutViaY(0.5);


    std::vector<BoundaryNode<2>> BNV;
    std::vector<InteriorNode<2>> INV;



    Coordinate co{0,0};
    BoundaryNode<2> BN(co,0,0,false);
    std::pair<bool,int> N{false,0};
    std::pair<bool,int> E{false,0};
    std::pair<bool,int> S{false,0};
    std::pair<bool,int> W{false,0};
    InteriorNode<2> IN{co,0,N,E,S,W};
    int globalbn{0};
    int globalin{0};
    double boundvalue{0};

    //Set up connection matrix to aid set up of nodes

    //std::vector<line> Lines;
    int sizey = ceil((maxy-miny)/mystepsize)+1;
    int sizex = ceil((maxx-minx)/mxstepsize)+1;
    std::vector<std::vector<ConnectS > > Connect;
    Connect.reserve(sizex);
    for(int i=0;i<sizex;i++)
    {
        std::vector<ConnectS> temp;
        temp.reserve(sizey);
        for(int i=0;i<sizey;i++)
        {
            temp.push_back(ConnectS({0,0},0,0));
        }
        Connect.push_back(temp);

    }
    auto f = ConnectS({0,0},0,0);

    //Connect[sizex-1][sizey-1]=ConnectS({0,0},0,0);
    int numBN(0),numIN(0);
    int count=0;
//PROBLEM: maxy-(count)*mystepsize IS VERY SLIGHTLY BELOW 0   CUTVIAY FAILS HERE
    while((count) < sizey)
    {
        //std::cout<<"Input to cut via y is "<<maxy-count*mystepsize<<"   "<<mystepsize<<std::endl;
        auto line ( mShape->CutViaY(maxy-count*mystepsize,mystepsize/2.0));

        //std::cout<<"WHATLISLINE?"<<line.first[0]<<" TO "<<line.second[0]<<std::endl;

        //First deal with first and last lines
        if(count == 0 || count ==sizey-1)
        {

            int xcount=0;
            while(minx + xcount * mxstepsize < line.first[0])
            {
                co={minx + xcount * mxstepsize,line.first[1]};
                Connect[count][xcount]=ConnectS(co,0,0);
                xcount++;

            }

            int count2=0;
            //std::cout<<"TESTESTEST"<<line.first[0]+ count2*mxstepsize<<"    "<<line.second[0]<<std::endl;
            while(line.first[0]+ count2*mxstepsize <=line.second[0])
            {
                co={line.first[0]+count2*mxstepsize,line.first[1]};
                Connect[count][xcount+count2]=ConnectS(co,1,globalbn);
                numBN++;
                globalbn++;
                count2++;
                //std::cout<<"i="<<count2;
            }
            //std::cout<<"pleaseno"<<line.first[1]<<std::endl;
            for(int i=count2+xcount;i<sizex;i++)
            {
                //std::cout<<"i="<<count2;
                co={minx + i * mxstepsize,line.first[1]};
                Connect[count][i]=ConnectS(co,0,0);

            }
            //std::cout<<"pleaseno"<<line.first[1]<<std::endl;
        }
        else
        {
            for(int i=0;i<sizex;i++)
            {
                co={minx + i * mxstepsize,line.first[1]};
                if(minx + i*mxstepsize < line.first[0]-mxstepsize/2.0)
                {
                    //std::cout<<"I= "<<i<<"count = "<<count<<std::endl;
                    //std::cout<<"value= "<<minx + i*mxstepsize<<"count = "<<line.first[0]<<std::endl;
                    Connect[count][i]=ConnectS(co,0,0);
                }
                else if(minx + i*mxstepsize <line.first[0]+mxstepsize/2.0 && minx + i*mxstepsize>= line.first[0]-mxstepsize/2.0)
                {
                    Connect[count][i]=ConnectS(co,1,globalbn);
                    numBN++;
                    globalbn++;
                }
                else if(minx + i*mxstepsize <=line.second[0]+mxstepsize/2.0 && minx + i*mxstepsize> line.second[0]-mxstepsize/2.0)
                {
                    Connect[count][i]=ConnectS(co,1,globalbn);
                    numBN++;
                    globalbn++;
                }
                else if(minx + i*mxstepsize > line.second[0]+mxstepsize/2.0)
                {
                    Connect[count][i]= ConnectS(co,0,0);
                }
                else
                {
                    Connect[count][i]= ConnectS(co,2,globalin);
                    numIN++;
                    globalin++;
                }
            }
        }
        count++;
    }

/*
     int a=sizex;
    int b=sizey;
    for (int i=0;i<a;i++)
    {
        std::cout<<"|";
        for (int j=0;j<b;j++)
        {
            std::cout<<std::setprecision(5)<<std::setw(10)<<(Connect)[i][j].type<<std::setw(10);
        }
        std::cout<<"|"<<std::endl;

    }
*/

    BNV.reserve(numBN);
    INV.reserve(numIN);
    //std::cout<<"finish";
    //Set up boundary and interior nodes
    for(int i=0;i<sizex;i++)
    {
        for(int j=0;j<sizey;j++)
        {
            if(Connect[i][j].type==0)
            {
                continue;
            }
            else if(Connect[i][j].type==1)
            {
                //workout boundvalue here

                BN.ChangeValues(Connect[i][j].C,Connect[i][j].globalval,boundvalue);
                BNV.push_back(BN);

            }
            else if(Connect[i][j].type==2)
            {
                //Cal N,S,W,E
                N={(Connect[i-1][j].type==1),Connect[i-1][j].globalval};
                S={(Connect[i+1][j].type==1),Connect[i+1][j].globalval};
                E={(Connect[i][j+1].type==1),Connect[i][j+1].globalval};
                W={(Connect[i][j-1].type==1),Connect[i][j-1].globalval};

                IN.ChangeValues(Connect[i][j].globalval,N,E,S,W);
                INV.push_back(IN);
            }
        }
    }
    mGF.reset(new GridFunction<2>(INV,BNV,{mxstepsize,mystepsize}));
}
