#include "morseEncoder.h"
#include <pico/stdlib.h>

void morseEncoder::sendMsg(const char *msg, const uint16_t len)
{
    if( !enabled)
        return;

    for(int i=0; i < len; i++)
    {
        if( msg[i] == ' ')
        {
            sleep_ms(word_sp_delay);
        }
        else
        {
            uint8_t ptrn = char2pattern(msg[i]);
            sendPattern(ptrn);
        }
    }
}

uint8_t morseEncoder::char2pattern(const char character)
{
    char letter = character | 0x20;                 // Convert letters to lower case
    uint8_t index;
    if (letter >= 'a' && letter <= 'z') index = letter - 'a';
    else if (letter >= '0' && letter <= '9') index = letter - '0' + 26;
    else if (letter >= '+' && letter <= '/') index = letter - '+' + 36;
    else if (letter == '?') index = 41;
    else if (letter >= '&' && letter <= ')') index = letter - '&' + 42;
    else if (letter >= '!' && letter <= '"') index = letter - '!' + 46;
    else index = 0x80;

    return Chars[index];
}

void morseEncoder::sendPattern(uint8_t pattern)
{
    while( pattern != 0x80)
    {
        tx_cb(true);
        if( pattern & 0x80)
            sleep_ms(dash_delay);
        else
            sleep_ms(dot_delay);
        tx_cb(false);
        sleep_ms(dot_delay);
        pattern <<= 1;
    }
    sleep_ms(dash_delay - dot_delay);
}

