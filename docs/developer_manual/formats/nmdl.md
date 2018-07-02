# NMDL Format Specification

**This version:** 1

## Introduction

The NMDL (**N**ihonium **M**o**d**e**l**) format is a file format used for storing 3D models for the Nihonium Game Engine.  
NMDL files should have the '.nmdl' file extension.

**Note:** All multi-byte values are in little endian format.

## Basic Structure

Each model consists of a series of meshes. Each mesh consists of a name and list of positions, normals and UVs, as well as a list of faces.
Each face consists of 3 sets of indices into the vertex array, one for each vertex.

|Field           |Size    |Description                                                                              |
|----------------|--------|-----------------------------------------------------------------------------------------|
|Magic           |4 bytes |Magic string used to identify an NMDL file. Always "NMDL" in ASCII (0x4E 0x4D 0x44 0x4C).|
|Version         |4 bytes |Used to identify the version. For this version, it should be 0x00000001.                 |
|Number of Meshes|4 bytes |The number of meshes in the model.                                                       |
|Meshes          |Variable|A series of meshes (see Mesh Format below).                                              |

## Mesh Format

|Field                       |Size                              |Description                                                                          |
|----------------------------|----------------------------------|-------------------------------------------------------------------------------------|
|Name Length                 |4 bytes                           |The length of name of the mesh.                                                      |
|Name                        |Name Length bytes                 |The name of the mesh.                                                                |
|Default Material Path Length|4 bytes                           |The length of the path of the default material.                                      |
|Default Material Path       |Default Material Path Length bytes|The path of the default material.                                                    |
|Metadata                    |4 bytes                           |Currently not used, but will be in the future. Each byte should have a value of 0x00.|
|Number of Vertices          |4 bytes                           |The number of vertices in the mesh.                                                  |
|Number of Faces             |4 bytes                           |The number of faces in the mesh.                                                     |
|Positions                   |Number of Vertices * 3 * 4 bytes  |A list of positions in floating-point format, ordered as XYZ.                        |
|Normals                     |Number of Vertices * 3 * 4 bytes  |A list of normals in floating-point format, ordered as XYZ.                          |
|UVs                         |Number of Vertices * 2 * 4 bytes  |A list of UVs in floating-point format, ordered as XY.                               |
|Faces                       |Number of Faces * 3 * 2 bytes     |A list of faces in the mesh, each containing 3 indices.                              |
