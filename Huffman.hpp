/*
***********************************
*           Darshan Vala          *
*						U39780959             *
*                                 *
***********************************
*/

#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
#include <map>

#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"

using namespace std;

class HuffmanTree : public HuffmanTreeBase {
    public:
         string compress(const string inputStr);
         string serializeTree() const;
         string decompress(const string inputCode, const std::string serializedTree);
         void postOrder (HuffmanNode* root);
         void compute(HuffmanNode* root, string inputStr, map<char, string> &strMap);

    private:

        HuffmanNode *t_Node;
        string period = "";
        HeapQueue<HuffmanNode*, HuffmanNode::Compare> heap;

};

#endif
