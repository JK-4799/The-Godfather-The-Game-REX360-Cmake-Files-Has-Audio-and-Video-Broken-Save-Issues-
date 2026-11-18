// godfather_recomp - ReXGlue Recompiled Project

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include <rex/app/title_app.h>

#include "generated/default/godfather_recomp_init.h"

class GodfatherRecompApp : public rex::app::TitleApp {
 public:
  GodfatherRecompApp() : TitleApp("godfather_recomp", kPPCImageConfig) {
    timeBeginPeriod(1);
  }
};

REX_TITLE_APP(GodfatherRecompApp)
