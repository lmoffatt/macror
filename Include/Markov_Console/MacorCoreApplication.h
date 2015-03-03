#ifndef MACORCOREAPPLICATION
#define MACORCOREAPPLICATION

#include "Markov_IO/ABC_Var.h"

#include <QCoreApplication>
#include <QKeyEvent>

#include <string>
#include <vector>



namespace  Markov_Console {

  class MacrorCoreApplication
  {
  public:

    MacrorCoreApplication(int &argc, char **argv);
    ~MacrorCoreApplication();

    static std::vector<std::string> arguments();

    static void setOrganizationName(const std::string &orgName);
    static std::string organizationName();
    static void setApplicationName(const std::string &application);
    static std::string applicationName();

    static void setApplicationVersion(const std::string &version);
    static std::string applicationVersion();

    static MacrorCoreApplication *instance() { return self; }

    static int exec();

    static void processEvents(QEventLoop::ProcessEventsFlags flags = QEventLoop::AllEvents);
    static void processEvents(QEventLoop::ProcessEventsFlags flags, int maxtime);
    static void exit(int retcode=0);

    static bool sendEvent(QObject *receiver, QEvent *event);
    static void postEvent(QObject *receiver, QEvent *event, int priority = Qt::NormalEventPriority);

    static void sendPostedEvents(QObject *receiver = 0, int event_type = 0);
    static void removePostedEvents(QObject *receiver, int eventType = 0);
    static QAbstractEventDispatcher *eventDispatcher();
    static void setEventDispatcher(QAbstractEventDispatcher *eventDispatcher);

    virtual bool notify(QObject *, QEvent *);

    static bool startingUp();
    static bool closingDown();

    static std::string applicationDirPath();
    static std::string applicationFilePath();
    static qint64 applicationPid();

    static void setLibraryPaths(const std::vector<std::string> &);
    static std::vector<std::string> libraryPaths();
    static void addLibraryPath(const std::string &);
    static void removeLibraryPath(const std::string &);



    void organizationNameChanged();
    void organizationDomainChanged();
    void applicationNameChanged();
    void applicationVersionChanged();

  protected:
    bool event(QEvent *);

    virtual bool compressEvent(QEvent *, QObject *receiver, QPostEventList *);




#endif // QT_NO_QOBJECT

    // Not present in QCoreApplication

    static std::string buildVersion()const;
    static std::string buildDate()const;
    static std::string uncommitedFiles()const;

    static std::string version()const;
    static std::string wellcomeMessage(unsigned ncols=80)const;



  protected:
    QCoreApplication(QCoreApplicationPrivate &p);


  private:
#ifndef QT_NO_QOBJECT
    static bool sendSpontaneousEvent(QObject *receiver, QEvent *event);
    bool notifyInternal(QObject *receiver, QEvent *event);
#endif

    void init();

    static MacrorCoreApplication *self;

  };

  class MacrorKeyEvent
  {
  public:
    enum Key {

//        Key_Escape = 0x01000000,                // misc keys
        Key_Tab = 0x01000001,
//        Key_Backtab = 0x01000002,
//        Key_Backspace = 0x01000003,
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
        Key_Any = Key_Space,
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

        Key_BraceLeft = 0x7b,
        Key_Bar = 0x7c,
        Key_BraceRight = 0x7d,
        Key_AsciiTilde = 0x7e,


    };
    explicit MacrorKeyEvent(Key key);



    MacrorKeyEvent(const MacrorKeyEvent &other);
    virtual ~MacrorKeyEvent();
    MacrorKeyEvent &operator=(const MacrorKeyEvent &other);
    inline Key key() const { return static_cast<Key>(k); }
//    inline bool spontaneous() const { return spont; }

//    inline void setAccepted(bool accepted) { m_accept = accepted; }
//    inline bool isAccepted() const { return m_accept; }

//    inline void accept() { m_accept = true; }
//    inline void ignore() { m_accept = false; }

  protected:
    ushort k;

  };






  class CommandManager: public Markov_IO::ABC_Data
  {
  public:
    CommandManager();
    virtual ~CommandManager();

    // self reference

    std::string buildVersion()const;
    std::string buildDate()const;
    std::string uncommitedFiles()const;

    virtual std::string version()const;
    virtual std::string wellcomeMessage(unsigned ncols=80)const;



    // command building interaction
    virtual std::vector<std::string> complete(const std::string& hint);

    virtual std::vector<std::string> complete(const std::string &hint,
                                              const std::string& category);



    //execuete line
    virtual bool runLine(std::string commandLine);



    virtual void printErrorMessage(const std::string& errorMessage);



    virtual std::string  getDir()const {return dir_;}
    virtual bool setDir(const std::string& dir);

    virtual Markov_IO::ABC_IO* getIO()const {return io_;}
    virtual void setIO(Markov_IO::ABC_IO* io){io_=io;}


    virtual bool Event(MacrorKeyEvent *k)

