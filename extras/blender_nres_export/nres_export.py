bl_info = {
  "name": "NRES Export"
  "category": "Export"
}

import Blender
import bpy

def write_file(filename):

  out = open(filename, "w")

  scene = bpy.data.scenes.active

  for obj in scene.objects:
    pass

  out.close()


Blender.Window.FileSelector(write_file, "Export")