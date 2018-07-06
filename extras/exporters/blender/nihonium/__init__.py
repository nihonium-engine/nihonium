# TODO: PEP-8 compliance.

bl_info = {
    "name": "Nihonium NMDL format",
    "author": "IDid",
    "version": (0, 0, 2),
    "blender": (2, 79, 0),
    "location": "File > Import-Export",
    "description": "Export NMDL",
    "wiki_url": "https://github.com/IDidMakeThat/nihonium/tree/master/extras/"
                "exporters/blender",
    "tracker_url": "", # TODO: Link to issues.
    "category": "Import-Export"
}

import importlib

import bpy
from bpy.props import (
    BoolProperty,
    FloatProperty,
    StringProperty,
    EnumProperty
)
from bpy_extras.io_utils import ExportHelper

from . import export_nmdl
importlib.reload(export_nmdl) # For development purposes.


class ExportNMDL(bpy.types.Operator, ExportHelper):

    bl_idname = "export_mesh.nmdl"
    bl_label = "Export NMDL"
    bl_options = {"PRESET"}

    filename_ext = ".nmdl"

    filter_glob = StringProperty(
        default = "*.nmdl;*.nmtl",
        options = {"HIDDEN"}
    )

    selection_only = BoolProperty(
        name = "Selection Only",
        description = "Export selected objects only",
        default = False
    )

    use_mesh_modifiers = BoolProperty(
        name = "Apply Modifiers",
        description = "Apply modifiers",
        default = True
    )

    use_mesh_modifiers_render = BoolProperty(
        name = "Use Modifiers' Render Settings",
        description = "Use render settings when applying modifiers to mesh objects",
        default = False
    )

    write_materials = BoolProperty(
        name = "Write Materials",
        description = "Write out the NMTL file",
        default = True
    )

    def execute(self, context):
        from . import export_nmdl

        export_nmdl.write(context, self.filepath, self.write_materials, self.use_mesh_modifiers, self.use_mesh_modifiers_render, self.selection_only)

        return {"FINISHED"}

def menu_func_export(self, context):
    self.layout.operator(ExportNMDL.bl_idname, text = "Nihonium NMDL (.nmdl)")

classes = {
    ExportNMDL
}

def register():
    for v in classes:
        bpy.utils.register_class(v)

    bpy.types.INFO_MT_file_export.append(menu_func_export)

def unregister():
    bpy.types.INFO_MT_file_export.remove(menu_func_export)

    for v in classes:
        bpy.utils.unregister_class(v)

if __name__ == "__main__":
    register()
