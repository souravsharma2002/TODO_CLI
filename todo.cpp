#include <iostream>
#include<fstream>
#include<string.h>
#include<string>
#include<ctime>
#include<vector>



void ls()
{
    std::vector<std::string> lines;
    std::fstream file;
    file.open("todo.txt",std::ios::in);
    if (file.is_open()){ //checking whether the file is open
      std::string tp;
      while(getline(file, tp)){ //read data from file object and put it into string.
         lines.push_back(tp); //print the data of the string
      }
      file.close(); //close the file object.
   }
   if(lines.size()==0)
   {
       std::cout<<"There are no pending todos!\n";
       return;
   }
   for(int i=lines.size()-1;i>=0;i--)
   {
       std::cout<<"["<<i+1<<"]"<<" "<<lines[i]<<"\n";
   }

}

void add(std::string line)
{
    std::fstream file;
    file.open("todo.txt",std::ios::app);
    if(file.is_open()) //checking whether the file is open 
    {
      file<<line<<'\n'; //inserting text
      file.close(); //close the file object
   }
}

bool del(int num)
{
    std::fstream file;
    file.open("todo.txt",std::ios::in);
    std::ofstream ofs; 
    ofs.open("temp.txt", std::ofstream::out); 
    char c; 
    int line_no = 1;
    bool check=false; 
    while (file.get(c)) 
    { 
        // if a newline character 
        if(line_no==num)check=true;
  
        // file content not to be deleted 
        if (line_no != num) 
            ofs << c; 
         if (c == '\n') 
        line_no++; 
    } 
    ofs.close(); 
  
    // closing input file 
    file.close(); 
  
    // remove the original file 
    remove("todo.txt"); 
  
    // rename the file 
    rename("temp.txt","todo.txt" ); 
    return check;
}

bool done(int num)
{
    time_t now = time(0);
    tm *gmtm = localtime(&now);
    std::fstream file;
    file.open("todo.txt",std::ios::in);
    std::ofstream ofs; 
    ofs.open("temp.txt", std::ofstream::out); 
    std::fstream done;
    done.open("done.txt",std::ios::app);
    int n= 1;
    if (file.is_open()){ //checking whether the file is open
      std::string tp;
      while(getline(file, tp)){ //read data from file object and put it into string.
         if(n==num)
         {
             done<<"x "<<1900+gmtm->tm_year<<"-"<<1+gmtm->tm_mon<<"-"<<gmtm->tm_mday<<" "<<tp<<"\n";
         }
         
         else if(n!=num)
         {
             ofs<<tp<<"\n";
         } 
         n++;
      }
      file.close(); //close the file object.
   } 
    ofs.close(); 
  
    // closing input file 
    done.close(); 
  
    // remove the original file 
    remove("todo.txt"); 
  
    // rename the file 
    rename("temp.txt","todo.txt" ); 
    if(num>n || num<1)
    return false;
    else
    {
        return true;
    }
    
}

void report()
{
    int pending_count=0,done_count=0;
    time_t now = time(0);
    tm *gmtm = localtime(&now);
    std::fstream file;
    file.open("todo.txt",std::ios::in);
    std::fstream done;
    done.open("done.txt",std::ios::in);
    int n= 1;
    if (file.is_open()){ //checking whether the file is open
      std::string tp;
      while(getline(file, tp)){ //read data from file object and put it into string.
        pending_count++;
      }
      file.close(); //close the file object.
   } 
   if (done.is_open()){ //checking whether the file is open
      std::string tp;
      while(getline(done, tp)){ //read data from file object and put it into string.
        done_count++;
      }
      done.close(); //close the file object.
   } 
   std::cout<<1900+gmtm->tm_year<<"-"<<1+gmtm->tm_mon<<"-"<<gmtm->tm_mday<<" Pending : "<<pending_count<<" Completed : "<<done_count<<"\n";


}
int main(int argc, char* argv[])
{

    int pendingcount=0;
    int donecount=0;
    if(argc==1)
    {
        std::cout<<"Usage :-\n$ ./todo add \"todo item\"  # Add a new todo\n$ ./todo ls               # Show remaining todos\n$ ./todo del NUMBER       # Delete a todo\n$ ./todo done NUMBER      # Complete a todo\n$ ./todo help             # Show usage\n$ ./todo report           # Statistics\n";
    }
    else if(strcmp(argv[1],"help")==0)
    {
        std::cout<<"Usage :-\n$ ./todo add \"todo item\"  # Add a new todo\n$ ./todo ls               # Show remaining todos\n$ ./todo del NUMBER       # Delete a todo\n$ ./todo done NUMBER      # Complete a todo\n$ ./todo help             # Show usage\n$ ./todo report           # Statistics\n";
    }
    else if(strcmp(argv[1],"ls")==0)
    {
        ls();
    }
    else if(strcmp(argv[1],"add")==0)
    {
        if(argc==2)
        {
            std::cout<<"Error: Missing todo string. Nothing added!\n";
        }
        else
        {
            add(argv[2]);
            pendingcount++;
            std::cout<<"Added todo: \""<<argv[2]<<"\""<<std::endl;
        }
    }
    else if(strcmp(argv[1],"del")==0)
    {
        if(argc==2)
        {
            std::cout<<"Error: Missing NUMBER for deleting todo.\n";
        }
        else
        {
            bool check=del(atoi(argv[2]));
            if(check==true)
            {
                pendingcount--;
                std::cout<<"Deleted todo #"<<argv[2]<<std::endl;
            }
            else if(check==false)
            {
                std::cout<<"Error: todo #"<<argv[2]<<" does not exist. Nothing deleted."<<std::endl;
            }
        }
        

    }
    else if(strcmp(argv[1],"done")==0)
    {
        if(argc==2)
        {
            std::cout<<"Error: Missing NUMBER for marking todo as done.\n";
        }
        else
        {
            bool check=done(atoi(argv[2]));
            if(check==true)
            {
                pendingcount--;
                donecount++;
                std::cout<<"Marked todo #"<<argv[2]<<" as done."<<std::endl;
            }
            else if(check==false)
            {
                std::cout<<"Error: todo #"<<argv[2]<<" does not exist."<<std::endl;
            }
        } 

    }
    else if(strcmp(argv[1],"report")==0)
    {
        report();
    }
    
    return 0;
}
// working fine
