import bpy
from struct import pack

def mesh_triangulate(this):
    import bmesh
    bm = bmesh.new()
    bm.from_mesh(this)
    bmesh.ops.triangulate(bm, faces=bm.faces)
    bm.to_mesh(this)
    bm.free()

def write(context,
          file_name,
          export_material=True,
          apply_modifiers=True,
          use_render_modifiers=False,
          selected_only=False):

    if selected_only:
        objects = context.selected_objects
    else:
        objects = context.scene.objects

    if bpy.ops.object.mode_set.poll():
        bpy.ops.object.mode_set(mode="OBJECT")

    with open(file_name, "wb") as f:

        # Write header.
        f.write(bytes([0x4E, 0x4D, 0x44, 0x4C])) # Magic
        f.write(pack("<L", 0x00000001)) # Version
        f.write(pack("<L", len(objects))) # Number of meshes

        for v in objects:
            if apply_modifiers or v.type != "MESH":
                try:
                    obj = v.to_mesh(
                        context.scene,
                        True,
                        "RENDER" if use_render_modifiers else "PREVIEW"
                    )
                    is_temp_mesh = True
                except:
                    obj = None
            else:
                obj = v.data
                if not obj.tessfaces and obj.polygons:
                    obj.calc_tessface()
                is_temp_mesh = False

            if obj is not None:
                mesh_triangulate(obj)
                f.write(pack("<L", 0))
                f.write(pack("<L", len(obj.vertices)))
                f.write(pack("<L", len(obj.polygons)))
 
                for vertex in obj.vertices:
                    for i in [0, 2, 1]: # Make sure to swap Y and Z axes.
                        f.write(pack("f", vertex.co[i]))
                    for i in range(0, 3):
                        f.write(pack("f", vertex.normal[i]))
                    for i in range(0, 2):
                        f.write(pack("f", 0))

                for poly in obj.polygons:
                    for i in range(0, 3):
                        f.write(pack("<H", poly.vertices[i]))
