//jtar software
#include "file.h"
#include "includes.h"

struct fInfo{
    string filename;
    bool isDir = false;

};

//prototypes
int check_errors(int argc, char *argv[]);
bool check_dir(string filename);
void find_files(fInfo file);

int main(int argc, char *argv[]){

    int type = check_errors(argc,  argv);
    int size; //holds # of files/dirs
    int counter; //temp counter
    vector <fInfo> file_vec; //inital file vector
    vector <fInfo> all_files; //holds all the files to be stored in .tar
    struct fInfo temp; //temp fInfo struct
    vector <fInfo> :: iterator it;
    string to_find = "/";

    //swtich statement to handle request type
    switch(type){
        //error was found 
        case -1:
            exit(0);
            break;
        case 0:
            size = argc - 3;
            counter = 0; //temp counter
            //put all inital files into an array and check for dir
            for(int i=3; i<argc; i++){
                temp.filename = argv[i];
                temp.isDir = check_dir(temp.filename);
                //housekeeping, removes '/' from end of directory
                if(temp.isDir){
                   int x = temp.filename.find(to_find);
                   temp.filename = temp.filename.substr(0, x);    
                }
                file_vec.push_back(temp);
                counter++;
            }

            for(it = file_vec.begin(); it != file_vec.end(); it++){
                temp = *it;
                find_files(temp);   
                cout << "looping" << endl;        
            }
            cout << "back in switch" << endl;

            break;

        case 1:
            cout << "-tf chosen" << endl;
            break;
        case 2:
            cout << "-xf chosen" << endl;
            break;
        case 3: 
            system("cat help");
            break;

    }


    return 0;
}

bool check_dir(string filename){
    struct stat s_struct;
    stat(filename.c_str(), &s_struct);
    if(S_ISDIR(s_struct.st_mode)){
        return true;
    }
    return false;
}

void find_files(fInfo file){
    struct fInfo temp; 
    cout << file.filename << endl;
    cout << "hi hi hi" << endl;

    if(check_dir(file.filename)){
        DIR* dirp = opendir(file.filename.c_str()); //open the directory
        struct dirent *ptr; //pointer
        while((ptr = readdir(dirp)) != NULL){
            string name = ptr -> d_name;
            if(name == "." || name == ".."){
                //makes it so that current and parent directories are ignored when parsing dir 
            }
            else{
                temp.filename = file.filename + '/' + ptr->d_name;
                cout << temp.filename << endl;
                temp.isDir = check_dir(temp.filename); //checks to see if new file is dir so can list dirs in dirs
                find_files(temp);
            }
        }
        closedir(dirp);
    }
    
} 




