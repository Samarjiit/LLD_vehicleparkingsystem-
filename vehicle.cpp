#include<bits/stdc++.h>
using namespace std;

class Vehicle{
    private:
        int rowNum;
        int spotNum;
        //parking time
        chrono::time_point<chrono::system_clock>parkingStartTime;

    public:
        Vehicle(){
            rowNum=-1;
            spotNum=-1;
        }
        void occupySpot(int r,int c){
            parkingStartTime=chrono::system_clock::now();
            rowNum=r;
            spotNum=c;
        }
        void vacateSpot(){
            rowNum=-1;
            spotNum=-1;
        }

    int calculateParkingDurationInHours(){
        auto now=chrono::system_clock::now(); //auto -implicitly copy what is on r8 side 
        auto duration=chrono::duration_cast<chrono::hours>(now-parkingStartTime);
        cout<<"debug time"<<duration.count()<<endl;
        return duration.count(); //actual no of hours 
    }
        //use parking time and current time
        virtual int calculateParkingFee()=0;
        virtual string getType()=0;
    
};


class Car:public Vehicle{
    public:
      string getType(){
        return "Car";
      }
      int calculateParkingFee(){
        return 5*calculateParkingDurationInHours();
      }
};

class Bike :public Vehicle{
    public:
      string getType(){
        return "Bike";
      }
      int calculateParkingFee(){
        return 2*calculateParkingDurationInHours();
      }
};

//now all vechicle are netural for parking lot
class Parking{
    private:
        int rows;
        int spotsPerRow;
        vector<vector<Vehicle*>>grid;

    public:
        void create(int r,int c){
            rows=r;
            spotsPerRow=c;
            grid.resize(r);
            for(int i=0;i<r;i++){
                grid[i].resize(c);
            }
        }

        pair<int ,int >findVacantSpot(){
            for(int i=0;i<rows;i++){
                for(int j=0;j<spotsPerRow;j++){
                    if(grid[i][j]==NULL)return {i,j};
                }
            }
            cout<<"no valid parking space found!!"<<endl;
            return {-1,-1};
        }

        bool park(Vehicle*v,int rowNum,int spotNum){

            if(grid[rowNum][spotNum]!=NULL){
                cout<<"Sorry !!! no parking available at"<<rowNum<<", "<<spotNum<<" \n";
                return false;
            }
            v->occupySpot(rowNum,spotNum);
            grid[rowNum][spotNum]=v;
             cout<<"Your vehicle is parked at "<<rowNum<<", "<<spotNum<<"spot \n";

            return true;
        }

        bool park(Vehicle *v){
            pair<int,int>spot=findVacantSpot();
            v->occupySpot(spot.first,spot.second);
            if(spot.first>=0&& spot.second>=0 &&spot.first<rows && spot.second <spotsPerRow)
                return    park(v,spot.first,spot.second);
           
            cout<<"sorry!!! no parking available.\n";
            return false;
            
        }

        void leave(Vehicle *v){
                for(int i=0;i<rows;i++){
                    for(int j=0;j<spotsPerRow;j++){
                        if(grid[i][j]==v){
                            grid[i][j]=NULL;
                            int fee=v->calculateParkingFee();
                            cout<<"Fees is - Rs. "<<fee<<endl;
                            v->vacateSpot();
                        }
                    }
                }
        }

        void printParking(){
            for(int i=0;i<rows;i++){
                for(int j=0;j<spotsPerRow;j++){
                    cout<<grid[i][j]<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
        }
};


int main(){

        Parking p;
        p.create(3,2);
        p.printParking();

        Car c1,c2;
        Bike b1;
        p.park(&c1);
        p.printParking();

        p.park(&c2,0,0);
        p.printParking();

        p.park(&c2);
        p.printParking();

        p.park(&b1,2,1);
        p.printParking();
        p.leave(&c2);
        p.printParking();
        p.leave(&c1);
        p.printParking();
        p.leave(&b1);
        p.printParking();
    return 0;
}




Output :
0 0 
0 0 
0 0 

Your vehicle is parked at 0, 0spot 
0x61fee0 0 
0 0 
0 0 

Sorry !!! no parking available at0, 0 
0x61fee0 0 
0 0 
0 0 

Your vehicle is parked at 0, 1spot 
0x61fee0 0x61fec8 
0 0 
0 0 

Your vehicle is parked at 2, 1spot 
0x61fee0 0x61fec8 
0 0 
0 0x61feb0 

debug time0
Fees is - Rs. 0
0x61fee0 0 
0 0 
0 0x61feb0 

debug time0
Fees is - Rs. 0
0 0 
0 0 
0 0x61feb0 

debug time0
Fees is - Rs. 0
0 0 
0 0 
0 0 