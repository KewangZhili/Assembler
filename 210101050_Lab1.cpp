#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<iomanip>
#include<bits/stdc++.h>
#include<sstream>
static bool flag=false;
using namespace std;

char label[20],opcode[8],operand[16],address[8];

int hash_fn(const char str[]){
	int hash_val=0;
	for(int i=0;str[i]!='\0';i++)  hash_val+=(int)str[i];
	return hash_val%29;
}
struct instruction
{
	string label_;
	string opcode_;
	string operand_;

	instruction(string label_ = "", string opcode_ = "", string operand_ = "")
	{
		this -> label_ = label_;
		this -> opcode_ = opcode_;
		this -> operand_ = operand_;
	}

	bool is_comment()
	{
		return (label_ == ".");
	}

	bool has_label()
	{
		return (label_ != "");
	}

	
};
string strip(string s)
{
	s.erase(remove(s.begin(), s.end(), ' '), s.end());
	return s;
}
void process_line(string line, instruction* instr)
{
	string label_, opcode_, operand_,word;
	
    stringstream iss(line);
    vector<string> words;
        while(iss >> word) 
        {
            words.push_back(word);
        }

		if(line[0] == '.')
        {
            (*instr).label_ = ".";
            (*instr).opcode_ = "";
            (*instr).operand_ = "";
			return;
        }

		if(words.size() == 3)
        {
            (*instr).label_ = words[0];
            (*instr).opcode_ = words[1];
            (*instr).operand_ = words[2];
        }
        else if(words.size() == 3)
        {
            (*instr).label_ = words[0];
            (*instr).opcode_ = words[1];
            (*instr).operand_ = words[2];
        }
        else if(words.size() == 2) 
        {
            (*instr).label_ = "";
            (*instr).opcode_ = words[0];
            (*instr).operand_ = words[1];

        }
        else{
            (*instr).label_ = "";
			(*instr).operand_ = "";
            (*instr).opcode_ = words[0];
		}

}

string process_line_2(string line, instruction* instr)
{
	string label_, opcode_, operand_, LOCCTR_,word;
	
	
    stringstream iss(line);
    vector<string> words;
        while(iss >> word) 
        {
            words.push_back(word);
        }

		if(line[0] == '.'){
            (*instr).label_=line;
            return "";

        }

        else{
            if(words.size()==4)
            {
                (*instr).label_ = words[1];
                (*instr).opcode_ = words[2];
                (*instr).operand_ = words[3];
                return words[0];
            }

            
            else if(words.size() == 3)
            {
                (*instr).label_ = "";
                (*instr).opcode_ = words[1];
                (*instr).operand_ = words[2];
                return words[0];
            }
            else if(words.size() == 2) 
            {
                (*instr).label_ = "";
                (*instr).opcode_ = words[0];
                (*instr).operand_ = "";
                return words[0];

            }
            else{
                
                return words[0];
            }
        }

}

int hexa_to_deci(char hexdecnumber[])
{
	int decimalnumber=0; 
    // used to store the power index 
    int cnt=0; 
    // used to store the digit 
    int digit; 
    // iterating the loop using length of hexadecnumber 
    for (int i = (strlen(hexdecnumber) - 1); i >= 0; i--) { 
        
        // using switch case finding the equivalent decimal 
        // digit for each hexa digit 
        switch (hexdecnumber[i]) { 
        case 'A': 
            digit = 10; 
            break; 
        case 'B': 
            digit = 11; 
            break; 
        case 'C': 
            digit = 12; 
            break; 
        case 'D': 
            digit = 13; 
            break; 
        case 'E': 
            digit = 14; 
            break; 
        case 'F': 
            digit = 15; 
            break; 
        default: 
            digit = hexdecnumber[i] - 0x30; 
        } 
        
        // obtaining the decimal number 
        decimalnumber = decimalnumber + (digit)*pow((double)16, (double)cnt); 
        cnt++; 
    } 
    return decimalnumber;
}

