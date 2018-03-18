//
//  SFRealPlayer.cpp
//  assignment4
//
//  Created by Amr Elfiky on 3/16/18.
//  Copyright © 2018 Amr Elfiky. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <SFGame.hpp>
#include <SFPlayer.hpp>
#include <sstream>

//overload priority queue comparator in order to optimize decisions
struct cmp {
    bool operator()(const std::pair<int, std::vector<std::string> > &a,
                        const std::pair<int, std::vector<std::string> > &b) {
        
        return a.first < b.first;
    }
};


class SFRealPlayer : public SFPlayer {
    //priority queue stores best decisions on top
    std::priority_queue<std::pair<int, std::vector<std::string> >,
        std::vector<std::pair<int, std::vector<std::string> > >, cmp> pq;
    
public:
    SFRealPlayer(PieceColor color) : SFPlayer(color) {};
    
    
    void takeTurn(SFGame &aGame) {
        if (neighborhood(aGame)) {
            return;
        }
    }
    //this function goes through the gameboard and gets all possible moves
    bool neighborhood(SFGame &aGame) {
        SFBoard board = aGame.getBoard();
        SFTile (&tiles)[SFBoard::kBoardHeight][SFBoard::kBoardWidth] = board.getTiles();
        
        //go throw every array index
        for (int row = 0; row <  SFBoard::kBoardHeight; ++row) {
            for (int col = 0; col < SFBoard::kBoardWidth; ++col) {
                //get the tile at that index
                SFTile &t = tiles[row][col];
                //if tile is not empty
                if (!t.isEmpty()) {
                    SFPiece &piece = t.getPiece();
                    //this is my piece because it's red
                    if (piece.getColor() == PieceColor::red) {
                        //get the list of possible moves
                        possibleMoves(tiles, row, col, piece.isKing());
                    }
                }
            }
        }
        //null check against pq
        if (pq.size() != 0) {
            //get the best decision
            std::vector<std::string> top = pq.top().second;
            pq.pop();
            //process the args from the string vector
            process(top, aGame);
            return true;
        }
        return false;
    }
    //this function converts the string args to an actual function call
    void process(std::vector<std::string> t, SFGame &game) {
        if (t.size() < 5)
            std::cerr << "PROCESS VEC LT 3\n";
        
        std::string move = t.at(0);
        std::string rowCurr = t.at(1);
        std::string colCurr = t.at(2);
        std::string rowDest = t.at(3);
        std::string colDest = t.at(4);
        // get current row and column
        std::stringstream ss1(rowCurr);
        int rowC = 0; ss1 >> rowC;
        std::stringstream ss2(colCurr);
        int colC = 0; ss2 >> colC;
        // get row and col of the destination
        std::stringstream ss3(rowDest);
        int rowD = 0; ss3 >> rowD;
        std::stringstream ss4(colDest);
        int colD = 0; ss4 >> colD;
        
        if (move.compare("move") == 0) {
            std::cout << "moving: " << rowC << "," << colC << " to " << rowD << "," << colD << "\n";
            
            game.move(this, SFLocation(rowC, colC), SFLocation(rowD, colD));
        } else if (move.compare("jump") == 0) {
            std::cout << "jumping: " << rowC << "," << colC << " to " << rowD << "," << colD << "\n";
            game.jump(this, SFLocation(rowC, colC), SFLocation(rowD, colD));
        } else {
            std::cerr << "NOT MOVE OR JUMP\n";
        }
    }
    // this function stores all the arguments of a function call inside of a string vector
    // for use later
    void createMove(std::string move, int rowCur, int colCur, int rowDest, int colDest) {
        std::vector<std::string> moveVec;
        moveVec.push_back(move);
        moveVec.push_back(std::to_string(rowCur));
        moveVec.push_back(std::to_string(colCur));
        moveVec.push_back(std::to_string(rowDest));
        moveVec.push_back(std::to_string(colDest));
        
        if (move.compare("move") == 0) {
            pq.push(std::pair<int, std::vector<std::string> >(1,moveVec));
        }
        if (move.compare("jump") == 0) {
            pq.push(std::pair<int, std::vector<std::string> >(2,moveVec));
        }
    }
    
