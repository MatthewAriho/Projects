/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Matthew Ariho, Mohammad Omar Sheikh
// St.# : 301374078 , 
// Email: mariho@sfu.ca , osheikh@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

// a5.cpp

#include "cmpt_error.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <unistd.h>

using namespace std;

const string white="\033[37;1;40m";		//red text green background -0;31,
const string blue="\033[34;42m";	//1;32m
const string black="\033[30;1;107m";	//1;33m
const string cyan="\033[35;103m";		//0;3m
const string magneta="\033[36;42m";	//0;35m
const string reset_color="\033[0m";	//0m

const string empty_cell = " " + blue + " . " + reset_color;// + "|";
const string white_cell = " " + black + " O " + reset_color;// + "|";
const string black_cell = " " + white + " X " + reset_color;// + "|";
const string move_cell = " " + cyan + " ! " + reset_color;// + "|";
const string bad_move_cell = " " + blue + " ! " + reset_color;// + "|";
const string center = "			";

enum class Cell{
	empty,
	black,
	white,
	move,
	bad_move,
};

typedef vector<vector<Cell>> Board; //matrix of cells

vector<Cell> row_of_cells(){
	vector<Cell> c;
	for(int i=0; i<8; i++){
		c.push_back(Cell::empty);
	}
	return c;
}

void starting_pieces(Board &b){
	Cell setter = Cell::white;
	for(int i=3; i<5; i++){
		int j=3;
		b[i][j]= setter;
		if(setter==Cell::black) setter = Cell::white;
		else setter = Cell::black;
		j++;
		b[i][j]= setter;
	}
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
	Board result={r1, r2, r3, r4, r5, r6, r7, r8};
	starting_pieces(result);
	return result;
}

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
		case Cell::black : return black_cell; 
		case Cell::white : return white_cell; 
		case Cell::move : return move_cell;
		case Cell::bad_move : return bad_move_cell;
	}
	return empty_cell;
}
void display(const Board& board){
	cout<<center<<"       ";
	for(int i=0; i<8; i++){
		cout<<(i+1)<<"   ";
	}
	string s1=center+"    ";
	string s2=center+"    ";
	for(int i=0; i<17; i++){
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
		if(counter!=8) cout<<s2;
		r++;
		counter++;
	}
	cout<<s2;
	cout<<center<<"Number of player pieces "<<black_cell<<" - "<< count(board, Cell::black)<<" \n"
		<<center<<"Number of opponent pieces "<<white_cell<<" - "<< count(board, Cell::white)<<" \n";
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
		return (row*8)+(col+1);
	}
};
class Player{
public:
	string name;
	int score;
	//get current score
	virtual int currentScore() const =0;
	//get updated score
	virtual void newScore()=0;
	virtual string get_name() const=0;
	virtual void win_draw_lose(Player* p)=0;
	virtual ~Player(){}
};

class Human_player: public Player{
private:
	const Cell type= Cell::black;
public:
	string name;
	int score;
	//default constructor
	Human_player()
	:name(""), score(0){}
	//setting human as color black
	Cell get_cell(){
		return type;
	}
	int currentScore() const {
		return score;
	}
	//get updated score
	void newScore() {
		score++;
	}
	string get_name() const{
		return name;
	}
	void win_draw_lose(Player* p){
		int score_p1=this->currentScore();
		int score_p2=p->currentScore();
		if(score_p1>score_p2){
			cout<<this->get_name()<<" wins !!!\n"
				<<p->get_name()<<" loses :(\n";
			p->newScore();
		}else if(score_p1<score_p2){
			cout<<p->get_name()<<" wins !!!\n";
			newScore();
			cout<<this->get_name()<<" loses :(\n";
		}else if(score_p1==score_p2){
			cout<<p->get_name()<<" and "<<this->get_name()<<"draw...\n";
		}
		cout<<"Current score ="<<score_p1<<" VS Opponent score ="<<score_p2<<"\n";
	}
	Human_player(string& n)
	:name(n), score(0){
		if(name==""){
			cout<<"Provide a name to your player\n";
			cin>>n;
			name=n;
		}
	}
	//destructor
	~Human_player(){}
};

