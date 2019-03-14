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
void find_files(fInfo file, vector<fInfo> &all_files);
string get_protection(string filename);
string get_size(string filename);
string get_timestamp(string filename);
string format_time(string time);

int main(int argc, char *argv[]){

    int type = check_errors(argc,  argv);
    int size; //holds # of files/dirs
    int counter; //temp counter
    vector <fInfo> file_vec; //inital file vector
    vector <fInfo> all_files; //holds all the files to be stored in .tar
    struct fInfo temp; //temp fInfo struct
    vector <fInfo> :: iterator it;
    string to_find = "/";
    vector<File> final_files;
    string time, fSize, protection;
    int tar_size = 0;

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

            //get all files into all_files vector 
            for(it = file_vec.begin(); it != file_vec.end(); it++){
                temp = *it;
                find_files(temp, all_files);   
            }

            //create the Files and put them in the file vector            
            for(it = all_files.begin(); it != all_files.end(); it++){
                temp = *it;
                time = get_timestamp(temp.filename);
                time = format_time(time);                         
                fSize = get_size(temp.filename);
                protection = get_protection(temp.filename);   
                File store(temp.filename.c_str(), protection.c_str(), fSize.c_str(), time.c_str());
                //turn on dir flag if necessary and do size calculation
                if(temp.isDir){
                    store.flagAsDir();
                    int y = store.recordSize();
                    //wont include fileSize bc would be including it twice then
                    tar_size = tar_size + y;
                }
                else{
                    int y = store.recordSize();
                    //caculate the size of the tar file
                    tar_size = tar_size + y + stoi(fSize);
                }

                final_files.push_back(store);  
            }    
            cout << tar_size << endl;        


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

//returns modify time
string get_timestamp(string filename){
    struct stat s_struct;
    stat(filename.c_str(), &s_struct);
    time_t mt_time = s_struct.st_mtime;
    string time = ctime(&mt_time);
    return time;

}

//formats the time string
string format_time(string time){

    //aint pretty but it works
    map <string, string> months;
    months["Jan"] = "01";
    months["Feb"] = "02";
    months["Mar"] = "03";
    months["Apr"] = "04";
    months["May"] = "05";
    months["Jun"] = "06";
    months["Jul"] = "07";
    months["Aug"] = "08";
    months["Sep"] = "09";
    months["Oct"] = "10";
    months["Nov"] = "11";
    months["Dec"] = "12";
    
    string format;
    string ignore; //will ignore the day of the week
    string month;
    int day, hour, min, sec, year;
    char tmp;
    
    stringstream ss;
    ss.str(time);
    ss>>ignore;
    ss>>month;
    ss>>day;
    ss>>hour;
    ss>>tmp;
    ss>>min;
    ss>>tmp;
    ss>>sec;
    ss>>year;

    format = to_string(year) + months[month] + to_string(day) + to_string(hour) + to_string(min) + "." + to_string(sec);    
    return format; 
}

//returns size of file
string get_size(string filename){
    struct stat s_struct;
    stat(filename.c_str(), &s_struct);
    return to_string(s_struct.st_size);
}

//returns octal form of protection mode
string get_protection(string filename){
    struct stat s_struct;
    stat(filename.c_str(), &s_struct);
    string permissions;    

    //gets decimal val of protection mode
    int user = (s_struct.st_mode & S_IRWXU);
    int group = (s_struct.st_mode & S_IRWXG);
    int world = (s_struct.st_mode & S_IRWXO);
   

    //cheap and dirty way of doing octal, but will always work in this case
    //convert to octal. user and group always divisible by 64 and 8 respetivly, world always needs mod
    user = user/64;
    group = group/8;
    world = world%8;

    permissions = to_string(user) + to_string(group) + to_string(world);
    return permissions;
}

//checks if string is a directory
bool check_dir(string filename){
    struct stat s_struct;
    stat(filename.c_str(), &s_struct);
    if(S_ISDIR(s_struct.st_mode)){
        return true;
    }
    return false;
}

//gets all the files and stores them in a vector
void find_files(fInfo file, vector<fInfo> &all_files){
    struct fInfo temp; 
    
    all_files.push_back(file); //add file to the vector list
    //checks dirs recursively
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
                temp.isDir = check_dir(temp.filename); //checks to see if new file is dir so can list dirs in dirs
                find_files(temp, all_files);
            }
        }
        closedir(dirp);
    }   
} 




