/* Copyright (c) 2015 Simon Toth kontakt@simontoth.cz
* Lincensed under the MIT license: http://opensource.org/licenses/MIT
*/

#ifndef FASTLINEREADER_H
#define FASTLINEREADER_H

// STD C++
#include <iosfwd>

/** Quick line-by-line parser of text files for POSIX/Linux
*
*  This function provides a fast line parser with a callback model.
*
* @param filename file to be parsed
* @param callback function that will be called for each line
* @returns 0 on success, -1 if file could not be opened
**/
int fastLineParser(const char * const filename, void(*callback)(const char * const, const char * const));

#endif // FASTLINEREADER_H