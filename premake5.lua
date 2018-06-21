workspace "nihonium"

  -- This puts the most likely platform first depending on the target.
  if _ACTION:sub(1, 2) == "vs" then
    platforms { "windows", "linux", "windows_editor", "linux_editor"}
  elseif _ACTION == "gmake" then
    platforms { "linux", "windows", "windows_editor", "linux_editor"}
  else
    platforms { "windows", "linux", "windows_editor", "linux_editor"}
  end

  configurations { "debug", "release" }

project "nihonium"

  kind "ConsoleApp"

  language "C++"

  targetdir "bin/%{cfg.buildcfg}"

  files {
    "external/hmm/HandmadeMath.c",
    "external/stb_image/stb_image.c",
    "external/duktape/duktape.c",
    "source/renderer/renderer_base.cpp",
    "source/filesystem/filesystem.cpp",
    "source/filesystem/mount_base.cpp",
    "source/filesystem/mount_nar.cpp",
    "source/filesystem/mount_directory.cpp",
    "source/model/model.cpp",
    "source/model/mesh_base.cpp",
    "source/shader/shader_base.cpp",
    "source/log/logger.cpp",
    "source/object/object.cpp",
    "source/object/binding_log.cpp",
    "source/object/binding_filesystem.cpp",
    "source/object/binding_model.cpp",
    "source/object/binding_shader.cpp",
    "source/object/binding_renderer.cpp",
    "source/object/world_single.cpp"
  }

  filter "configurations:debug"
    defines { "NH_DEBUG" }
    symbols "On"

  filter "configurations:release"
    optimize "On"

  filter "platforms:windows"
    links { "glfw", "opengl32" }
    defines { "NH_WINDOWS" }
    files {
      "external/glad/glad.c",
      "source/main/main_windows.cpp",
      "source/renderer/renderer_glfw_gl.cpp",
      "source/model/mesh_gl.cpp",
      "source/shader/shader_gl.cpp"
    }
    
  filter "platforms:linux"
    links { "glfw", "GL", "dl", "X11", "Xinerama", "Xrandr", "Xcursor", "pthread" }
    defines { "NH_LINUX" }
    files {
      "external/glad/glad.c",
      "source/main/main_linux.cpp",
      "source/renderer/renderer_glfw_gl.cpp",
      "source/model/mesh_gl.cpp",
      "source/shader/shader_gl.cpp"
    }

project "glfw"

    kind "StaticLib"
    language "C++"
    targetdir "bin/external/%{cfg.buildcfg}"

    includedirs { "include" }

    defines { "_CRT_SECURE_NO_WARNINGS" } -- For MSVC.

    files {
      "external/glfw/src/context.c",
      "external/glfw/src/init.c",
      "external/glfw/src/input.c",
      "external/glfw/src/monitor.c",
      "external/glfw/src/vulkan.c",
      "external/glfw/src/window.c"
    }

    filter "platforms:windows or windows_editor"
      defines { "_GLFW_WIN32" }
      files {
        "external/glfw/src/win32_init.c",
        "external/glfw/src/win32_joystick.c",
        "external/glfw/src/win32_monitor.c",
        "external/glfw/src/win32_time.c",
        "external/glfw/src/win32_tls.c",
        "external/glfw/src/win32_window.c",
        "external/glfw/src/wgl_context.c",
        "external/glfw/src/egl_context.c"
      }


    filter "platforms:linux or linux_editor"
      links { "GL", "dl", "X11", "Xinerama", "Xrandr", "Xcursor", "pthread" }
      defines { "_GLFW_X11" }
      files {
        "external/glfw/src/x11_init.c",
        "external/glfw/src/x11_monitor.c",
        "external/glfw/src/x11_window.c",
        "external/glfw/src/xkb_unicode.c",
        "external/glfw/src/linux_joystick.c",
        "external/glfw/src/posix_time.c",
        "external/glfw/src/posix_tls.c",
        "external/glfw/src/glx_context.c",
        "external/glfw/src/egl_context.c",
      }
