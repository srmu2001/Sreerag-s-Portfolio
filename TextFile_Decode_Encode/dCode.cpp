#include "mainwindow.hpp"




    void MainWindow::saveDecodedFile()
{
    // Open the input file in binary mode
    inFile.open(inFileName, ios::in | ios::binary);

    // Read the size of the Huffman tree
    unsigned char size;
    inFile.read(reinterpret_cast<char*>(&size), 1);

    // Reading count at the end of the file which is the number of bits appended to make the final value 8-bit
    inFile.seekg(-1, ios::end);
    char count0;
    inFile.read(&count0, 1);

    // Ignore the meta data (Huffman tree) (1 + 17 * size) and read the remaining file
    inFile.seekg(1 + 17 * size, ios::beg);

    // Vector to store the decoded text
    vector<unsigned char> text;
    unsigned char textseg;
    inFile.read(reinterpret_cast<char*>(&textseg), 1);
    while (!inFile.eof())
    {
        text.push_back(textseg);
        inFile.read(reinterpret_cast<char*>(&textseg), 1);
    }

    Node *curr = root;
    string path;

    // Iterate through the decoded text
    for (int i = 0; i < text.size() - 1; i++)
    {
        // Converting decimal number to its equivalent 8-bit binary code
        path = decToBin(text[i]);

        // Handling the last character and adjusting the bit count
        if (i == text.size() - 2)
        {
            path = path.substr(0, 8 - count0);
        }

        // Traversing Huffman tree and appending resultant data to the file
        for (int j = 0; j < path.size(); j++)
        {
            if (path[j] == '0')
            {
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }

            // If leaf node is reached, append the data to the output
            if (curr->left == NULL && curr->right == NULL)
            {
                out += curr->data;
                curr = root;
            }
        }
    }

    // Close the input file
    inFile.close();
}


string MainWindow::decToBin(int inNum)
{
    string temp = "", res = "";
    while (inNum > 0)
    {
        temp += (inNum % 2 + '0');
        inNum /= 2;
    }

    // Append leading zeros to make it 8-bit
    res.append(8 - temp.length(), '0');
    for (int i = temp.length() - 1; i >= 0; i--)
    {
        res += temp[i];
    }

    return res;
}


void MainWindow::getTree()
{
    // Open the input file in binary mode
    inFile.open(inFileName, ios::in | ios::binary);

    // Read the size of the MinHeap
    unsigned char size;
    inFile.read(reinterpret_cast<char*>(&size), 1);

    // Create the root of the Huffman tree
    root = new Node();

    // Next size * (1 + 16) characters contain (char)data and (string)code[in decimal]
    for(int i = 0; i < size; i++)
    {
        char aCode;
        unsigned char hCodeC[16];

        // Read the character and its corresponding Huffman code
        inFile.read(&aCode, 1);
        inFile.read(reinterpret_cast<char*>(hCodeC), 16);

        // Convert decimal characters into their binary equivalent to obtain code
        string hCodeStr = "";
        for (int i = 0; i < 16; i++)
        {
            hCodeStr += decToBin(hCodeC[i]);
        }

        // Removing padding by ignoring leading '0's and the first '1' character
        int j = 0;
        while (hCodeStr[j] == '0')
        {
            j++;
        }
        hCodeStr = hCodeStr.substr(j + 1);

        // Adding node with aCode data and hCodeStr string to the Huffman tree
        buildTree(aCode, hCodeStr);
    }

    // Close the input file
    inFile.close();
}


void MainWindow::buildTree(char a_code, string& path)
{
    Node* curr = root;

    // Iterate through the Huffman code
    for (int i = 0; i < path.length(); i++)
    {
        // Traverse left for '0', right for '1'
        if (path[i] == '0')
        {
            if (curr->left == NULL)
            {
                curr->left = new Node();
            }
            curr = curr->left;
        }
        else if (path[i] == '1')
        {
            if (curr->right == NULL)
            {
                curr->right = new Node();
            }
            curr = curr->right;
        }
    }

    // Assign the data to the leaf node
    curr->data = a_code;
}
