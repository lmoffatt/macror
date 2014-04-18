#include <unistd.h>
#include <termios.h>
#include "Macror_Console/KeyEvent.h"



namespace Macror_Console {


  bool KeyEvent::check()
  {
    struct termios oldt;
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt); /*store old settings */
    newt = oldt; /* copy old settings to new settings */
    newt.c_lflag &= ~(ICANON | ECHO); /* make one change to old settings in new settings */
    newt.c_cc[VMIN] = 0;
    newt.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); /*apply the new settings immediatly */
    auto res=read(STDIN_FILENO, &buf, buffMax);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); /*reapply the old settings */
    return res>0;
  }

  KeyEvent::Key KeyEvent::getKey() const
  {
    if (((buf[0]>'A')&&(buf[0]<='Z'))||((buf[0]>'a')&&(buf[0]<='b')))
      return Key_Aphabetic;
    else if ((buf[0]>'0')&&(buf[0]<='9'))
      return Key_Numeric;
    else if (getChar()=="\t")
      return Key_Tab;
    else if (getChar()==" ")
      return Key_Space;
    else if ((getChar()=="\n")||(getChar()=="\r\n"))
      return Key_Return;
    else if ((buf[0]=='\177')|(buf[0]=='\b'))
      return Key_Backspace;
    else if ((getChar()=="\033[A")||((buf[0]==-32)&&(buf[1]=='H')))
      return Key_Up;
    else if ((getChar()=="\033[B")||((buf[0]==-32)&&(buf[1]=='P')))
      return Key_Down;
    else if ((getChar()=="\033[C")||((buf[0]==-32)&&(buf[1]=='M')))
      return Key_Right;
    else if ((getChar()=="\033[D")||((buf[0]==-32)&&(buf[1]=='K')))
      return Key_Left;
    else
      return Key_Other;
   }

  std::string KeyEvent::getChar()const
  {
    return buf;
  }



}
