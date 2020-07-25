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

const string empty_cell = "  . ";// + "|";
const string o_cell = "  O ";// + "|";
const string x_cell = "  X ";// + "|";
const string move_cell = "  ! ";// + "|";
const string bad_move_cell = "  ~ ";// + "|";
const string center = "			";

enum class Cell{
	empty,
	x,
	o,
	move,
	bad_move,
};

typedef vector<vector<Cell>> Board; //matrix of cells

int count(const Board &board, Cell c){
	int result=0;
	for(const vector <Cell>&row : board){
		for(Cell a: row){
			if(c==a) result++;
		}
	}
	return result;
}

string to_str(const Cell& c){
	switch(c){
		case Cell::empty : return empty_cell;
		case Cell::x : return x_cell;
		case Cell::o : return o_cell;
		case Cell::move : return move_cell;
		case Cell::bad_move : return bad_move_cell;
	}
	return empty_cell;
}
void display(const Board& board){
	cout<<center<<"       "<<"GAME ON\n"
        <<center<<"       ";
	for(int i=0; i<3; i++){
		cout<<(i+1)<<"   ";
	}
	string s1=center+"    ";
	string s2=center+"    ";
	for(int i=0; i<6; i++){
		s1+= " _";
		s2+= " -";
	}
	s1+="\n";
	s2+="\n";
	cout<<"\n"<<s1;
	char r = 'a';
	int counter =1;
	for(const vector<Cell> & row : board){
		cout<<center<<" "<<r<<"- |";
		for(Cell c: row){
			cout<<to_str(c)<<"";
		}
		cout<<"|\n";
		if(counter!=3) cout<<s2;
		r++;
		counter++;
	}
	cout<<s2;
	// cout<<center<<"Number of player pieces "<<x_cell<<" - "<< count(board, Cell::x)<<" \n"
	// 	<<center<<"Number of opponent pieces "<<o_cell<<" - "<< count(board, Cell::o)<<" \n";
}

struct loc{
	int row;
	int col;
	loc(int r, int c){
		row =r;
		col =c;
	}
	loc()
	:row(-1), col(-1)
	{}
	loc(const loc &l)
	{row=l.row, col=l.col;}
	int to_int(){
		return (row*3)+(col+1);
	}
	void print(){
		cout<<row<<" , "<<col<<"\n";
	}
};

bool operator==(loc a, loc b){
	return a.row==b.row&&a.col==b.col;
}

bool search_char(char c, char t){
	const int aTA = 32;
	return c==t||c==t-aTA;
}

bool is_lower(char c){
	return (c>=97&&c<=99);
}

bool is_upper(char c){
	return (c>=65&&c<=67);
}


bool is_alpha(char c){
	return is_lower(c)||is_upper(c);
}

bool is_num(char c){
	return (c>=49&&c<=51);
}

bool check_format(const string& s){
	return (s.size()==2)&&((is_alpha(s[0])&&is_num(s[1]))||(is_num(s[0])&&is_alpha(s[1])));
}

string get_input(){
	string result="";
	cout << "\nWhere would you like to place your piece?\n";
	cin>>result;
	while(!check_format(result)){
		cout << "Invalid input- where would you like to place your piece?\n";
		cin>>result;
	}
	return result;
}

loc get_location(){

 	loc result{};
 	string input = get_input();
 	//letter first or number first
 	//this allows for either C3 or 3C to work etc..
 	if(is_alpha(input[0])){
 		if(is_lower(input[0])) result.row= ((int)input[0])-97;
 		else result.row= ((int)input[0])-65;
 		result.col = ((input[1] - 49));
 	}else{
 		result.col = ((input[0] - 49));
 		if(is_lower(input[1])) result.row= ((int)input[1])-97;
 		else result.row= ((int)input[1])-65;
 	}
 	return result;
}

bool is_valid(loc l, const Board& v){
	if(v[l.row][l.col]!= Cell::empty) return false;
	else return true;
}

vector<Cell> row_of_cells(){
	vector<Cell> c;
	for(int i=0; i<3; i++){
		c.push_back(Cell::empty);
	}
	return c;
}

int rand_cell(int size){
	srand (time(NULL));
	return rand()%size;
}

void starting_pieces(Board &b){
	//cout<<"IN STARTING PIECES\n";
	loc possible_move;
	//cout<<"Enter starting location: ";
	possible_move =get_location();
	//cout<<"Setting...."<<possible_move.row<<" , "<<possible_move.col<<"\n";
	b[possible_move.row][possible_move.col]= Cell::x;
	//cout<<"OUT STARTING PIECES\n";
}

Board make_empty_board(){
	vector <Cell> r1 = row_of_cells();
	vector <Cell> r2 = row_of_cells();
	vector <Cell> r3 = row_of_cells();
	Board result={r1, r2, r3};
	return result;
}

