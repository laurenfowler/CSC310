Outline


    1. Some inital set up

        Idea: I will create a struct to contain the intital command line files. There will be a string filename and boolean isDir
 
        a. Compare all file names to list of files names in the directory. Will be stored in a vector of structs with a pointer
           If no match: cerr and exit the program
            i. note: this will be done inside a function 

        b. Send to function that uses inode data to determine if it is a directory or not. I wrote code to do this in Lab 3
           so I will probably reuse it in this project.  


    2. -cf function: 

        Assumptions: All files/dirs exist in the directory and are labeled properly by the time I execute the cf function
  
        Details: 

            a. Loop through struct of files/dirs. Each filename is sent to a function alongside a pointer to a vector of File objects. 

            b. Inside the function:
                note: looping until the end of the vector object 
                i.   If name belongs to a file in the current directory, get all data from stat, might send to specialized functions
                     that extract particular data, and put it into a file object, which will then be appened to the vector
                ii.  If name belongs to a directory, call function to open the directory and add all the new files/directories to
                     the vector of structs
                     1. This would likely have the call to list out all of the files within the directory
                     note: I would expect upon return to original function that the vector would be longer, and any directories within
                           directories would be handled properly by being sent to be opened again, so on and so forth

            c. Results in a fully populated vector of File objects 

    3. -xf function:


        Details:
        
            a. Open file and loop through reading in each record as a File until end of file, then storing the file contents as a string. 

            b. If I come across a directory, I will get the size of it and make all the next X bytes of files are placed in that directory.
               Afterwards, I will continue to open the files into the main directory until another subdirectory or eof. 

            c. Create the file and put the content back into it

            c. Use touch to restore the access/modification times, and use chmod to restore the permissions    

             


 




