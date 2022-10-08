#pragma once

#include <iostream>

#include <opencv2/core.hpp>

#include <opencv2/imgcodecs.hpp>

#include <opencv2/highgui.hpp>
#include <cstring>


struct RNode {

    int data;
    
    RNode* next;
    RNode* prev;
    RNode operator=(RNode n) {
        data = n.data;
        next = n.next;
        prev = n.prev;
        return *this;
    }
};



class LinkedList {
public:
    RNode* head;
public:
    LinkedList() {
        head = NULL;
    }

    void insertAtEnd(int data) {
        RNode* newRNode = new RNode;

        newRNode->data = data;

        newRNode->next = NULL;

        RNode* temp = head;

        if (head == NULL) {
            newRNode->prev = NULL;
            head = newRNode;
            return;
        }

        while (temp->next != NULL) {
            temp = temp->next;
        }


        temp->next = newRNode;

        newRNode->prev = temp;
    }
    void insertAtBeginning(int data) {
        struct RNode* newRNode = new RNode;

        newRNode->data = data;

        newRNode->next = (head);

        newRNode->prev = NULL;

        if ((head) != NULL)
            head->prev = newRNode;


        head = newRNode;
    }

    void print() {
        RNode* ptr;
        ptr = head;
        if (head == NULL) {
            std::cout << "List is empty" << std::endl;

        }
        else {
            while (ptr != NULL) {
                if (ptr->data == -1) {
                    std::cout << ptr->data << std::endl;
                }
                else {
                    std::cout << ptr->data << " ";

                }
                ptr = ptr->next;
            }
        }
    }

 

 

    bool IsEmpty() {
        if (head == NULL) {
            return true;
        }
        return false;
    }

    

};


void computeRLC(cv::Mat img) {
    int rows = img.rows;
    int cols = img.cols;

    int** img_arr = new int* [rows];
    int start_index;
    int end_index;
    for (int i = 0; i < rows; i++) {
        img_arr[i] = new int[cols];
    }

    LinkedList rlc;
    bool white_found = false;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img_arr[i][j] = int(img.at<uint8_t>(i, j));
        }
    }
    int x;
    string d = "";
    for (int i = 0; i < rows; i++) {
        start_index = 0;
        end_index = 0;
        x = 0;
        while (x < img.cols) {
            if (!white_found) {
                if (img_arr[i][x] == 255) {
                    white_found = true;
                    start_index = x + 1;
                }
            }
            else if (white_found) {
                if (img_arr[i][x] != 255) {
                    white_found = false;
                    end_index = x;
                    rlc.insertAtEnd(start_index);
                    rlc.insertAtEnd(end_index);
                }
            }

            else if (!white_found && x == cols - 1) {
                white_found = true;
                start_index = x + 1;
                end_index = x + 1;
                rlc.insertAtEnd(start_index);
                rlc.insertAtEnd(end_index);
            }

            x++;


        }

        rlc.insertAtEnd(-1);


   




    }


    rlc.print();



    for (int i = 0; i < rows; i++) {
        delete[] img_arr[i];
    }

    delete[] img_arr;


}