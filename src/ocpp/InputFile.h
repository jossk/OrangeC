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
#ifndef InputFile_h
#define InputFile_h

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <stdio.h>
#include "ppDefine.h"

class InputFile
{
    enum { LINE_WIDTH = 4096 };
public:
    InputFile(bool fullname, const std::string &Name) : 
        name(Name), lineno(0), errlineno(0), errname(GetErrorName(fullname, name)),
        inComment(false), commentLine(0), endedWithoutEOL(false), file(NULL) { }
    virtual ~InputFile() 
    { 
        if (file) 
            fclose(file); 
        CheckErrors(); 
    }
    virtual bool Open()
    {
        file = fopen(name.c_str(),"r");
        return file != NULL;
    }
    int GetLineNo() { return lineno; }
    int GetErrorLine() { return errlineno; }
    std::string GetErrorFile() { return errname; }
    void CheckErrors();
    virtual bool GetLine(std::string &line) ;
    void SetErrlineInfo(std::string &name, int line)
    {
        errname = name;
        lineno = line;
    }
protected:
    std::string GetErrorName(bool full, std::string &name);
    virtual int StripComment(char *line) { return strlen(line); }
    bool ReadLine(char *line);
protected:
    bool inComment;
    int commentLine;
    int lineno;
    int errlineno;
private:
    FILE *file;
    std::string name;
    std::string errname;
    bool endedWithoutEOL;
} ;
#endif