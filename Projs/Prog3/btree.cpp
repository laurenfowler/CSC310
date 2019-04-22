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
        int c = 0;
        BTNode node = getNode(recAddr); //get node trying to insert into
        bool leaf = isLeaf(node);

        while(!leaf){
            //compare record trying to store
            //find child under record greater than one we are trying to insert  
            //keep going down until leaf is found
            //update rec address as we go
        }
        
        //if we got here, node is a leaf
        if(node.currSize == 4){
            cout << "houston we have a split" << endl;
            //insert key like normal
            splitNode(key, recAddr);
        }
        else{
            //insert node
            node.currSize++; //increment size of the node 
            cout << "houston we inserting a key in this bitch" << endl; 
            node.contents[node.currSize-1] = key; //at this moment it is not ordered, I can put it in a set later when needed to order

           //will be the recAddr of the node
           //write out updated node to file
           treeFile.seekp(recAddr, ios::beg);
           treeFile.write((char *) &node, sizeof(BTNode));
           treeFile.clear();
           //cout << "current node size " <<  node.currSize << endl;
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
        BTNode node = getNode(recAddr);

        //create set
        //set <int> nodeSet;
        set <keyType> nodeSet;
        //set <int> :: iterator it;
        set <keyType> :: iterator it;

        nodeSet.insert(key);
        for(int i=0; i<node.currSize; i++){
            //insert UPC code for each album into set
            //nodeSet.insert((stoi(node.contents[i].getUPC())));
            nodeSet.insert(node.contents[i]);
        }

        //get middle and remove

    }

    bool BTree:: search(string key, BTNode t, int tAddr){

    }
 

    








 
