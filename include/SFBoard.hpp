//
//  SFBoard.hpp
//  checkers
//
//  Created by rick gessner on 2/27/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#ifndef SFBoard_hpp
#define SFBoard_hpp

#include "SFPiece.hpp"

enum class TileColor {white, black};

struct SFTile {
  int size;
  TileColor  tileColor;
  SFPiece* pieceOnTile;
  SFPiece& getPiece() {
    return *pieceOnTile;
  }
  bool isEmpty() {
    return pieceOnTile == nullptr;
  }
  SFTile(TileColor aTileColor)
    : tileColor(aTileColor) {
  }
};

class SFGame;
class SFBoard {
public:

  static const int kBoardWidth = 8;
  static const int kBoardHeight= 8;
  
  SFBoard();
  
  SFTile (&getTiles())[SFBoard::kBoardHeight][SFBoard::kBoardWidth] {return tiles;}

  friend class SFGame;

protected:
  SFTile tiles[SFBoard::kBoardHeight][SFBoard::kBoardWidth];
  
};

#endif /* SFBoard_hpp */

