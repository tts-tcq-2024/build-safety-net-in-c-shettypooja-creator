#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <ctype.h>
#include <string.h>

// Create a lookup table for Soundex codes
char soundexTable[26] = {
    '0', '1', '2', '3', '0', '1', '2', '0', '0', '2', // A-J
    '2', '4', '5', '5', '0', '1', '2', '6', '2', '3', // K-T
    '0', '1', '0', '2', '0', '2'                      // U-Z
};

char getSoundexCode(char c) 
{
    if (isalpha(c)) 
    {
        return soundexTable[toupper(c) - 'A'];
    }
    return '0';
}

void append_to_soundex(char code,int *sIndex,char *soundex)
{
    soundex[*sIndex] = code;
    *sIndex += (code != '0' && code != soundex[*sIndex - 1]);
    
}

void processSoundex(const char *name,int len,int *sIndex,char *soundex)
{
    int i = 1;
    while (i < len && *sIndex < 4) 
    {
        char code = getSoundexCode(name[i]);
        append_to_soundex(code,sIndex,soundex);       
        i++;
    }
}

void generateSoundex(const char *name, char *soundex) 
{
    int len = strlen(name);
    soundex[0] = toupper(name[0]);
    int sIndex = 1;

    processSoundex(name,len,&sIndex,soundex);
    
    while (sIndex < 4) 
    {
        soundex[sIndex++] = '0';
    }

    soundex[4] = '\0';
}

#endif // SOUNDEX_