class Assembler_Class
{
	class OPTAB{
		struct node{
			char name[8],code[2];
			node *link;
		}*hash_table[29];
		public:
            OPTAB(){
                //DEFINE OPTAB in the default constructor

                /* LDA, LDX, LDL,STA, STX, STL, LDCH, STCH, ADD,
                SUB, MUL, DIV, COMP, J, JLT, JEQ, JGT, JSUB, RSUB, TIX, TD, RD,
                WD, RESW, RESB, WORD, BYTE  
                */
                for(int i=0;i<29;i++)   hash_table[i]=NULL;
                insert("JEQ","30");//
                insert("JGT","34");//
                insert("JLT","38");//
                insert("JSUB","48");//
                insert("LDA","00");//
                insert("LDCH","50");//
                insert("LDL","08");//
                insert("LDX","04");//
                insert("ADD","18");//
                insert("AND","40");
                insert("COMP","28");//
                insert("DIV","24");//
                insert("J","3c");//
                insert("MUL","20");//
                insert("OR","44");
                insert("RD","d8");//
                insert("RSUB","4c");
                insert("STA","0c");//
                insert("STCH","54");//
                insert("STL","14");//
                insert("STSW","e8");
                insert("STX","10");//
                insert("SUB","1c");//
                insert("TD","e0");//
                insert("TIX","2c");//
                insert("WD","dc");//
            }

            bool search(const char*name){
                //When in 1st pass(from input file ) and in 2nd pass(from buffer and the intermediate code file) 
                //opcode is checked and searched
                int i=hash_fn(name);
                node *r;
                for(r=hash_table[i];r!=NULL;r=r->link)
                        if(!strcmp(name,r->name))
                                return true;
                return false;
            }
            void insert(const char*name,const char*code){
                //new opcodes are entered(in the default constructor)
                int val=hash_fn(name);
                node *temp=new node;
                strcpy(temp->name,name);
                strcpy(temp->code,code);
                if(hash_table[val]==NULL)
                    temp->link=NULL;
                else
                    temp->link=hash_table[val];
                hash_table[val]=temp;
            }
            char* retrieve(const char*name){
                //If an opcode is found return it's name else return NULL and error handling is taken care of later
                int i=hash_fn(name);
                node *r;
                for(r=hash_table[i];r!=NULL;r=r->link)
                    if(!strcmp(name,r->name))
                            return r->code;
                return NULL;
            }
            ~OPTAB(){
                //destructor is called when the programme terminates and all opcodes and optables are closed
                int i;
                node *temp;
                for(i=0;i<29;i++){
                    for(;hash_table[i]!=NULL;){
                        temp=hash_table[i];
                        hash_table[i]=temp->link;
                        delete temp;
                    }
                }
            }	
	}optab;
	class SYMTAB
	{
        //SYMTAB SHALL STORE NAME OF THE label and the ADDRESS(in dec)(or the LOCCTR) where that label occurred
		struct node{
			char name[16];
			int address;
			node* link;
		}*hash_table[29];

		public:
            SYMTAB(){
                //Initialising SYMTAB using default constructor
                for(int i=0;i<29;i++)   hash_table[i]=NULL;
            }
            bool search(const char* str){
                //Search fn in the SYMTAB to search for defined labels
                int i=hash_fn(str);
                for(node *r=hash_table[i];r!=NULL;r=r->link)
                    if(!strcmp(str,r->name))
                        return true;
                return false;
            }
            void insert(const char*name,const int address){
                //Inserts newly defined label as encountered in pass1
                int i=hash_fn(name);
                node *temp=new node;
                strcpy(temp->name,name);
                temp->address=address;
                if(hash_table[i]==NULL)
                    temp->link=NULL;
                else
                    temp->link=hash_table[i];
                hash_table[i]=temp;
            }
            int retrieve(const char* str){
                //Retrieves the address(in decimal) of the address/LOCCTR of the label from SYMTAB if it exists else returns 0
                int i=hash_fn(str);
                node *r;
                for(r=hash_table[i];r!=NULL;r=r->link)
                    if(!strcmp(str,r->name))
                        return r->address;
                return 0;
            }
            ~SYMTAB(){
                //Destroys the symtab and clears the space used by it upon termination of the programme
                int i;
                node *temp;
                for(i=0;i<29;i++){
                    for(;hash_table[i]!=NULL;){
                        temp=hash_table[i];
                        hash_table[i]=temp->link;
                        delete temp;
                    }
                }
            }
        }symtab;
	int LOCCTR,strt_add,prog_len,literal_redifined_error_count,undefined_opcode_error_count,invalid_opcode_err_count;
    /*
        LOCCTR->stores current address
        strt_addr->stores the start edress from where the prog shall start
        prog_len:Total size of the prog.
        and the error counts are as named
    */

