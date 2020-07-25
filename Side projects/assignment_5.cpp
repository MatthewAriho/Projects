#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

const int NUM_ABILTIES =5;
const int total=300;

int inputCheck(int &i, int lowest, int highest){
	while(i<lowest||i>highest){
		std::cout<<"Enter a number between "<<lowest<<" and "<<highest<<" - ";
		std::cin>>i;
		std::cout<<std::endl;
	}
}

double inputCheck(double &i, double lowest, double highest){
	while(i<lowest||i>highest){
		std::cout<<"Enter a number between "<<lowest<<" and "<<highest<<" - ";
		std::cin>>i;
		std::cout<<std::endl;
	}
}

int checkInputforint(std::string &s){
	for(int i=0; i<s.length(); i++){
		if(s[i]!='1'&&s[i]!='2'&&s[i]!='3'&&s[i]!='4'&&s[i]!='5'&&s[i]!='6'&&s[i]!='7'&&s[i]!='8'&&s[i]!='9'&&s[i]!='0'){
			std::cout<<"Invalid input.. Re-enter value -";
			std::cin>>s;
			i=-1;
		}
	}
	//std::cout<<"Checked"<<std::endl;
	return std::stoi(s);
}

void displayMainMenu(){
	std::string line1('*',45);
	std::string line2('*', 13);
	std::cout<<line1<<std::endl
			<<"* TokinmonTracker by Bobby Chan sn 5555555 *"<< std::endl
			<<line1<<std::endl
			<<line2<<std::endl
			<<"* Main Menu *"<<std::endl
			<<line2<<std::endl
			<<"1. List Tokimons"<<std::endl
			<<"2. Add a new Tokimon"<<std::endl
			<<"3. Remove a Tokimon"<<std::endl
			<<"4. Change Tokimon ability"<<std::endl
			<<"5. Change Tokimon height"<<std::endl
			<<"6. Change Tokimon weight"<<std::endl
			<<"7. Exit"<<std::endl<<std::endl;
}

void displayAllTokis(std::string* names, double** h_weights, int** abilities, int size){
	std::string line('*', 22);
	std::cout<<line<<std::endl
			<<"* List of Tokimons *"<<std::endl
			<<line<<std::endl;
	for(int i=0; i< size; i++){
		std::cout<<i+1<<". "<<names[i]<<", "<< h_weights[i][0] <<" cm, "<< h_weights[i][1] <<" kg, "<<"Abilities: ";
		std::string t_abilities="";
		for(int j=0; j<NUM_ABILTIES; j++){
			if(j==0) t_abilities+= "fly="+std::to_string(abilities[i][j])+", ";
			if(j==1) t_abilities+= "fire="+std::to_string(abilities[i][j])+", ";
			if(j==2) t_abilities+= "water="+std::to_string(abilities[i][j])+", ";
			if(j==3) t_abilities+= "electricity="+std::to_string(abilities[i][j])+", ";
			if(j==4) t_abilities+= "freeze="+std::to_string(abilities[i][j]);
		}
		std::cout<<t_abilities<<std::endl;
	}
}

void addNewToki(std::string* &names, double** &h_weights, int** &abilities, std::string n_name, double n_weight, double n_height, int n_abilities[],int size){
	std::string* names_new = new std::string[total];
	int** abilities_new= new int*[total];
	double** h_weights_new= new double*[total];
	for (int i = 0; i < total; i++){
	    abilities_new[i] = new int[NUM_ABILTIES];
	    h_weights_new[i] = new double[2];
	}
	for(int i=0; i<size+1; i++){
		if(i<size){
			names_new[i]=names[i];
			for(int j=0; j<2; j++){
				h_weights_new[i][j]= h_weights[i][j];
			}
			for(int k=0; k<NUM_ABILTIES; k++){
				abilities_new[i][k]= abilities[i][k];
			}
		}else{
			names_new[i]= n_name;
			h_weights_new[i][0]= n_height;
			h_weights_new[i][1]= n_weight;
			for(int l=0; l<NUM_ABILTIES; l++){
				abilities_new[i][l]= n_abilities[l];
			}
		}
	}
	delete [] names;
	delete [] h_weights;
	delete [] abilities;
	names= names_new;
	h_weights= h_weights_new;
	abilities = abilities_new;
	//std:: cout <<names[size]<<" , "<<h_weights[size][0]<<" , "<<h_weights[size][1]<<" , "<<abilities[size][0]<<" ,"<<abilities[size][1]<<" ,"<<abilities[size][2]<<" ,"<<abilities[size][3]<<" ,"<<abilities[size][4]<<std::endl;
	names_new, h_weights_new, abilities_new = nullptr;
}

void deleteToki(int n, std::string* &names, double** &h_weights, int** &abilities, int size){
	std::string* names_new = new std::string[total];
	int** abilities_new= new int*[total];
	double** h_weights_new= new double*[total];
	for (int i = 0; i < total; i++){
	    abilities_new[i] = new int[NUM_ABILTIES];
	    h_weights_new[i] = new double[2];
	}
	for(int i=0; i<size; i++){
		if(i<n){
			names_new[i]=names[i];
			for(int j=0; j<2; j++){
				h_weights_new[i][j]= h_weights[i][j];
			}
			for(int k=0; k<NUM_ABILTIES; k++){
				abilities_new[i][k]= abilities[i][k];
			}
		}else if(i>n){
			names_new[i-1]=names[i];
			for(int j=0; j<2; j++){
				h_weights_new[i-1][j]= h_weights[i][j];
			}
			for(int k=0; k<NUM_ABILTIES; k++){
				abilities_new[i-1][k]= abilities[i][k];
			}
		}
	}
	std::cout<<names[n]<<" has been removed!"<<std::endl;
	delete [] names;
	delete [] h_weights;
	delete [] abilities;
	names= names_new;
	h_weights= h_weights_new;
	abilities = abilities_new;
	names_new, h_weights_new, abilities_new = nullptr;
}

