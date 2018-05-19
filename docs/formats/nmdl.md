# NMDL Format Specification

**This version:** 1

## Introduction

The NMDL (**N**ihonium **M**o**d**e**l**) format is a file format used for storing 3D models for the Nihonium Game Engine.  
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

|Field                |Size                              |Description                                                   |
|---------------------|----------------------------------|--------------------------------------------------------------|
|Metadata             |4 bytes                           |Currently not used, but will be in the future. Set to all 0s. |
|Mesh Name Length     |4 bytes                           |The length of the name of the mesh, in bytes.                 |
|Material Name Length |4 bytes                           |The length of the name of the default material, in bytes.     |
|Number of Positions  |4 bytes                           |The number of positions in the mesh.                          |
|Number of Normals    |4 bytes                           |The number of normals in the mesh.                            |
|Number of UVs        |4 bytes                           |The number of UVs in the mesh.                                |
|Number of Faces      |4 bytes                           |The number of faces in the mesh.                              |
|Mesh Name            |Mesh Name Length bytes            |The name of the mesh.                                         |
|Material Name        |Material Name Length bytes        |The name of the default material to use.                      |
|Positions            |Number of Positions * 3 * 4 bytes |A list of positions in floating-point format, ordered as XYZ. |
|Normals              |Number of Normals * 3 * 4 bytes   |A list of normals in floating-point format, ordered as XYZ.   |
|UVs                  |Number of UVs * 2 * 4 bytes       |A list of UVs in floating-point format, ordered as XY.        |
|Faces                |Number of Faces * 3 * 2 bytes     |A list of all faces in the mesh (See Face Index Order below). |

## Face Index Order

The 9 indices in each face are in the following order. Each is represented as a 2 byte integer.

1. Vertex 1 Position
2. Vertex 1 Normal
3. Vertex 1 UV
4. Vertex 2 Position
5. Vertex 2 Normal
6. Vertex 2 UV
7. Vertex 3 Position
8. Vertex 3 Normal
9. Vertex 3 UV