    ifstream fin;
    ofstream fout,obj_prog;

    //File streams defined 

	char prog_name[16],input_file[32],buffer[65536];

    //buffer stores the intermediate text after pass 1

	
    


	public:
        Assembler_Class(char* file)
        {
            literal_redifined_error_count=0;
            undefined_opcode_error_count=0;
            invalid_opcode_err_count=0;
            strcpy(input_file,file);
            fin.open(input_file);
            fin.getline(buffer,65536,EOF);
            cout<<"<---~~~INPUT FILE~~~--->\n"<<buffer<<"\n";
            fin.close();
            fin.open(input_file);
            fout.open("PASS_1_output.txt");
        }
        void pass1();
        void pass2();
        ~Assembler_Class()
        {
            //Destructor prints all the ouptut in the terminal and closes all streams
            fin.open("Intermediate.txt");
            fin.getline(buffer,65536,EOF);
            cout<<"<~~~~~ASSEMBLY LISTING~~~>\n"<<buffer<<"\n";
            fin.close();
            fin.open(prog_name);
            fin.getline(buffer,65536,EOF);
            cout<<"<~~~~~OBJECT PROGRAM~~~~~>\n"<<"GENERATED AFTER PASS_2 IN THE FILE NAMED AS PER INSTRUCTIONS"<<endl<<buffer<<"\n";
            fin.close();
            cout<<"\nOBJECT PROGRAM SIZE  : "<<prog_len<<" Bytes";
            cout<<"\n\nERRORS:\n";
            cout<<"REDEFINED SYMBOLS ( literals ): "<<literal_redifined_error_count;
            cout<<"\nUNDEFINED SYMBOLS (literals or opcodes ) : "<<undefined_opcode_error_count;
            cout<<"\nINVALID OPCODES   : "<<invalid_opcode_err_count<<"\n";
        }
};


