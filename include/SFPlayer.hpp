//
//  SFPlayer.hpp
//  checkers
//
//  Created by rick gessner on 2/27/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#ifndef SFPlayer_hpp
#define SFPlayer_hpp
#include "SFPiece.hpp"

class SFGame; //forward declare...

class SFPlayer {
PieceColor color;
public:
  SFPlayer(PieceColor aColor);
  virtual void takeTurn(SFGame &aGame)=0;
  PieceColor getColor();
};

#endif /* SFPlayer_hpp */
