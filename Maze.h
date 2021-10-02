template <typename> class Maze;
class  Square
{
	short flag;
	short mark;
	Point possition;
public:
	Square(){mark=0;}
	Point& Possition(){return possition;}
	short& Flag(){return flag;}
	short& Mark(){return mark;}
	bool operator!=(Square temp){
		if(flag==temp.flag && mark==temp.mark && possition==temp.possition)
			return false;
		return true;
	}
	friend ostream& operator<<(ostream & out,Square temp)
	{
		out<<temp.possition;
		return out;
	}
};
template <typename var>
class Mouse
{
private:
	Stack<var> Way;
	Stack<var> Block;
	Stack<var> Multi_way;
public:
	var *possition;
	Mouse(int length):Way(length),Multi_way(length),Block(length){}
	template <typename> friend class Maze;
};	
template <typename var=Square>
class Maze
{
	Array<var> Ground;
	Mouse<var> Rat;
public:
	Maze(int row,int column):Ground(row+2,column+2),Rat(row*column){
		//Creating Ground
		for(int i=0;i<row+2;i++)
			for(int j=0;j<column+2;j++){
				if(!(i&&j)||i==row+1||j==column+1)
					Ground.Set(i,j).Flag()=Denied;
				else
					Ground.Set(i,j).Flag()=Allow;
				Ground.Set(i,j).Possition()=Point(i,j);
			}	
		//Desfault Values
		Ground.Set(1,1).Flag()=Seen;
		Rat.possition=&Ground.Set(1,1);
		Rat.Way.Push(*(Rat.possition));
		Ground.Set(row,column).Flag()=Finish;
		//Blocking Houses
		char decide;cout<<"\tblocking houses:\n";
		cout<<"(Suppose Index starts of 1!)\n";
		Point temp;
		do{
			Maze::Draw(this);
			cout<<"Enter Row:";cin>>temp.x;
			cout<<"Enter Column:";cin>>temp.y;
			Ground.Set(temp.x,temp.y).Flag()=Denied;
			Rat.Block.Push(Ground.Set(temp.x,temp.y));
			cout<<"Continue ?[Yes(y) or No(n)]:";cin>>decide;
		}while(decide!='n');
		Maze::Draw(this);
	}
	static Maze<>* Create(){
		int row,column;
		cout<<"Enter Row:";cin>>row;
		cout<<"Enter Column:";cin>>column;
		Maze<>*Pointer= new Maze<>(row,column);
		return Pointer;
	}
	static bool Menu()
	{
		Maze<>* Game;
		cout<<"\tMaze Game\n";
		cout<<"1)Create Maze\t2)Solve Maze  :";
		char select;
		cin>>select;
		switch (select)
		{
			case '1':Game=Maze<>::Create();break;
			case '2':Maze<>::Solve(Game);break;
			default:return true;
		}
		return false;
	}
	static void Solve(Maze<> * Game){
		cout<<"\tSolve"<<endl;
		cout<<"1)Solve with Stack\t2)Solve with Queue  :";
		char decide;
		cin>>decide;
		switch(decide){
			case '1':Solve_Stack(Game);break;
			case '2':Solve_Queue(Game);break;
			default:break;
		}
		delete Game;
	}
	//Solving with Stack
	static void Solve_Stack(Maze<>* Game){
		bool spin= Game->Ground.Column()>Game->Ground.Row() ? false:true;
		while(Game->Rat.possition->Flag()!=Finish){
			bool First_Move=false;
			Point move;
			for(short i=0;i<4;i++){
				Point temp=Game->Rat.possition->Possition()+Direct[spin][i];	
				if(Game->Ground.Set(temp.x,temp.y).Flag()==Allow ||
					 Game->Ground.Set(temp.x,temp.y).Flag()==Finish)
				{
					if(!First_Move){
						First_Move=true;
						move=temp;
					}
					else{
						Game->Rat.Multi_way.Push(*(Game->Rat.possition));
						break;
					}
				}
			}
			if(First_Move){
				Game->Rat.possition=&Game->Ground.Set(move.x,move.y);
				if(Game->Rat.possition->Flag()!=Finish)
					Game->Rat.possition->Flag()=Seen;
				Game->Rat.Way.Push(*(Game->Rat.possition));
			}
			else
			{
				while(*(Game->Rat.possition)!=Game->Rat.Multi_way.Return())
				{
					Game->Rat.possition->Flag()=Denied;
				    Game->Rat.Way.Pop();
					Point temp =Game->Rat.Way.Return().Possition();
					Game->Rat.possition=&Game->Ground.Set(temp.x,temp.y);
				}
				Game->Rat.Multi_way.Pop();
			}
			spin=!spin;
		}
		Maze<>::Draw(Game);
		cout<<"Way:";Game->Rat.Way.Echo();
	}
	static void Draw(Maze<>*Game){
		cout<<endl;
		for(int i=1;i<=Game->Ground.Row()-2;i++){
			cout<<"\t";	
			for(int j=1;j<=Game->Ground.Column()-2;j++){
				if(j==Game->Ground.Column()-2){
					if(Game->Rat.Block.Search(Game->Ground.Set(i,j)))
						cout<<"B\n";
					else if(Game->Rat.Way.Search(Game->Ground.Set(i,j)))
						cout<<"S\n";//Game->Rat.Way.Len()-counter++
					else
						cout<<"+\n";
				}
				else{
					if(Game->Rat.Block.Search(Game->Ground.Set(i,j)))
						cout<<"B  ";
					else if(Game->Rat.Way.Search(Game->Ground.Set(i,j)))
						cout<<"S  ";//Game->Rat.Way.Len()-counter++
					else
						cout<<"+  ";
				}
			}
		}
		cout<<endl;
	}
	static void Solve_Queue(Maze<>* game){}
	~Maze(){}

};
