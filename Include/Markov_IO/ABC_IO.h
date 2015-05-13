#ifndef ABC_IO_H
#define ABC_IO_H
#include <string>
#include <sstream>
#include <map>
#include <vector>

namespace Markov_IO
{

  enum Key {
    Key_Escape = 0x01000000,                // misc keys
    Key_Tab = 0x01000001,
    //        Key_Backtab = 0x01000002,
    Key_Backspace = 0x01000003,
    Key_Return = 0x01000004,
    Key_Enter = 0x01000005,                       //located in keypad
    //        Key_Insert = 0x01000006,
    //        Key_Delete = 0x01000007,
    //        Key_Pause = 0x01000008,
    //        Key_Print = 0x01000009,
    //        Key_SysReq = 0x0100000a,
    //        Key_Clear = 0x0100000b,
    Key_Home = 0x01000010,                // cursor movement
    Key_End = 0x01000011,
    Key_Left = 0x01000012,
    Key_Up = 0x01000013,
    Key_Right = 0x01000014,
    Key_Down = 0x01000015,
    Key_PageUp = 0x01000016,
    Key_PageDown = 0x01000017,
    //        Key_Shift = 0x01000020,                // modifiers
    //        Key_Control = 0x01000021,
    //        Key_Meta = 0x01000022,
    //        Key_Alt = 0x01000023,
    //        Key_CapsLock = 0x01000024,
    //        Key_NumLock = 0x01000025,
    //        Key_ScrollLock = 0x01000026,
    //        Key_F1 = 0x01000030,                // function keys
    //        Key_F2 = 0x01000031,
    //        Key_F3 = 0x01000032,
    //        Key_F4 = 0x01000033,
    //        Key_F5 = 0x01000034,
    //        Key_F6 = 0x01000035,
    //        Key_F7 = 0x01000036,
    //        Key_F8 = 0x01000037,
    //        Key_F9 = 0x01000038,
    //        Key_F10 = 0x01000039,
    //        Key_F11 = 0x0100003a,
    //        Key_F12 = 0x0100003b,
    //        Key_F13 = 0x0100003c,
    //        Key_F14 = 0x0100003d,
    //        Key_F15 = 0x0100003e,
    //        Key_F16 = 0x0100003f,
    //        Key_F17 = 0x01000040,
    //        Key_F18 = 0x01000041,
    //        Key_F19 = 0x01000042,
    //        Key_F20 = 0x01000043,
    //        Key_F21 = 0x01000044,
    //        Key_F22 = 0x01000045,
    //        Key_F23 = 0x01000046,
    //        Key_F24 = 0x01000047,
    //        Key_F25 = 0x01000048,                // F25 .. F35 only on X11
    //        Key_F26 = 0x01000049,
    //        Key_F27 = 0x0100004a,
    //        Key_F28 = 0x0100004b,
    //        Key_F29 = 0x0100004c,
    //        Key_F30 = 0x0100004d,
    //        Key_F31 = 0x0100004e,
    //        Key_F32 = 0x0100004f,
    //        Key_F33 = 0x01000050,
    //        Key_F34 = 0x01000051,
    //        Key_F35 = 0x01000052,
    //        Key_Super_L = 0x01000053,                 // extra keys
    //        Key_Super_R = 0x01000054,
    //        Key_Menu = 0x01000055,
    //        Key_Hyper_L = 0x01000056,
    //        Key_Hyper_R = 0x01000057,
    //        Key_Help = 0x01000058,
    //        Key_Direction_L = 0x01000059,
    //        Key_Direction_R = 0x01000060,
    Key_Unknown= 0x00,
    Key_Space = 0x20,                // 7 bit printable ASCII
    Key_Exclam = 0x21,
    Key_QuoteDbl = 0x22,
    Key_NumberSign = 0x23,
    Key_Dollar = 0x24,
    Key_Percent = 0x25,
    Key_Ampersand = 0x26,
    Key_Apostrophe = 0x27,
    Key_ParenLeft = 0x28,
    Key_ParenRight = 0x29,
    Key_Asterisk = 0x2a,
    Key_Plus = 0x2b,
    Key_Comma = 0x2c,
    Key_Minus = 0x2d,
    Key_Period = 0x2e,
    Key_Slash = 0x2f,
    Key_0 = 0x30,
    Key_1 = 0x31,
    Key_2 = 0x32,
    Key_3 = 0x33,
    Key_4 = 0x34,
    Key_5 = 0x35,
    Key_6 = 0x36,
    Key_7 = 0x37,
    Key_8 = 0x38,
    Key_9 = 0x39,
    Key_Colon = 0x3a,
    Key_Semicolon = 0x3b,
    Key_Less = 0x3c,
    Key_Equal = 0x3d,
    Key_Greater = 0x3e,
    Key_Question = 0x3f,
    Key_At = 0x40,
    Key_A = 0x41,
    Key_B = 0x42,
    Key_C = 0x43,
    Key_D = 0x44,
    Key_E = 0x45,
    Key_F = 0x46,
    Key_G = 0x47,
    Key_H = 0x48,
    Key_I = 0x49,
    Key_J = 0x4a,
    Key_K = 0x4b,
    Key_L = 0x4c,
    Key_M = 0x4d,
    Key_N = 0x4e,
    Key_O = 0x4f,
    Key_P = 0x50,
    Key_Q = 0x51,
    Key_R = 0x52,
    Key_S = 0x53,
    Key_T = 0x54,
    Key_U = 0x55,
    Key_V = 0x56,
    Key_W = 0x57,
    Key_X = 0x58,
    Key_Y = 0x59,
    Key_Z = 0x5a,
    Key_BracketLeft = 0x5b,
    Key_Backslash = 0x5c,
    Key_BracketRight = 0x5d,
    Key_AsciiCircum = 0x5e,
    Key_Underscore = 0x5f,
    Key_QuoteLeft = 0x60,
    Key_a = 0x61,
    Key_b = 0x62,
    Key_c = 0x63,
    Key_d = 0x64,
    Key_e = 0x65,
    Key_f = 0x66,
    Key_g = 0x67,
    Key_h = 0x68,
    Key_i = 0x69,
    Key_j = 0x6a,
    Key_k = 0x6b,
    Key_l = 0x6c,
    Key_m = 0x6d,
    Key_n = 0x6e,
    Key_o = 0x6f,
    Key_p = 0x70,
    Key_q = 0x71,
    Key_r = 0x72,
    Key_s = 0x73,
    Key_t = 0x74,
    Key_u = 0x75,
    Key_v = 0x76,
    Key_w = 0x77,
    Key_x = 0x78,
    Key_y = 0x79,
    Key_z = 0x7a,
    Key_BraceLeft = 0x7b,
    Key_Bar = 0x7c,
    Key_BraceRight = 0x7d,
    Key_AsciiTilde = 0x7e,
  };
  inline bool isOperator(Key k)
  {
    return (((k>=Key_Exclam)&&(k<Key_0))
            ||(k>Key_9)&&(k<Key_A)
            ||(k>Key_Z)&&(k<Key_a)
            ||(k>Key_z)&&(k<=Key_AsciiTilde));

  }


