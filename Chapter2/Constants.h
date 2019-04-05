#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace Constants {
  extern char const * const ApplicationName(void);
  extern std::string ResourcePath(const std::string &subDir);
  extern char const * const WindowTitle(void);
  extern int WindowPositionX(void);
  extern int WindowPositionY(void);
  extern int WindowWidth(void);
  extern int WindowHeight(void);
  extern int DefaultRendererWindow(void);
  extern int FramesPerSecond(void);
  extern int FrameWait(void);
};

#endif // CONSTANTS_H

