//
//  SFGame.hpp
//  checkers
//
//  Created by rick gessner on 2/27/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#ifndef SFGame_hpp
#define SFGame_hpp

#include "SFPlayer.hpp"
#include "SFBoard.hpp"
#include "SFPiece.hpp"

class SFGame {  
public:
  
  virtual ~SFGame() {}

  static SFGame* create();
  
  virtual SFGame& run(SFPlayer &yourPlayer, SFPlayer &opponentPlayer)=0;
  
  virtual SFBoard& getBoard()=0;

  virtual bool move(SFPlayer *aPlayer, SFLocation aPieceLocation, SFLocation aDest)=0;

  virtual bool jump(SFPlayer *aPlayer, SFLocation aPieceLocation, SFLocation aDest)=0;
  
  virtual bool jump(SFPlayer *aPlayer, SFLocation aPieceLocation, SFLocation aDest1, SFLocation aDest2)=0;
  
  virtual bool jump(SFPlayer *aPlayer, SFLocation aPieceLocation, SFLocation aDest1, SFLocation aDest2,
                    SFLocation aDest3)=0;
  
  virtual bool jump(SFPlayer *aPlayer, SFLocation aPieceLocation, SFLocation aDest1, SFLocation aDest2,
                    SFLocation aDest3, SFLocation aDest4)=0;
  
  
};

#endif /* SFGame_hpp */
