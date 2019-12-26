#include "runner_emscripten.h"

#ifdef __EMSCRIPTEN__

#include <emscripten.h>

namespace ImGui {
namespace ImGuiRunner {

RunnerEmscripten *gRunnerEmscripten = nullptr;

void emscripten_imgui_main_loop(void* arg)
{
  (void)arg;
  gRunnerEmscripten->LoopProc();
}

void RunnerEmscripten::Run()
{
  FullInit();
  gRunnerEmscripten = this;
  // This function call won't return, and will engage in an infinite loop, processing events from the browser, and dispatching them.

  //int fps = 0; // 0 <=> let the browser decide. This is the recommended way, see https://emscripten.org/docs/api_reference/emscripten.h.html#browser-execution-environment
  int fps = 120;
  emscripten_set_main_loop_arg(emscripten_imgui_main_loop, NULL, fps, true);

  SDL_GL_SetSwapInterval(1); // Enable vsync
}

void RunnerEmscripten::SetupImgGuiContext()
{
  AbstractRunner::SetupImgGuiContext();
  // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
  // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
  ImGui::GetIO().IniFilename = NULL;
}

void RunnerEmscripten::Select_Gl_Version()
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
}

std::string RunnerEmscripten::GlslVersion()
{
  //const char* glsl_version = "#version 100";
  const char* glsl_version = "#version 300 es";
  return glsl_version;
}

void RunnerEmscripten::InitGlLoader()
{
}



} // namespace ImGuiRunner
} // namespace ImGui

#endif // #ifdef __EMSCRIPTEN__