class Computer_player : public Player{
private:
	const Cell type= Cell::white;
public:
	string name;
	int score;
	Computer_player()
	: name("Computer"), score(0){}

	Cell get_cell(){
		return type;
	}
	int currentScore() const {
		return score;
	}
	//get updated score
	void newScore() {
		score++;
	}
	string get_name() const{
		return name;
	}
	void win_draw_lose(Player* p){
		int score_p1=this->currentScore();
		int score_p2=p->currentScore();
		if(score_p1>score_p2){
			cout<<this->get_name()<<" wins !!!\n"
				<<p->get_name()<<" loses :(\n";
			p->newScore();
		}else if(score_p1<score_p2){
			cout<<p->get_name()<<" wins !!!\n";
			newScore();
			cout<<this->get_name()<<" loses :(\n";
		}else if(score_p1==score_p2){
			cout<<p->get_name()<<" and "<<this->get_name()<<"draw...\n";
		}
		cout<<"Current score ="<<score_p1<<" VS Opponent score ="<<score_p2<<"\n";
	}
	~Computer_player(){}
};

vector <loc> find_current(const Board& b, const Cell& c){
	vector <loc> found;
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(b[i][j]==c){
				loc l(i,j);
				found.push_back(l);
			}
		}
	}
	return found;
}

void search_direction(vector<loc>& p, const Board& b, const loc& c, const int& dy, const int& dx, Cell opp){
	//make sure there is at least 1 opp piece before own piece
	//cout<<"Searching moves "<<c.row<<" , "<<c.col<<" dx ="<<dx<<"  dy= "<<dy<<"\n";
	int i=c.row+dy;
	int j=c.col+dx;
	Cell current = b[i][j];
	Cell empty =Cell::empty;
	//make sure u dont leave the board, but check the directions
	while((i<8&&j<8)&&(i>=0&&j>=0)){
		//
		//if the you find the opponent..
		if(b[i][j]==opp){
			i=i+dy; //incrament i by direction dy
			j=j+dx; //incrament j by direction dx
			if((i<0||i>7)||(j<0||j>7)){
				return;
			}
			if(b[i][j]==empty){
				//cout<<"Found!! at "<<i<<" , "<<j<<" Cell"<<c.row<<" , "<<c.col<<" dx = "<<dx<<" dy ="<<dy<<to_str(opp)<<"\n";
				loc n(i,j);
				p.push_back(n);
				break;
			}
		}else if(b[i][j]==empty){
			//cout<<"Empty\n";			
			break;
		}else{ break;}
		i=i+dy;
		j=j+dx;
		if(i<0||i>7){
			return;
		}
		if(j<0||j>7){
			return;
		}
		if(b[i][j]==current) break; //once you see youself, stop
		//cout<<"i - "<<i<<" and j - "<<j<<"\n";
	}
	//cout<<"Finished...\n";
}

string valid_location(loc l){

	//converts location from vector to location on board. EX: 15 -> G2

	if(l.col == 7) return string(1, (char) 72 ) + to_string(l.row+1);
	return string(1, (char) (l.col + 65)) + to_string(l.row+1); 
}

void display_moves(Board& b, vector<loc>& moves){
	//cout<<"Display moves\n";
	string s= "Valid good moves include - { ";
	for(loc l : moves){
		//cout<<"Change\n";
		b[l.row][l.col]= Cell::move;
		s+=valid_location(l)+" ";
	}
	s+=" }";
	/*s+=" \n\nOther moves include- { ";
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(b[i][j]==Cell::empty){ 
				b[i][j]=Cell::bad_move;
				loc l{i,j};
				s+=valid_location(l)+" ";
				moves.push_back(l);
			}
		}
	}
	s+=" }";*/
	cout<<to_str(Cell::bad_move)<<" -  Possible move\n"
		<<to_str(Cell::move)<<" - Good Possible move\n";
	//cout<<"Display\n";
	display(b);
	cout<<s<<"\n";
}

