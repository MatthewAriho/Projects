#include "cmpt_error.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

const string white="\033[37;1;40m";		//red text green background -0;31,
const string blue="\033[34;42m";	//1;32m
const string black="\033[30;1;107m";	//1;33m
const string cyan="\033[35;103m";		//0;3m
const string magneta="\033[36;42m";	//0;35m
const string reset_color="\033[0m";	//0m

const string empty_cell = " " + blue + " . " + reset_color;// + "|";
const string white_cell = " " + white + " O " + reset_color;// + "|";
const string black_cell = " " + black + " X " + reset_color;// + "|";
const string move_cell = " " + cyan + " ! " + reset_color;// + "|";
const string bad_move_cell = " " + blue + " ! " + reset_color;// + "|";
const string center = "			";

enum class Cell{
	empty,
	black,
	white,
	move,
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
	}
	return empty_cell;
}
void display(const Board& board){
	cout<<center<<"    ";
	for(int i=0; i<8; i++){
		cout<<(i+1)<<" ";
	}
	string s1=center+"   ";
	string s2=center+"   ";
	for(int i=0; i<8; i++){
		s1+= " _";
		s2+= " -";
	}
	s1+="\n";
	s2+="\n";
	cout<<"\n"<<s1;
	char r = 'a';
	int counter =1;
	for(const vector<Cell> & row : board){
		cout<<center<<" "<<r<<"-";
		for(Cell c: row){
			cout<<to_str(c)<<"";
		}
		cout<<"\n";
		if(counter!=8) cout<<s2;
		r++;
		counter++;
	}
	cout<<s2;//OR S1- DECIDE LATER
	cout<<"Number of player pieces "<<black_cell<<"| - "<< count(board, Cell::black)<<" "
			<<"Number of opponent pieces "<<white_cell<<"| - "<< count(board, Cell::white)<<" \n";
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

int z=0;
void search_direction(vector<loc>& p, const Board& b, const loc& c, const int& dy, const int& dx, Cell opp){
	z++;
	//make sure there is at least 1 opp piece before own piece
	//cout<<"Searching moves "<<z<<" dx ="<<dx<<"  dy= "<<dy<<"\n";
	int i=c.row;
	int j=c.col;
	Cell current = b[i][j];
	Cell empty =Cell::empty;
	//make sure u dont leave the board, but check the directions
	while((i<8&&j<8)&&(i>=0&&j>=0)){
		/*if(b[i][j]==empty){
			//cout<<"Found!!\n";
			loc n(i,j);
			p.push_back(n);
			break;
		}*/
		if(b[i][j]==opp){
			i=i+dy;
			j=j+dx;
			if(b[i][j]==empty){
				//cout<<"Found!!\n";
				loc n(i,j);
				p.push_back(n);
				break;
			}
		}
		i=i+dy;
		j=j+dx;
		if(b[i][j]==current) break;
		//cout<<"i - "<<i<<" and j - "<<j<<"\n";
	}
	//cout<<"Finished...\n";
}

string valid_location(loc l){

	//converts location from vector to location on board. EX: 15 -> G2

	if(l.col == 7) return string(1, (char) 72 ) + to_string(l.row+1);
	return string(1, (char) (l.col + 65)) + to_string(l.row+1); 
}

void display_moves(Board& b, const vector<loc> moves){
	//cout<<"Display moves\n";
	string s= "Valid move include - { ";
	for(loc l : moves){
		//cout<<"Change\n";
		b[l.row][l.col]= Cell::move;
		s+=valid_location(l)+" ";
	}
	s+=" }";
	//cout<<"Display\n";
	display(b);
	cout<<s<<"\n";
}

/*void print(const vector <loc>& v){
	//cout<<"Solutions =";
	for(loc l:v){
		cout<<l.row<<" , "<<l.col<<" and ";
	}
	//cout<<"\n";
}*/

bool search_char(char c, char t){
	const int aTA = 32;
	return c==t||c==t-aTA;
}

bool no_moves(Board& b){
	display(b);
	if(count(b, Cell::black)<count(b, Cell::white)) cout<<"No possible moves left. PLayer -"<</*p<<*/" wins!!\n";	//to be changed
	else cout<<"No possible moves left. Player -"/*<<p*/<<" wins!!\n";
	char again;
	cout<<"Do you wish to play again?\n Press Y/y to Continue, N/n to quit the game\n";
	cin>>again;
	if(search_char(again, 'y')) return true;
	else if(search_char(again, 'n')) return false;
	else{
		while(!(search_char(again, 'y'))&&!(search_char(again, 'n'))){
			cout<<"Do you wish to play again?\n Press Y/y to Continue, N/n to quit the game\n";
			cin>>again;
		}
		if(search_char(again, 'y'))return true;
		else if(search_char(again, 'n')) return false;
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
	cout << "where would you like to place your piece?\n";
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
	//cout<<result.row<<" , "<<result.col<<" this is my input mofo\n";
 	return result;
}

bool is_valid(loc l, const vector<loc>& v){
	for(loc a:v){
		if(a.row==l.row&&a.col==l.col) return true;
	}
	return false;
}

void search_flips(vector<loc>& p, const Board& b, const loc& c, const int& dy, const int& dx, const Cell a, const Cell opp){
	// cout<<red+ "Searching flip moves "<<" dx ="<<dx<<"  dy= "<<dy<<reset_color<<" Move made....="<<c.row<<" , "<<c.col<<"\n";
	int i=c.col+dx;
	int j=c.row+dy;
	if (i<0||j<0) return;
	if(b[j][i]==a) return;
	// cout<<"Current move = "<<j<<" , "<<i<<"\n";
	//Cell current = b[i][j];
	///Cell empty =opp;
	//make sure u dont leave the board, but check the directions
	while((i<8&&j<8)&&(i>=0&&j>=0)){
		if(i==0 && dx<0){
			return;
		}
		if(j==0 && dy<0){
			return;
		}
		if (i<0||j<0) return;
		//if find your piece, then if the opponent pieces between you
		//cout<<"Outer loop....\n";
		// cout<<"At location "<<j<<" , "<<i<<" with dy= "<<dy<<" and dx="<<dx<<"\n";
		if(b[j][i]==a){
			//cout<<"FLip to be made ends here....="<<j<<" , "<<i<<"\n";
			//cout<<"Found other piece like you....\n";

			while((i<8&&j<8)&&(i>=0&&j>=0)){
				//cout<<"Inner loop....\n";
				i=i-dx;
				j=j-dy;
				//if (i<0||j<0) return;
				if(b[j][i]==opp){
					//cout<<"Found opponent piece after finding yourself....\n";
					// cout<<"FLip to be made....="<<j<<" , "<<i<<"\n";
					loc n;
					n.row=j;
					n.col =i;
					p.push_back(n);
				}else if(b[j][i]==a){
					//cout<<"FOund starting position....\n";
					//cout<<"FLip to be made starts here....="<<j<<" , "<<i<<"\n";
					return;
				}else if(b[j][i]==Cell::empty){
					return;
				}
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
	}
	//cout<<red<<"Finished...flip search"<<reset_color<<"\n";
}

vector<loc> flip(Board& b, const vector<loc> &current, const Cell& c, const Cell&opp){
	vector<loc> flips;
	// cout<<red+"Possible flip moves"+reset_color<<"\n";
	//vector <loc> current = find_current(b);
	//vector <loc> possible;
	//Cell c= Cell::black;
	//Cell opp= Cell::white;
	// cout<<"Searching flip moves\n";
	for(loc l : current){
		// cout<<"Move made....="<<l.row<<" , "<<l.col<<"\n";
		int dx=0;
		int dy=0;
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
		// print(flips);
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

	// cout<<"Priority Moves.....\n";
	//vector<loc> allowed; //all the possible moves that can be done
	//count flips for each move and put in vector
	vector<moves> best_moves(allowed.size());
	int mostPieces=0;
	vector <moves> best_move_flips={};
	vector <loc> best_move_corner={};
	vector <loc> best_move_sides={};

	for (int i=0; i < allowed.size(); i++){
		moves best_move{allowed[i],flip_count(b, allowed[i], Cell::white, Cell::black)};
		best_moves[i] = best_move;
		// loop through all the possible moves and how many pieces it can give

	}

	/*for(int i=0; i<best_moves.size(); i++){
		cout<<"Location = "<<best_moves[i].l.row<<" , "<<best_moves[i].l.col<<" flips = "<<best_moves[i].flips<<"to_int = "<<best_moves[i].l.to_int()<<"\n";
	}*/

	//flip most pieces
	for(int i=0; i < best_moves.size(); i++){
		// cout<<"Flips.....\n";
		if(best_moves[i].flips > mostPieces){
			// cout<<"Location = "<<best_moves[i].l.row<<" , "<<best_moves[i].l.col<<" flips = "<<best_moves[i].flips<<" to_int = "<<best_moves[i].l.to_int()<<"\n";
			mostPieces = best_moves[i].flips;
			best_move_flips.push_back(best_moves[i]);
			//cout<<"Location = "<<best_move_flips.row<<" , "<<best_move_flips.col<<" to_int = "<<best_move_flips.to_int()<<"\n";
		}
	}

	//prioritize corners
	for(int i=0; i < best_moves.size(); i++){
		// cout<<"Corner.....\n";
		if(best_moves[i].to_int()==1|| best_moves[i].to_int()==8||best_moves[i].to_int()==57||best_moves[i].to_int()==64){
			// cout<<"Location = "<<best_moves[i].l.row<<" , "<<best_moves[i].l.col<<" flips = "<<best_moves[i].flips<<"to_int = "<<best_moves[i].l.to_int()<<"\n";
			best_move_corner.push_back(best_moves[i].l);
			//cout<<"Location = "<<best_move_corner.row<<" , "<<best_move_corner.col<<" to_int = "<<best_move_corner.to_int()<<"\n";
		}
	}

	//prioritize the sides
	for(int i=0; i < best_moves.size(); i++){
		// cout<<"Sides.....\n";
		//these are for the side columns 1 and 8
		if(best_moves[i].to_int() % 8 ==1 || best_moves[i].to_int()==0){
			// cout<<"Location = "<<best_moves[i].l.row<<" , "<<best_moves[i].l.col<<" flips = "<<best_moves[i].flips<<"to_int = "<<best_moves[i].l.to_int()<<"\n";
			best_move_sides.push_back(best_moves[i].l);
			//cout<<"Location = "<<best_move_sides.row<<" , "<<best_move_sides.col<<" to_int = "<<best_move_sides.to_int()<<"\n";
		}
		// these are for rows 1 and 8
		if((best_moves[i].to_int()>=1 && best_moves[i].to_int()<=8)|| (best_moves[i].to_int()>=57 && best_moves[i].to_int()<=64)){
			// cout<<"Location = "<<best_moves[i].l.row<<" , "<<best_moves[i].l.col<<" flips = "<<best_moves[i].flips<<"to_int = "<<best_moves[i].l.to_int()<<"\n";
			best_move_sides.push_back(best_moves[i].l);
			//cout<<"Location = "<<best_move_sides.row<<" , "<<best_move_sides.col<<" to_int = "<<best_move_sides.to_int()<<"\n";
		}
	}

	//cout<<"Location = "<<best_move_flips.row<<" , "<<best_move_flips.col<<" to_int = "<<best_move_flips.to_int()<<"\n";
	//cout<<"Location = "<<best_move_corner.row<<" , "<<best_move_corner.col<<" to_int = "<<best_move_corner.to_int()<<"\n";
	//cout<<"Location = "<<best_move_sides.row<<" , "<<best_move_sides.col<<" to_int = "<<best_move_sides.to_int()<<"\n";

	if(best_move_corner.size()<=0){
		if(best_move_flips.size()<=0){
			if(best_move_sides.size()<=0){
				// cout<<"Rand run....\n";
				return best_moves[rand_cell(best_moves.size())].l;
			}else{
				return best_move_sides[rand_cell(best_move_sides.size())];
			}
		}else{
			return best_move_flips[max_flips(best_move_flips)].l;
		}
	}else{
		return best_move_corner[rand_cell(best_move_corner.size())];
	}

}

void update_board(Board& b, vector<loc>& valid, const Cell c){
	loc move;
	if(c==Cell::black){
		// cout<<"Placing Black Piece.....\n";
		move = get_location();
	}
	else if(c==Cell::white){
		// cout<<"Placing White Piece.....\n";
		move = priorityMoves(b, valid);
	}

	while(!is_valid(move, valid)){
		string p="";
		if(c==Cell::white) p= white_cell;
		else p= black_cell;
		// cout<<"Suggested move for p ="<<p<<"| "<<move.row<<" , "<<move.col<<"\n";
		display_moves(b, valid);
		if(c==Cell::black) move=get_location();
		else if(c==Cell::white) move = priorityMoves(b, valid);
	}
	b[move.row][move.col]=c;
	//vector<loc> f;
	//cout<<"Flipping....\n";
	vector<loc> moves_made={move};
	// print(moves_made);
	if(c==Cell::black) do_flip(b, moves_made, Cell::black, Cell::white);
	else do_flip(b, moves_made, Cell::white, Cell::black);
	//display(b);
}

void reset_moves(Board& b){
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(b[i][j]==Cell::move) b[i][j]= Cell::empty;
		}
	}
}

void check_for_duplicates(vector<loc>& p){
	for(int i=0; i<p.size(); i++){
		for(int j=i+1; j<p.size(); j++){
			if(p[i].row==p[j].row&&p[i].col==p[j].col){
				//cout<<p[i].row<<" , "<<p[i].col<<" size = "<<p.size()<<" j = "<<j<<"\n";
				//cout<<p[j].row<<" , "<<p[j].col<<" size = "<<p.size()<<" j = "<<j<<"\n";
				p.erase(p.begin()+j);
				//cout<<p[j].row<<" , "<<p[j].col<<"- Changed size = "<<p.size()<<" j = "<<j<<"\n";
			}
		}
	}
}


void swap(Cell&c, Cell& l){
	/*cout<<"Swapping...\n";
	string p1, p2;
	if(c==Cell::black){
		p1=black_cell;
		if(l==Cell::white) p2= white_cell;
		else p2= black_cell;
	}else{
		p1= white_cell;
		if(l==Cell::white) p2= white_cell;
		else p2= black_cell;
	}
	cout<<"Player = "<<p1<<" Opponent = "<<p2<<"\n";*/
	Cell temp=c;
	c=l;
	l=temp;
	/*if(c==Cell::black){
		p1=black_cell;
		if(l==Cell::white) p2= white_cell;
		else p2= black_cell;
	}else{
		p1= white_cell;
		if(l==Cell::white) p2= white_cell;
		else p2= black_cell;
	}
	cout<<"Player = "<<p1<<" Opponent = "<<p2<<"\n Emd of swap\n";*/
}

void possible_moves(Board& b, vector<loc>& possible, Cell& c, Cell& opp){
	//cout<<"Possible moves\n";
	vector <loc> current = find_current(b, c);
	//vector <loc> possible;
	//Cell c= Cell::white;
	//cout<<"Searching moves\n";
	for(loc l : current){
		int dx=0;
		int dy=0;
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
	check_for_duplicates(possible);

	while((possible.size()!=0)){
		// string p1,p2;
		// if(c==Cell::black) p1=black_cell, p2= white_cell;
		// else p2=black_cell, p1= white_cell;
		// cout<<"Player = "<<p1<<" Opponent = "<<p2<<"\n";
		if((count(b, Cell::black)==0)||(count(b, Cell::white)==0)) break;
		//cout<<"New Moves....\n";
		if(opp==Cell::white){
			// cout<<"Black piece....\n";
			display_moves(b, possible);
			//display_moves(b, possible);
			//cout<<"Resetting....\n";
			reset_moves(b);
			//cout<<"Updating....\n";
			update_board(b,possible, c);
			display(b);
			possible.clear();
		}else if(opp==Cell::black){
			cout<<"Thinking....\n";
			reset_moves(b);
			update_board(b,possible, c);
			possible.clear();
		}
		swap(c,opp);
		possible_moves(b, possible, c, opp);
	}
	if(no_moves(b)) b=make_empty_board(), display(b), possible_moves(b, possible, c, opp);//end game
	else{
		cout<<"Thank you for playing!!!\n";
		throw;		//change
	}
}


//play sets moves- input(done), location returned(done), update the board and print it
//do the some shit for the CPU - PRIORITY- Corners(if included), move that will sandwich the most tiles, make move, update board

int main(){
	Board b= make_empty_board();
	display(b);
	vector<loc> p;
	Cell a= Cell::white;
	Cell op= Cell::black;
	possible_moves(b,p, op,a );
}
//nn
// integrate cpu and normal player