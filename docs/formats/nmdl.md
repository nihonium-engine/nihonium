# NMDL Format Specification

**This version:** 1

## Introduction

The NMDL (*N*ihonium *M*o*d*e*l*) format is a file format used for storing 3D models for the Nihonium Game Engine.  
NMDL files should have the '.nmdl' file extension.

**Note:** All multi-byte values are in little endian format.

## Basic Structure

Each model consists of a series of meshes. Each mesh consists of a name and list of positions, normals and 5 sets of UVs, as well as a list of faces.
Each face consists of 7 sets of indices into the lists of positions, normals and UVs, respectively for each vertex.
All faces are triangles.

|Field           |Size    |Description                                                                              |
|----------------|--------|-----------------------------------------------------------------------------------------|
|Magic           |4 bytes |Magic string used to identify an NMDL file. Always "NMDL" in ASCII (0x4E 0x4D 0x44 0x4C).|
|Version         |4 bytes |Used to identify the version. For this version, it should be 0x00000001.                 |
|Number of Meshes|4 bytes |The number of meshes in the model.                                                       |
|Meshes          |Variable|A series of meshes (see Mesh Format below).                                              |

## Mesh Format
|Field                  |Size                                 |Description                                                     |
|-----------------------|-------------------------------------|----------------------------------------------------------------|
|Mesh Name Length       |4 bytes                              |The length of the name of the mesh, in bytes.                   |
|Number of Vertices     |4 bytes                              |The number of vertices in the mesh.                             |
|Number of Normals      |4 bytes                              |The number of normals in the mesh.                              |
|Number of Albedo UVs   |4 bytes                              |The number of albedo UVs in the mesh.                           |
|Number of Normal UVs   |4 bytes                              |The number of normal UVs in the mesh.                           |
|Number of Metallic UVs |4 bytes                              |The number of metallic UVs in the mesh.                         |
|Number of Roughness UVs|4 bytes                              |The number of roughness UVs in the mesh.                        |
|Number of AO UVs       |4 bytes                              |The number of AO UVs in the mesh.                               |
|Number of Faces        |4 bytes                              |The number of faces in the mesh.                                |
|Mesh Name              |Variable                             |The name of the mesh.                                           |
|Vertices               |Number of Vertices * 3 * 4 bytes     |A list of vertices in floating-point format, ordered as XYZ.    |
|Normals                |Number of Normals * 3 * 4 bytes      |A list of normals in floating-point format, ordered as XYZ.     |
|Albedo UVs             |Number of Albedo UVs * 2 * 4 bytes   |A list of albedo UVs in floating-point format, ordered as XY.   |
|Normal UVs             |Number of Normal UVs * 2 * 4 bytes   |A list of normal UVs in floating-point format, ordered as XY.   |
|Metallic UVs           |Number of Metallic UVs * 2 * 4 bytes |A list of metallic UVs in floating-point format, ordered as XY. |
|Roughness UVs          |Number of Roughness UVs * 2 * 4 bytes|A list of roughness UVs in floating-point format, ordered as XY.|
|AO UVs                 |Number of AO UVs * 2 * 4 bytes       |A list of AO UVs in floating-point format, ordered as XY.       |
|Faces                  |Number of Faces * 7 * 4 * 3 bytes    |A list of all faces in the mesh (See Face Index Order below).   |

# Face Index Order

The 21 sets of indices in each face are in the following order. Each is represented as a 4 byte integer.

1.  Vertex 1 Position
2.  Vertex 1 Normal
3.  Vertex 1 Albedo UV
4.  Vertex 1 Normal UV
5.  Vertex 1 Metallic UV
6.  Vertex 1 Roughness UV
7.  Vertex 1 AO UV
8.  Vertex 2 Position
9.  Vertex 2 Normal
10. Vertex 2 Albedo UV
11. Vertex 2 Normal UV
12. Vertex 2 Metallic UV
13. Vertex 2 Roughness UV
14. Vertex 2 AO UV
15. Vertex 3 Position
16. Vertex 3 Normal
17. Vertex 3 Albedo UV
18. Vertex 3 Normal UV
19. Vertex 3 Metallic UV
20. Vertex 3 Roughness UV
21. Vertex 3 AO UV