    // this function gets all possible moves and then delegates to createMove
    void possibleMoves(SFTile (&tiles)[SFBoard::kBoardHeight][SFBoard::kBoardWidth],
                       int row, int col, bool king) {
        int rowAbove = row + 1; //index of the row above
        int colLeft = col - 1; //index of col to the left
        int colRight = col + 1; //index of col to the right
        
        
        if (checkIndex(rowAbove, colLeft)) {
            //SFTile &t = tiles[colLeft][rowAbove];
            SFTile &t = tiles[rowAbove][colLeft];
            if (t.isEmpty()) {
                //push single move to PQ
                createMove("move",row,col,rowAbove,colLeft);
            } else {
                if (t.getPiece().getColor() == PieceColor::black) {
                    //jump available, need to check if it is a valid jump
                    if (checkValidTile(tiles, rowAbove+1, colLeft-1)) {
                        //jump is available, so push jump to PQ
                        createMove("jump",row,col,rowAbove+1, colLeft-1);
                    }
                }
            }
            
        }
        if (checkIndex(rowAbove, colRight)) {
            //SFTile &k = tiles[colRight][rowAbove];
            SFTile &k = tiles[rowAbove][colRight];
            if (k.isEmpty()) {
                //push single move to PQ
                createMove("move",row,col,rowAbove, colRight);
            } else {
                if (k.getPiece().getColor() == PieceColor::black) {
                    //jump available, need to check if it is a valid jump
                    if (checkValidTile(tiles, rowAbove+1, colRight+1)) {
                        //jump is available, so push jump to PQ
                        createMove("jump",row,col, rowAbove+1, colRight+1);
                    }
                }
            }
            
        }
        //CASE: we can go up and down
        if (king) {
            int rowBelow = row - 1;
            if (checkIndex(rowBelow, colLeft)) {
                //SFTile &t = tiles[colLeft][rowBelow];
                SFTile &t = tiles[rowBelow][colLeft];
                if (t.isEmpty()) {
                    //push single move to PQ
                    createMove("move",row,col,rowBelow, colLeft);
                } else {
                    if (t.getPiece().getColor() == PieceColor::black) {
                        //jump available, need to check if it is a valid jump
                        if (checkValidTile(tiles, rowBelow-1, colLeft-1)) {
                            //jump is available, so push jump to PQ
                            createMove("jump",row,col,rowBelow-1, colLeft-1);
                        }
                    }
                }
                
            }
            if (checkIndex(rowBelow, colRight)) {
                //SFTile &t = tiles[colRight][rowBelow];
                SFTile &t = tiles[rowBelow][colRight];
                if (t.isEmpty()) {
                    //push single move to PQ
                    createMove("move",row,col,rowBelow, colRight);
                } else {
                    if (t.getPiece().getColor() == PieceColor::black) {
                        //jump available, need to check if it is a valid jump
                        if (checkValidTile(tiles, rowBelow-1, colRight+1)) {
                            //jump is available, so push jump to PQ
                            createMove("jump",row,col,rowBelow-1, colRight+1);
                        }
                    }
                }
            }
        }
        
    }
    
    //helper to check index of tile stays within bounds
    bool checkIndex(int row, int col) {
        if (row > 7 || row < 0 || col > 7 || col < 0) {
            return false;
        }
        return true;
    }
    
    // check if where we are going to move contains a valid tile within the game board
    bool checkValidTile(SFTile (&tiles)[SFBoard::kBoardHeight][SFBoard::kBoardWidth], int row, int col) {
        //indice check on the tile we want to check
        if (!checkIndex(row, col)) {
            return false;
        }
        //get the tile in the game board
        //SFTile &t = tiles[col][row];
        SFTile &t = tiles[row][col];
        //if tile is not empty then the board does not contain a valid piece
        if (!t.isEmpty()) {
            return false;
        }
        //can only move to black tiles
        if (t.tileColor == TileColor::white) {
            return false;
        }
        
        return true;
    }

   
};