void Assembler_Class::pass1(){
    //pass 1 analyses the code doesnt compute anything it constructs opcode(looking into optables),literal(symtable).

    //here fouts are done to intermideate file pass.txt and on to the terminalk as well
    char label[20],opcode[8],operand[16],address[8];
	
	int loc_temp;
    //this shall temporarily store the LOCCTR
    string line;
    
        
		getline(fin, line);

		instruction instr;
		process_line(line, &instr); 


        strcpy(opcode,instr.opcode_.c_str());
       strcpy(operand,instr.operand_.c_str());
       strcpy(label,instr.label_.c_str());


    if(strcmp(opcode,"START")) {
        cout<<endl<<"----------------"<<"FILE ERROR...,Either it Doesn't look like an assembly program."<<"OR NAME OF FIRST LABEL BESIDE START EXCEEDS 20 IN SIZE ENSURE THAT <20"<<endl<<"Try again"<<endl;
        flag=true;
        exit(1);
    }
    //Read each instruction line by line

    //If in the first line there is no label besides START instruction then I'am naming my programme 
    //as untitled else stick the label as the name of the programme

	if(!strcmp(opcode,"START")){
        //When it is  the start instruction

		strcpy(prog_name,label);

		strt_add=hexa_to_deci(operand);
		LOCCTR=strt_add;

        //LOCCTR stores the address of the current instruction

		fout<<setw(4)<<setfill('0')<<hex<<LOCCTR<<"\t";
        //prints LOCCTR in file i

		fout<<label<<"\t";
		fout<<opcode<<"\t";
		fout<<operand<<"\n";

         getline(fin, line);

	
		process_line(line, &instr); 


        strcpy(opcode,instr.opcode_.c_str());
       strcpy(operand,instr.operand_.c_str());
       strcpy(label,instr.label_.c_str());

	}
	else{
        //Assumption->1:: If an untitled progrramme is set then it goes into 0 address and therefore starting LOCCTR=0
		strt_add=0;
		LOCCTR=0;
		strcpy(prog_name,"UNTITLED");
	}
	while(strcmp(opcode,"END")){
        
		loc_temp=LOCCTR;
		if(strcmp(label,".")){
			if(strlen(label)!=0){
                //searching whether labels exist in symtab
				if(!symtab.search(label)) symtab.insert(label,LOCCTR);
				else{
					cout<<"ERROR: |"<<label<<"| REDEFINED\n";
					literal_redifined_error_count++;
				}
			}
			if(optab.search(opcode))
				LOCCTR+=3;
			else if(!strcmp(opcode,"WORD"))
                //RESERVES 3B OF ADDRESS AND FILLS IN THE CONTENT THAT IS WRITTEN ON THE RIGHT OF THE WORD IN THAT ADDRESS
				LOCCTR+=3;
			else if(!strcmp(opcode,"RESW"))
                //RESERVES AS MANY WORD(*3 BYTES) OF ADDRESS AS IS SPECIFIED IN THE OPERAND FIELD
				LOCCTR+=(3*atoi(operand));
			else if(!strcmp(opcode,"RESB"))
                ////RESERVES AS MANY BYTES OF  ADDRESS AS IS SPECIFIED IN THE OPERAND FIELD
				LOCCTR+=atoi(operand);

			else if(!strcmp(opcode,"BYTE"))
			{
				if(operand[0]=='X')
                    //Only Stores 1B for all that is written in operand after X eg X'01' ->All of 01 is stored in 1 B
					LOCCTR+=(strlen(operand)-3)/2;
				else
                    //RESERVES 1B OF ADDRESS AND FILLS IN THE CONTENT THAT IS WRITTEN ON THE RIGHT OF THE WORD IN THAT ADDRESS for as many variables as there are 
					LOCCTR+=(strlen(operand)-3);
			}
			else
			{
                //This error occurs when there there is '.' instead of label field(i.e. label field is invalid.)
				cout<<"ERROR: INVALID OPCODE |"<<opcode<<"| found.Returning....\n";
                
				invalid_opcode_err_count++;
                // flag=true;
                // return;
			}
			fout<<setw(4)<<setfill('0')<<hex<<loc_temp;
            //Converts and prints in req format the current LOCCTR value
		}
		fout<<"\t";
        fout<<label<<"\t";
        fout<<opcode<<"\t";
        fout<<operand<<"\n";
		getline(fin, line);

	
		process_line(line, &instr); 


        strcpy(opcode,instr.opcode_.c_str());
       strcpy(operand,instr.operand_.c_str());
       strcpy(label,instr.label_.c_str());
	}
    fout<<"\t";
    fout<<label<<"\t";
    fout<<opcode<<"\t";
    fout<<operand<<"\n";
	fin.close();
	fout.close();

    //store all the assembly code_generated with line no.s in the buffer

	fin.open("PASS_1_output.txt");
	fin.getline(buffer,65536,EOF);
	cout<<"<---INTERMEDIATE FILE--->\n"<<buffer<<"\n";
    cout<<"Generated after 1 pass by the assembler"<<endl;
	fin.close();
	prog_len=LOCCTR-strt_add;


}
void Assembler_Class::pass2(){
	char address[8],label[20],opcode[8],operand[16],first_address[4];
	int text_record_length=0,increment=0;
	bool relative,isRES;
	char object_code[6],text_record[64];

	stringstream T(text_record),O(object_code);
    //DEFINING TWO STRINGSTREAM

	fin.open("PASS_1_output.txt");
    //The code that was given is appended with the line no.s and printed in the assembly format
	fout.open("Intermediate.txt");

    //opening the output file stream obj_prog
	obj_prog.open(prog_name);
    string line;
    
        instruction instr;
        
		getline(fin, line);
    
		
		string address_=process_line_2(line, &instr); 

        strcpy(address,address_.c_str());
        strcpy(opcode,instr.opcode_.c_str());
       strcpy(operand,instr.operand_.c_str());
       strcpy(label,instr.label_.c_str());

    //find the first address or inital LOCCTR
	if(!strcmp(opcode,"START"))
	{
		fout<<address<<"\t";
		fout<<label<<"\t";
		fout<<opcode<<"\t";
		fout<<operand<<"\t";
		fout<<"\t\n";
        getline(fin, line);

		
		address_=process_line_2(line, &instr); 

        strcpy(address,address_.c_str());
        strcpy(opcode,instr.opcode_.c_str());
       strcpy(operand,instr.operand_.c_str());
       strcpy(label,instr.label_.c_str());

	obj_prog<<"H."<<prog_name;
    //obj_code must start with .H

    //Assembly code 
	for(int i=0;i<20-strlen(prog_name);i++)  obj_prog<<" ";
    //

	obj_prog<<"."<<setw(6)<<setfill('0')<<hex<<strt_add<<".";
	obj_prog<<setw(6)<<setfill('0')<<hex<<prog_len<<"\n";

	strcpy(first_address,address);

	while(strcmp(opcode,"END")){
        
		O.str("");
		if(strcmp(label,".")){
			if(optab.search(opcode)){
				if(strlen(operand)!=0){
					char actual_operand[16]="";
					relative=false;
                    //Searching for relative addressing
					for(int i=0;i<strlen(operand)-2;i++){
						actual_operand[i]=operand[i];

                        //having ,X indicates rel addressing
						if(operand[i+1]==',' && operand[i+2]=='X'){
							relative=true;
							break;
						}
					}
					if(relative){
						if(symtab.search(actual_operand)){
							O<<optab.retrieve(opcode)<<setw(4)<<setfill('0')<<hex<<symtab.retrieve(actual_operand)+32768;
						}
						else{
                            //PRINTS ERROR IF OPCODE NOT FOUND IN OPTABLE
                            O<<optab.retrieve(opcode)<<"0000";
                            cout<<"ERROR: |"<<operand<<"| UNDEFINED\n";
                            undefined_opcode_error_count++;
        	            }
					
					}
					else if(symtab.search(operand)) O<<optab.retrieve(opcode)<<setw(4)<<setfill('0')<<hex<<symtab.retrieve(operand);
                    //print the opcode in req format

					else{
						O<<optab.retrieve(opcode)<<"0000";
						cout<<"ERROR: | "<<operand<<"| UNDEFINED \n";
						undefined_opcode_error_count++;
					}
				}

                //if operand doesnt exists prints all o in the objectcode
				else O<<optab.retrieve(opcode)<<"0000";
				increment=3;
			}
			else if(strcmp(opcode,"WORD") && !(strcmp(opcode,"BYTE"))){
                //byte
				if(operand[0]=='X'){
                    
                    ////Only Stores 1B for all that is written in operand after X eg X'01' ->All of 01 is stored in 1 B
					for(int i=2;i<strlen(operand)-1;i++)
						O<<(char)tolower(operand[i]);
					increment=(strlen(operand)-3)/2;
				}
				else if(operand[0]=='C'){
                    ////RESERVES 1B OF ADDRESS AND FILLS IN THE CONTENT THAT IS WRITTEN ON THE RIGHT OF THE WORD IN THAT ADDRESS for as many variables as there are 
					for(int i=2;i<strlen(operand)-1;i++)
						O<<hex<<(int)operand[i];
					increment=strlen(operand)-3;
				}
				else{
                    //no operand found fill with 0s as operand
					O<<setw(6)<<setfill('0')<<hex<<atoi(operand);
					increment=3;
				}
			}
			text_record_length+=increment;

            //can show atmost 30 chars
			if(text_record_length>30){
				obj_prog<<"T."<<setw(6)<<setfill('0')<<first_address<<"."<<setw(2)<<setfill('0')<<hex<<text_record_length-increment<<T.str()<<"\n";
				text_record_length=increment;
				strcpy(first_address,address);
				T.str("");
			}
			T<<"."<<O.str();
		}

		fout<<address<<"\t";
		fout<<label<<"\t";
		fout<<opcode<<"\t";
		fout<<operand<<"\t";
		fout<<O.str()<<"\n";
        //printing the generated opcode in output file

        getline(fin, line);

		
		address_=process_line_2(line, &instr); 

        strcpy(address,address_.c_str());
        strcpy(opcode,instr.opcode_.c_str());
       strcpy(operand,instr.operand_.c_str());
       strcpy(label,instr.label_.c_str());

        //CHECKING FOR ANY RESERVED ADDRESSES
        
		isRES=false;
		if((!strcmp(opcode,"RESW"))||(!strcmp(opcode,"RESB"))){
			obj_prog<<"T."<<setw(6)<<setfill('0')<<first_address<<"."<<setw(2)<<setfill('0')<<hex<<text_record_length<<T.str()<<"\n";
			text_record_length=0;
			T.str("");
		}
		while((!strcmp(opcode,"RESW"))||(!strcmp(opcode,"RESB"))){
			fout<<address<<"\t";
            fout<<label<<"\t";
            fout<<opcode<<"\t";
            fout<<operand<<"\n";
			getline(fin, line);

		
		address_=process_line_2(line, &instr); 

        strcpy(address,address_.c_str());
        strcpy(opcode,instr.opcode_.c_str());
       strcpy(operand,instr.operand_.c_str());
       strcpy(label,instr.label_.c_str());
            
			isRES=true;
		}
		if(isRES) strcpy(first_address,address);
	}
	if(!isRES)  obj_prog<<"T."<<setw(6)<<setfill('0')<<first_address<<"."<<setw(2)<<setfill('0')<<hex<<text_record_length<<T.str()<<"\n";
    obj_prog<<"E."<<setw(6)<<setfill('0')<<hex<<strt_add;
    //searchinf for the label from which the main prog must start.

    fout<<address<<"\t";
    fout<<label<<"\t";
    fout<<opcode<<"\t";
    fout<<operand<<"\t";
    fin.close();
    fout.close();
    obj_prog.close();


}



}

int main(int argc,char* argv[]){
	char fname[32];
    
	if(argc==1){
		cout<<"You haven's added any file name yet...run the programme again as \".a.out <File Name.>\"\n";

		cin>>fname;
	}
	else    strcpy(fname,argv[1]);



	Assembler_Class newAssemblyClass(fname);
    //cout<<"THE FILE WHERE THE INTERMEDIATE CODE IS SAVED IS PASS_1_OUTPUT.txt AND WHERE THE OBJECT code is SAVED IS the name of the programme(label beside the ||START operation|| if it exists else UNTITLED ).."<<endl;
	newAssemblyClass.pass1();
    if(flag){
        return 0;
    }
	newAssemblyClass.pass2();

       //cout<<"THE FILE WHERE THE INTERMEDIATE CODE IS SAVED IS PASS_1_OUTPUT.txt AND WHERE THE OBJECT code is SAVED IS the name of the programme(label beside the ||START operation|| if it exists else UNTITLED ).."<<endl;

	return 0;
}