#include "btree.h"

//public functions

    //Btree constructor, assumes root is at offset 0
    BTree::BTree(){
        rootAddr = 0;
        height = 0;
        read = 0;
        write = 0;
        strcpy(treeFileName, "\0"); //initally no file name

    }

    //writes out dummy and root to file
    void BTree::writeHeader(char * filename){
        strcpy(treeFileName, filename);
        treeFile.open(treeFileName, ios::in|ios::out|ios::binary);
        BTNode dummy;
       
        //inital root address
        rootAddr = sizeof(BTNode);
       
        //make child[0] = root address
        dummy.child[0] = rootAddr;


        //write dummy to file
        treeFile.write((char *) &dummy, sizeof(BTNode));

        //reset file pointer
        treeFile.clear();

        //create root to be written
        BTNode root; 
        //root.currSize = 0; //initalize current size of the root
        treeFile.write((char*) &root, sizeof(BTNode));

        //reset file pointer
        treeFile.clear();
    }

    void BTree::insert(keyType key){
        cout << "Now inserting " << key << endl;
        insert(key, rootAddr, -1, -1);
 
    }

    void BTree::reset(char * filename){
        strcpy(treeFileName, filename);
        treeFile.open(treeFileName, ios::in|ios::out|ios::binary); //set up tree file pointer
        BTNode dummy = getNode(0);
        rootAddr = dummy.child[0]; //where the address of root is contained
        root = getNode(dummy.child[0]); //get the root node from file into mem
    }

    void BTree::close(){

    }

    void BTree::printTree(){
        cout << "-------- B-Tree of Height " << height << " --------" << endl;
       printTree(rootAddr);
    }

    void BTree::inorder(){

    }

    void BTree::reverse(){

    }

    int BTree::getHeight(){
        return height;
    }

    bool BTree::search(string key){

    }

    keyType BTree::retrieve(string key){

    }

    void BTree::totalio() const{

    }

    int BTree::countLeaves(){

    }


