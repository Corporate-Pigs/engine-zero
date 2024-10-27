#pragma once

#include <string>
#include <unordered_map>

namespace Engine {

enum InputKey {
    K_UNKNOWN = 0,

    K_RETURN = '\r',
    K_ESCAPE = '\x1B',
    K_BACKSPACE = '\b',
    K_TAB = '\t',
    K_SPACE = ' ',
    K_EXCLAIM = '!',
    K_QUOTEDBL = '"',
    K_HASH = '#',
    K_PERCENT = '%',
    K_DOLLAR = '$',
    K_AMPERSAND = '&',
    K_QUOTE = '\'',
    K_LEFTPAREN = '(',
    K_RIGHTPAREN = ')',
    K_ASTERISK = '*',
    K_PLUS = '+',
    K_COMMA = ',',
    K_MINUS = '-',
    K_PERIOD = '.',
    K_SLASH = '/',
    K_0 = '0',
    K_1 = '1',
    K_2 = '2',
    K_3 = '3',
    K_4 = '4',
    K_5 = '5',
    K_6 = '6',
    K_7 = '7',
    K_8 = '8',
    K_9 = '9',
    K_COLON = ':',
    K_SEMICOLON = ';',
    K_LESS = '<',
    K_EQUALS = '=',
    K_GREATER = '>',
    K_QUESTION = '?',
    K_AT = '@',

    /*
       Skip uppercase letters
     */

    K_LEFTBRACKET = '[',
    K_BACKSLASH = '\\',
    K_RIGHTBRACKET = ']',
    K_CARET = '^',
    K_UNDERSCORE = '_',
    K_BACKQUOTE = '`',
    K_a = 'a',
    K_b = 'b',
    K_c = 'c',
    K_d = 'd',
    K_e = 'e',
    K_f = 'f',
    K_g = 'g',
    K_h = 'h',
    K_i = 'i',
    K_j = 'j',
    K_k = 'k',
    K_l = 'l',
    K_m = 'm',
    K_n = 'n',
    K_o = 'o',
    K_p = 'p',
    K_q = 'q',
    K_r = 'r',
    K_s = 's',
    K_t = 't',
    K_u = 'u',
    K_v = 'v',
    K_w = 'w',
    K_x = 'x',
    K_y = 'y',
    K_z = 'z',
};

class InputManager {
   public:
    virtual void setActionMapping(const std::unordered_map<std::string, InputKey>& keyBinds) = 0;
    
    virtual void setActionMapping(const std::string& action, const InputKey& key) = 0;

    virtual bool removeFromActionMapping(const std::string& action) = 0;
  
    virtual bool isPerformingAction(const std::string& action) const = 0;
};
}  // namespace Engine