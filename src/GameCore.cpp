//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        GameCore.cpp                              //
//            █ █        █ █        CoreHangman                               //
//             ████████████                                                   //
//           █              █       Copyright (c) 2015, 2016                  //
//          █     █    █     █      AmazingCow - www.AmazingCow.com           //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
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
//        The email is: acknowledgment_opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must not be misrepresented as being the original software.      //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

//Header
#include "../include/GameCore.h"

//std
#include <sstream>
#include <algorithm>
#include <iterator>

//Usings.
USING_NS_COREHANGMAN;

// Constants //
const int GameCore::kUnlimitedMoves = -1;


// CTOR/DTOR //
GameCore::GameCore(int maxMoves /* = kUnlimitedMoves */) :
    m_status  (Status::Continue),
    m_moves   (0),
    m_maxMoves(maxMoves)
{
    //Empty...
}


// Public Methods //
void GameCore::setWord(const std::string &word, bool reset /* = true */)
{
    //Set the word and indexes.
    m_word = word;

    m_spaceIndexes.clear();
    m_openIndexes.clear();

    //Find the space chars.
    for(int i = 0; i < m_word.size(); ++i)
    {
        if(m_word[i] == ' ')
        {
            m_spaceIndexes.push_back(i);
            m_openIndexes.push_back(i);
        }
    }

    //Reset the used letters.
    m_usedLetters.clear();

    //Reset the moves.
    if(reset)
        resetMoves();
}


std::vector<int> GameCore::checkLetter(char letter)
{
    //Game is already over.
    if(m_status != Status::Continue)
        return std::vector<int>();

    //Letter is already used.
    if(!canUseLetter(letter))
        return std::vector<int>();

    //Get the current count of opened index, it
    //will be used to check if player hits a letter.
    auto sizeBefore = m_openIndexes.size();

    //Add all indexes that match the letter.
    for(int i = 0; i < m_word.size(); ++i)
    {
        if(std::toupper(m_word[i]) == std::toupper(letter))
            m_openIndexes.push_back(i);
    }

    //Size is equal, means that player doesn't hit the letter.
    if(sizeBefore == m_openIndexes.size())
        ++m_moves;

    //Add the letter to used list.
    m_usedLetters.push_back(std::toupper(letter));


    //Make the the vectors organized.
    std::sort(std::begin(m_openIndexes), std::end(m_openIndexes));
    std::sort(std::begin(m_usedLetters), std::end(m_usedLetters));

    //Check status.
    //Player open all letters. - Victory.
    if(m_openIndexes.size() == m_word.size())
    {
        m_status = Status::Victory;
    }
    //Max moves is enforced and player reach it - Defeat.
    else if(m_maxMoves != GameCore::kUnlimitedMoves &&
            m_moves > m_maxMoves)
    {
        m_status = Status::Defeat;
    }

    return m_openIndexes;
}

const std::vector<char>& GameCore::getUsedLetters() const
{
    return m_usedLetters;
}

bool GameCore::canUseLetter(char letter) const
{
    //If the iterator isn't at end means that letter is already used.
    return (std::find(std::begin(m_usedLetters),
                      std::end  (m_usedLetters),
                      letter) == std::end(m_usedLetters));
}


const std::string& GameCore::getOpenWord() const
{
    return m_word;
}
std::string GameCore::getClosedWord() const
{
    std::stringstream ss;

    for(int i = 0; i < m_word.size(); ++i)
    {
        auto it = std::find(std::begin(m_openIndexes),
                            std::end  (m_openIndexes),
                            i);

        //We have this index - Letter is open.
        if(it != std::end(m_openIndexes))
            ss << m_word[i];
        //We don't have this index - Letter is closed.
        else
            ss << "*";
    }

    return ss.str();
}


const char GameCore::getLetterAt(int index) const
{
    return m_word[index];
}
const std::vector<int>& GameCore::getSpaceIndexes() const
{
    return m_spaceIndexes;
}


void GameCore::resetMoves()
{
    m_moves = 0;
}


Status GameCore::getStatus() const
{
    return m_status;
}


int GameCore::getMovesCount() const
{
    return m_moves;
}
int GameCore::getMaxMovesCount() const
{
    return m_maxMoves;
}
