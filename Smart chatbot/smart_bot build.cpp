class Verb{
public:
	string present;
	string past;
	string past_participle;
	string present_continuous;

	Verb(const string &pr, const string &ps, const string &pp, const string&pc)
	:present(pr), past(ps), past_particple(pp), present_continuous(pc)
	{}
};

vector <string> verbs;
verbs.push_back(Verb("have","had", "had", "having"));
verbs.push_back(Verb("do","did", "done", "doing"));
verbs.push_back(Verb("say","said", "said","saying"));
verbs.push_back(Verb("go","went", "gone","going"));
verbs.push_back(Verb("get","got", "got","getting"));
verbs.push_back(Verb("make","made", "made", "making"));
verbs.push_back(Verb("know","knew", "known","knowing"));
verbs.push_back(Verb("think","thought", "thought","thinking"));
verbs.push_back(Verb("take","took", "taken","taking"));
verbs.push_back(Verb("see","saw", "seen","seeing"));
verbs.push_back(Verb("come","came", "come","coming"));
verbs.push_back(Verb("want","wanted", "wanted","wanting"));
verbs.push_back(Verb("look","looked", "looked","looking"));
verbs.push_back(Verb("use","used", "used","using"));
verbs.push_back(Verb("find","found", "found","finding"));
verbs.push_back(Verb("give","gave", "given","giving"));

const vector <string> adjectives={"able" ,"bad","best","better","big","black","certain","clear","different",
								"early","easy","economic","federal","free","full","good","great","hard","high",
								"human","important","international","large","late","little","local","long","low",
								"major","military","national","new","old","only","other","political","possible",
								"public","real","recent","right","small","social","special","strong","sure","true",
								"white","whole","young"};


class Smart_bot: public Chatbot{
private:
	string s_name;
	string response;
	string latest;
	string previous;
public:
	Smart_bot(const string &s);

  	string name(){	// Name of this Chatbot
  		return s_name;
  	}
  	// Give a string to this chatbot.
  	void tell(const string& s){
		previous = latest;
		latest=s;
	}

  	int random(int size) const{
  		long long i =(time(NULL) * prime1) + prime2;
  		long long j = i%size;
  		return j;
  	}
  	bool is_alpha(const char&c){
  		return (c>='a'&&c<='z')||(c>='A'&&C<='Z')
  	}
  	bool searchWord(const string &s, int position) const{		//looks for a substring in a string
  		bool result = false;
	  	for(int i=0; i<s.size(); i++){
	  		if(!is_alpha(s[i])) return result;
	  		if(latest[position]!=s[i]||latest[position]!=(s[i]+aTA)){
	  			return result;
	  		}else{
	  			position++;
	  		}
	  	}
	  	result = true;
	  	return result;
	}
  	bool greetings(){
  		const vector<string> greetings={"hello", "hi", "greetings", "sup", "what's up"};
  		const vector<string> greetings_responses={"sup bro", "hey", "*nods*", "hey you get my snap?"};
  		for(int j=0; j<greetings.size(); j++){
  			for(int i =0; i<latest.size(); i++){
	  			if(latest.size()-i>=greetings[j].size()){
			  		if(searchWord(greetings[j], i)){
			  			return greetings_responses[random()];
			  		}
		  		}
	  		}
	  	}
  	}

  	string adjective_present(){
  		for(int i=0; i<adjectives.size(); i++){
  			for(int j=0; j<latest.size(); j++){
  				if(searchWord(adjectives[i], j)) return adjectives[i];
  			}
  		}
  		return "None";
  	}

  	Verb verb_present(){
  		for(int i=0; i<verbs.size(); i++){
  			for(int j=0; j<latest.size(); j++){
  				if((searchWord(verbs[i].present,j))||(searchWord(verbs[i].past,j))||(searchWord(verbs[i].past_participle,j))||(searchword(verbs[i].present_continuous, j))) return verbs[i];
  			}
  		}
  		return "None";
  	}

  	string pronoun(){
  		for(int i=0; i<latest.size(); i++){
  			if(searchWord("you", i)) return "I";
  			if(searchWord(" I ", i)||searchWord("I'")) return "you";
  		}else{
  			return "None";
  		}
  	}
  	string emotions(){
  		Verb emotions;
  		emotions.push_back("feel", "felt", "felt", "feeling");
  		emotions.push_back("love", "loved", "loved", "loving");
  		emotions.push_back("hate", "hated", "hated", "hating");
  		emotions.push_back("like", "liked", "liked", "liking");
  		emotions.push_back("disgust", "disguested", "disgusted", "disgusting");
  		emotional respones ={"Oh... ", "Tell me more about these feelings.","Do you really believe I don't ","Perhaps in good time I will feel this strongly about something like you.", "Sometimes i feel the same ", " You should not feel like that",  "Do you awlays feel like this?"};
		for(int i=0; i<verbs.size(); i++){
			for(int j=0; j<latest.size(); j++){
	  			if(searchWord(emotions[i].present,j)||(searchWord(emotions[i].past,j))||(searchWord(emotions[i].past_participle,j))||(searchword(emotions[i].present_continuous, j))) return emotions[random(emotions.size())];
	  		}
	  	}
		return "None";
	}	

