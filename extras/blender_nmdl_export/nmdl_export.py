bl_info = {
  "name": "NMDL Export",
  "version": (0, 0, 1),
  "location": "File > Export > NMDL Model",
  "description": "Nihonium Engine NMDL format (.nmdl)",
  "category": "Export"
}

import bpy

def write_file(filename):

  out = open(filename, "w")

  scene = bpy.data.scenes.active

  for obj in scene.objects:
    pass

  out.close()


Blender.Window.FileSelector(write_file, "Export")