#include "List.hpp"

node::node(){
    next = NULL;
    score = 0;
    name = "Player";
}

node::node(string playerName, int playerScore){    
    next = NULL;
    score = playerScore;
    name = playerName;
}

list::list(){
    head = tail = NULL;
    size = 0;
}


list::~list() {
    while(size)
        remove();
}

void list::remove() {
    node* del = head;
    if (del!=NULL) {
        head=head->next;
        del->next = NULL;
        delete del;
    }
}

void list::insert(string playerName, int playerScore) {
    node *n = new node(playerName, playerScore);
    node *tmp=head;
    if(tmp == NULL){
        head = tail = n;
    }
    else if(tmp == head && tmp == tail){
        if(n->score<tmp->score){
            head->next=n;
            tail=n;
        }
        else{
            n->next=head;
            head=n;
        }
    }
    else{
        node *prev=NULL;
        while(tmp != NULL && n->score<tmp->score){
            prev=tmp;
            tmp=tmp->next;
        }
        if(prev == NULL){
            head=n;
            n->next=tmp;
        }
        else if(tmp == NULL){
            prev->next=n;
            tail=n;
        }
        else{
            n->next=prev->next;
            prev->next=n;
        }
    }
    size++;
}
void list::read(){
    ifstream file("Leaderboards.txt");
    if(file.is_open()){
        for(int i=0;i<5;i++){
            string tname;
            int tscore;
            if(file>>tname>>tscore){
               insert(tname, tscore);
            }
        }
        file.close();
    }
}

void list::write(){
    ofstream file("Leaderboards.txt");
    node *tmp = head;
    for(int count = 0; tmp != NULL && count<5; count++){
        file << tmp->name << " " << tmp->score <<endl;
        tmp = tmp->next;
    } 
    file.close();
}

// void list::display() {
//     node *tmp = this->head;
//     for (int i = 0; i < 5; i++) {
//         if (tmp != NULL) {
            
//         }
//         tmp = tmp->next;
//     }
// }

// void list::display(sf::RenderWindow& window) {
//     node* tmp = this->head;

//     // Define the starting Y position for the first entry
//     float yPos = 200.f;

//     for (int i = 0; i < 5; i++) {
//         sf::Text text;
//         text.setFont(font);
//         text.setCharacterSize(24);
//         text.setFillColor(sf::Color::White);
//         text.setOutlineThickness(2.f);
//         text.setOutlineColor(sf::Color::Black);

//         if (tmp != NULL) {
//             text.setString(tmp->name + " - Score: " + to_string(tmp->score));
//             text.setPosition(10.f, yPos);
//             window.draw(text);

//             // Increase Y position for the next entry
//             yPos += 30.f;
//         }
//         tmp = tmp->next;
//     }
// }

node* list::operator[](int index){
    node *tmp = head;
    for(int i = 0; i < index; i++)
        tmp = tmp->next;
    return tmp;
}
//
// void BST::insertHelper(node* n, string playerName, int playerScore) {
//     if (n==NULL) 
//         n = new node(playerName, playerScore);
//     else {
//         if (playerScore > n->score)
//             insertHelper(n->left, playerName, playerScore);
//         else 
//             insertHelper(n->right, playerName, playerScore);
//     }
// }

// void BST::displayLeaderboard() {
//     font.loadFromFile("assets/FlappyFont.ttf");
//     //leaderboardText.setString("Player 0");
//     leaderboardText.setFont(font); // assuming font is available in the Game class
//     leaderboardText.setCharacterSize(24);
//     leaderboardText.setFillColor(sf::Color::White);
//     leaderboardText.setOutlineThickness(2.f);
//     leaderboardText.setOutlineColor(sf::Color::Black);

//     float yPos = 1.f; // Starting Y position
//     int displayCount = 0;
//     displayInOrder(root, window, leaderboardText, yPos, displayCount);
// }

// void BST::displayInOrder(node* n, sf::RenderWindow& window, sf::Text& leaderboardText, float yPos, int displayCount) {
//     cout<<"display inorder"<<endl;
//     if (n != NULL && displayCount < 5) {
//         displayInOrder(n->right, window, leaderboardText, yPos, displayCount);
//         leaderboardText.setString(n->name + " - Score: " + to_string(n->score));
//         leaderboardText.setPosition(10.f, yPos);
//         cout<<"display inorder if"<<endl;
//         //cout<<n->name + " - Score: " + to_string(n->score);
//         window.draw(leaderboardText);
//         yPos += 3.f; // Adjust the vertical spacing as needed
//         displayCount++;
//         displayInOrder(n->left, window, leaderboardText, yPos, displayCount);
//     }
// }

// // template class BST<Player>;