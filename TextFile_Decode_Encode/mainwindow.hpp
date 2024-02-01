
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;
namespace Ui
{
class MainWindow;
}

///
///  Represents a Huffman Tree node created in the process of compressing or decompressing files.
///  It holds information about character data, frequency, Huffman code,
///  and includes two pointers indicating connections to the left and right nodes, if they are present.
///
    struct Node
{
    char data;
    unsigned freq;
    string code;
    Node *left, *right;

    ///  Constructor to initialize the node
    Node() {
        left = right = NULL; // Initialize left and right pointers to NULL (leaf node initially)
    }
};

///  Define the MainWindow class inheriting from QMainWindow
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ///  Constructor with optional parent parameter
    explicit MainWindow(QWidget *parent = nullptr);

    ///  Destructor
    ~MainWindow();

    ///  Function to compress the input file
    void compress();

    ///  Function to decompress the input file
    void decompress();

    ///  User interface object
    Ui::MainWindow *ui;

private:
    ///  Vector of tree nodes representing characters' ASCII values with initialized frequencies
    std::vector<Node*> arr;

    ///  Input and output file streams
    std::fstream inFile, outFile;

    ///  Strings to store file names
    std::string outFileName, inFileName;

    ///  Root node of the Huffman tree
    Node *root;

    ///  Strings to store input and output data
    std::string in = "";
    std::string out = "";

    ///  Comparator class for the priority queue in the Min Heap
    class Compare
    {
    public:
        bool operator() (Node* l, Node* r)
        {
            return l->freq > r->freq;
        }
    };

    ///  Priority queue representing the Min Heap
    std::priority_queue<Node*, std::vector<Node*>, Compare> minHeap;

    ///  Function to initialize a vector of tree nodes representing character ASCII values with initialized frequencies
    void createArr();

    ///  Function to traverse the constructed tree to generate Huffman codes for each present character
    void traverse(Node*, std::string);

    ///  Function to convert binary string to its equivalent decimal value
    int binToDec(std::string);

    ///  Function to convert a decimal number to its equivalent binary string
    std::string decToBin(int);

    ///  Function to reconstruct the Huffman tree while decoding the file
    void buildTree(char, std::string&);

    ///
    ///  This function reads the input file, records the frequency of every character present in the file,
    ///  and then establishes a Min Heap structure. This structure is built using a priority queue,
    ///  storing nodes and utilizing their frequencies as the basis for comparison.
    ///
    void createMinHeap();

    ///
    ///  This function constructs the Huffman tree by replicating the previously created Min Heap while preserving the original one.
    ///  It removes the two nodes with the lowest frequency, designates them as the left and right nodes for a new node,
    ///  and assigns the frequency of the new node as the sum of the frequencies of the two removed nodes.
    ///  This new node is then added back to the Min Heap. This procedure is repeated until the size of the Min Heap reaches 1.
    ///
    void createTree();

    ///
    /// This function traverses through the entire Huffman tree, assigning binary codes to each node.
    ///
    void createCodes();

    ///
    ///  This function stores the Huffman-encoded input file into the output file.
    ///  Save format : {minHeapSize}{minHeap}{Ecoded input file characters}{count0}
    ///
    ///  minHeap = ({character data} {huffman code for that character}) * minheapsize.
    ///  {huffman code for that character} = A sequence of 128 bits is divided into 16 decimal numbers. Each of these numbers represents an 8-bit binary number.
    ///
    ///  {Encoded input File characters} {count0} = The entire file is transformed into its Huffman-encoded form, represented as a binary code.
    ///  This binary string is then segmented into 8-bit decimal numbers.
    ///  If the remaining bits at the end are less than 8 bits, the necessary number of '0's (calculated as 8 - remainingBits) is appended at the end.
    ///  count0 denotes the count of '0's appended at the end.
    ///
    void saveEncodedFile();

    ///
    ///  This function reads the entire set of characters from the encoded input file, as well as the value of count0,
    ///  while skipping the initial {MinHeapSize * (1 + 16)} characters in the file.
    ///  The decimal values are then converted into their binary equivalents (Huffman codes),
    ///  and the resulting characters are appended to the output file by traversing the reconstructed Huffman tree.
    ///  The final count0 number of '0's are disregarded as they were additional bits added during the saving of the encoded file.
    ///
    void saveDecodedFile();

    ///
    ///  This function reads the Min Heap information stored at the beginning of the file and reconstructs the Huffman tree by appending one node at a time.
    ///  The first value, MinHeapSize, indicates the size of the Min Heap.
    ///  The subsequent {MinHeapSize * (1+16)} elements consist of character data and 16 decimal values representing 128 bits of binary Huffman code.
    ///  The function disregards the initial (127 - code.length()) '0's, as well as the leading '1' bit, and appends the node accordingly.
    ///
    void getTree();

private slots:
    /// Slot for the "Open File" button click event
    void on_OpenFile_clicked();

    /// Slot for the "Save File" button click event
    void on_SaveFile_clicked();
};


#endif // MAINWINDOW_H
