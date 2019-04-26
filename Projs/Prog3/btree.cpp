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
        //cout << "Now inserting " << key << endl;
        insert(key, rootAddr);
 
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
        //if its a leaf print it
        if(isLeaf(recAddr)){
            BTNode dummy = getNode(recAddr);
            printNode(recAddr);
        }
        //if its not a leaf, print it and go through its chilluns
        else{
            BTNode dummy = getNode(recAddr);
            printNode(recAddr);
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

    void BTree:: insert(keyType key, int recAddr){ //,int oneAddr, int twoAddr){
        int nAddr;
        BTNode node = getNode(recAddr); //get node trying to insert into
        bool leaf = isLeaf(node);

        if(leaf && node.currSize < 4){
            //insert the key

            if(node.currSize == 0){
                node.contents[0] = key;
                cout << "key " << key << " inserted at " << 0 << endl;
            }
            else{
                cout << "node.currSize = " << node.currSize << endl;
                int i = node.currSize-1; 
                keyType cmp = node.contents[i];
                cout << "contents at " << i << " " << cmp << endl;
                
                while(i>=0){
                    cout << "in while loop" << endl;
                    cout << "comparing key " << key << endl;
                    cout << "with          " << cmp << endl;    
                    if(key < cmp){
                        cout << "placing cmp in " << i+1 << endl;
                        node.contents[i+1] = cmp;
                    }
                    else{
                        //insert key at sorted loc
                        //node.contents[i+1] = key;
                        //cout << "key " << key << " inserted at " << i+1 << endl; 
                        //cout << "breaking out of loop" << endl;
                        break;
                    }
                    
                    i--;
                    cmp = node.contents[i];
                }       
                //insert key at sorted loc
                node.contents[i+1] = key;
                cout << "key " << key << " inserted at " << i+1 << endl; 
            }

            cout << "sorted" << endl;
            for(int i=0; i<node.currSize+1; i++){
                cout << node.contents[i] << endl;
            }

            //increment currSize after succefully inserting
            node.currSize++;

            //write out updated node
            treeFile.seekp(recAddr, ios::beg);
            treeFile.write((char *) &node, sizeof(BTNode));
            treeFile.clear();
            return;
        } 

        if(leaf && node.currSize == 4){
           // cout << "houston we have a split" << endl;
           // splitNode(key, recAddr);
            return;
        }

        int x = 0;
        //if it's not a leaf
        if(!leaf){
            //search for child branch to go to
            while(key < node.contents[x]){
                x++;
            }
            nAddr = node.child[x];
            insert(key, nAddr); //here is the recursion


            //???come back with the place to insert new key if split address does not equal -1

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

    void BTree:: splitNode(keyType& key, int recAddr){ //, int& oneAddr, int& twoAddr){
        cout << "in split node" << endl;
        BTNode node = getNode(recAddr); //get full node

        //create set
        set <keyType> nodeSet;
        set <keyType> :: iterator it;

        nodeSet.insert(key);
        for(int i=0; i<node.currSize; i++){
            //insert album into set to be ordered
            nodeSet.insert(node.contents[i]);
        }

    }

    bool BTree:: search(string key, BTNode t, int tAddr){

    }
 

    








 