	string short_response(){
		if(latest.size()<10){
			for(int i =0; i<latest.size(); i++){
				vector <string> decision = {"agree", "disagree"};
				if(searchWord("yes",i)||searchWord("yea", i)||searchWord("nah", i)||searchWord("no", i)||searchWord("where", i)||searchWord("when"), i){
					string response = "I " + decision[random(decision.size())];
					return response;
				}
			}
		}
		return "None";
	}

  	bool is_question(){
  		for(int i=0; i<latest.size(); i++){
  			if(searchWord("what",i)||searchWord("do you know", i)||searchWord("why", i)||searchWord("how", i)||searchWord("where", i)||searchWord("when"), i) return true;
  		}
  		return false;
  	} 

  	bool contains_symbols(){
  		for(int i=0; i<latest.size(); i++){
  			if(searchWord("!")||searchWord("~")||searchWord("#")||searchWord("@")||searchWord("$")||searchWord("%")||searchWord("^")||searchWord("&")||searchWord("*"), i) return true;
  		}
  		return false;
  	}

  	string get_reply(){			// Get a string from this chatbot.
  		if(contains_symbols()){
  			response = "I don't understand";
  		}else{
  			if(previous==latest){
  				response = "Please do not repeat yourself";
	  		}else{
	  			for(int i =0; i<latest.size(); i++){
		  			if(searchword("date", i)||searchword("time", i)){
		  				Datetime_bot * d = new Datetime_bot{d, {""}};
		  				response = "The time and date are as follows " + d->date_time();
		  				delete d;
		  				return response;
		  			}
		  		}
	  			if(is_question()){
	  				vector <string> question_responses={"Sorry, I wish I knew.", "I wish I could be of more help.", "I am unable to answer your question."};
	  				response = questions_responses[random(question_responses.size())];
	  			}else{
	  				vector <string> general_responses={"That sounds really cool.", "Sounds like my idea of fun", "Cool."};
	  				vector <string> input_contains_verb={"I have heard of that before and "," I have actually done that before and "," I have had my reservations about it but "};
	  				if(pronoun()=="None"){
	  					if(verb_present()=="None"){
	  						if(adjective_present()!="None"){
	  							string adjective = adjective_present();
		  						general_responses.push_back("Do you often feel "+);
		  						general_responses.push_back("Do you enjoy feeling "+);
		  					}
	  						response = "I do not know what you are taking about but " + general_responses[random(general_responses.size())];
	  					}else{
	  						response = input contains_verb[random(input_contains_verb.size())] + general_responses[random(general_responses.size())];
	  					}
	  				}else{
	  					if(verb_present()=="None"){
	  						response = "I have not heard about that but " + general_responses[random(general_responses.size())];
	  					}else{
	  						Verb v= verb_present();
	  						if(adjective()=="None"){
		  						vector <string> customized_responses[19];
		  						customized_responses[0]="Don't you believe that I can ";
							    customized_responses[1]="Perhaps you would like to be able to ";
							    customized_responses[2]="You want me to be able to ";
							    customized_responses[3]="Perhaps you don't want to ";
							    customized_responses[4]="Do you want to be able to ";
							    customized_responses[5]="What makes you think I am ";
							    customized_responses[6]="Does it please you to believe I am ";
							    customized_responses[7]="Perhaps you would like to be ";
							    customized_responses[8]="Do you sometimes wish you were ";
							    customized_responses[9]="Perhaps you can now ";
							    customized_responses[10]="Why don't you ";
							    customized_responses[11]="Do you wish to be able to ";
							    customized_responses[16]="Do you want me to ";
							    customized_responses[17]="Do you think you should be able to ";
							    customized_responses[18]="Why can't you ";
		  						response = customized_responses[random(customized_responses.size())] + v.present;
		  						if(((response[0]=='d'||response[0]=='D')&&(response[1]=='o'||response[1]=='O'))||(((response[0]=='w'||response[0]=='W'))&&(response[1]=='h'||response[1]=='H')&&(response[2]=='o'||response[2]=='O'))) response += " ?";
		  						return response;
		  					}else{
		  						string adjective = adjective_present();
		  						vector <string> description_1 ={" was not ", " was "};
		  						vector <string> description_2 ={"fun activity", "risky but ultimately a good experience to have.", " dull and or laughable activity"}
		  						string article="";
		  						if(adjective[0]='a'||adjective[0]='e'||adjective[0]='i'||adjective[0]='o'||adjective[0]='u'){
		  							article = "an";
		  						}else{
		  							article ="a";
		  						}
		  						response = "I have always thought "+ v.present_continuous+ "something" +description_1[random(description_1.size())]+ article + description_2[random(description_2.size())];
		  					}
	  					}
	  				}
	  			}
	  		}
  	}
  	}
	~Smart_bot(){
		s_name="";
		response="";
		latest="";
		previous="";
	}
};

Smart_bot::Smart_bot(const string &s)
:s_name(s)
{
	if(s="") cmpt::error("Invalid name passed to Smart bot");
	cout<<"Hey, my name is "<<this->name()<<" , ask me anything\n";
	string temp;
	cin>>temp;	//fix
	tell(temp);
}

// Give a string to this chatbot.

// Get a string from this chatbot.
//replace something with an activity that ties in well with the given verb
//references to the eliza bot