//private functions

    void BTree:: printTree(int recAddr){
        //cout << recAddr << endl;
        //if its a leaf print it
        if(isLeaf(recAddr)){
            BTNode dummy = getNode(recAddr);
            //cout << "node is a leaf" << endl;
            printNode(recAddr);
        }
        //if its not a leaf, print it and go through its chilluns
        else{
            BTNode dummy = getNode(recAddr);
            printNode(recAddr);
            //cout << dummy.num_children << endl;
            for(int i=0; i <= dummy.currSize; i++){
                printTree(dummy.child[i]);
            }
        }
    }

    void BTree:: inorder(int rootAddr){

    }

    void BTree:: reverse(int rootAddr){

    }

    int BTree:: findAddr(keyType key, BTNode t, int tAddr){

    }

    int BTree:: findpAddr(keyType key, BTNode t, int tAddr){

    }

    //oneAddr is parent address
    void BTree:: insert(keyType key, int recAddr, int oneAddr, int twoAddr){
        int nAddr;
        BTNode node = getNode(recAddr); //get node trying to insert into
        bool leaf = isLeaf(node);

         //int x = 0;
        //if it's not a leaf
        if(!leaf){
            int x = node.currSize;
            //search for child branch to go to
            for(x =node.currSize-1; x > -1; x--){
                //when key is greater than key compared to, go to that
                //if it never reaches this statement, key goes to 0
                if(!(key < node.contents[x])){
                    break;
                }
            }
           
            nAddr = node.child[x+1];
            insert(key, nAddr, recAddr, twoAddr); //here is the recursion

            return;
        }

         if(leaf && node.currSize == 4){
            //cout << "houston we have a split" << endl;
            int childAddr;
            splitNode(key, recAddr, oneAddr, childAddr);
           
            //get parent
            node = getNode(oneAddr);
            
            int i = node.currSize-1; 
                keyType cmp = node.contents[i];
               
                //compare each key from right to left 
                while(i>=0){
                    //if key is less than cmp, move cmp to i+1
                    if(key < cmp){
                        node.contents[i+1] = cmp;
                        node.child[i] = node.child[i+1];
                    }
                    else{
                        //key is greater than cmp at i
                        //key needs to be inserted at i+1
                        break;
                    }
                    //decrement i and get next cmp
                    i--;
                    cmp = node.contents[i];
                }       
                cout << i << endl;
                //insert key at sorted loc
                node.contents[i+1] = key;
                node.child[i] = recAddr;
                node.child[i+1] = childAddr;


            //increment currSize after succefully inserting
            node.currSize++;

            //write out updated node
            treeFile.seekp(oneAddr, ios::beg);
            treeFile.write((char *) &node, sizeof(BTNode));
            treeFile.clear();
            return;
        }

         if(leaf && node.currSize < 4){
            //insert the key

            //if node is empty, insert key in first slot
            if(node.currSize == 0){
                node.contents[0] = key;
            }
            else{
                int i = node.currSize-1; 
                keyType cmp = node.contents[i];
               
                //compare each key from right to left 
                while(i>=0){
                    //if key is less than cmp, move cmp to i+1
                    if(key < cmp){
                        node.contents[i+1] = cmp;
                    }
                    else{
                        //key is greater than cmp at i
                        //key needs to be inserted at i+1
                        break;
                    }
                    //decrement i and get next cmp
                    i--;
                    cmp = node.contents[i];
                }       

                //insert key at sorted loc
                node.contents[i+1] = key;
            }

            /*cout << "sorted" << endl;
            for(int i=0; i<node.currSize+1; i++){
                cout << node.contents[i] << endl;
            }*/

            //increment currSize after succefully inserting
            node.currSize++;

            //write out updated node
            treeFile.seekp(recAddr, ios::beg);
            treeFile.write((char *) &node, sizeof(BTNode));
            treeFile.clear();
            return;
        } 

    }



    BTNode BTree:: getNode(int recAddr){
       treeFile.seekg(recAddr, ios::beg); //seek from beginning
       BTNode node;
       treeFile.read((char *) &node, sizeof(BTNode));
       treeFile.clear();
       return node; 
    }

    void BTree:: printNode(int recAddr){
        BTNode node = getNode(recAddr);
        cout << "     *** node of size " << node.currSize << " ***     " << endl;
        for(int i=0; i<node.currSize; i++){
            cout << node.contents[i] << endl;
        }    
    }

    void BTree:: placeNode(keyType k, int recAddr, int oneAddr, int twoAddr){

    }

    bool BTree:: isLeaf(int recAddr){
        BTNode check = getNode(recAddr);
        if(check.num_children == 0){
            return true;
        }
        return false;
        
    }

    bool BTree:: isLeaf(BTNode t){
        if(t.num_children == 0){
            return true;
        }
        return false;
    }

    int BTree:: countLeaves(int recAddr){

    }

    void BTree:: adjRoot(keyType rootElem, int oneAddr, int twoAddr){

    }

    void BTree:: splitNode(keyType& key, int recAddr, int& oneAddr, int& twoAddr){
        cout << "Splitting" << endl;
        BTNode node = getNode(recAddr); //get full node
        BTNode newLeft, newRight;

        //create set to get middle key
        set <keyType> nodeSet;
        set <keyType> :: iterator it;

        nodeSet.insert(key);
        for(int i=0; i<node.currSize; i++){
            //insert album into set to be ordered
            nodeSet.insert(node.contents[i]);
        }
    
        if(height == 0){
            oneAddr = -1;
            //create new root
            BTNode newRoot;
            
            //start iterator it at begining again
            it = nodeSet.begin();
            
            //new left gets recAddr
            newLeft.currSize = 2;
            newLeft.num_children = 0;
            newLeft.contents[0] = *it;
            advance(it,1);
            newLeft.contents[1] = *it;           

            advance(it, 1); //get middle

            newRoot.num_children = 2;
            newRoot.currSize = 1;
            newRoot.contents[0] = *it;
 
            newRight.num_children = 0;
            newRight.currSize = 2;
            advance(it, 1); 
            newRight.contents[0] = *it;
            advance(it, 1);
            newRight.contents[1] = *it;

            //write out left child
            treeFile.seekg(recAddr, ios::beg);
            //cout << "first child: " << treeFile.tellp() << endl;
            treeFile.write((char *) &newLeft, sizeof(BTNode));
            treeFile.clear();

            //cout << "second child: " << treeFile.tellp() << endl;

            newRoot.child[0] = recAddr;
            newRoot.child[1] = treeFile.tellp();
          
            treeFile.write((char *) &newRight, sizeof(BTNode));

            //cout << "root: " << treeFile.tellp() << endl;;
            rootAddr = treeFile.tellp();

            //update dummy
            BTNode dummy = getNode(0);
            dummy.child[0] = rootAddr;
            //cout << "dummy.child[0] == " << dummy.child[0] << endl;

            //write dummy
            treeFile.seekg(0, ios::beg);
            treeFile.write((char *) &dummy, sizeof(BTNode));
            treeFile.clear();

            //write root
            treeFile.seekp(rootAddr, ios::beg);
            treeFile.write((char *) &newRoot, sizeof(BTNode));
            treeFile.clear();

            //increment tree height
            height++;
        }
        else{
            //create left and right 
            it = nodeSet.begin();
            newLeft.currSize = 2;
            newLeft.num_children = 0;
            newLeft.contents[0] = *it;
            advance(it,1);
            newLeft.contents[1] = *it;           


            advance(it, 1); //get middle
            key = *it; //middle key       

            newRight.num_children = 0;
            newRight.currSize = 2;
            advance(it, 1); 
            newRight.contents[0] = *it;
            advance(it, 1);
            newRight.contents[1] = *it;

            //write out new left and right to end of file
            treeFile.seekg(recAddr, ios::beg);
            //get address of new left child, sent back to insert
            treeFile.write((char *) &newLeft, sizeof(BTNode));
            treeFile.seekg(0, ios::end);
            twoAddr = treeFile.tellp();    
            cout << twoAddr << endl;
            //write out newRight
            treeFile.write((char *) &newRight, sizeof(BTNode));   

        }

    
    }

    bool BTree:: search(string key, BTNode t, int tAddr){

    }
 

    








 
