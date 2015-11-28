//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███                                                  //
//            █ █        █ █        GameCore.h                                //
//             ████████████         Hangman Core                              //
//           █              █       Copyright (c) 2015 AmazingCow             //
//          █     █    █     █      www.AmazingCow.com                        //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
//                                                                            //
//                                                                            //
//                  This software is licensed as GPLv3                        //
//                 CHECK THE COPYING FILE TO MORE DETAILS                     //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     0. You **CANNOT** change the type of the license.                      //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.AmazingCow.com/acknowledgment.html for details).    //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgmentopensource@AmazingCow.com               //
//     3. Altered source versions must be plainly marked as such,             //
//        and must notbe misrepresented as being the original software.       //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

#ifndef __HangmanCore_include_GameCore_h__
#define __HangmanCore_include_GameCore_h__

//std
#include <string>
//HangmanCore.
#include "HangmanCore_Utils.h"
#include "Status.h"

NS_HANGMANCORE_BEGIN

class GameCore
{
    // Constants / Typedef / Enums //
public:
    ///@brief A meta value meaning that player can play indefinitely.
    ///@see GameCore::GameCore
    static const int kUnlimitedMoves;

    // CTOR/DTOR //
public:
    ///@brief Constructs the GameCore.
    ///@param maxMoves How many tries player has to win the game -
    ///Default GameCore::kUnlimitedMoves
    ///@see GameCore::kUnlimitedMoves
    GameCore(int maxMoves = kUnlimitedMoves);


    // Public Methods //
public:
    ///@brief
    ///@param
    ///@param
    ///@see
    void setWord(const std::string &word, bool reset = true);


    ///@brief    
    ///@param
    ///@returns
    ///@see
    std::vector<int> checkLetter(char letter);

    ///@brief    
    ///@returns
    ///@see
    const std::vector<char>& getUsedLetters() const;

    ///@brief    
    ///@param
    ///@returns
    ///@see
    bool canUseLetter(char letter) const;


    ///@brief    
    ///@returns
    ///@see
    const std::string& getOpenWord() const;

    ///@brief    
    ///@returns
    ///@see
    std::string getClosedWord() const;


    ///@brief    
    ///@param
    ///@returns
    ///@see    
    const char getLetterAt(int index) const;

    ///@brief    
    ///@returns
    ///@see
    const std::vector<int>& getSpaceIndexes() const;

    ///@brief    
    ///@returns
    ///@see
    const std::vector<int>& getOpenIndexes() const;

    ///@brief    
    ///@see
    void resetMoves();


    ///@brief Get the current status of game.
    ///@returns the current status of game.
    ///@see Status, GameCore::getMovesCount,
    ///GameCore::getMaxMovesCount, GameCore::kUnlimitedMoves.
    Status getStatus() const;


    ///@brief Get how many moves the player did so far.
    ///@returns The number of player's moves.
    ///@see Status, GameCore::getMaxMovesCount,
    ///GameCore::kUnlimitedMoves.
    int getMovesCount() const;

    ///@brief Get how many moves the player can do.
    ///@returns The number of moves or GameCore::kUnlimitedMoves
    ///if there is no restriction..
    ///@see Status, GameCore::getMovesCount,
    ///GameCore::kUnlimitedMoves
    int getMaxMovesCount() const;

    // iVars //
private:
    std::string       m_word;
    std::vector<int>  m_spaceIndexes;
    std::vector<int>  m_openIndexes;
    std::vector<char> m_usedLetters;

    Status m_status;
    
    int m_moves;
    int m_maxMoves;
};

NS_HANGMANCORE_END
#endif // defined(__HangmanCore_include_GameCore_h__) //