void alterTokiAbility(std::string ability, int strength, int n, int** abilities){
	int index=-1;
	if(ability=="fly") index= 0;
	else if(ability=="fire") index= 1;
	else if(ability=="water") index= 2;
	else if(ability=="electricity") index= 3;
	else if(ability=="freeze") index= 4;

	if(index==-1){
		std::cout<<"ERROR- No ability matches this description"<<std::endl;
	}

	abilities[n][index]= strength;
}

void alterTokiHeight(double** h_weights, int n, double h){
	h_weights[n][0]= h;
}

void alterTokiWeight(double** h_weights, int n, double w){
	h_weights[n][1]= w;
}

int main(){
	displayMainMenu();
	std::string* names = new std::string[total];
	int** abilities= new int*[total];
	double** h_weights= new double*[total];
	for (int i = 0; i < total; i++){
	    abilities[i] = new int[NUM_ABILTIES];
	    h_weights[i] = new double[2];
	}
	int size=0;
	//displayAllTokis(names, h_weights, abilities, size);
	std::string s_input;
    std::cin>>s_input;
	int input= checkInputforint(s_input);
	while(inputCheck(input, 1, 7)){
        int n=input;
        if(n==1){
            displayAllTokis(names, h_weights, abilities, size);
        }else if(n==2){
            std::string name="";
            std::cout<<"Enter Tokimon's name:   ";
            std::cin>>name;
            double height;
            std::cout<<"Enter Tokimon's height:   ";
            std::cin>>height;
            inputCheck(height, 10, 99);
            double weight;
            std::cout<<"Enter Tokimon's weight:   ";
            std::cin>>weight;
            inputCheck(weight, 4, 30);
            int n_abilities[5];
            std::cout<<"Enter abilities (fly, fire, water, electricity, freeze) :";
            std::cin>>n_abilities[0]>>n_abilities[1]>>n_abilities[2]>>n_abilities[3]>>n_abilities[4];
            inputCheck(n_abilities[0],0, 99);
            inputCheck(n_abilities[1], 0, 99);
            inputCheck(n_abilities[2], 0, 99);
            inputCheck(n_abilities[3], 0 ,99);
            inputCheck(n_abilities[4], 0, 99);
            //error checks to see if values are correct
            addNewToki(names, h_weights, abilities, name, height, weight, n_abilities, size);
            //std::cout<<name<<" , "<<height<<" , "<<weight;
            //std:: cout <<names[size]<<" , "<<h_weights[size][0]<<" , "<<h_weights[size][1]<<" , "<<abilities[size][0]<<" ,"<<abilities[size][1]<<" ,"<<abilities[size][2]<<" ,"<<abilities[size][3]<<" ,"<<abilities[size][4]<<std::endl;
            size++;
        }else if(n==3){
        	displayAllTokis(names, h_weights, abilities, size);
            std::cout<<"(Enter 0 to cancel)         ";
            int k;
            std::cin>>k;
            if(k>0){
            	inputCheck(k, 1, size);
	            deleteToki(k-1, names, h_weights, abilities, size);
	            size--;
	        }else{
	        	break;
	        }
        }else if(n==4){
            displayAllTokis(names, h_weights, abilities, size);
            std::cout<<"(Enter 0 to cancel)";
            int k;
            std::cin>>k;
            inputCheck(k, 1, size);
            std::cout<<"Which ability (0 to cancel)?";
            std::string a;
            std::cin>>a;
            if(checkInputforint(a)<=0) break;
            std::cout<<"New Value?                  ";
            int s;
            std::cin>>s;
            inputCheck(s, 0, 99);
            //error checks to see if values are correct
            if(k>0){
	            alterTokiAbility(a, s, k-1, abilities);
           		std::cout<<names[k-1]<<" has "<<a<<" ability "<<s<<std::endl<<std::endl;
	        }else{
	        	break;
	        }
        }else if(n==5){
            displayAllTokis(names, h_weights, abilities, size);
            std::cout<<"(Enter 0 to cancel)         ";
            int k;
            std::cin>>k;
            inputCheck(k, 1, size);
            std::cout<<"New Value?                  ";
            double s;
            std::cin>>s;
            inputCheck(s, 10, 99);
            //error checks to see if values are correct
            if(k>0){
	            alterTokiHeight(h_weights, k-1, s);
            	std::cout<<names[k-1]<<" is now "<<s<<" cm "<<std::endl<<std::endl;
	        }else{
	        	break;
	        }
        }else if(n==6){
            displayAllTokis(names, h_weights, abilities, size);
            std::cout<<"(Enter 0 to cancel)         ";
            int k;
            std::cin>>k;
            inputCheck(k, 1, size);
            std::cout<<"New Value?                  ";
            double s;
            std::cin>>s;
            inputCheck(s, 4, 30);
            //error checks to see if values are correct
            if(k>0){
	            alterTokiWeight(h_weights, k-1, s);
            	std::cout<<names[k-1]<<" is now "<<s<<" kg "<<std::endl<<std::endl;
	        }else{
	        	break;
	        }
        }else if(n==7){
            std::cout<<"BYE!";
            return 0;
        }
        std::cout<<std::endl<<std::endl;
        displayMainMenu();
        std::cin>>input;
	}
}


//write a feature such as sorting them based on the user's input/preference