    {
//      if (message !=nullptr)  // message indicates a cue to the operator like a missing parameter
//        message->close();
//      if (textCursor().blockNumber()!=blockCount()-1)
//        moveCursor(QTextCursor::End);
//      QTextCursor c=textCursor();
//      auto p=c.position();

      switch(k->key())
        {
        case MacrorKeyEvent::Key_Home:
          {
            moveCursor(QTextCursor::StartOfBlock);
            moveCursor(QTextCursor::Right,QTextCursor::MoveAnchor);
            moveCursor(QTextCursor::Right,QTextCursor::MoveAnchor);
            break;
          }
        case MacrorKeyEvent::Key_Left:
          {
            if(textCursor().positionInBlock()>2)
              {
                moveCursor(QTextCursor::Left,QTextCursor::MoveAnchor);
                tail.prepend(cmdWord[0]);
                cmdWord.chop(1);

              }

          }
          break;
        case MacrorKeyEvent::Key_Backspace:
          {
            if(textCursor().positionInBlock()>2)
              {
                QPlainTextEdit::keyPressEvent(e);
                tail.clear();
                if (!cmdWord.isEmpty())
                  cmdWord.chop(1);
                else
                  cmdLine.chop(1);
              }

          }
          break;
        case MacrorKeyEvent::Key_Right:
          {
            moveCursor(QTextCursor::Right,QTextCursor::MoveAnchor);
            if (!tail.isEmpty())
              {
                cmdWord.append(tail[0]);
                tail.remove(0,1);
              }
          }
          break;
        case MacrorKeyEvent::Key_Up:
          {
            tail=cm_->getH().up((cmdLine+cmdWord).toStdString()).c_str();

            c.setPosition(p);
            c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
            c.removeSelectedText();
            c.insertText(tail);
            c.setPosition(p);
            setTextCursor(c);
          }
          break;

          //    case MacrorKeyEvent::Key_Right:
        case MacrorKeyEvent::Key_Down:
          {

            tail=cm_->getH().down((cmdLine+cmdWord).toStdString()).c_str();
            c.setPosition(p);
            c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
            c.removeSelectedText();
            c.insertText(tail);
            c.setPosition(p);
            setTextCursor(c);
          }
          break;

        case MacrorKeyEvent::Key_Tab:
          {
            c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
            c.removeSelectedText();
            setTextCursor(c);


            std::vector<std::string> res=
                cm_->complete(cmdWord.toStdString());

            if ((res.size()==1)&&(res.front()[0]!='<')&&(res.front()[0]!='['))
              {
                tail=
                    Markov_Console::Autocomplete::suggestedCharacters(
                      res,cmdWord.toStdString()).c_str();
                c.movePosition(QTextCursor::EndOfLine);
                c.insertText(tail);
                setTextCursor(c);
                cmdWord+=tail;
                tail.clear();

               }
            else if(res.size()>0)
              {
                if (previous_key==MacrorKeyEvent::Key_Tab)
                  {

                    tail=Markov_Console::Autocomplete::suggestedCharacters(res,cmdWord.toStdString()).c_str();
                    //auto pp=c.position();
                    c.insertText(tail);
                    setTextCursor(c);
                    cmdWord+=tail;
                    tail.clear();

                    QStringList list;
                    QString field;
                    for (auto item:res)
                      {
                        if ((item.front()=='<')||(item.front()=='['))
                          field=QString(item.substr(1,item.size()-2).c_str());
                        else
                          list<<QString(item.c_str());
                      }
                    if (list.size()>0)
                      {
                        bool ok;
                        QString fieldselect = Markov_GUI::MyInputDialog::getItem(this,cmdLine,list,&ok,0);
                        std::stringstream ss(fieldselect.toStdString());
                        Markov_Console::Token tok;
                        tok.get(ss);
                        ss.get();
                        if (ss)
                          {
                            fieldselect.prepend('"');
                            fieldselect.append('"');
                          }
                        if (ok && !fieldselect.isEmpty())
                          {
                            c.setPosition(c.position()-cmdWord.size(),QTextCursor::KeepAnchor);
                            c.removeSelectedText();
                            setTextCursor(c);
                            c.insertText(fieldselect);
                            setTextCursor(c);

                            cmdWord=fieldselect;
                          }
                      }
                    else
                      {
                        QString field;
                        for (std::size_t i=0;i<res.size()-1; i++)
                          {
                            if ((res[i].front()=='<')||(res[i].front()=='['))
                              field+=QString(res[i].c_str())+QString(",");

                          }
                        field+=res.back().c_str();
                        message=new QLabel(field,this);
                        message->setBuddy(this);
                        message->setFrameStyle(QFrame::Panel | QFrame::Sunken);
                        message->move(cursorRect().center().operator +=(QPoint(+10,-10)));

                        message->show();

                      }
                  }
              }

          }

          break;
        case MacrorKeyEvent::Key_PageUp:
        case MacrorKeyEvent::Key_PageDown:
          break;
        case MacrorKeyEvent::Key_Space:
          {
            QTextCursor c=textCursor();
            c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
            c.removeSelectedText();
            QString err=cm_->add_single_token(cmdWord.toStdString()).c_str();
            if (!err.toStdString().empty())
              {
                c.insertText("\n");
                setTextCursor(c);
                putError(err.toStdString());
                cmdWord.clear();
                c.insertText(">>"+cmdLine);
                setTextCursor(c);
              }
            else
              {
                cmdLine+=cmdWord+" ";
                c.insertText(" ");
                setTextCursor(c);
                cmdWord.clear();

              }
          }
          break;
        default:
          {
            QString s=e->text();
            if (s=="\r")
              {
                cmdLine+=cmdWord+tail;
                c.movePosition(QTextCursor::EndOfLine);

                c.insertText("\n");
                setTextCursor(c);

                commandLine(cmdLine);
                put(">>");
                cm_->clear_tokens();
                cmdLine.clear();
                cmdWord.clear();
                tail.clear();
                cm_->getH().reset();

              }
            else
              {
                cmdWord+=s;
                c.insertText(s);
                setTextCursor(c);

              }
          }

        }
      previous_key=e->key();
    }



    };




  class CommandWindow
  {

  };

}





#endif // MACORCOREAPPLICATION