bool not_full(Board b){
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if(b[i][j]==Cell::empty) return false;
		}
	}
	return true;
}
void search_direction(vector<loc>& p, const Board& b, const loc& c, const int& dy, const int& dx, Cell opp){		//overhaul function
	//make sure there is at least 1 opp piece before own piece
	//cout<<"Searching moves "<<c.row<<" , "<<c.col<<" dx ="<<dx<<"  dy= "<<dy<<"\n";
	int i=c.row;
	int j=c.col;
	//Cell current = b[i][j];
	Cell empty =Cell::empty;
	int count = 0;
	int added=0;
	//make sure u dont leave the board, but check the directions
	while((i<3&&j<3)&&(i>=0&&j>=0)){
		//if the you find the opponent..
		if(b[i][j]==opp){
			count++;
			//cout<<"opp found at "<<i<<" , "<<j<<" - "<<count<<"\n";
		}else if(b[i][j]==empty){
			loc l(i,j);
			p.push_back(l);
			added++;
		}
		i=i+dy;
		j=j+dx;
	}
	if(count<2){
		//remove everything u added
		for(int i=0; i<added; i++){
			p.pop_back();
		}
	}
	//cout<<"Finished...\n";
}

void search_directions(const Board& b, vector<loc> &v, int r, int cl, Cell c){
	int dx=0;
	int dy=0;
	loc l(r,cl);
	dx++; //(1,0)
	search_direction(v, b, l, dy, dx, c);
	dy++; //(1,1)
	search_direction(v, b, l, dy, dx, c);
	dx--; //(0,1)
	search_direction(v, b, l, dy, dx, c);
	dy--;
	dy--; //(0,-1)
	search_direction(v, b, l, dy, dx, c);
	dx--; //(-1,-1)
	search_direction(v, b, l, dy, dx, c);
	dy++; //(-1,0)
	search_direction(v, b, l, dy, dx, c);
	dy++; //(-1,1)
	search_direction(v, b, l, dy, dx, c);
	dx*=-1;
	dy*=-1; //(1,-1)
	search_direction(v, b, l, dy, dx, c);
}

void check_for_duplicates(vector<loc>& p){
	for(int i=0; i<p.size(); i++){
		for(int j=i+1; j<p.size(); j++){
			if(p[i].row==p[j].row&&p[i].col==p[j].col){
				p.erase(p.begin()+j);
			}
		}
	}
}

void make_move(Board & b){
	Cell opp= Cell::x;
	Cell c = Cell::o;
	if(count(b, opp)==1){
		if(b[1][1]==Cell::empty){
			b[1][1]=Cell::o;
			return;
		}else{
			for(int i=0; i<3; i=i+2){
				if(b[0][i]==Cell::empty){
					b[0][i]= Cell::o;
					return;
				}
			}
			for(int i=0; i<3; i=i+2){
				if(b[i][0]==Cell::empty){
					b[i][0]= Cell::o;
					return;
				}
			}
			for(int i=0; i<3; i=i+2){
				if(b[2][i]==Cell::empty){
					b[i][0]= Cell::o;
					return;
				}
			}
		}
		// check the if the center or the corners are occupied and pick those
	}else{
		vector<loc> possible_blocks;
		vector<loc> possible_wins;
		//cout<<"Start searching...\n";
		for(int i=0; i<3; i++){
			if(b[0][i]==opp){
				search_directions(b, possible_blocks, 0, i, opp);
				//cout<<"...blocks\n";
			}else if(b[0][i]==c){
				search_directions(b, possible_wins, 0, i, c);
				//cout<<"...wins\n";
			}
		}
		//cout<<"Done searching...1\n";
		for(int i=0; i<3; i++){
			if(b[i][0]==opp){
				search_directions(b, possible_blocks, i, 0, opp);
				//cout<<"...blocks\n";
			}else if(b[i][0]==c){
				search_directions(b, possible_wins, i, 0, c);
				//cout<<"...wins\n";
			}
		}
		//cout<<"Done searching...2\n";
		for(int i=0; i<3; i++){
			if(b[2][i]==opp){
				search_directions(b, possible_blocks, 2, i, opp);
				//cout<<"...blocks\n";
			}else if(b[2][i]==c){
				search_directions(b, possible_wins, 2, i, c);
				//cout<<"...wins\n";
			}
		}
		//cout<<"Done searching...3\n";
		for(int i=0; i<3; i++){
			if(b[i][2]==opp){
				search_directions(b, possible_blocks, i, 2, opp);
				//cout<<"...blocks\n";
			}else if(b[i][2]==c){
				search_directions(b, possible_wins, i, 2, c);
				//cout<<"...wins\n";
			}
		}
		//<<"Done searching...4\n";
		//cout<<"Moves available ="<<possible_blocks.size()<<"\n";
		check_for_duplicates(possible_blocks);
		check_for_duplicates(possible_wins);
		//cout<<"No duplicates...\n";
		for(int i=0; i<possible_blocks.size(); i++){
			for(int j=0; j<possible_wins.size(); j++){
				if(possible_blocks[i]==possible_wins[i]){
					b[possible_blocks[i].row][possible_blocks[i].col]= Cell::o;
					return;
				}
			}
		}
		//cout<<"No win and block in same move\n";
		if(possible_wins.size()==0){
			cout<<"Let's win\n";
			//cout<<"Moves available ="<<possible_blocks.size()<<"\n";
			loc l = possible_blocks[rand_cell(possible_blocks.size())];
			//l.print();
			b[l.row][l.col]=Cell::o;
			cout<<"It is done\n";
		}else{
			cout<<"No you don't!!!\n";
			loc l = possible_wins[rand_cell(possible_wins.size())];
			//l.print();
			b[l.row][l.col]=Cell::o;
			cout<<"You tried to pull a sneaky on me!!!\n";
		}

		//search for opp cells, then search each direction for another opp cell
		//if another is found{
			//do u have a winning move, if u do, do it
			//else //block the opponent, u can also look for a cell that blocks multiple opp possible wins
		//}
		//else,  make your own move
		//look for possible blocks or possible moves to win, prioritise winning over blocking
	}

}