  inline bool isAlpha(Key k)
  {
    return (((k>=Key_A)&&(k<=Key_Z))
            ||(k>=Key_a)&&(k<=Key_z));
  }

  inline bool isNumber(Key k)
  {
    return (((k>=Key_0)&&(k<=Key_9)));
  }

  inline char toText(Key k){
    switch (k) {
      case Key_Return:
        return '\n';
        break;
      case Key_Unknown: return  0x00;
      case Key_Space : return  0x20;                // 7 bit printable ASCII
      case Key_Exclam : return  0x21;
      case Key_QuoteDbl : return  0x22;
      case Key_NumberSign : return  0x23;
      case Key_Dollar : return  0x24;
      case Key_Percent : return  0x25;
      case Key_Ampersand : return  0x26;
      case Key_Apostrophe : return  0x27;
      case Key_ParenLeft : return  0x28;
      case Key_ParenRight : return  0x29;
      case Key_Asterisk : return  0x2a;
      case Key_Plus : return  0x2b;
      case Key_Comma : return  0x2c;
      case Key_Minus : return  0x2d;
      case Key_Period : return  0x2e;
      case Key_Slash : return  0x2f;
      case Key_0 : return  0x30;
      case Key_1 : return  0x31;
      case Key_2 : return  0x32;
      case Key_3 : return  0x33;
      case Key_4 : return  0x34;
      case Key_5 : return  0x35;
      case Key_6 : return  0x36;
      case Key_7 : return  0x37;
      case Key_8 : return  0x38;
      case Key_9 : return  0x39;
      case Key_Colon : return  0x3a;
      case Key_Semicolon : return  0x3b;
      case Key_Less : return  0x3c;
      case Key_Equal : return  0x3d;
      case Key_Greater : return  0x3e;
      case Key_Question : return  0x3f;
      case Key_At : return  0x40;
      case Key_A : return  0x41;
      case Key_B : return  0x42;
      case Key_C : return  0x43;
      case Key_D : return  0x44;
      case Key_E : return  0x45;
      case Key_F : return  0x46;
      case Key_G : return  0x47;
      case Key_H : return  0x48;
      case Key_I : return  0x49;
      case Key_J : return  0x4a;
      case Key_K : return  0x4b;
      case Key_L : return  0x4c;
      case Key_M : return  0x4d;
      case Key_N : return  0x4e;
      case Key_O : return  0x4f;
      case Key_P : return  0x50;
      case Key_Q : return  0x51;
      case Key_R : return  0x52;
      case Key_S : return  0x53;
      case Key_T : return  0x54;
      case Key_U : return  0x55;
      case Key_V : return  0x56;
      case Key_W : return  0x57;
      case Key_X : return  0x58;
      case Key_Y : return  0x59;
      case Key_Z : return  0x5a;
      case Key_BracketLeft : return  0x5b;
      case Key_Backslash : return  0x5c;
      case Key_BracketRight : return  0x5d;
      case Key_AsciiCircum : return  0x5e;
      case Key_Underscore : return  0x5f;
      case Key_QuoteLeft : return  0x60;
      case Key_a : return  0x61;
      case Key_b : return  0x62;
      case Key_c : return  0x63;
      case Key_d : return  0x64;
      case Key_e : return  0x65;
      case Key_f : return  0x66;
      case Key_g : return  0x67;
      case Key_h : return  0x68;
      case Key_i : return  0x69;
      case Key_j : return  0x6a;
      case Key_k : return  0x6b;
      case Key_l : return  0x6c;
      case Key_m : return  0x6d;
      case Key_n : return  0x6e;
      case Key_o : return  0x6f;
      case Key_p : return  0x70;
      case Key_q : return  0x71;
      case Key_r : return  0x72;
      case Key_s : return  0x73;
      case Key_t : return  0x74;
      case Key_u : return  0x75;
      case Key_v : return  0x76;
      case Key_w : return  0x77;
      case Key_x : return  0x78;
      case Key_y : return  0x79;
      case Key_z : return  0x7a;
      case Key_BraceLeft : return  0x7b;
      case Key_Bar : return  0x7c;
      case Key_BraceRight : return  0x7d;
      case Key_AsciiTilde : return  0x7e;

      default:
        return 0x00;
        break;
      }
  }




  class ABC_IO
  {
  public:


    /// put a string to the output source
    virtual void put(const std::string&)=0;
     void put(char c)
    {
      std::string s;
      s.push_back(c);
      put(s);
    }

    virtual void putError(const std::string& ) =0;

    virtual std::string getItemFromList(const std::string& title,
                                        const std::vector<std::string>& list,
                                        bool &ok,
                                        std::size_t current) =0;

    virtual std::string
    getItemFromSeveralLists(const std::string& title,
                            const std::map<std::string,std::vector<std::string> >& list,
                            bool &ok,
                            std::size_t current) =0;



    virtual void showMessage(const std::string& m)=0;

    virtual void move_cursor(int n)=0;

    virtual void erase_from_cursor(int n)=0;
    
    virtual void move_end()=0;
    virtual void move_home()=0;


  };


}
#endif // ABC_IO_H
