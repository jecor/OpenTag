//----------------------------------------------------------------------------------------
// tagconvert: convert TAG (Transport de l'Agglomération Grenobloise) bus/tram
// hours to C code ready to be integrated in Arduino
// Copyright (c) 2013 Jérôme Cornet <jerome@aldorande.net>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//----------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
   if (argc < 3)
   {
      std::cerr << "usage: " << argv[0] << " inputtextfile outputcppfile" << std::endl;
      return 1;
   }
   
   std::ifstream inputFile(argv[1]);
   if (!inputFile)
   {
      std::cerr << "Unable to open input file " << argv[1] << std::endl;
      return 2;
   }
   std::ofstream outputFile(argv[2]);
   if (!outputFile)
   {
      std::cerr << "Unable to open input file " << argv[2] << std::endl;
      return 2;
   }
   
   outputFile << "const prog_uint16_t tramA[] PROGMEM = \n{ " << std::endl;
   outputFile << "   ";
   
   std::string line;
   unsigned long lineCount = 0;
   unsigned int value;
   unsigned int indent = 0;
   
   while (std::getline(inputFile, line))
   {
      if ((lineCount % 3) == 0)
      {
         indent++;
         if (line[1] == ':')
         {
            value = (line[0]-48)*60 + (line[2]-48)*10 + (line[3]-48);
            outputFile << value << ", ";
         }
         else if (line[2] == ':')
         {
            value = (line[0]-48)*60*10 + (line[1]-48)*60 + (line[3]-48)*10 + (line[4]-48);
            outputFile << value << ", ";
         }
         else
         {
            std::cerr << "Unable to parse line: " << std::endl;
            std::cerr << line << std::endl;
            return 3;
         }
      }
      lineCount++;
      if (indent == 4)
      {
         indent = 0;
         outputFile << std::endl << "   ";
      }
   }
   
   outputFile << "\n};" << std::endl;
   
   return 0;
}