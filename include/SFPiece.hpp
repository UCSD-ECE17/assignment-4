//
//  SFPiece.hpp
//  checkers
//
//  Created by rick gessner on 2/27/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#ifndef SFPiece_hpp
#define SFPiece_hpp

enum class PieceColor {black, red};

struct SFLocation {
  int       row;
  int      col;
  SFLocation(int aRow, int aCol) : row(aRow), col(aCol){}
};

class SFRealGame;

class SFPiece {
  bool king;
  PieceColor color;
public:
  bool onBoard;
  SFPiece(PieceColor color);
  bool isKing();
  PieceColor getColor();
  friend class SFRealGame;
};

#endif /* SFPiece_hpp */
