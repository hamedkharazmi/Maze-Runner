template <typename var>
class Array{
private:
    var *pointer;
    const int row;
    const int column;
    const int MAX_SIZE;
public:
    Array(int row,int column):
    MAX_SIZE(row*column),row(row),column(column){
        pointer =new var [MAX_SIZE];}
    ~Array(){delete[] pointer;}
    var& Set(int row,int column){return pointer[row*(this->column-1)+column];}
    int Row(){return row;}
    int Column(){return column;}
};
template <typename var>
class Stack
{
private:
    var *Pointer;
    int front;
    const int max;
    bool IsFull(){
        if(front==max){
            std::cout<<"Stack is Full!\n";
            return true;
        }
        return false;
    }
    bool IsEmpty(){
        if(front==-1){
            std::cout<<"Stack is empty!\n";
            return true;
        }
        return false;
    }
public:
    Stack(int length):max(length){Pointer=new var[max];front=0;}
    ~Stack(){delete[] Pointer;front=0;}
    var Pop(){if(!IsEmpty()) return Pointer[--front];}
    var Return(){if(!IsEmpty()) return Pointer[front-1];}
    void Push(var data){if(!IsFull()) Pointer[front++]=data;}
    void Echo(){
        if(!IsEmpty()){
            std::cout<<"{ ";
            for(int i=0;i<front;i++)
                std::cout<<Pointer[i]<<" ,";
            std::cout<<"\b}\n";
        }
    }
    bool Search(var& temp){
        if(!IsEmpty()){
            for(int i=0;i<front;i++)
                if(!(Pointer[i]!=temp))return true;
            return false;
        }
    }
    int Len(){return front-1;}
};
template <typename var>
class Queue
{
private:
    int front;
    int rear;
    var *Pointer;
    const int MAX;
    int Index(int number){return (number+1)%MAX;}
    void Reset(){rear=front=-1;}
    bool IsFull(){
        if(Index(rear)==front){
            std::cout<<"Queue Is Full!"<<std::endl;
            return true;
        }
        return false;
    }
    bool IsEmpty(){
        if(rear==-1&&front==-1){
            std::cout<<"Queue Is Empty!"<<std::endl;
            return true;
        }
        return false;
    }
public:
    Queue(int length):MAX(length){Pointer=new var[MAX];Reset();}
    ~Queue(){delete[] Pointer;Reset();}
    void Push(var data){
        if(!IsFull()){
            if(rear==-1)
                front=0;
            rear=Index(rear);
            Pointer[rear]=data;
        }
    }
    var Pop(){
        int temp=front;
        if(!IsEmpty()){
            if(front!=rear)
                front=Index(front); 
            else
                Reset();
            return Pointer[temp];
        }
    }
    void Echo(){
        if(!IsEmpty()){
            int j=front;
            std::cout<<"Queue:[";
            for(int i=0;i<this->len();i++){
                std::cout<<Pointer[j]<<",";
                j=Index(j);
            }
            std::cout<<"\b]\n";
        }
    }
    bool Search(var &temp){
        if(!IsEmpty()){
            int j=front;
            for(int i=0;i<this->len();i++){
                if(!(Pointer[j]!=temp))
                    return true;
                j=Index(j);
            }
            return false;
        }
    }
    int Len(){return front>rear ? MAX-(front-rear-1):rear-front+1;}
    int Size(){return MAX;}
    
};
struct Point{
    short x,y;
    Point(short x=0,short y=0):x(x),y(y){}
    Point operator+(const Point &temp)
    {
        Point result ;
        result.x=x+temp.x;
        result.y=y+temp.y;
        return result;
    }
    bool operator==(Point &temp){if(x==temp.x && y==temp.y) return true; return false;}
    friend ostream& operator<<(ostream& out,Point&temp){cout<<"("<<temp.x<<","<<temp.y<<")";}
};
enum Status{Allow,Denied,Seen,Finish};
const Point Direct[][4]={
    {Point(0,1),Point(1,0),Point(0,-1),Point(-1,0)},
    {Point(1,0),Point(0,1),Point(0,-1),Point(-1,0)},
};
