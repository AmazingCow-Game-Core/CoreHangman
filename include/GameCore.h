//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███                                                  //
//            █ █        █ █        GameCore.h                                //
//             ████████████         CoreHangman                               //
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

#ifndef __CoreHangman_include_GameCore_h__
#define __CoreHangman_include_GameCore_h__

//std
#include <string>
//CoreHangman
#include "CoreHangman_Utils.h"
#include "Status.h"

NS_COREHANGMAN_BEGIN

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
    ///@brief Set the game word - All other operations will 
    ///be done against this word. This method must be called
    ///at the begin of each game.
    ///@param word A string with the word that will be played.
    ///@param reset If true the previous moves count will be 
    ///reseted, otherwise all moves will be kept.
    ///@see GameCore::getMovesCount, GameCore::getMaxMovesCount,
    ///GameCore::checkLetter.
    void setWord(const std::string &word, bool reset = true);


    ///@brief Try a letter against the current word set at
    ///GameCore::setWord method. If the letter is already 
    ///used it will return a empty vector and nothing will be 
    ///done. If a letter is not used, the letter will be checked
    ///against the word and all indexes that it appears will be 
    ///returned. 
    ///The moves count will be incremented only if the letter
    ///is not used and doesn't appears into the word.
    ///@param letter The letter that will be tested.
    ///@returns A empty vector if a letter is already used 
    ///or if it was not found in the word, otherwise returns
    ///a vector with indexes that match the tried letter.
    ///@see GameCore::setWord, GameCore::getUsedLetter.
    std::vector<int> checkLetter(char letter);

    ///@brief Gets all already tried letters.
    ///@returns All used letters.
    ///@see GameCore::checkLetter, GameCore::canUseLetter.
    const std::vector<char>& getUsedLetters() const;

    ///@brief Check if a given letter can be used or not. 
    ///@param letter Any valid char.
    ///@returns True if letter can be used i.e. will do anything 
    ///into the game or false if it is already used.
    ///@see GameCore::checkLetter, GameCore::getUsedLetters.
    bool canUseLetter(char letter) const;


    ///@brief Gets a the word in plain text.
    ///@returns A plain word string.
    ///@see GameCore::getClosedWord.
    const std::string& getOpenWord() const;

    ///@brief Gets the word with the indexes
    ///that was not opened it replaced with the '*' char.
    ///@returns A string with all not opened indexes
    ///replaced with '*' char.
    ///@see GameCore::getClosedWord.
    std::string getClosedWord() const;


    ///@brief Gets the letter at the index.
    ///@param index The index of the desired letter.
    ///@warning index MUST BE VALID. 
    ///@returns The letter.
    const char getLetterAt(int index) const;

    ///@brief Gets all indexes that are spaces in the word. 
    ///@returns The indexes.
    ///@see GameCore::getOpenIndexes.
    const std::vector<int>& getSpaceIndexes() const;

    ///@brief Gets all indexes that are open in the word,
    ///i.e. player already match the letters.
    ///@returns The indexes.
    ///@see GameCore::getSpaceIndexes.
    const std::vector<int>& getOpenIndexes() const;

    ///@brief Reset the moves count.
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

NS_COREHANGMAN_END
#endif // defined(__CoreHangman_include_GameCore_h__) //
