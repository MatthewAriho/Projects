//make board- 43*23
//make snake
//spawn snake
//make snake move in one direction
//control snake
//implement food
//make snake interact with food
//make sure game ends when it hits the border

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <dos.h> //for delay
#include <conio.h> //for getch()
using namespace std;

// class Cell{
// public:
// 	string type;
// 	Cell(const string s)
// 	:type(s){
// 		try{
// 			if(type!="empty"&&type!="body"&&type!="head"&&type!="food") throw;//crash
// 		}catch(...){
// 			cout<<"Incorrect cell initialisation";
// 		}
// 	}
// };

enum class Cell{
	empty,
	food,
	body,
	head,
};

class Cood{
public:
	int row;
	int col;

	Cood(int r, int c):
	row(r), col(c){
	}
	Cood(const Cood &a)
	:Cood(a.row, a.col){

	}
    Cood(){
    }
};

class Snake{
public:
	int length;
	Cood head;
	vector <Cood> body;
	int dir;	//0- north, 1-east, 2-south, 3-west

	Snake(const int l, const Cood h, int d):
	length(l), head(h), dir(d){
		if(d==0){
			Cood a(head);
			a.row++;
			for(int i=0; i<l; i++){
				body.push_back(a);
				a.row++;
			}
		}else if(d==1){
			Cood a(head);
			a.col--;
			for(int i=0; i<l; i++){
				body.push_back(a);
				a.col--;
			}
		}else if(d==2){
			Cood a(head);
			a.row--;
			for(int i=0; i<l; i++){
				body.push_back(a);
				a.row--;
			}
		}if(d==3){
			Cood a(head);
			a.col++;
			for(int i=0; i<l; i++){
				body.push_back(a);
				a.col++;
			}
		}
	}
	Snake()
	:Snake(3, Cood(10,20), 1){
	}
	void move(){
		if(dir==0){
			//each body part moves to the position of the cell infront of it
			for(int i=length-1; i>=0; i--){
				if(i==0){
					body[0]=head;
					head.row--;
				}else{
					body[i]=body[i-1];
				}
			}
		}else if(dir==1){
			for(int i=length-1; i>=0; i--){
				if(i==0){
					body[0]= head;
					head.col++;
				}else{
					body[i]=body[i-1];
				}
			}
		}else if(dir==2){
			for(int i=length-1; i>=0; i--){
				if(i==0){
					body[0]= head;
					head.row++;
				}else{
					body[i]=body[i-1];
				}
			}
		}else if(dir==3){
			for(int i=length-1; i>=0; i--){
				if(i==0){
					body[0]= head;
					head.col--;
				}else{
					body[i]=body[i-1];
				}
			}
		}
	}
	void feed(){
		Cood a(body[length-1]);
		if(dir==0){
			a.row--;
		}else if(dir==1){
			a.col--;
		}else if(dir==2){
			a.row++;
		}else if(dir==3){
			a.col++;
		}
		body.push_back(a);
		length++;
	}

};


typedef vector<vector<Cell>> Board; //matrix of cells

vector<Cell> row_of_cells(){
	vector<Cell> c;
	for(int i=0; i<43; i++){
		c.push_back(Cell::empty);
	}
	return c;
}

Board make_empty_board(){
	vector <Cell> r1 = row_of_cells();
	vector <Cell> r2 = row_of_cells();
	vector <Cell> r3 = row_of_cells();
	vector <Cell> r4 = row_of_cells();
	vector <Cell> r5 = row_of_cells();
	vector <Cell> r6 = row_of_cells();
	vector <Cell> r7 = row_of_cells();
	vector <Cell> r8 = row_of_cells();
	vector <Cell> r9 = row_of_cells();
	vector <Cell> r10 = row_of_cells();
	vector <Cell> r11 = row_of_cells();
	vector <Cell> r12 = row_of_cells();
	vector <Cell> r13 = row_of_cells();
	vector <Cell> r14 = row_of_cells();
	vector <Cell> r15 = row_of_cells();
	vector <Cell> r16 = row_of_cells();
	vector <Cell> r17 = row_of_cells();
	vector <Cell> r18 = row_of_cells();
	vector <Cell> r19 = row_of_cells();
	vector <Cell> r20 = row_of_cells();
	vector <Cell> r21 = row_of_cells();
	vector <Cell> r22 = row_of_cells();
	vector <Cell> r23 = row_of_cells();
	Board result={r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23};
	return result;
}