void print(const vector <loc>& v){
	//cout<<"Solutions =";
	for(loc l:v){
		cout<<l.row<<" , "<<l.col<<" and ";
	}
	//cout<<"\n";
}

bool search_char(char c, char t){
	const int aTA = 32;
	return c==t||c==t-aTA;
}

bool no_moves(Board& b, Player* p1, Player* p2){
	display(b);
	//check for any moves left for each color here
	if(count(b, Cell::black)<count(b, Cell::white)) p1->newScore(), cout<<"No possible moves left. PLayer -"<<p2->get_name()<<" wins!!\n";	//to be changed
	else if(count(b, Cell::black)>count(b, Cell::white)) p2->newScore(), cout<<"No possible moves left. Player -"<<p1->get_name()<<" wins!!\n";
	//no pieces left for either player 
	else cout<<"No possible moves left. Neither Player -"<<p1->get_name()<<" or "<<p2->get_name()<<" wins\n";
	char again;
	cout<<"Do you wish to play again?\n Press Y/y to Continue and any other character to quit the game\n";
	cin>>again;
	if(search_char(again, 'y')) return true;
	else{
		cout<<"Thank you for playing!!!\n";
		p1->win_draw_lose(p2);
		return false;
	}	
	return false;
}

bool is_lower(char c){
	return (c>=97&&c<=104);
}

bool is_upper(char c){
	return (c>=65&&c<=72);
}

bool is_alpha(char c){
	return is_lower(c)||is_upper(c);
}

