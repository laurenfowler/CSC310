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
        BTNode dummy = getNode(0);
        treeFile.write((char *) &dummy, sizeof(BTNode));
        
        //seek correct position for root to be written
        treeFile.seekg(dummy.child[0]);
        BTNode root = getNode(rootAddr);
        treeFile.write((char*) &root, sizeof(BTNode));
    }

    void BTree::insert(keyType key){

    }

    void BTree::reset(char * filename){
        strcpy(treeFileName, filename);
        treeFile.open(treeFileName, ios::in|ios::out|ios::binary);
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
        if(recAddr != -1){
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

    void BTree:: insert(keyType key, int recAddr, int oneAddr, int twoAddr){

    }

    BTNode BTree:: getNode(int recAddr){

    }

    void BTree:: printNode(int recAddr){

    }

    void BTree:: placeNode(keyType k, int recAddr, int oneAddr, int twoAddr){

    }

    bool BTree:: isLeaf(int recAddr){

    }

    bool BTree:: isLeaf(BTNode t){

    }

    int BTree:: countLeaves(int recAddr){

    }

    void BTree:: adjRoot(keyType rootElem, int oneAddr, int twoAddr){

    }

    void BTree:: splitNode(keyType& key, int recAddr, int& oneAddr, int& twoAddr){

    }

    bool BTree:: search(string key, BTNode t, int tAddr){

    }
 

    








 
