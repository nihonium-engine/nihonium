import bpy
import json
from struct import pack

def mesh_triangulate(this):
    import bmesh
    bm = bmesh.new()
    bm.from_mesh(this)
    bmesh.ops.triangulate(bm, faces=bm.faces)
    bm.to_mesh(this)
    bm.free()

def make_material_parameter_single(name, value):
    return {
        "name": name,
        "type": "single",
        "value": value
    }

def make_material_parameter_map(name, path):
    return {
        "name": name,
        "type": "map",
        "components": 4,
        "path": path
    }

# TODO: This function is not yet complete.
def write_material(material):

    material_path = material_name_to_path(material.name)

    # TODO: Possibly support non-node materials.
    if material.use_nodes:

        nodes = material.node_tree.nodes

        principled_shader = nodes.get("Principled BSDF")

        if principled_shader:
            base_color = principled_shader.inputs["Base Color"]
            if len(base_color.links) == 0 \
                or base_color.links[0].from_node.name != "Image Texture" \
                or not base_color.links[0].from_node.image:

                albedo = make_material_parameter_single(
                    "albedo",
                    [
                        base_color.default_value[0],
                        base_color.default_value[1],
                        base_color.default_value[2],
                        base_color.default_value[3]
                    ]
                )
            else:
                pass

        else:
            albedo = make_material_parameter_single("albedo", [1, 0, 1, 1])
            normal = make_material_parameter_single("normal", [0, 1, 0])
            roughness = make_material_parameter_single("roughness", [0])
            metallic = make_material_parameter_single("metallic", [0])
            ao = make_material_parameter_single("ao", [0])

    else:
        pass
    

    json_material = {
        "vertex_shader": "nh:shaders/pbr_vert.vert",
        "fragment_shader": "nh:shaders/pbr_frag.frag",
        "parameters": [
            albedo,
            normal,
            roughness,
            metallic,
            ao
        ]
    }

    return json_material
"""
This function takes the name of a material and creates a file name
based on it.
"""
def material_name_to_path(name):
    return "mat_%s.json" % name

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
        f.write(pack("<L", 0)) # Number of meshes (placeholder)

        num_meshes = 0

        for v in objects:
            if apply_modifiers or v.type != "MESH":
                try:
                    mesh = v.to_mesh(
                        context.scene,
                        True,
                        "RENDER" if use_render_modifiers else "PREVIEW"
                    )
                    is_temp_mesh = True
                except:
                    mesh = None
            else:
                mesh = v.data
                if not obj.tessfaces and obj.polygons:
                    obj.calc_tessface()
                is_temp_mesh = False

            if mesh:
                num_meshes += 1

                mesh_triangulate(mesh)

                material = None
                if len(mesh.materials) > 0:
                    material = mesh.materials[0]

                material_name = material_name_to_path(material.name) if material else ""

                vertices = []
                indices = []

                for poly in mesh.polygons:

                    for i in poly.loop_indices:
                        l = mesh.loops[i]
                        if not mesh.uv_layers.active:
                            uv_x = 0
                            uv_y = 0
                        else:
                            uv_x = mesh.uv_layers.active.data[l.index].uv[0]
                            uv_y = mesh.uv_layers.active.data[l.index].uv[1]

                        vertex = (
                            mesh.vertices[l.vertex_index].co[0],
                            mesh.vertices[l.vertex_index].co[2],
                            mesh.vertices[l.vertex_index].co[1],
    
                            mesh.vertices[l.vertex_index].normal[0],
                            mesh.vertices[l.vertex_index].normal[2],
                            mesh.vertices[l.vertex_index].normal[1],
    
                            uv_x,
                            uv_y
                        )

                        try:
                            indices.append(vertices.index(vertex))
                        except:
                            vertices.append(vertex)
                            indices.append(len(vertices) - 1)

                # Metadata
                f.write(pack("<L", 0))

                # Name length
                f.write(pack("<L", len(v.name.encode("utf-8"))))

                # Default material path length
                f.write(pack("<L", len(material_name.encode("utf-8"))))

                # Number of vertices
                f.write(pack("<L", len(vertices)))

                print(len(indices))

                # Number of faces
                f.write(pack("<L", len(indices) // 3))

                # Name
                f.write(v.name.encode("utf-8"))

                # Default material path
                f.write(material_name.encode("utf-8"))

                # Vertices
                for vertex in vertices:
                    for i in range(0, 8):
                        f.write(pack("f", vertex[i]))

                # Indices
                for index in indices:
                    f.write(pack("<H", index))

        f.seek(8)
        f.write(pack("<L", num_meshes))
