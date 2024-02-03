
//SREERAG MURALEEDHARAN


#include "mainwindow.hpp"



void MainWindow::createMinHeap()
{
    char id;

    // Open the input file for reading
    inFile.open(inFileName, ios::in);

    // Incrementing frequency of characters that appear in the input file
    inFile.get(id);
    while (!inFile.eof())
    {
        arr[id]->freq++;
        inFile.get(id);
    }

    // Close the input file
    inFile.close();

    // Pushing the Nodes which appear in the file into the priority queue (Min Heap)
    for (int i = 0; i < 128; i++)
    {
        if (arr[i]->freq > 0)
        {
            minHeap.push(arr[i]);
        }
    }
}


void MainWindow::createTree()
{
    Node *left, *right;

    // Creating Huffman Tree with the Min Heap created earlier
    priority_queue<Node*, vector<Node*>, Compare> tempPQ(minHeap);
    while (tempPQ.size() != 1)
    {
        left = tempPQ.top();
        tempPQ.pop();

        right = tempPQ.top();
        tempPQ.pop();

        root = new Node();
        root->freq = left->freq + right->freq;

        root->left = left;
        root->right = right;
        tempPQ.push(root);
    }
}

void MainWindow::traverse(Node* r, string str)
{
    if (r->left == NULL && r->right == NULL)
    {
        r->code = str;
        return;
    }

    traverse(r->left, str + '0');
    traverse(r->right, str + '1');
}

void MainWindow::createCodes()
{
    // Traversing the Huffman Tree and assigning specific codes to each character
    traverse(root, "");
}




int MainWindow::binToDec(string inStr)
{
    int res = 0;
    for (auto c : inStr)
    {
        res = res * 2 + c - '0';
    }
    return res;
}

void MainWindow::saveEncodedFile()
{
    // Saving encoded (.huf) file
    inFile.open(inFileName, ios::in);

    string s = "";
    char id;

    // Saving the meta data (Huffman tree)
    in += (char)minHeap.size();
    priority_queue<Node*, vector<Node*>, Compare> tempPQ(minHeap);
    while (!tempPQ.empty())
    {
        Node* curr = tempPQ.top();
        in += curr->data;

        // Saving 16 decimal values representing the code of curr->data
        s.assign(127 - curr->code.length(), '0');
        s += '1';
        s += curr->code;

        // Saving decimal values of every 8-bit binary code
         in += (char)binToDec(s.substr(0, 8));
        for (int i = 0; i < 15; i++)
        {
            s = s.substr(8);
            in += (char)binToDec(s.substr(0, 8));
        }

        tempPQ.pop();
    }
    s.clear();

    // Saving codes of every character appearing in the input file
    inFile.get(id);
    while (!inFile.eof())
    {
        s += arr[id]->code;

        // Saving decimal values of every 8-bit binary code
        while (s.length() > 8)
        {
            in += (char)binToDec(s.substr(0, 8));
            s = s.substr(8);
        }
        inFile.get(id);
    }

    // Finally, if bits remaining are less than 8, append 0's
    int count = 8 - s.length();
    if (s.length() < 8)
    {
        s.append(count, '0');
    }

    in += static_cast<char>(binToDec(s));
    // Append count of appended 0's
    in += static_cast<char>(count);

    // Write the in string to the output file

    // Close the input file
    inFile.close();
}
