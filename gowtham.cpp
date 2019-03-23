#include <iostream>
#include <string>

#if defined(__WIN32__)
  #include <windows.h>

  std::string getpassword()
    {
    std::string result;
    HANDLE      hstdin;
    DWORD       mode;
    BOOL        isconsole;

    hstdin    = GetStdHandle( STD_INPUT_HANDLE );
    isconsole = GetConsoleMode( hstdin, &mode );

    if (isconsole)
      SetConsoleMode( hstdin, mode & ~(ENABLE_ECHO_INPUT) );

    std::getline( std::cin, result );

    if (isconsole)
      SetConsoleMode( hstdin, mode );

    return result;
    }

#else
  #include <unistd.h>
  #include <termios.h>

  std::string getpassword()
    {
    std::string    result;
    struct termios echo;
    struct termios noecho;
    bool           isconsole;

    isconsole = isatty( 0 );

    if (isconsole)
      {
      tcgetattr( 0, &echo );
      noecho = echo;
      noecho.c_lflag &= ~(ECHO);
      tcsetattr( 0, TCSANOW, &noecho );
      }

    std::getline( std::cin, result );

    if (isconsole)
      tcsetattr( 0, TCSANOW, &echo );

    return result;
    }

#endif


int main()
  {
  using namespace std;
  string pwd;

  cout << "Please enter a (fake) password> " << flush;

  pwd = getpassword();

  cout << "\nGood job. Your password is \"" << pwd << "\"\n";

  return 0;
  }
