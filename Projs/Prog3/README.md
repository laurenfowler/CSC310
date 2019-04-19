Design the B-Tree Class: 
    
        BTree() 
            --constructor to create a new b-tree with empty root BTNode and the address of that node
        
        void insert(keyType key);
            --This function will iterate through the b-tree and find where the new key should be inserted.
              It should also handle splits.
 
        int search(string key); 
            --This function will search the b-tree for the key (which should be the UPC code) until it finds
              a match. If a match is found, it returns the location on disc, else it will return -1 for a 
              not found value

        void print();
            --calls private function printTree with private value of the rootAddress and then 
              uses preorder traveral to print out contents of the tree in the proper format. 
              This will use recursion
            
        int height(); 
            --traverses the tree to the left until it reaches a leaf, incrementing the height count after
              every traversal. returns the height of the tree

        int countLeaves();
            --counts the total number of leave in the tree at any given moment and returns the value as 
              an integer

        //thoughts
            --could I create a class function to easily access the information in a node? Should I?
              I would think this would help in searching for the key match?

Creating the B-Tree: 

        1. Get the address of the root node from the index file for the binary tree and place it into the dummy
           node in the root of the binary tree

        2. Open the file from the command line arguements and use the Album class istream operator overload to
           read in the album from the file

        3. Once the file is read in, create a BTNode and insert it into the B-Tree

        4. If a split occurs, handle the movement of the root node address

        Note: -1 indicates that there is no file 




