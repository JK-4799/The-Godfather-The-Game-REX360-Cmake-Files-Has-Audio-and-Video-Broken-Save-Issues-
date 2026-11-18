// godfather_recomp - ReXGlue Recompiled Project

#include <filesystem>
#include "generated/default/godfather_recomp_funcs.h"

REX_HOOK_RAW(sub_825712C8) {
  ctx.r3.s64 = 0;
}

REX_HOOK_RAW(sub_82571D40) {
  ctx.r3.s64 = 0;
}

// Bypass SaveManager STFS header/handle error (return 0 = valid) if save payload exists on disk
REX_HOOK_RAW(sub_82A6D090) {
  namespace fs = std::filesystem;
  std::error_code ec;
  fs::path savePath = fs::path("user") / "B13EBABEBABEBABE" / "454107E9" / "00000001" / "The Godfather" / "The Godfather";
  if (fs::exists(savePath, ec) && fs::file_size(savePath, ec) > 0) {
    ctx.r3.s64 = 0;
  } else {
    ctx.r3.s64 = 2;
  }
}
