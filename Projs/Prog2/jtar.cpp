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
string add_0(string name);

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
    vector<File> :: iterator fit; //file iterator (its fit)
    string time, fSize, protection, tar_name;
    int tar_size = 0;
    File tmp;

    //swtich statement to handle request type
    switch(type){
        //error was found 
        case -1:
            exit(0);
            break;
        case 0:
        {
            size = argc - 3;
            counter = 0; //temp counter
            //put all inital files into an vector and check for dir
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
                
                //create the file 
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

            //create tar name and open the file
            tar_name = argv[2];
            fstream outfile(tar_name, ios::out | ios::binary);

            //z is a temp string to hold string of tar_size
            string z = to_string(tar_size);
            //write size of tar to file
            outfile.write((char *) z.c_str(), sizeof(char)*z.size());

            //create the tar file 
            for(fit=final_files.begin(); fit != final_files.end(); fit++){
                tmp = *fit;
                outfile.write((char *) &tmp, sizeof(File));
                //get contents of a file if it is not a directory
                if(tmp.isADir() == false){
                    fstream infile(tmp.getName().c_str(), ios::in);
                    //get length of file and read into a char array
                    size = stoi(tmp.getSize());
                    char buf[size];
                    infile.read(buf, size);
                    //write out file contents to outfile
                    outfile.write((char *) &buf, size);
                    infile.close();
                }
            }
            outfile.close();
            break;
        }
        case 1:
        {
            fstream infile(argv[2], ios::in|ios::binary);     
     
            //get size of tar file
            infile >> tar_size;  
           
            while(infile.read((char *) &tmp, sizeof(File))){
                cout << tmp.getName() << endl;

                //will skip over file info
                if(tmp.isADir() == false){
                    int move_bytes = stoi(tmp.getSize());
                    infile.seekg(move_bytes, ios::cur);
                }
            }
            
            break;
        }
        case 2:
        {
            fstream infile(argv[2], ios::in|ios::binary);     
            string command;
            //get size of tar file
            infile >> tar_size;  
           
            while(infile.read((char *) &tmp, sizeof(File))){
                string fname = tmp.getName();
                if(tmp.isADir()){
                    //check to see if dir exists by opening it and checking for failure  
                    fstream check(fname.c_str(), ios::in);
                    //if it fails, do mkdir
                    if(check.fail() == true){
                        command = "mkdir ";
                        command.append(fname);
                        system(command.c_str());

                        //restore the permissions on the file
                        command = "chmod ";
                        command.append(tmp.getPmode());
                        command.append(" ");
                        command.append(fname);
                        system(command.c_str());

                        //restore the time on the file
                        command = "touch -t ";
                        command.append(tmp.getStamp());
                        command.append(" ");
                        command.append(fname);
                        system(command.c_str());

                    }
                }
                else{
                    //get size of file and read in contents
                    size = stoi(tmp.getSize());
                    char buf[size]; 
                    infile.read((char *) &buf, size);

                    //remove the file and then open the file for ouput
                    //command = "rm ";
                    //command.append(fname);
                    //system(command.c_str());
                    fstream newfile(fname.c_str(), ios::out);
            
                    //write contents to the file 
                    newfile.write((char *)&buf, sizeof(char)*size);
                
                    //restore the permissions on the file
                    command = "chmod ";
                    command.append(tmp.getPmode());
                    command.append(" ");
                    command.append(fname);
                    system(command.c_str());

                    //restore the time on the file
                    command = "touch -t ";
                    command.append(tmp.getStamp());
                    command.append(" ");
                    command.append(fname);
                    system(command.c_str());

                }
            }
            break;
        }
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
    time_t at_time = s_struct.st_atime;
    string time = ctime(&at_time);
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

    format = to_string(year) + months[month] + to_string(day) + add_0(to_string(hour)) + add_0(to_string(min)) + "." + add_0(to_string(sec));  
    return format; 
}

string add_0(string name){

    if(name.size() == 1){
        return "0" + name;
    }

    return name;

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