bool search_win(const Board& b, int r, int c, int dy, int dx){
	int i=r;
	int j=c;
	Cell empty =Cell::empty;
	int count_x = 0;
	int count_o= 0;
	//make sure u dont leave the board, but check the directions
	while((i<3&&j<3)&&(i>=0&&j>=0)){
		//if the you find the opponent..
		if(b[i][j]==Cell::o){
			count_o++;
			//cout<<"opp found at "<<i<<" , "<<j<<" - "<<count<<"\n";
		}else if(b[i][j]==Cell::x){
			count_x++;
		}
		i=i+dy;
		j=j+dx;
	}
	if(count_x==3||count_o==3){
		if(count_x==3){
			cout<<"YOU WIN!!!\n";
		}else if(count_o==3){
			cout<<"Nice try.....Maybe next time:)\n";
		}
		return true;
	}else{
		return false;
	}
}

bool search_wins(const Board& b, int r, int c){
	int dx=0;
	int dy=0;
	dx++; //(1,0)
	if(search_win(b, r, c, dy, dx)) return true;
	dy++; //(1,1)
	if(search_win(b, r, c, dy, dx)) return true;
	dx--; //(0,1)
	if(search_win(b, r, c, dy, dx)) return true;
	dy--;
	dy--; //(0,-1)
	if(search_win(b, r, c, dy, dx)) return true;
	dx--; //(-1,-1)
	if(search_win(b, r, c, dy, dx)) return true;
	dy++; //(-1,0)
	if(search_win(b, r, c, dy, dx)) return true;
	dy++; //(-1,1)
	if(search_win(b, r, c, dy, dx)) return true;
	dx*=-1;
	dy*=-1; //(1,-1)
	if(search_win(b, r, c, dy, dx)) return true;

	return false;
}

bool no_winner(const Board& b){
	//make sure there is at least 1 opp piece before own piece
	//cout<<"Searching moves "<<c.row<<" , "<<c.col<<" dx ="<<dx<<"  dy= "<<dy<<"\n";
	for(int i=0; i<3; i++){
		if(b[0][i]!=Cell::empty){
			if(search_wins(b, 0, i)) return false;
			//cout<<"...blocks\n";
		}
	}
	//cout<<"Done searching...1\n";
	for(int i=0; i<3; i++){
		if(b[i][0]!=Cell::empty){
			if(search_wins(b, i, 0)) return false;;
			//cout<<"...blocks\n";
		}
	}
	//cout<<"Done searching...2\n";
	for(int i=0; i<3; i++){
		if(b[2][i]!=Cell::empty){
			if(search_wins(b, 2, i)) return false;;
			//cout<<"...blocks\n";
		}
	}
	//cout<<"Done searching...3\n";
	for(int i=0; i<3; i++){
		if(b[i][2]!=Cell::empty){
			if(search_wins(b, i, 2)) return false;;
			//cout<<"...blocks\n";
		}
	}

	return true;
}

int main(){
	//initialize board
	Board b= make_empty_board();
	display(b);
	starting_pieces(b);
	system("cls");
	display(b);
	while((!not_full(b))&&no_winner(b)){
		make_move(b);
		//cout<<"IN LOOP\n";
		system("cls");
		display(b);
		if(!no_winner(b)) break;
		loc possible_move=get_location();
		while(!is_valid(possible_move, b)){
			cout<<"Invalid move...\n";
			possible_move=get_location();
		}
		b[possible_move.row][possible_move.col]= Cell::x;
		system("cls");
		display(b);
	}
	system("cls");
    while(1==1){
    	cout<<center<<"       GAME OVER\n";
    	system("cls");
    }
}

