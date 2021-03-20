#include <iostream>
#include <string>
#include <vector>
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
        "\\____/\\__,_/\\__,_/_/   \\__,_/\\____/\\____/_/ /_/____/\\____/_/\\___/ "
    <<endl<<endl;
    vector<string> mainCommands;
    mainCommands.push_back("list");
    mainCommands.push_back("help");
    mainCommands.push_back("info");
    
    vector<Room> rooms;
    vector<AccessLevel> levels;
    vector<PersonType> types;
    vector<Person> people;
    
    int randval=randRange(3,30);
    for(int i=0;i<randval;i++){
        Room r;
        r.id=i;
        r.type="class room";
        rooms.push_back(r);
    }
    randval=randRange(3,15);
    for(int i=0;i<randval;i++){
        Room r;
        r.id=i;
        r.type="lecture room";
        rooms.push_back(r);
    }
    randval=randRange(2,10);
    for(int i=0;i<randval;i++){
        Room r;
        r.id=i+30;
        r.type="conference room";
        rooms.push_back(r);
    }
    randval=randRange(3,30);
    for(int i=0;i<randval;i++){
        Room r;
        r.id=i+30;
        r.type="cabinet";
        rooms.push_back(r);
    }
    randval=randRange(1,1);
    for(int i=0;i<randval;i++){
        Room r;
        r.id=i+30;
        r.type="director cabinet";
        rooms.push_back(r);
    }
    randval=randRange(3,10);
    for(int i=0;i<randval;i++){
        Room r;
        r.id=i+30;
        r.type="toilet";
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
    
    types.push_back(directort);
    types.push_back(admint);
    types.push_back(professort);
    types.push_back(studentt);
    
    
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
    
    
    vector<ConScope> scopes;
    
    ConScope rootScope;
    rootScope.name="root";
    rootScope.subscopes.push_back("control");
    rootScope.subscopes.push_back("watch");
    scopes.push_back(rootScope);
    
    ConScope control;
    control.name="control";
    control.subscopes.push_back("people");
    control.subscopes.push_back("access levels");
    control.subscopes.push_back("rooms");
    control.subscopes.push_back("people types");
    scopes.push_back(control);
    
    
    ConScope peopleC;
    peopleC.name="people";
    scopes.push_back(peopleC);
    ConScope levelsC;
    levelsC.name="access levels";
    scopes.push_back(levelsC);
    ConScope roomsC;
    roomsC.name="rooms";
    scopes.push_back(roomsC);
    ConScope typesC;
    typesC.name="people types";
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
                printCon(nesting, "BREAKING NEWS!!!");
                Person p=people[randRange(0,people.size()-1)];
                printCon(nesting,p.type+" "+p.name);
                
                Room r=rooms[randRange(0,rooms.size()-1)];
                
                if(randRange(0,4)!=1){
                    printCon(nesting, "JUST TRIED TO ACCESS "+r.type+" number "+to_string(r.id)+"!");
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
                                    if(levels[j].access[k]==r.type){
                                        ok=true;
                                    }
                                }
                            }
                        }
                    }
                    if(ok){
                        printCon(nesting, "it's okay, he has all the rights to do so");
                    }else{
                        printCon(nesting, "ALAAAAAAAAARRRRRRRRM!!!! call the police");
                    }
                }else{
                    Person pp=people[randRange(0,people.size()-1)];
                    printCon(nesting, "JUST TRIED TO MODIFY "+pp.type+" "+pp.name+"'s data!");
                    
                    if(p.type=="admin"){
                        printCon(nesting, "it's okay, he has all the rights to do so");
                        printCon(nesting, "add rights to visit room number "+to_string(r.id));
                        printCon(nesting, "it is a "+r.type);
                        pp.customAccess.push_back(r.id);
                    }else{
                        printCon(nesting, "ALAAAAAAAAARRRRRRRRM!!!! call the police");
                    }
                }
            }
            printCon(nesting, "");
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
        }
    }
    //simThread.join();
}
