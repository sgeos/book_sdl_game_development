#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace Constants {
  extern const char * const ApplicationName(void);
  extern std::string ResourcePath(const std::string &subDir);
  extern const char * const WindowTitle(void);
  extern int WindowPositionX(void);
  extern int WindowPositionY(void);
  extern int WindowWidth(void);
  extern int WindowHeight(void);
  extern int DefaultRendererWindow(void);
  extern int FramesPerSecond(void);
  extern int FrameWait(void);
  extern int AnimationFrames(void);
};

#endif // CONSTANTS_H

