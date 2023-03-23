/*
***********************************
*           Darshan Vala          *
*						U39780959             *
*                                 *
***********************************
*/

#ifndef HUFFMAN_CPP
#define HUFFMAN_CPP
#include "Huffman.hpp"

//Returns serialized tree
string HuffmanTree::serializeTree() const{
    return period;
}

//compress the string
string HuffmanTree::compress(const string inputStr){
    map<char, int> frequency;
    map<char, string> m2;

    string result = "";
    int store = 0;

   //getting the characters
   int j = 0;
    for(j = 0; j < inputStr.length(); j++){
        frequency[inputStr[j]]++;
    }

    // inserts freq
    for(auto at : frequency){
        heap.insert(new HuffmanNode(at.first, at.second));
    }

    do{
        HuffmanNode* left = heap.min();
        heap.removeMin();

        HuffmanNode* right = heap.min();
        heap.removeMin();

        store = left -> getFrequency() + right -> getFrequency();
        heap.insert(new HuffmanNode('\0', store, t_Node, left, right));

    }while(heap.size() > 1); // if error get rid of do while and just make while

        HuffmanNode* root = heap.min();
        postOrder(root);
        compute(root, "", m2);

        for(j = 0; j < inputStr.length(); j++){
            result += m2[inputStr[j]];

        }

        return result;
}//**********************************************************************************************************


// check if it is a leaf or branch
//add L+char or B
void HuffmanTree::compute(HuffmanNode* root, string inputStr, map<char, string> &strMap){
    if(root == NULL){
      return;
    }

    if(root -> isLeaf()){
        strMap[root -> getCharacter()] = inputStr;
    }


    compute(root -> left, inputStr + "0", strMap);
    compute(root -> right, inputStr + "1", strMap);

    if(root -> isLeaf()){
        period.push_back('L');
        period.push_back(root -> getCharacter());
    }

    else
    {
        period.push_back('B');
    }
}

//Function used to decompress the string
string HuffmanTree::decompress (const string inputCode, const string serializedTree){

    bool flag = false;
    HuffmanNode* location;
    stack<HuffmanNode*> load;
    string solved = "";
    char i;
    auto bots = 0; // hahaha... funny no?

    for(auto bots = 0; bots < serializedTree.length(); bots++){

        if(serializedTree[bots] == 'L'){
            bots++;
            i = serializedTree[bots];
            HuffmanNode* newN = new HuffmanNode(i, 0, NULL, NULL, NULL);
            load.push(newN);
        }

        else{
            HuffmanNode *r = load.top();
            load.pop();
            HuffmanNode *l = load.top();
            load.pop();

            HuffmanNode* newNode = new HuffmanNode(0,0,NULL,l,r);

            load.push(newNode);
        }
    }

    HuffmanNode* root = load.top();

    while(bots < inputCode.length()){
        if(!flag){
            location = root;
            flag = true;
        }

        else{
            if(location -> isLeaf()){
                solved.push_back(location -> getCharacter());
                flag = false;
            }

            else{
                if(inputCode[bots]=='1'){
                    location = location -> right;
                }

                else{
                    location = location -> left;
                }

                bots++; // roll out...
            }
        }
    }

    solved.push_back(location -> getCharacter());
    return solved;

}

//Recursive function to go through the binary tree
//proud of this
void HuffmanTree::postOrder(HuffmanNode* root){

    if(root == NULL){
        postOrder(root -> left);
        postOrder(root -> right);


        if(root -> isLeaf()){
            period.push_back('L');
            period.push_back(root -> getCharacter());
        }

        else{
            period.push_back('B');
        }
    }
}


#endif
