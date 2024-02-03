#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include<ios>

using namespace std;



void MainWindow::createArr()
{
    for (int i = 0; i < 128; i++)
    {
        arr.push_back(new Node());
        arr[i]->data = i;
        arr[i]->freq = 0;
    }
}

void MainWindow::compress()
{
    createMinHeap();
    createTree();
    createCodes();
    saveEncodedFile();
}


void MainWindow::decompress()
{
    getTree();
    saveDecodedFile();
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_OpenFile_clicked()
{
    // Check if the "Compress File" option is selected
    if(ui->CompressFile->isChecked())
    {
        // Open a file dialog to select a text file for compression
        QString filename = QFileDialog::getOpenFileName(
            this,
            tr("Open Text File"),
            "/home",
            "Text File (*.txt)"
            );
        inFileName = filename.toLatin1().data();

        // Display the selected file path in the UI
        ui->textEdit->setText(QString(filename));

        // Initialize the array of nodes
        createArr();

        // Start the compression process
        compress();
    }

    // Check if the "Decompress File" option is selected
    if(ui->DecompressFile->isChecked())
    {
        // Open a file dialog to select a Huffman file for decompression
        QString filename = QFileDialog::getOpenFileName(
            this,
            tr("Open Huffman File"),
            "/home",
            "Huffman (*.huff)"
            );
        inFileName = filename.toLatin1().data();

        // Display the selected file path in the UI
        ui->textEdit->setText(QString(filename));

        // Initialize the array of nodes
        createArr();

        // Start the decompression process
        decompress();
    }
}


void MainWindow::on_SaveFile_clicked()
{
    // Check if the "Compress File" option is selected
    if(ui->CompressFile->isChecked())
    {
        // Open a file dialog to save the Huffman encoded file
        QString filename = QFileDialog::getSaveFileName(
            this,
            tr("Save Huffman Encoded File"),
            "/home",
            tr("Huffman (*.huff)")
            );
        outFileName = filename.toLatin1().data();

        // Open the output file in binary mode and write the encoded data
        outFile.open(outFileName, ios::out | ios::binary);
        outFile.write(in.c_str(), in.size());
        outFile.close();

        // Display the saved file path in the UI
        ui->textEdit_2->setText(QString(filename));
    }

    // Check if the "Decompress File" option is selected
    if(ui->DecompressFile->isChecked())
    {
        // Open a file dialog to save the decompressed text file
        QString filename = QFileDialog::getSaveFileName(
            this,
            tr("Save Text File"),
            "/home",
            tr("Text File (*.txt)")
            );
        outFileName = filename.toLatin1().data();

        // Open the output file and write the decoded data
        outFile.open(outFileName, ios::out);
        outFile.write(out.c_str(), out.size());
        outFile.close();

        // Display the saved file path in the UI
        ui->textEdit_2->setText(QString(filename));
    }
}