string to_str(const Cell& c, const Snake &s){
	if(c==Cell::empty) return " ";
	else if(c==Cell::food) return "F";
	else if(c==Cell::body) return "*";
	else if(c==Cell::head){
		if(s.dir==0) return "^";
		else if(s.dir==1) return ">";
		else if(s.dir==2) return "v";
		else if(s.dir==3) return "<";
	}
	return " ";
}

void draw_snake(Snake &s, Board &b){
	Cood position(s.head);
	b[position.row][position.col]=Cell::head;
	for(Cood a : s.body){
		b[a.row][a.col]= Cell::body;
	}
}

void delay(int n){
    int a=n;
    for(int i=0; i<n; i++){
        a=a+i;
    }
}
void display(const Board& board, const Snake& s){
	const string center = "			";
	cout<<center<<"       ";
	string s1=center+"     ";
	string s2=center+"     ";
	for(int i=0; i<43; i++){
		s1+= "_";
		s2+= "-";
	}
	s1+="\n";
	s2+="\n";
	cout<<"\n "<<s1;
	char r = 'a';
	int counter =1;
	for(const vector<Cell> & row : board){
		cout<<center<<" "<<r<<"- |";
		for(Cell c: row){
			cout<<to_str(c,s)<<"";
		}
		cout<<"|\n";
		if(counter==23) cout<<s2;
		r++;
		counter++;
	}
	cout<<"Use W/w to move upwards \n"
			<<"A/a to move towards the right \n"
			<<"S/s to move downwards \n"
			<<"D/d to move towards the left \n"
			<<"Else to keep moving. \n";
	delay(10000000);
}

bool check_input(char c){
	return !(c=='a'||c=='A'||c=='s'||c=='S'||c=='d'||c=='D'||c=='w'||c=='W');
}

char input(){
	char s;
	do{

	}while(!check_input(s));
	return s;
}

void empty_board(Board& b){
	for(int i=0; i<23; i++){
		for(int j=0; j<43; j++){
			if(b[i][j]!=Cell::food) b[i][j]=Cell::empty;
		}
	}
}

Cood rand_cell(int r, int c){
	Cood d;
	srand (time(NULL));
	d.row= rand()%r;
	d.col= rand()%c;
	return d;
}

void Food(Board& b){
	Cood f= rand_cell(23,43);
	Cell c= Cell::food;
	b[f.row][f.col]=c;
}

bool operator==(const Cood& c, const Cood& d){
	return c.row==d.row&&c.col==d.col;
}

bool in_bounds(const Snake& s){
	Cood position(s.head);
	bool result = true;
	if(position.col==0&&s.dir==3) result= false;
	else if(position.row==0&&s.dir==0) result= false;
	else if(position.row==22&&s.dir==2) result= false;
	else if(position.col==42&&s.dir==1) result= false;
	for(Cood b:s.body){
		if(b==position) return false;
	}
	return result;
}

bool check_for_food(const Snake&s, const Board&b){
	Cood position(s.head);
	if(s.dir==0){
		return b[position.row-1][position.col]==Cell::food;
	}else if(s.dir==1){
		return b[position.row][position.col+1]==Cell::food;
	}else if(s.dir==2){
		return b[position.row+1][position.col]==Cell::food;
	}else if(s.dir==3){
		return b[position.row][position.col-1]==Cell::food;
	}
}

int main(){
	//initialize board
	Board b= make_empty_board();
	Snake s;
	draw_snake(s, b);
	Food(b);
	display(b, s);
	empty_board(b);
    char move='m';
	while(in_bounds(s)){
        Cood position(s.head);
		move=getch();
		if(move=='a'||move=='A'){		//check direction and make sure it makes sense- u cant go west when u r currently facing east
			s.dir= 3;
		}else if(move=='d'||move=='D'){
			s.dir= 1;
		}else if(move=='s'||move=='S'){
			s.dir= 2;
		}else if(move=='w'||move=='W'){
			s.dir= 0;
		}
		do{
			if(check_for_food(s,b)){
				s.feed();
				b[position.row][position.col]=Cell::empty;
				Food(b);
			}
			s.move();
			draw_snake(s, b);
			system("cls");
			display(b, s);
			empty_board(b);
		}while(!kbhit()&&in_bounds(s));
	}
	cout<<"You died!\n";
}


//fix end bugs
//add lives
//add scoring system