bool is_num(char c){
	return (c>=49&&c<=56);
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

bool is_valid(loc l, const vector<loc>& v){
	for(loc a:v){
		if(a.row==l.row&&a.col==l.col) return true;
	}
	return false;
}

void search_flips(vector<loc>& p, const Board& b, const loc& c, const int& dy, const int& dx, const Cell a, const Cell opp){
	//cout<<black+ "Searching flip moves "<<" dx ="<<dx<<"  dy= "<<dy<<reset_color<<" Move made....="<<c.row<<" , "<<c.col<<"\n";
	//initializers for our directions to search
	int i=c.col+dx; 
	int j=c.row+dy;

	//making sure we are still on the board here
	if (i>7||j>7) return;
	if (i<0||j<0) return;

	//stop once you find yourself
	if(b[j][i]==a) return;
	//cout<<"Current move = "<<j<<" , "<<i<<"\n";
	//Cell current = b[i][j];
	///Cell empty =opp;

	//make sure u dont leave the board, but check the directions
	while((i<8&&j<8)&&(i>=0&&j>=0)){
		//if find your piece, then if the opponent pieces between you
		//cout<<"Outer loop....\n";
		//cout<<"At location "<<j<<" , "<<i<<" with dy= "<<dy<<" and dx="<<dx<<"\n";
		if(b[j][i]==a){
			//flips to be made ends here.
			i=i-dx;
			j=j-dy;
			while((i<8&&j<8)&&(i>=0&&j>=0)){
				//Inner loop.... while you are still on the board;
				
				//if the piece you are looking at is the opponent
				if(b[j][i]==opp){
					//cout<<"found flip at"<<j<<" , "<<i<<"\n";					
					loc n;
					n.row=j;
					n.col =i;
					//push back for flips to be made
					p.push_back(n);
					if((i-dx)==c.col&&(j-dy)==c.row){				
						//cout<<"flip search completed\n";						
						return;
					}
				}else if(b[j][i]==a){
					//cout<<"flip search completed\n";
					//once you've found starting position
					// flips to be made starts here
					return;
				}else if(b[j][i]==Cell::empty){
					return;
				}
				i=i-dx;
				j=j-dy;
			}
		}else if(b[j][i]==opp){
			//cout<<"Found opponent piece like you....\n";
			// i=i+dx;
			// j=j+dy;
		}else if(b[j][i]==Cell::empty){
			//cout<<"Found no piece like you....\n";
			return;
		}
		//cout<<"i - "<<i<<" and j - "<<j<<"\n";
		i=i+dx;
		j=j+dy;
		if (i>7||j>7) return;
		if (i<0||j<0) return;
	}
	// cout<<black<<"Finished...flip search"<<reset_color<<"\n";
}

vector<loc> flip(Board& b, const vector<loc> &current, const Cell& c, const Cell&opp){
	vector<loc> flips;
	for(loc l : current){
		int dx=0;
		int dy=0;

	//search numbers of flips in each directions 
		dx++; //(1,0)
		search_flips(flips, b, l, dy, dx, c, opp);
		// print(flips);
		dy++; //(1,1)
		search_flips(flips, b, l, dy, dx, c, opp);
		// print(flips);
		dx--; //(0,1)
		search_flips(flips, b, l, dy, dx, c, opp);
		// print(flips);
		dy--;
		dy--; //(0,-1)
		search_flips(flips, b, l, dy, dx, c, opp);
		// print(flips);
		dx--; //(-1,-1)
		search_flips(flips, b, l, dy, dx, c, opp);
		// print(flips);
		dy++; //(-1,0)
		search_flips(flips, b, l, dy, dx, c, opp);
		// print(flips);
		dy++; //(-1,1)
		search_flips(flips, b, l, dy, dx, c, opp);
		// print(flips);
		dx*=-1;
		dy*=-1; //(1,-1)
		search_flips(flips, b, l, dy, dx, c,  opp);
		//print(flips);
		//cout<<"for move -"<<l.row<<" , "<<l.col<<"\n"; 
	}
	return flips;
}

void do_flip(Board&b , const vector<loc> v, const Cell&c, const Cell& opp){
	vector<loc> flips = flip(b, v, c, opp);
	for(loc f:flips){
		b[f.row][f.col]=c;
	}
}

int flip_count(Board b, const loc l, const Cell c, const Cell& opp){
	vector<loc> v{l};
	vector<loc> flips = flip(b, v, c, opp);
	return flips.size();
}


class moves{
public:
	loc l;
	int flips;
	moves()
	:l{-1,-1}, flips(-1){
	}
	moves(const loc n, const int m)
	:l{n.row, n.col},flips(m){
	}
	int to_int(){
		return (l.row*8)+(l.col+1);
	}
};

int rand_cell(int size){
	srand (time(NULL));
	return rand()%size;
}

/*int search_vectors(const vector<loc>&c, const vector<loc>&v){
	for(int i=0; i<c.size(); i++){
		for(int j=0; j<v.size(); j++){
			if(c[i]==v[j]) return i;
		}
	}
}*/

int max_flips(const vector<moves>&v){
	int max=0;
	int index=0;

	//search for most peices flipped
	for(int i=0; i<v.size(); i++){
		if(v[i].flips>max){
			max= v[i].flips;
			index=i;
		}
	}
	return index;
}

loc priorityMoves(Board& b, const vector<loc>& allowed){

	//used this link to help me find some strategies
		//http://samsoft.org.uk/reversi/strategy.htm

	//count flips for each move and put in vector

	// contained to store moves
	vector<moves> best_moves(allowed.size());
	int mostPieces=0;
	vector <moves> best_move_flips={};
	vector <loc> best_move_corner={};
	vector <loc> best_move_sides={};
	//print(allowed);
	for (int i=0; i < allowed.size(); i++){

		// loop through all the possible moves and how many pieces it can give
		moves best_move{allowed[i], flip_count(b, allowed[i], Cell::white, Cell::black)};
		best_moves[i] = best_move;
		//cout<<"Location = "<<best_moves[i].l.row<<" , "<<best_moves[i].l.col<<" flips = "<<best_moves[i].flips<<" to_int = "<<best_moves[i].l.to_int()<<"\n";
		
	}

	/*for(int i=0; i<best_moves.size(); i++){
		cout<<"Location = "<<best_moves[i].l.row<<" , "<<best_moves[i].l.col<<" flips = "<<best_moves[i].flips<<"to_int = "<<best_moves[i].l.to_int()<<"\n";
	}*/

	//flip most pieces
	for(int i=0; i < best_moves.size(); i++){
		// cout<<"Flips.....\n";
		if(best_moves[i].flips > mostPieces){
			//cout<<"Location = "<<best_moves[i].l.row<<" , "<<best_moves[i].l.col<<" flips = "<<best_moves[i].flips<<" to_int = "<<best_moves[i].l.to_int()<<"\n";
			//best_moves_flips will hold the amount of pieces flipped
			best_move_flips.push_back(best_moves[i]);
			//cout<<"Location = "<<best_move_flips.row<<" , "<<best_move_flips.col<<" to_int = "<<best_move_flips.to_int()<<"\n";
		}
	}

	//prioritize corners
	for(int i=0; i < best_moves.size(); i++){
		// 1,8,57, and 64 represent our corners, so prioritize them if you have it as a moves
		if(best_moves[i].to_int()==1|| best_moves[i].to_int()==8||best_moves[i].to_int()==57||best_moves[i].to_int()==64){
			best_move_corner.push_back(best_moves[i].l);
		}
	}

	//prioritize the sides
	for(int i=0; i < best_moves.size(); i++){
		//these are for the side columns 1 and 8
		if(best_moves[i].to_int() % 8 ==1 || best_moves[i].to_int()==0){
			// put them into a VECTOR/CONTAINER
			best_move_sides.push_back(best_moves[i].l);
		}

		// these are for rows 1 and 8
		if((best_moves[i].to_int()>=1 && best_moves[i].to_int()<=8)|| (best_moves[i].to_int()>=57 && best_moves[i].to_int()<=64)){
			//put these into the same contained as columns 1-8
			best_move_sides.push_back(best_moves[i].l);
			//cout<<"Location = "<<best_move_sides.row<<" , "<<best_move_sides.col<<" to_int = "<<best_move_sides.to_int()<<"\n";
		}
	}

	for(int i=0; i<best_move_flips.size(); i++){
		int largest = best_move_flips[i].flips;
		int largest_index=i;
		for(int j=i; j<best_move_flips.size(); j++){
			if(best_move_flips[j].flips>largest){
				largest_index=j;
				largest= best_move_flips[i].flips;
			}
		}
		moves temp = best_move_flips[i]; 
		best_move_flips[i]= best_move_flips[largest_index];
		best_move_flips[largest_index]= temp;
	}


//this is our priority list for moves
//if you have a corner and a flip, prioritize this move
	if(best_move_corner.size()>0){
		//cout<<"\nCorners found\n";
		if(best_move_flips.size()>0){
		//cout<<"\nFlips also found\n";
			for(loc c: best_move_corner){
				for(moves m: best_move_flips){
					if(c.row==m.l.row&&c.col==m.l.col){
						//cout<<c.row<<" , "<<c.col<<" and flips ="<<m.flips<<" was found- Flips and corner\n";
						return c;
					}else{
						//cout<<"no corner with flips\n";
					}
				}
			}
		}else{
			//cout<<"A random corner was chosen\n";
			return best_move_corner[rand_cell(best_move_corner.size())];
		} // after this, if corner and flips arent together, prioritize most flips, then sides with most flips
	}else if(best_move_flips.size()>0){
		//cout<<best_move_flips[0].l.row<<" , "<<best_move_flips[0].l.col<<" and flips ="<<best_move_flips[0].flips<<" was chosen- Flips\n";
		return best_move_flips[0].l;
	}else if(best_move_sides.size()>0){
		if(best_move_flips.size()>0){
			for(loc s: best_move_sides){
				for(moves m: best_move_flips){
					//cout<<s.row<<" , "<<s.col<<" was found- Sides and flips\n";
					if(s.row==m.l.row&&s.col==m.l.col) return s;
				}
			}
		}else{ //if none of the above apply, return random from sides
			//cout<<"A random side was chosen\n";
			return best_move_sides[rand_cell(best_move_sides.size())];
		}
	}
		//cout<<"Nothing was found\n";
		//if you have nothing at all, pick random cell
		return best_moves[rand_cell(best_moves.size())].l;
}

void check_for_move_made(Board&b, vector<loc>& possible){
	for(int i=0; i<possible.size(); i++){
		loc c = possible[i];
		//if a piece has already been placed in a cell, take it out for possible moves
		if(b[c.row][c.col]==Cell::black||b[c.row][c.col]==Cell::white){
			possible.erase(possible.begin()+i);
		}
	}
}

void update_board(Board& b, vector<loc>& valid, const Cell c){
	loc move;
	if(c==Cell::black){
		// get location of piece...
		vector<loc> input = {get_location()};

		//look at input from user
		check_for_move_made(b,input);
		while(input.size()==0){
			input.push_back(get_location());
			check_for_move_made(b,input);
		}
		move = input[0];
	}
	else if(c==Cell::white){
		// else if it is a white piece, the bot will choose what is returned from priority moves function
		move = priorityMoves(b, valid);
	}
	while(!is_valid(move, valid)){
		string p="";
		if(c==Cell::white) p= white_cell;
		else p= black_cell;
		// cout<<"Suggested move for p ="<<p<<"| "<<move.row<<" , "<<move.col<<"\n";
		//display board once moves is made
		display_moves(b, valid);

		//if c is you (black), get location
		if(c==Cell::black) move=get_location();

		//if c is not you (white), bot will return from priority moves function
		else if(c==Cell::white) move = priorityMoves(b, valid);
	}
	b[move.row][move.col]=c;
	
	vector<loc> moves_made={move};
	//do flips once out of loop
	if(c==Cell::black) do_flip(b, moves_made, Cell::black, Cell::white);
	else do_flip(b, moves_made, Cell::white, Cell::black);
}

void reset_moves(Board& b){
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(b[i][j]==Cell::move||b[i][j]==Cell::bad_move) b[i][j]= Cell::empty;
		}
	}
}


