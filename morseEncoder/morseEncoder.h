#include <functional>
#include <cstdint>

class morseEncoder
{
public:
    morseEncoder(std::function<void(bool)> _tx_cb, const uint8_t _wpm=5):
    tx_cb(_tx_cb),
    enabled(false)
    {
        if(_wpm != 0)
            setWpm(_wpm);
        else
            setWpm(5);
    }

    void setWpm(const uint8_t _wpm)
    {
        wpm = _wpm;
        if(_wpm == 0)
            wpm = 5;
        dot_delay = 60000L/ (uint16_t)wpm;
        dot_delay /= 50;
        dash_delay = dot_delay * 3;
        word_sp_delay = dot_delay * 7;
    }

    void enable()
    {
        enabled = true;
    }
    void disable()
    {
        enabled = false;
    }

    void sendMsg(const char *msg, const  uint16_t len);

private:
    uint8_t wpm;
    uint16_t dot_delay;
    uint16_t dash_delay;
    uint16_t word_sp_delay;
    bool enabled;
    std::function<void(bool)> tx_cb;

    uint8_t char2pattern(const char character);
    void sendPattern(uint8_t pattern);

    uint8_t Chars[48] = {
        //A           B           C           D           E           F
          0b01100000, 0b10001000, 0b10101000, 0b10010000, 0b01000000, 0b00101000,
        //G           H           I           J           K           L
          0b11010000, 0b00001000, 0b00100000, 0b01111000, 0b10110000, 0b01001000,
        //M           N           O           P           Q           R
          0b11100000, 0b10100000, 0b11110000, 0b01101000, 0b11011000, 0b01010000,
        //S           T           U           V           W           X
          0b00010000, 0b11000000, 0b00110000, 0b00011000, 0b01110000, 0b10011000,
        //Y           Z           0           1           2           3
          0b10111000, 0b11001000, 0b11111100, 0b01111100, 0b00111100, 0b00011100,
        //4           5           6           7           8           9
          0b00001100, 0b00000100, 0b10000100, 0b11000100, 0b11100100, 0b11110100,
        //+           ,           -           .           /           ?
          0b01010110, 0b11001110, 0b10000110, 0b01010110, 0b10010100, 0b00110010,
        //&           '           (           )           !           "            
          0b10101110, 0b01000100, 0b10110100, 0b10110110, 0b10101110, 0b01001010,
        };

};
