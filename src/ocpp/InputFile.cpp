/*
    Software License Agreement (BSD License)
    
    Copyright (c) 1997-2011, David Lindauer, (LADSoft).
    All rights reserved.
    
    Redistribution and use of this software in source and binary forms, 
    with or without modification, are permitted provided that the following 
    conditions are met:
    
    * Redistributions of source code must retain the above
      copyright notice, this list of conditions and the
      following disclaimer.
    
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the
      following disclaimer in the documentation and/or other
      materials provided with the distribution.
    
    * Neither the name of LADSoft nor the names of its
      contributors may be used to endorse or promote products
      derived from this software without specific prior
      written permission of LADSoft.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER 
    OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
    OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
    OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
    ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    contact information:
        email: TouchStone222@runbox.com <David Lindauer>
*/
#include "InputFile.h"
#include "Errors.h"

void InputFile::CheckErrors()
{
    if (inComment)
        Errors::Warning("Non-terminated comment started in line " + Errors::ToNum(commentLine));
    if (endedWithoutEOL)
        Errors::TrivialWarning("File not terminated with End Of Line character");
}
bool InputFile::GetLine(std::string &line)
{
    char buf[LINE_WIDTH];
    while (inComment)
    {
        int m = ReadLine(buf);
        if (!m)
            return false;
        m = StripComment(buf);
        if (m)
        {
            buf[m] = 0;
            break;
        }
    }
    line = std::string(buf);
    return true;
}
std::string InputFile::GetErrorName(bool full, std::string &name)
{
    if (full)
    {
        return name;
    }
    else
    {
        const char *p = name.c_str();
        const char *q = strrchr(p, '\\');
        if (!q)
        {
            q = strrchr(p, ':');
            if (q)
                q++;
            else
                q = p;	
        }
        else
        {
            q++;
        }
        return std::string(q);
    }
}
bool InputFile::ReadLine(char *line)
{
    line[0] = 0;
    lineno ++;
    fgets(line, LINE_WIDTH, file);
    int n = strlen(line);
    if (n)
    {
        if (line[n-1] != '\n')
            endedWithoutEOL = true;
        else
            line[n-1] = 0;
        return true;
    }
    return false;
}