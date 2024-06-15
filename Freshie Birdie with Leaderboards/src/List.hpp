#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>

using namespace std;

class node{
public:
    string name;
    int score;
    node *next;
    node();
    node(string, int);
};

class list {
public:
    list();
    ~list();
    // void displayLeaderboard();
    void insert(string, int);
    void remove();
    void read();
    void write();
    // sf::RenderWindow window;
    // sf::Text leaderboardText;
    node* operator[](int);
    int size;
    node *head, *tail;
    // void insertHelper(node* node, string, int);
    // void displayInOrder(node* node, sf::RenderWindow& window, sf::Text&, float, int);
    // void remove(node* node);
    // sf::Font font;
};

// #include "BST.cpp"