//remove any duplicated moves in vector of choices function
void check_for_duplicates(vector<loc>& p){
	for(int i=0; i<p.size(); i++){
		for(int j=i+1; j<p.size(); j++){
			if(p[i].row==p[j].row&&p[i].col==p[j].col){		
				p.erase(p.begin()+j);
			}
		}
	}
}

// swap function for user and bot to switch from black and white piece
void swap(Cell&c, Cell& l){
	
	Cell temp=c;
	c=l;
	l=temp;
}

bool check_for_end(Board& b, Cell& c){
	vector <loc> current = find_current(b, c);
	vector <loc> possible;
	for(loc l : current){
		int dx=0;
		int dy=0;

	//this function will search all possible 8 directions on the board for possible moves
		dx++; //(1,0)
		search_direction(possible, b, l, dy, dx, c);
		//print(possible);
		dy++; //(1,1)
		search_direction(possible, b, l, dy, dx, c);
		//print(possible);
		dx--; //(0,1)
		search_direction(possible, b, l, dy, dx, c);
		//print(possible);
		dy--;
		dy--; //(0,-1)
		search_direction(possible, b, l, dy, dx, c);
		//print(possible);
		dx--; //(-1,-1)
		search_direction(possible, b, l, dy, dx, c);
		//print(possible);
		dy++; //(-1,0)
		search_direction(possible, b, l, dy, dx, c);
		//print(possible);
		dy++; //(-1,1)
		search_direction(possible, b, l, dy, dx, c);
		//print(possible);
		dx*=-1;
		dy*=-1; //(1,-1)
		search_direction(possible, b, l, dy, dx, c);
		//print(possible);
	}
	if(possible.size()<=0) return true;
	else return false; 
}
void possible_moves(Board& b, vector<loc>& possible, Cell& c, Cell& opp, Player* p1, Player* p2){
	//Possible moves
	vector <loc> current = find_current(b, c);

	//search for moves from current direction
	for(loc l : current){
		int dx=0;
		int dy=0;

	//this function will search all possible 8 directions on the board for possible moves
		dx++; //(1,0)
		search_direction(possible, b, l, dy, dx, opp);
		//print(possible);
		dy++; //(1,1)
		search_direction(possible, b, l, dy, dx, opp);
		//print(possible);
		dx--; //(0,1)
		search_direction(possible, b, l, dy, dx, opp);
		//print(possible);
		dy--;
		dy--; //(0,-1)
		search_direction(possible, b, l, dy, dx, opp);
		//print(possible);
		dx--; //(-1,-1)
		search_direction(possible, b, l, dy, dx, opp);
		//print(possible);
		dy++; //(-1,0)
		search_direction(possible, b, l, dy, dx, opp);
		//print(possible);
		dy++; //(-1,1)
		search_direction(possible, b, l, dy, dx, opp);
		//print(possible);
		dx*=-1;
		dy*=-1; //(1,-1)
		search_direction(possible, b, l, dy, dx, opp);
		//print(possible);
	}
	if(opp==Cell::white){
		display_moves(b, possible);
	}
	//throw away duplicated moves
	check_for_duplicates(possible);

	//check to see if the moves has already been made and erase if it is
	check_for_move_made(b, possible);
	//if you have moves to make
	while((possible.size()!=0)){
		//if((count(b, Cell::black)==0)||(count(b, Cell::white)==0)) break;
		//cout<<"New Moves...."<<to_str(c)<<"and opponent = "<<to_str(opp)<<"\n";
		if(opp==Cell::white){
		//if opponent is white cell
		//it is users turn to make a move
		//display then update board
			//display_moves(b, possible);
			reset_moves(b);

			//cout<<"Updating....\n";
			update_board(b,possible, c);
			display(b);
			possible.clear();
		}else if(opp==Cell::black){
			// else if the opponent if the opponent is black via swap function
			//execute possible moves
			cout<<"Thinking....\n";
			reset_moves(b);
			update_board(b,possible, c);
			possible.clear();
		}
		//swap to bots/opponents turn
		swap(c,opp);
		usleep(1000000);
		possible_moves(b, possible, c, opp, p2, p1);
		if(possible.size()==0){
			//cout<<"Size for"<<to_str(c)<<" = 0\n";
			swap(c,opp);
			possible_moves(b, possible, c, opp, p1, p2);	//game ends if both the player and computer have no possible moves
			//if(possible.size()==0) cout<<"Size for"<<to_str(c)<<" = 0\n";
			//else cout<<"Size for"<<to_str(c)<<" = "<<possible.size()<<"\n";
		}
	}
}


int main(){
	//initialize board
	Board b= make_empty_board();
	display(b);

	vector<loc> p;
	string n="";

	//constructing players
	Human_player * h= new Human_player(n);
	Computer_player * bot= new Computer_player();

	//
	Cell a = h->get_cell();
	Cell opp = bot->get_cell();
	possible_moves(b, p, a, opp, h, bot);
	// end game if no moves left to be made
	if(no_moves(b, h, bot)){
		b=make_empty_board(), display(b), possible_moves(b, p, a, opp, h, bot);//end game
	}else{
		delete h;
		h=nullptr;
		delete bot;
		bot=nullptr;
	}

}
