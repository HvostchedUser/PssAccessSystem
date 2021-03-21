#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "utils.cpp"

using namespace std;

// TODO: Brown access level for all toilets


// Thanks https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

string getTime(){
    time_t my_time = time(NULL); 
    return ctime(&my_time);
}

void prompt(vector<ConScope> sc,int nesting){
    for(int i=0;i<nesting*2;i++){
        cout<<" ";
    }
    for(int i=0;i<sc.size();i++){
        cout<<" ❯ "<<sc[i].name;
    }
    cout<<" ❯❯❯ ";
}
void printCon(int nesting, string s){
    for(int i=0;i<(nesting+1)*2;i++){
        cout<<" ";
    }
    cout<<s<<endl;
}
void execCon(int nesting,string command, ConScope curScope,vector<Room> rooms,vector<AccessLevel> levels, vector<PersonType> types, vector<Person> people){
    if(command=="people_list"){
        for(int i=0;i<people.size();i++){
            printCon(nesting,"Person #"+to_string(i));
            printCon(nesting,"Name: "+people[i].name);
            printCon(nesting,"Type: "+people[i].type);
            printCon(nesting,"Access types: ");
            for(int ii=0;ii<people[i].baseAccessTypes.size();ii++){
                printCon(nesting,people[i].baseAccessTypes[ii]);
            }
            printCon(nesting,"Custom access rooms: ");
            for(int ii=0;ii<people[i].customAccess.size();ii++){
                printCon(nesting,to_string(people[i].customAccess[ii]));
            }
            printCon(nesting,""+to_string(i));
            printCon(nesting,"");
        }
    }else if (command=="levels_list"){
        for(int i=0;i<levels.size();i++){
            printCon(nesting, ">> "+levels[i].levelName);
            for(int ii=0;ii<levels[i].access.size();ii++){
                printCon(nesting,levels[i].access[ii]);
            }
            printCon(nesting, "");
        }
    }else if (command=="person_type_list"){
        for(int i=0;i<types.size();i++){
            printCon(nesting, ">> "+types[i].typeString);
            for(int ii=0;ii<types[i].properties.size();ii++){
                printCon(nesting,types[i].properties[ii]);
            }
            printCon(nesting, "");
        }
    }else if (command=="rooms_list"){
        for(int i=0;i<rooms.size();i++){
            printCon(nesting, "#"+to_string(rooms[i].id));
            for(int ii=0;ii<rooms[i].type.size();ii++){
                printCon(nesting,rooms[i].type[ii]);
            }
            printCon(nesting, "");
        }
    }else if (command==""){
        
    }
}
int randRange(int min, int max){
    return min + (rand() % static_cast<int>(max - min + 1));

}
string namegen(bool fem){
    string res="";
    string mid[]={"gra","am","ni","cho","va","nad","si","vil","mi","sa","eb","shon", "ri","li","sa","ma","da","ad","re","su","vo","tyo","sla"};
    string endFem[]={"na","va","sha","rtha","ka","tya","ya","ad","el"};
    string endMa[]={"im","sim","kal","al","ed","ey","an","ok","chek","ad"};
    int randval=randRange(1,4);
    for(int i=0;i<randval;i++){
        res+=mid[randRange(0,22)];
    }
    if(fem){
        res+=endFem[randRange(0,8)];
    }else{
        res+=endMa[randRange(0,9)];
    }
    return res;
}
string surnamegen(bool fem){
    string res="";
    string mid[]={"gra","am","ni","cho","va","nad","si","vil","mi","sa","eb","shon", "ri","li","sa","ma","da","ad","re","su","vo","tyo","sla"};
    string endFem[]={"ova","ivech","cheva","anth","al","ets","ya","enko","on","and","oux"};
    string endMa[]={"ov","ivech","chev","anth","al","ets","ya","enko","er","and","oux"};
    
    int randval=randRange(1,4);
    for(int i=0;i<randval;i++){
        res+=mid[randRange(0,22)];
    }
    if(fem){
        res+=endFem[randRange(0,10)];
    }else{
        res+=endMa[randRange(0,10)];
    }
    
    return res;
}
int main(){
    
    // Bootsplash
    cout<<
        "   ______                     ________                       __   "<<endl<<
        "  / ____/_  ______ __________/ / ____/___  ____  _________  / /__ "<<endl<<
        " / / __/ / / / __ `/ ___/ __  / /   / __ \\/ __ \\/ ___/ __ \\/ / _ \\"<<endl<<
        "/ /_/ / /_/ / /_/ / /  / /_/ / /___/ /_/ / / / (__  ) /_/ / /  __/"<<endl<<
        "\\____/\\__,_/\\__,_/_/   \\__,_/\\____/\\____/_/ /_/____/\\____/_/\\___/ v2.0"
    <<endl<<endl;
    vector<string> mainCommands;
    mainCommands.push_back("list");
    mainCommands.push_back("help");
    mainCommands.push_back("info");
    mainCommands.push_back("emergency");
    mainCommands.push_back("endemerg");
    
    vector<Room> rooms;
    vector<AccessLevel> levels;
    vector<PersonType> types;
    vector<Person> people;
    
    bool emergency=false;
    int randval=randRange(3,30);
    for(int i=0;i<randval;i++){
        Room r;
        r.id=i;
        r.type.push_back("class room");
        rooms.push_back(r);
    }
    randval=randRange(3,15);
    for(int i=0;i<randval;i++){
        Room r;
        r.id=i;
        r.type.push_back("lecture room");
        if(i<4){
            r.type.push_back("guest_available");
        }
        rooms.push_back(r);
    }
    randval=randRange(2,10);
    for(int i=0;i<randval;i++){
        Room r;
        r.id=i+30;
        r.type.push_back("conference room");
        if(i<4){
            r.type.push_back("guest_available");
        }
        rooms.push_back(r);
    }
    randval=randRange(3,30);
    for(int i=0;i<randval;i++){
        Room r;
        r.id=i+30;
        r.type.push_back("cabinet");
        rooms.push_back(r);
    }
    randval=randRange(1,1);
    for(int i=0;i<randval;i++){
        Room r;
        r.id=i+30;
        r.type.push_back("director cabinet");
        rooms.push_back(r);
    }
    randval=randRange(3,10);
    for(int i=0;i<randval;i++){
        Room r;
        r.id=i+30;
        r.type.push_back("toilet");
        rooms.push_back(r);
    }
    
    AccessLevel green;
    green.levelName="green";
    green.access.push_back("lecture room");
    green.access.push_back("conference room");
    green.access.push_back("class room");
    AccessLevel yellow;
    yellow.levelName="yellow";
    yellow.access.push_back("lecture room");
    yellow.access.push_back("conference room");
    yellow.access.push_back("class room");
    yellow.access.push_back("cabinet");
    AccessLevel red;
    red.levelName="red";
    red.access.push_back("lecture room");
    red.access.push_back("conference room");
    red.access.push_back("director cabinet");
    AccessLevel blue;
    red.levelName="blue";
    blue.access.push_back("guest_available");
    AccessLevel noLevel;
    noLevel.levelName="no_level";
    AccessLevel brown;
    brown.levelName="brown";
    brown.access.push_back("toilet");
    
    levels.push_back(green);
    levels.push_back(yellow);
    levels.push_back(red);
    levels.push_back(noLevel);
    levels.push_back(brown);
    levels.push_back(blue);
    
    PersonType directort;
    directort.typeString="director";
    directort.properties.push_back("costume");
    PersonType admint;
    admint.typeString="admin";
    admint.properties.push_back("hobbies");
    PersonType professort;
    professort.typeString="professor";
    professort.properties.push_back("subject");
    PersonType studentt;
    studentt.typeString="student";
    studentt.properties.push_back("course");
    //Guest accounts
    PersonType guestt;
    guestt.typeString="guest";
    guestt.properties.push_back("special info");
    
    types.push_back(directort);
    types.push_back(admint);
    types.push_back(professort);
    types.push_back(studentt);
    types.push_back(guestt);
    
    
    randval=randRange(20,100);
    for(int i=0;i<randval;i++){
        Person p;
        bool sex=randRange(0,1)==1;
        p.name=namegen(sex)+" "+surnamegen(sex);
        p.baseAccessTypes.push_back("brown");
        p.baseAccessTypes.push_back("green");
        p.type="student";
        for(int i=0;i<studentt.properties.size();i++){
            p.properties.push_back("some value");
        }
        people.push_back(p);
    }
    randval=randRange(1,10);
    for(int i=0;i<randval;i++){
        Person p;
        bool sex=randRange(0,1)==1;
        p.name=namegen(sex)+" "+surnamegen(sex);
        p.baseAccessTypes.push_back("brown");
        p.baseAccessTypes.push_back("no_level");
        p.type="admin";
        for(int i=0;i<admint.properties.size();i++){
            p.properties.push_back("some value");
        }
        people.push_back(p);
    }
    randval=randRange(1,1);
    for(int i=0;i<randval;i++){
        Person p;
        bool sex=randRange(0,1)==1;
        p.name=namegen(sex)+" "+surnamegen(sex);
        p.baseAccessTypes.push_back("brown");
        p.baseAccessTypes.push_back("red");
        p.type="director";
        for(int i=0;i<directort.properties.size();i++){
            p.properties.push_back("some value");
        }
        people.push_back(p);
    }
    
    randval=randRange(2,10);
    for(int i=0;i<randval;i++){
        Person p;
        bool sex=randRange(0,1)==1;
        p.name=namegen(sex)+" "+surnamegen(sex);
        p.baseAccessTypes.push_back("brown");
        p.baseAccessTypes.push_back("red");
        p.type="professor";
        for(int i=0;i<professort.properties.size();i++){
            p.properties.push_back("some value");
        }
        people.push_back(p);
    }
    
    randval=randRange(0,20);
    for(int i=0;i<randval;i++){
        Person p;
        bool sex=randRange(0,1)==1;
        p.name=namegen(sex)+" "+surnamegen(sex);
        p.baseAccessTypes.push_back("blue");
        p.type="guest";
        for(int i=0;i<guestt.properties.size();i++){
            p.properties.push_back("some value");
        }
        people.push_back(p);
    }
    
    vector<ConScope> scopes;
    
    ConScope rootScope;
    rootScope.name="root";
    rootScope.subscopes.push_back("control");
    ConScope controlC;
    controlC.name="control";
    controlC.subscopes.push_back("empty");
    controlC.commands.push_back("door_open");
    controlC.commands.push_back("door_close");
    scopes.push_back(controlC);
    rootScope.subscopes.push_back("watch");
    scopes.push_back(rootScope);
    
    ConScope watch;
    watch.name="watch";
    watch.subscopes.push_back("people");
    //watch.subscopes.push_back("access levels");
    watch.subscopes.push_back("rooms");
    scopes.push_back(watch);
    
    
    ConScope peopleC;
    peopleC.name="people";
    peopleC.commands.push_back("people_list");
    peopleC.subscopes.push_back("access levels");
    peopleC.subscopes.push_back("people types");
    scopes.push_back(peopleC);
    ConScope levelsC;
    levelsC.name="access levels";
    levelsC.commands.push_back("levels_list");
    scopes.push_back(levelsC);
    ConScope roomsC;
    roomsC.name="rooms";
    roomsC.commands.push_back("rooms_list");
    scopes.push_back(roomsC);
    ConScope typesC;
    typesC.name="people types";
    typesC.commands.push_back("person_type_list");
    scopes.push_back(typesC);
    
    
    cout<<"Welcome, "<<exec("whoami")<<endl;
    
    cout<<"Logged in at "<<getTime()<<endl;
    
    cout<<"To get some help, write 'help'. This will work in any scope."<<endl<<endl;
    
    int nesting=0;
    
    
    vector<ConScope> history;
    history.push_back(rootScope);
    ConScope curScope;
    
    string input;
    
    while(true){
        curScope=history[history.size()-1];
        prompt(history,nesting);
        getline (std::cin,input);
        if(input=="help"){
            printCon(nesting, "");
            printCon(nesting, "This is your help message.");
            printCon(nesting, "");
            printCon(nesting, "You are a security manager in Innopolis University.");
            printCon(nesting, "");
            printCon(nesting, "This is the GuardConsole.");
            printCon(nesting, "");
            printCon(nesting, "In GuardConsole you navigate through scopes of entities.");
            printCon(nesting, "");
            printCon(nesting, "To visit a scope or to execute a command, just write it's name.");
            printCon(nesting, "");
            printCon(nesting, "To leave any scope, just press Enter.");
            printCon(nesting, "");
            printCon(nesting, "To list all the avalaible commands and entities, type 'list'.");
            printCon(nesting, "");
            printCon(nesting, "To get some information about what is happening");
            printCon(nesting, "                    in the university right now, type 'info'. (SIMULATED)");
            printCon(nesting, "");
            printCon(nesting, "            Good bye, old friend. May the Force be with you.");
            printCon(nesting, "");
        }else if(input=="list"){
            printCon(nesting, "");
            printCon(nesting, "subscopes:");
            printCon(nesting, "");
            for(int i=0;i<curScope.subscopes.size();i++){
                printCon(nesting+1, curScope.subscopes[i]);
            }
            printCon(nesting, "");
            printCon(nesting, "commands:");
            printCon(nesting, "");
            for(int i=0;i<curScope.commands.size();i++){
                printCon(nesting+1, curScope.commands[i]);
            }
            for(int i=0;i<mainCommands.size();i++){
                printCon(nesting+1, mainCommands[i]);
            }
            printCon(nesting, "");
        }else if(input=="info"){
            for(int ttt=0;ttt<10;ttt++){
                printCon(nesting, "");
                printCon(nesting, ">>BREAKING NEWS!!!");
                Person p=people[randRange(0,people.size()-1)];
                printCon(nesting,p.type+" "+p.name);
                
                Room r=rooms[randRange(0,rooms.size()-1)];
                
                if(randRange(0,4)!=1){
                    printCon(nesting, "JUST TRIED TO ACCESS ROOM NUMBER "+to_string(r.id)+"!");
                    string tagstr="(";
                    for(int ii=0;ii<r.type.size();ii++){
                        tagstr+=" "+r.type[ii]+" ";
                    }
                    tagstr+=")";
                    printCon(nesting, tagstr);
                    bool ok=false;
                    for (int i=0;i<p.customAccess.size();i++){
                        if(p.customAccess[i]==r.id){
                            ok=true;
                            break;
                        }
                    }
                    for (int i=0;i<p.baseAccessTypes.size();i++){
                        for(int j=0;j<levels.size();j++){
                            if(levels[j].levelName==p.baseAccessTypes[i]){
                                for(int k=0;k<levels[j].access.size();k++){
                                    for(int ii=0;ii<r.type.size();ii++){
                                        if(levels[j].access[k]==r.type[ii]){
                                            ok=true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if(ok||emergency){
                        printCon(nesting, "it's okay, this person has all the rights to do so");
                    }else{
                        printCon(nesting, "ALAAAAAAAAARRRRRRRRM!!!! call the police");
                    }
                }else{
                    Person pp=people[randRange(0,people.size()-1)];
                    printCon(nesting, "JUST TRIED TO MODIFY "+pp.type+" "+pp.name+"'s data!");
                    
                    if(p.type=="admin"){
                        printCon(nesting, "it's okay, this person has all the rights to do so");
                        printCon(nesting, "add rights to visit room number "+to_string(r.id));
                        printCon(nesting, "it's tags: ");
                        string tagstr="";
                        for(int ii=0;ii<r.type.size();ii++){
                            tagstr+=" "+r.type[ii]+" ";
                        }
                        tagstr+="";
                        printCon(nesting, tagstr);
                        pp.customAccess.push_back(r.id);
                    }else{
                        printCon(nesting, "ALAAAAAAAAARRRRRRRRM!!!! call the police");
                    }
                }
            }
            printCon(nesting, "");
        }else if(input=="emergency"){
            printCon(nesting, "ARE YOU SURE TO ENTER EMERGENCY MODE? (y/n)");
            getline (std::cin,input);
            if(input=="y"){
                if(!emergency){
                    emergency=true;
                    printCon(nesting, "ENTERING EMERGENCY MODE...");
                    this_thread::sleep_for(chrono::milliseconds(500));
                    printCon(nesting, "All rooms are unlocked!");
                    this_thread::sleep_for(chrono::milliseconds(200));
                    printCon(nesting, "Alarm active!");
                    this_thread::sleep_for(chrono::milliseconds(200));
                    printCon(nesting, "Emercom call is in process...");
                }else{
                    printCon(nesting, "Already in emergency mode... Making an additional Emercom call.");
                    this_thread::sleep_for(chrono::milliseconds(500));
                }
                this_thread::sleep_for(chrono::milliseconds(3000));
                std::cout << R"(
                          .----------.
                         /            \ 
                        |  .--. :::::: |
                        | /    \'::::' |
                        | \    /       |
                        |  |  | [][][] |
                        |  |  | [][][] |
                        |  |  | [][][] |
                        | /    \[][][] |
                        | \    /[][][] |
                        |  '--'        |
                        8\  8         /
                        8 '-8--------'
                        8   8
                        8   8
                        8   8
                        8   8
                        8  8'
                        `8'`

                )" << '\n';
                this_thread::sleep_for(chrono::milliseconds(1000));
                printCon(nesting, "Emercom answered!");
                this_thread::sleep_for(chrono::milliseconds(1000));
                printCon(nesting, "Hello. You have called to ASCII Emercom. (•ᴗ•)╯");
                this_thread::sleep_for(chrono::milliseconds(1000));
                printCon(nesting, "Your call is very important for us, please stay on the line (☞•ヮ•)☞");
                this_thread::sleep_for(chrono::milliseconds(4000));
                printCon(nesting, "Okay, just joking  (-ᴗ•)");
                this_thread::sleep_for(chrono::milliseconds(800));
                printCon(nesting, "So what is your problem? ( ꒡⌓꒡)");
                getline (std::cin,input);
                this_thread::sleep_for(chrono::milliseconds(1500));
                printCon(nesting, "I didn't understand anything, so let me ask you a couple of more precise questions ԅ(≖‿≖ԅ)");
                this_thread::sleep_for(chrono::milliseconds(2000));
                printCon(nesting, "Would you like to call police? (y/n)");
                getline (std::cin,input);
                if(input=="y"){
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    printCon(nesting, "Police will be there in 5 minutes!");
                    this_thread::sleep_for(chrono::milliseconds(1500));
                    std::cout << R"(
              ,
     __  _.-"` `'-.
    /||\'._ __{}_(
    ||||  |'--.__\
    |  L.(   ^_\^
    \ .-' |   _ |
    | |   )\___/
    |  \-'`:._]
    \__/;      '-.
                    )" << '\n';
                    this_thread::sleep_for(chrono::milliseconds(1000));
                }
                printCon(nesting, "Would you like to call an ambulance? (y/n)");
                getline (std::cin,input);
                if(input=="y"){
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    printCon(nesting, "Ambulance will be there in 5 minutes!");
                    this_thread::sleep_for(chrono::milliseconds(1500));
                    std::cout << R"(
              _____________[\_
             /  _|_    .--..--\
             |)  |     [__][___\___
             |        |   -|-   __ `\
           _(  .----. |    |   /  \ [)
           `'---\__/-----------\__/--'
                        )" << '\n';
                    this_thread::sleep_for(chrono::milliseconds(1000));
                }
                printCon(nesting, "Would you like to call special anti-alien super-armored robotic military forces? (y/n)");
                getline (std::cin,input);
                if(input=="y"){
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    printCon(nesting, "ლ(ಠ_ಠლ) every alien invader will be destroyed ლ(ಠ_ಠლ)");
                    this_thread::sleep_for(chrono::milliseconds(3000));
                    std::cout << R"(
       __
   _  |@@|
  / \ \--/ __
  ) O|----|  |   __
 / / \ }{ /\ )_ / _\
 )/  /\__/\ \__O (__
|/  (--/\--)    \__/
/   _)(  )(_
   `---''---`
                        )" << '\n';
                    this_thread::sleep_for(chrono::milliseconds(1000));
                }
                
                printCon(nesting, "Okay. That was all we can do for you, bye. (•‿•)つ");
                    this_thread::sleep_for(chrono::milliseconds(1500));
                printCon(nesting, "Call ended.");
                printCon(nesting, "When everything is okay, you can leave the emergency mode by writing 'endemerg'");
            }else{
                printCon(nesting, "Okay, false alarm");
            }
        }else if(input=="endemerg"){
            emergency=false;
            printCon(nesting, "Everything is alright now");
        }else if(input==""){
            history.erase(history.end()-1);
            if(history.size()<1){
                printCon(nesting, "");
                printCon(nesting,"You are in the root scope.");
                printCon(nesting, "");
                history.push_back(rootScope);
            }else{
                printCon(nesting, "");
                printCon(nesting, " ❮ "+curScope.name+" ❮ ");
                printCon(nesting, "");
                nesting--;
            }
        }else{
            bool found=false;
            bool executed=false;
            
            for(int i=0;i<curScope.subscopes.size();i++){
                if(input==curScope.subscopes[i]){
                    found=true;
                    for(int j=0;j<scopes.size();j++){
                        if(scopes[j].name==input){
                            history.push_back(scopes[j]);
                            executed=true;
                        }
                    }
                }
            }
            if(!found){
                
                for(int i=0;i<mainCommands.size();i++){
                    if(input==mainCommands[i]){
                        printCon(nesting,"");
                        execCon(nesting,input, curScope, rooms, levels, types, people);
                        found=true;
                        executed=true;
                        printCon(nesting,"");
                    }
                }
                
                for(int i=0;i<curScope.commands.size();i++){
                    if(input==curScope.commands[i]){
                        printCon(nesting,"");
                        execCon(nesting,input, curScope, rooms, levels, types, people);
                        found=true;
                        executed=true;
                        printCon(nesting,"");
                    }
                }
            }
            if(!found && !executed){
                printCon(nesting,"");
                printCon(nesting,"No such command or subscope");
                printCon(nesting,"");
            }
            if(found && !executed){
                printCon(nesting,"");
                printCon(nesting,"This scope is empty.");
                printCon(nesting,"");
            }
            if(emergency){
                printCon(nesting,">EMERGENCY<");
            }
        }
    }
    //simThread.join();
}
